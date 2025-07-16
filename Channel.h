#pragma  once
#include"noncopyable.h"
#include<functional>
#include<memory>
#include"Timestamp.h"
/**
 * 理清楚 EventLoop,Channel,Poller之间的关系，Reactor模型上对应多路事件分发器
 * Channel理解为通道，封装了sockfd和感兴趣的event，如EPOLLIN,EPOLLOUT事件、
 * 还绑定了poller返回的具体事件
 */
class   EventLoop;//EventLoop包含channel和poller

/**
 * 为什么用 std::function？
它是类型擦除的函数包装器，支持几乎所有可调用对象
比函数指针更灵活（支持捕获变量、类成员函数等）
在事件驱动框架中，可以延迟绑定各种不同形式的回调函数
 */
class  Channel:noncopyable
{
    public:
    using  EventCallback=std::function<void()>;
    using   ReadEventCallback=std::function<void(Timestamp)>;

    Channel(EventLoop *loop,int fd);//创建一个 Channel，绑定某个事件循环（EventLoop）和某个文件描述符 fd。
    ~Channel();

    void  handleEvent(Timestamp  receiveTime);//fd得到poller通知以后，处理事件的函数
    //设置回调函数对象,提供接口
void  setReadCallback(ReadEventCallback  cb)
{
    readCallback_=std::move(cb);
}
void   setWriteCallback(EventCallback  cb)
{
    writeCallback_=std::move(cb);
}
void    setCloseCallback(EventCallback cb)
{
    closeCallback_=std::move(cb);
}
void    setErrorCallback(EventCallback cb)
{
    errorCallback_=std::move(cb);
}
//防止当channel被手动remove掉，channel还在执行回调操作
void  tie(const  std::shared_ptr<void>&);
  
int   fd()const  {return   fd_; }
int   events()const   {return  events_;}
void    set_revents(int revt)
{
    revents_=revt;
}

//设置fd相应的事件状态
void   enableReading()
{
    events_|=KReadEvent;//在现有的关注事件中，加上 "可读事件"（KReadEvent）。
    update();//调用 update() 方法，更新底层的 epoll（或 poll/kqueue）注册事件
}
void   disableReading()
{
    events_&=~KReadEvent;//清除写事件
    update();
}
void   enableWriting()
{
    events_|=KWriteEvent;//清除写事件
    update();
}
void   disableWriting()
{
    events_&=~KWriteEvent;//清除写事件   //按位或，只要有一位是1就是1
    update();
}
void   disableAll()
{
    events_&=KNoneEvent;
    update();
}

//返回fd当前的事件状态
bool   isNoneEvent() const
{
    return  events_ ==KNoneEvent;
}
bool   isWriting() const
{
    return  events_ &KWriteEvent;  //按位与，两位都是1才是1
}
bool   isReading() const
{
    return  events_ &KReadEvent;
}

  int index()
  {
    return index_;
  }
  void  setindex(int idx)
  {
    index_=idx;
  }

  //one   loop  per   thread
  EventLoop*ownerLoop()
  {
    return loop_;
  }
  void  remove();

private:
    void   update();
    void    handleEventWithGuard(Timestamp  receiveTime);

    static   const   int  KNoneEvent;
    static   const   int  KReadEvent;
    static   const   int  KWriteEvent;

    EventLoop*loop_;//事件循环
    const  int  fd_;//fd,poller监听的对象
    int events_;//注册fd感兴趣的事件
    int  revents_;//poller返回的具体发生的事件
    int  index_;//用于 poll 模型时，在 pollfd 数组中的下标
    

    std::weak_ptr<void>  tie_;//用于解决对象生命周期问题，防止回调执行时对象已被销毁
    bool  tied_;
    //因为channel通道里面能够获知fd最终发生的具体的事件revents,所以他负责调用具体事件的回调操作
    ReadEventCallback  readCallback_;
    EventCallback   writeCallback_;
    EventCallback   closeCallback_;
    EventCallback   errorCallback_;
};
/**
 * Channel 是事件分发器，代表一个文件描述符（比如 socket），
 * 绑定了它感兴趣的 I/O 事件（如可读、可写），并负责在事件发生时调用你绑定的回调函数。
 * 
 */
/**
 * 保存一个 fd（socket/pipe 等）
保存这个 fd 关心的事件（读、写）
保存这个 fd 发生事件时要调用的回调函数
事件发生时由 EventLoop 调用 handleEvent，进而触发回调
 */

 /**
  * 
  */
 