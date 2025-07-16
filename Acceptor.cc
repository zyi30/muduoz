#include"Acceptor.h"
#include"Logger.h"
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<unistd.h>
#include"InetAddress.h"
static  int   createNonblocking()
{
   int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    if(sockfd<0)
    {
        LOG_FATAL("%s:%s:%d  listen socket  create err%d  \n:",__FILE__,__FUNCTION__,__LINE__,errno);
    }
    return   sockfd;
}

    Acceptor::Acceptor(EventLoop  *loop,const  InetAddress &listenAddr,bool  reuseport)
    :loop_(loop),
    acceptSocket_(createNonblocking()),
    acceptChannel_(loop,acceptSocket_.fd()),
    listenning_(false)
    {
        acceptSocket_.setReuseAddr(true);
         acceptSocket_.setReusePort(true);
        acceptSocket_.bindaddress(listenAddr);//bind
        //Tcpserver::start()  =>  Acceptor.listen   有新用户的连接，要执行一个回调(connfd=>channel=>subloop监听客户端读写时间)
        //baseloop=>监听到acceptChannel(listenfd)youshijian
        acceptChannel_.setReadCallback(std::bind(&Acceptor::handleRead,this));

    }

      Acceptor::~Acceptor()
      {
        acceptChannel_.disableAll();//取消该 Channel 所关注的所有事件（读、写等），然后调用 update() 更新在 epoll 中的注册状态。
        acceptChannel_.remove();//从 Poller（epoll）中注销一个 Channel 对象
      }

 
  
   
    void    Acceptor::listen()
    {
        listenning_=true;
        acceptSocket_.listen();
        acceptChannel_.enableReading();//acceptchannel=>poller(注册事件)监听是否有事件发生，如果有调用readcallback_回调=》Acceptor::handleRead()
    }

    
//listenfd有事件发生了。就是有新用户链接了
    void    Acceptor::handleRead()
    {
            InetAddress   peerAddr;
            int  connfd=acceptSocket_.accept(&peerAddr);
            if(connfd>=0)
            {
                if(newconnectionCallback_)
                {
                    newconnectionCallback_(connfd,peerAddr);//轮询找到subloop,唤醒分发新客户端的channel
                }
                else
                 {
                ::close(connfd);
                }
            }
            else
            {
                LOG_ERROR("%s:%s:%d accept  err:%d \n",__FILE__,__FUNCTION__,__LINE__,errno);
                if(errno==EMFILE)
                {
                    LOG_ERROR("%s:%ssockfd  reached   limit!  err:%d \n",__FILE__,__FUNCTION__,__LINE__);
                }
            }
            
    }