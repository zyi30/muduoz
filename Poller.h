#pragma  once 
#include"noncopyable.h"
#include<vector>
#include<unordered_map>
#include"Timestamp.h"
#include "Channel.h"
class   EventLoop;
//muduo库里面多路事件分发器的核心IO复用模块
class    Poller: noncopyable
{
public:
using  ChannelList=std::vector<Channel*>;
    Poller(EventLoop*loop);
    virtual  ~Poller();

    //给所有IO复用保留统一接口
    virtual Timestamp  poll(int timeoutMS,ChannelList*activeChannels )=0;
    virtual void   updateChannel(Channel *channel)=0;
    virtual void   removeChannel(Channel *channel)=0;
    //判断一个poller是否有channel
    bool hasChannel(Channel   *channel)const;

    //拿到默认的一个io复用处理
    static  Poller*newDefaultPoller(EventLoop *Loop);
protected:
//key: sockfd       value:sockfd所属的channel通道类型
    using  ChannelMap=std::unordered_map<int,Channel*>;
    ChannelMap  channels_;
private:
    EventLoop* ownerLoop_;//定义poller所属的事件循环EventLoop;
};