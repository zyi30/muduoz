#include"Channel.h"
#include"Logger.h"
#include<sys/epoll.h>
#include"EventLoop.h"
 const   int  Channel::KNoneEvent=0;//用于表示该 Channel 的 fd 没有注册到 epoll 中，或者已经被移除了。
 const   int  Channel::KReadEvent=EPOLLIN|EPOLLPRI;//..需要监听“读”相关事件
const   int  Channel::KWriteEvent=EPOLLOUT;//需要监听“写”事件。

 Channel::Channel(EventLoop *loop,int fd):loop_(loop),fd_(fd),events_(0),revents_(0),index_(-1),tied_(false)
 {  
 }
 Channel::~Channel()
 {
 }
 /**
  * std::weak_ptr 本身就是通过一个 shared_ptr 来构造的——它不拥有对象，只是观察它是否还活着。
把 shared_ptr<void> 给 weak_ptr<void> 是为了：
不延长对象生命周期（不像 shared_ptr 会增加引用计数）；
后续可以通过 lock() 判断这个对象是否还存活；
用 weak_ptr 来避免循环引用、悬空指针。
  */
 //channel的tie方法什么时候调用过
 void  Channel::tie(const  std::shared_ptr<void>&obj)
 {
    tie_=obj;
    tied_=true;
 }

 //当改变channel所表示的fd的events事件后，update负责在poller里面更改fd相对应的事件epoll_ctl;
void   Channel::update()
{
//通过Channel所属的Eventloop,调用poller的相应方法，注册fd的events相应事件
//add  code...
loop_->updateChannel(this);
}
//在channel所属的Eventloop中，把当前的channel删除掉
void   Channel::remove()
{
    //add code...
  loop_->removeChannel(this);
}

 void   Channel::handleEvent(Timestamp  receiveTime)//fd得到poller通知以后，处理事件的函数
{
    if(tied_)//表示这个 Channel 是否绑定了一个 shared_ptr 管理的资源
    {
        std::shared_ptr<void>guard=tie_.lock();//提升
        if(guard)
        {
            handleEventWithGuard(receiveTime);
        }
    }
    else//如果是独立 Channel，不绑定也安全。
    {
             handleEventWithGuard(receiveTime);
    }
}
//根据poller通知的channel发生的具体事件，由channel负责调用具体的回调操作
void     Channel::handleEventWithGuard(Timestamp  receiveTime)
{
    LOG_INFO("channel  handleEvent   revents:%d",revents_);
    if((revents_&EPOLLHUP) && !(revents_&EPOLLIN))//只有挂起事件，并且没有可读事件（即已经完全关闭连接，读不到数据）
    {
        if(closeCallback_)
        {
            closeCallback_();//如果用户注册了关闭事件回调函数，就调用它。
        }
    }
    if(revents_&EPOLLERR)//EPOLLERR：表示文件描述符发生错误，比如连接被重置
    {
        if(errorCallback_)
        {
            errorCallback_();
        }
    }
    if(revents_&(EPOLLIN|EPOLLPRI))//如果注册了读事件回调函数，则调用它，并将事件接收时间传入。
    {
        if(readCallback_)
        {
            readCallback_(receiveTime);
        }
    }
    if(revents_&EPOLLOUT)//可写
    {
        if(writeCallback_)
        {
            writeCallback_();
        }
    }
}