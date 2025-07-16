#include"EventLoop.h"
#include<sys/eventfd.h>
#include"Logger.h"
#include<unistd.h>
#include<fcntl.h>
#include<error.h>
#include"Poller.h"
#include"Channel.h"
#include<memory>
//防止一个线程创建多个Eventoop
//__thread  每个线程有一个独立的 t_loopInThisThread 变量副本，互不干扰。
//初始值是 nullptr，表示当前线程还没有创建 EventLoop。
__thread  EventLoop*t_loopInThisThread=nullptr;


//定义默认的poller  IO复用接口的超时时间
const   int   KPollTimeMs=10000;

//创建wakeupfd，用来唤醒subReactor处理新来的channel
/*
eventfd 创建的文件描述符维护了一个 64 位的无符号计数器。
write(fd, &val, 8)：将 val 累加到内部计数器中（最大为 UINT64_MAX）。
read(fd, &val, 8)：从计数器中取出当前值，并将计数器置为 0。
支持被 epoll 等 I/O 多路复用机制监听！
eventfd 主要用于在多线程/多进程之间进行事件通知或唤醒机制
它比传统的 pipe 更轻量、高效，常用于 Reactor 模型中线程的唤醒。
*/
int   createEventfd()
{
    int evtfd=::eventfd(0,EFD_NONBLOCK|EFD_CLOEXEC);
    if(evtfd<0)
    {
        LOG_FATAL("eventfd  error:%d\n",errno);
    }
    return evtfd;
}

    EventLoop::EventLoop()
    :looping_(false),
    quit_(false),
    callingPendingFunctors_(false),
    threadID_(CurrentThread::tid()),
    poller_(Poller::newDefaultPoller(this)),
    wakeupFD_(createEventfd()),
    wakeupChannel_(new   Channel(this,wakeupFD_))
    //currentActiveChannel_(nullptr)
    {
        LOG_DEBUG("Eventloop  created  %p  in  thread%d\n",this,threadID_);
        if(t_loopInThisThread)
        {
            LOG_FATAL("Another   EventLoop %p  exists  in   this  thread%d \n",t_loopInThisThread,threadID_);
        }
        else
        {
            t_loopInThisThread=this;
        }
        //设置wakeupfd的事件类型以及发生事件后的回调操作
        //为 wakeupChannel_ 设置一个读事件回调函数，当该 Channel 上的文件描述符
        //（wakeupFd_，通常是 eventfd）变为可读时，就会自动调用 EventLoop::handleRead() 函数。
        wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead,this));
        //std::bind(&EventLoop::handleRead, this) 的作用是：
        //把类成员函数和对象绑定在一起，生成一个无参的可调用对象，用于之后调用时自动执行 this->handleRead()。
        

        //每一个Eventloop都将监听wakeupchannel的读事件,添加到epoll
        wakeupChannel_->enableReading();
    }
    EventLoop::~EventLoop()
    {
        wakeupChannel_->disableAll();
        wakeupChannel_->remove();
        ::close(wakeupFD_);
        t_loopInThisThread=nullptr;
    }
    

    /*
    核心机制是利用 eventfd 实现 线程间通知 或 自唤醒机制
    eventfd 是 64 位的，所以读写都用 uint64_t 类型。
    wakeupFD_ 是一个 eventfd 文件描述符，用于“事件循环的唤醒”。
    此处调用 read()，从 eventfd 中读出一个值（我们写进去过 1）。
    这一步的目的 不是获取数据，而是 清除可读事件（EPOLLIN），避免 epoll 无限触发读事件。
    */
    void  EventLoop::handleRead()//唤醒
    {
        uint64_t  one =1;
        ssize_t  n=read(wakeupFD_,&one,sizeof  one);
        if(n!=sizeof  one)
        {
            LOG_ERROR("EventLoop::headleRead() reads  %zd  bytes  instead  of 8",n);
        }
    }
    //开启事件循环
    void   EventLoop::loop()
    {
        looping_=true;
        quit_=false;
        LOG_INFO("Eventloop %p start looping\n",this);
        while(!quit_)
        {
            activeChannels_.clear();
            //监听两类fd 一类是client的fd，一种是wakeupfd
            pollReturnTime_=poller_->poll(KPollTimeMs,&activeChannels_);
            for(Channel *channel:activeChannels_)//实际发生事件的channel
            {
                //Poller监听哪些channel发生事件了，上报给Eventloop,通知channel处理相应地事件
                channel->handleEvent(pollReturnTime_);
            }
            //执行当前EventLoop事件循环需要处理的回调操作
            /** 
             * IO线程 mainLoop  accept fd(channel打包fd)   mainloop只做新用户连接 唤醒subloop
             * mainloop事先注册一个回调cb(需要subloop来执行)    mainloop  通过wakeup唤醒subloop,
             * 然后执行下面的方法(mainloop注册的cb)
            */
            doPendingFunctors();
            
        }
        LOG_INFO("Eventloop %p stop   looping\n",this);
        looping_=false;
    }


    //退出事件循环
    /**
     * 一种是loop在自己的线程中调用quit;
     * 二：比如在subloop中，调用了mainloop的quit（在非loop线程中，调用loop的quit）
     */
    void EventLoop::quit()
    {
        quit_=true;
        if(!isInLoopThread())//：比如在subloop(worker)中，调用了mainloop的quit
        {
            wakeup();
        }
    }
     void  EventLoop::runInLoop(Functor  cb)//在当前loop中执行cb
     {
        if(isInLoopThread())//在当前的loop线程中，执行cb
        {
            cb();
        }
        else//在非当前的loop线程中，执行cb,需要唤醒loop所在线程，执行cb,“唤醒”只是打断 poll() 的阻塞，让 EventLoop 所在线程继续往下执行,最终自己执行任务
        {
                queueInLoop(cb);
        }
     }
    void  EventLoop::queueInLoop(Functor  cb)
    //把cb放到队列中，唤醒loop所在的线程，执行cb
    {
        {
            std::unique_lock<std::mutex>lock(mutex_);//构造时加锁，作用域结束时自动释放
            pendingFunctors_.emplace_back(cb);//直接构造
        }
        //唤醒相应的，需要执行上面回调操作的loop的线程了
        if(!isInLoopThread()||callingPendingFunctors_)//callingPendingFunctors_为true表示正在执行回调，
        //但是loop又有了新的回调，这个时候需要让 poll() 立即返回（唤醒）
        //进入下一轮事件循环，重新执行 doPendingFunctors()，从而尽快执行刚刚加入的 newFunc()。
        {
            wakeup();
        }
    }
     void  EventLoop::wakeup()//用来唤醒loop所在的线程(向wakeupfd写一个数据,
      //wakeupchannel就会发生读时间，当前loop线程就会被唤醒
    
     {
            uint64_t    one=1;
            ssize_t n=write(wakeupFD_,&one,sizeof one);
            if(n!=sizeof one)
            {
                LOG_ERROR("Evenyloop::wakeup()writes%lu  bytes   instead of 8\n",n);
            }
         }

    //Eventloop方法-》poller方法
    void    EventLoop::updateChannel(Channel*channel)//本质是channel通过eventloop调用poller
    {
        poller_->updateChannel(channel);
    }
    void    EventLoop::removeChannel(Channel*channel)
    {
        poller_->removeChannel(channel);
    }
    bool  EventLoop::hasChannel(Channel*channel)
    {
        return  poller_->hasChannel(channel);
    }
    void  EventLoop::doPendingFunctors()//执行回调
    {
        std::vector<Functor>functors;//局部变量
        callingPendingFunctors_=true;
        {
            std::unique_lock<std::mutex>lock(mutex_);
            functors.swap(pendingFunctors_);
        }

        for(const  Functor&functor:functors)
        {
            functor();//执行当前loop需要执行的回调函数
        }
        callingPendingFunctors_=false;
    }