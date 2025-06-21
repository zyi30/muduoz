#include"EventLoopThread.h"
#include"EventLoop.h"

 EventLoopThread::EventLoopThread(const ThreadInitCallback  &cb=ThreadInitCallback(),
    const   std::string&name= std::string()):
    loop_(nullptr),
    exiting_(false),
    thread_(std::bind(&EventLoopThread::threadFunc,this),name),
    mutex_(),
    cond_(),
    callback_(cb)
    {

    }
    
    EventLoopThread::~EventLoopThread()
    {
            exiting_=true;
            if(loop_!=nullptr)
            {
                loop_->quit();
                thread_.join();
            } 
    }

    EventLoop*EventLoopThread::startLoop()
    //这个函数是主线程（调用者线程）调用的，用来启动一个新线程，
    //并且等待新线程中 EventLoop 对象创建完成后返回它的地址。
    {
        thread_.start();//启动底层的新线程，执行的是EventLoopThread::threadFunc

        EventLoop *loop=nullptr;
        {
            std::unique_lock<std::mutex>lock(mutex_);
            while(loop_==nullptr)
            {
                cond_.wait(lock);
            }
            loop=loop_;
        }
        return loop;
    }

        //这个方法是在单独得新线程里面运行的
    void   EventLoopThread::threadFunc()
    {
        EventLoop loop;//创建一个独立的Eventloop,和上面得线程是一一对应了，one loop  per   thread
        if(callback_)
        {
            callback_(&loop);
        }
        {
            std::unique_lock<std::mutex>lock(mutex_);
            loop_=&loop;
            cond_.notify_one();
        }
        loop.loop();     //EventLoop  loop=>Poller->poll
        std::unique_lock<std::mutex>lock(mutex_);
            loop_=nullptr;

    }

    