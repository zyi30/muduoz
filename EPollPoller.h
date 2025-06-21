#pragma once

#include"Poller.h"
#include"Timestamp.h"
#include<vector>
#include<sys/epoll.h>
class  Channel;
/**
 * epoll使用
 * epoll_create
 * epoll_ctr   add/mod/del
 * epoll_wait
 */
class EPollPoller : public   Poller
{
public:
    EPollPoller(EventLoop  *loop);
    ~EPollPoller()override;

    //重写基类Poller的抽象方法
    Timestamp poll(int timeoutMS,ChannelList  *activeChannels)override;
    void   updateChannel(Channel  *channel)override;  //epoll_ctr->add/mod
    void   removeChannel(Channel *channel)override;     //epoll_ctr->del
    
private:
    static  const   int KInitEventListSize=16;
    //填写活跃的连接
    void   fillActiveChannels(int   numEvents,ChannelList  *activeChannels)const;
    //更新channel通道
    void   update(int operation,Channel*channel);
    using   EventList=std::vector<epoll_event>;
    int epollfd_;
    EventList  events_;
};