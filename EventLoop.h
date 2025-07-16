#pragma once
//事件循环类   主要包含了两个大模块  Channel   Poller(epoll的抽象）
#include<functional>
#include"noncopyable.h"
#include<vector>
#include <atomic>
#include <fcntl.h>
#include"Timestamp.h"
#include<memory>
#include<mutex>
#include "CurrentThread.h"
class   Channel;
class   Poller;
class  EventLoop:noncopyable
{
public:
    using  Functor=std::function<void()>;//所以 std::function<void()> 表示 可以封装任意 “无参、无返回” 的函数或可调用对象。
    EventLoop();
    ~EventLoop();
    void  loop();//开启事件循环
    void quit();//退出事件循环
    Timestamp   pollReturnTime()const{return  pollReturnTime_;}
    void  runInLoop(Functor  cb);//在当前loop中执行cb
    void  queueInLoop(Functor  cb);//把cb放到队列中，唤醒loop所在的线程，执行cb
    void  wakeup();//用来唤醒loop所在的线程

    //Eventloop方法-》poller方法
    void    updateChannel(Channel*channel);
    void    removeChannel(Channel*channel);
    bool  hasChannel(Channel*channel);

    
    bool  isInLoopThread()const{return threadID_==CurrentThread::tid();}
    //判断当前代码是否运行在创建这个 EventLoop 的线程中

    private:
    void  handleRead();//唤醒
    void  doPendingFunctors();//执行回调

    using  ChannelList=std::vector<Channel*>;
    /*
    为什么用原子？
在多线程场景下，多个线程可能访问或修改同一个布尔变量，会产生“竞态条件（race condition）”。
使用 std::atomic_bool 可以确保读写操作是线程安全的。*/
    std::atomic_bool looping_;//原子操作
    std::atomic_bool quit_;//表示退出loop循环
    std::atomic_bool callingPendingFunctors_;//标识当前loop是否有需要执行的回调操作
    const   pid_t  threadID_;//记录当前loop所在线程id
    Timestamp  pollReturnTime_;//poller返回发生事件的channel得时间点
    std::unique_ptr<Poller>poller_;//evenyloop管理的poller
    int   wakeupFD_;//(eventfd系统调用)//主要作用，当mainloop获取一个新用户的channel,通过轮询算法选择一个subloop,通过该成员唤醒subloop处理channel
    std::unique_ptr<Channel>wakeupChannel_;
    ChannelList   activeChannels_;
    //Channel   *currentActiveChannel_;
   // std::atomic_bool callingPendingFunctors_;//标识当前loop是否有需要执行的回调操作
    std::vector<Functor>pendingFunctors_;//存储loop需要执行的所有回调操作
    std::mutex  mutex_;//互斥锁，用来保护上面vector容器的线程安全操作
};