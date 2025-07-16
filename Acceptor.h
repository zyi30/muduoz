#pragma  once
#include"noncopyable.h"
#include"Channel.h"
#include"Socket.h"
#include<functional>
class  InetAddress;
class   EventLoop;
class   Acceptor:noncopyable
{
 public:

    using  NewconnectionCallback=std::function<void(int sockfd,const InetAddress&)>;

    Acceptor(EventLoop  *loop,const  InetAddress &listenAddr,bool  reuseport);
    ~Acceptor();

    void setNewconnectionCallback(const   NewconnectionCallback&cb)
    {
        newconnectionCallback_=cb;
    }
    bool listenning()const  {return listenning_;}
    void  listen();
 private:
    void  handleRead();
    EventLoop *loop_;//Acceptor用的就是用户定义的那个baseLoop,也称作mainLoop;
     Socket   acceptSocket_;
     Channel  acceptChannel_;
    NewconnectionCallback  newconnectionCallback_;
    bool  listenning_;
};