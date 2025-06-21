#include"EPollPoller.h"
#include <unistd.h>
#include"Channel.h"
#include"Logger.h"
#include<errno.h>
#include <string.h>
const   int  KNew=-1;//channel未添加到poller    channel成员变量index -1
const   int    KAdded=1;//channel已添加到poller
const   int    KDeleted=2;//channel从poller删除
/**
 * 这是对父类构造函数的调用。
Poller 是一个抽象基类，保存了事件循环 EventLoop 的指针 ownerLoop_。
这样，EPollPoller 就继承了 ownerLoop_ 成员，可以和事件循环打通。Poller(loop)

 */
EPollPoller::EPollPoller(EventLoop *loop):Poller(loop),epollfd_(::epoll_create1(EPOLL_CLOEXEC))//当调用 exec 系列函数时自动关闭该 fd。
,events_(KInitEventListSize)//epoll  create1
{
    if(epollfd_<0)
    {
        LOG_FATAL("epoll_create error:%d\n",errno);
    }
}
EPollPoller::~EPollPoller()
{
    ::close(epollfd_);
}
Timestamp EPollPoller::poll(int timeoutMS,ChannelList  *activeChannels)//epoll wait
//将发生事件的channel通过activeChannels告诉eventloop
  {
        LOG_INFO("func=%s=> fd total  count:%lu\n",__FUNCTION__,channels_.size());
        int  numEvents=::epoll_wait(epollfd_,&*events_.begin(),static_cast<int>(events_.size()),timeoutMS);
        int saveError=errno;
        Timestamp  now(Timestamp::now());//调用 Timestamp::now() 获取当前时间
         //用它返回的 Timestamp 对象去初始化一个变量 now
        if(numEvents>0)
        {
            LOG_INFO("%d events  happened \n",numEvents);
            fillActiveChannels(numEvents,activeChannels);
            if(numEvents==events_.size())
            {
                events_.resize(events_.size()*2);
            }
        }
        else  if(numEvents==0)
        {
            LOG_DEBUG("%s  timeout!\n",__FUNCTION__);
        }
        else
        {
            if(saveError!=EINTR)
            {
                errno=saveError;
                LOG_ERROR("EpollPoller::poll() error!");
            }
        }
        return now; //  正确返回一个 Timestamp 对象
  }
  //channel  update  remove->EventLoop  updateChannel  removeChannel->poller   updateChannel  removeChannel
  /**
   * EventLoop包含了  ChannelList      Poller
   *                                  ChannelMap<fd,channel*>
   */
void   EPollPoller::updateChannel(Channel  *channel)  //epoll_ctr->add/mod
{
    const int  index=channel->index();
    LOG_INFO("fuc=%s=> fd=%d   events=%d   index=%d \n",__FUNCTION__,channel->fd(),channel->events(),index);
    if(index==KNew||index==KDeleted)
    {
        if(index==KNew)
        {
            int fd=channel->fd();
            channels_[fd]=channel;
        }
        channel->setindex(KAdded);
        update(EPOLL_CTL_ADD,channel);
    }
    else//channel已经在poller注册过
    {
        int fd=channel->fd();
        if(channel->isNoneEvent())
        {
            update(EPOLL_CTL_DEL,channel);
            channel->setindex(KDeleted);
        }
        else//对某些事件感兴趣
        {
            update(EPOLL_CTL_MOD,channel);
        }
    }



}
    void   EPollPoller::removeChannel(Channel *channel)//epoll_ctr->del    //从poller中删除channel
    {
            int fd=channel->fd();
            int  index=channel->index();
             channels_.erase(fd);  //channelMap删除
              LOG_INFO("fuc=%s=> fd=%d \n",__FUNCTION__,fd);
             if(index==KAdded)
             {
                update(EPOLL_CTL_DEL,channel);//在epoll中注册过，要在epoll中删除
             } 
             channel->setindex(KNew);
   }
     void   EPollPoller::fillActiveChannels(int   numEvents,ChannelList  *activeChannels)const
     {
        for(int i=0;i<numEvents;++i)
        {
            Channel *channel=static_cast<Channel*>(events_[i].data.ptr);
            channel->set_revents(events_[i].events);
            activeChannels->push_back(channel);//Eventloop拿到了他的poller返回得所有发生事件得channel列表了
        }
     }
    //更新channel通道   epoll_ctl  add/del/mod
    void   EPollPoller::update(int operation,Channel*channel)
    {
        epoll_event  event;
        memset(&event,0,sizeof  event);

          int fd=channel->fd();
        event.events=channel->events();
        event.data.ptr=channel;
        event.data.fd=fd;
      
        if(::epoll_ctl(epollfd_,operation,fd,&event)<0)
        {
            if(operation==EPOLL_CTL_DEL)
            {
                LOG_ERROR("epoll_ctl  del  error:%d\n",errno);
            }
             else//自动exit
            {
                LOG_FATAL("epoll_ctl  add/mod  error:%d\n",errno);
            }
        }

    }
   