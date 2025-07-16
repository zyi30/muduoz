#include"TcpServer.h"
#include"Logger.h"
#include<strings.h>
#include<functional>
#include"Tcpconnection.h"
static  EventLoop*  CheckLoopNotNull(EventLoop*loop)
{
    if(loop==nullptr)
    {
        LOG_FATAL("%s:%s:%d mainloop is null!\n",__FILE__,__FUNCTION__,__LINE__);
    }
    return loop;
}


  TcpServer::TcpServer(EventLoop*loop,const  InetAddress  &ListenAddr,const  std::string &nameArg,Option  option)
  :loop_(CheckLoopNotNull(loop)),
  ipPort_(ListenAddr.toIpPort()),
  name_(nameArg),
  acceptor_(new Acceptor(loop,ListenAddr,option==KReusePort)),
  /**
   * 创建listenfd=>封装成为acceptchannel=>acceptchannel.enableReading向poller注册关注读事件=》poller进行监听，如果有读事件发生
   * =》调用回调函数acceptor::handleread=>返回connectfd=>newconnectioncallback被调用（Tcpserver设置（setnewconnectioncallback））
   */
    threadPool_(new EventLoopThreadPool(loop,name_)),
    connectionCallback_(),
    messageCallback_(),
    nextConnId_(1),
    started_(0)
  {
    //当有新用户连接时，会执行TcpServer::newConnection回调
        acceptor_->setNewconnectionCallback(std::bind(&TcpServer::newConnection,this,std::placeholders::_1,std::placeholders::_2));
  }

    TcpServer::~TcpServer()
    {
        for(auto&item :connections_)//遍历连接池：connections_ 是一个 unordered_map<std::string, TcpconnectionPtr>
        {
            TcpconnectionPtr  conn(item.second);//这个局部强智能指针对象，出右括号，可以自动释放new出来的Tcpconnection对象，构造一个局部的 shared_ptr 智能指针 conn，从 item.second 拷贝构造
            item.second.reset();//显式清空原 map 中的智能指针
            //销毁链接
            conn->getLoop()->runInLoop(std::bind(&Tcpconnection::connectDestroyed,conn));
            /**
             * 将连接销毁操作，转移到连接所属的 IO 线程中去执行。
            conn->getLoop() 获取的是该连接对象所归属的 EventLoop（一般是某个 subLoop）。
            runInLoop(...) 是异步操作：如果当前线程是该 loop 所在线程，就立即执行；否则会将任务加入该线程的事件队列中。
             */
        }
     }

   void   TcpServer::setThreadNum(int numThreads)
   {
      threadPool_->setThreadNum(numThreads);
   }
    void   TcpServer::start()//开启服务器监听
    {
        if(started_++==0)//防止一个tcpserver对象被start多次
        {
            threadPool_->start(threadInitCallback_);//启动底层的loop线程池
            loop_->runInLoop(std::bind(&Acceptor::listen,acceptor_.get()));
            /**
             * &Acceptor::listen 是 Acceptor 类的成员函数指针；
acceptor_.get() 是调用 listen() 的对象；
这个 bind 表达式会创建一个类似 std::function<void()> 的可调用对象，调用它时会执行 acceptor_->listen()。
             */
        }
    }

        //有一个新的客户端连接，会执行这个回调
   void  TcpServer::newConnection(int  sockfd,const   InetAddress &peerAddr)
   {
        EventLoop*ioloop=threadPool_->getNextLoop();//轮询算法选择一个subloop,来管理channel
        char buf[64]={0};
        snprintf(buf,sizeof  buf,"-%s#%d", ipPort_.c_str(),nextConnId_);
        ++nextConnId_;
        std::string connName=name_+buf;

        LOG_INFO("Tcpserver::newConnection[%s]-new connection [%s]from  %s\n",name_.c_str(),connName.c_str(),peerAddr.toIpPort().c_str());

        //通过sockfd获取其绑定的本机ip地址和端口信息
        sockaddr_in   local;
        ::bzero(&local,sizeof  local);
        socklen_t  addrlen=sizeof  local;
        if(::getsockname(sockfd,(sockaddr*)&local,&addrlen)<0)
        {
            LOG_ERROR("sockets::getLocalAddr");
        }
        InetAddress  localAddr(local);


        //根据连接成功的sockfd,创建TcpConnection连接对象
        TcpconnectionPtr  conn(new   Tcpconnection(
        
            ioloop,
            connName,
            sockfd,        //socket,channel
            localAddr,
            peerAddr));
        connections_[connName]=conn;
        //下面的回调都是用户设置的给tcpserver->tcpconnection->channel->poller->notify  channel调用回调
        conn->setConnectionCallback(connectionCallback_);
        conn->setMessageCallback(messageCallback_);
        conn->setWriteCompleteCallback(writeCompleteCallback_);
        //设置了如何关闭连接的回调  conn->shutdown
        conn->setCloseCallback(std::bind(&TcpServer::removeConnection,this,std::placeholders::_1));
        //直接调用Tcpconnection::connectEstablished
        ioloop->runInLoop(std::bind(&Tcpconnection::connectEstablished,conn));
   }

    //removeConnection() 是在当前线程调用的（通常是 subLoop），但 removeConnectionInLoop() 涉及主线程的数据结构，为了线程安全，必须通过 runInLoop() 投递到主线程去执行
     void   TcpServer::removeConnection(const  TcpconnectionPtr  &conn)//removeConnection()：线程安全地销毁连接
     {
            //线程安全地销毁一个 Tcp 连接对象 conn，并确保它的销毁逻辑是在 TcpServer 所在线程（也就是 main reactor）中执行的。
            loop_->runInLoop(std::bind(&TcpServer::removeConnectionInLoop,this,conn));
     }


     /**
      * poller先检测到连接关闭时间-》channel的回调函数closecallback_(tcpconnection::handleclose)->usercloseCallback_(connPtr);// 执行关闭回调 tcpserver::removeConnection
      * ->Tcpconnection::connectDestroyed

      */
    void   TcpServer::removeConnectionInLoop(const  TcpconnectionPtr  &conn)//该函数在 IO 线程（EventLoop 线程）中被执行，用于真正地移除并销毁一个连接
    {
            LOG_INFO("TcpServer::removeConnectionInLoop  [%s]-connection %s\n",name_.c_str(),conn->name().c_str());//打印日志，记录当前正在执行删除连接操作，服务器的名称+连接名称
            connections_.erase(conn->name());//从 TcpServer 的连接映射表 connections_ 中移除这个连接。
            EventLoop  *ioLoop=conn->getLoop();
            ioLoop->queueInLoop(std::bind(&Tcpconnection::connectDestroyed,conn));//不是直接调用销毁逻辑，而是交由该连接的 IO 线程去异步销毁，保证线程安全。   
     }