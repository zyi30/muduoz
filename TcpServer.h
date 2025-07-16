#pragma once
/**
 * 用户使用muduo编写服务器程序
 */
#include "EventLoop.h"
#include"Acceptor.h"
#include"InetAddress.h"
#include"noncopyable.h"
#include<functional>
#include<string>
#include<memory>
#include"EventLoopThreadPool.h"
#include"Callbacks.h"
#include<unordered_map>
#include"Tcpconnection.h"
#include"Buffer.h"
//对外的服务器编程使用的类
class   TcpServer:noncopyable
{
public:
using  ThreadInitCallback=std::function<void(EventLoop*)>;
enum  Option// 是否开启端口复用，Acceptor 构造时会根据这个配置创建监听 socket。
{
    KNoReusePort,
    KReusePort,
};
     
    TcpServer(EventLoop*loop,const  InetAddress  &ListenAddr,const  std::string &nameArg,  Option  option=KNoReusePort);

    ~TcpServer();

    void  setThreadInitcallback(const  ThreadInitCallback&cb){threadInitCallback_=cb;}//新线程初始化回调
    void  setConnectionCallback(const  ConnectionCallback&cb){connectionCallback_=cb;}//有连接建立时的回调
    void  setMessageCallback(const  MessageCallback&cb){messageCallback_=cb;}//有消息到达时的回调
    void  setWriteCompleteCallback(const  WriteCompleteCallback&cb){writeCompleteCallback_=cb;}//消息发送完成时的回调


    void  setThreadNum(int numThreads);//设置底层subloop的个数

    void  start();//开启服务器监听
private:
    void  newConnection(int  sockfd,const   InetAddress &peerAddr);// 有新连接到来时由 Acceptor 调用，建立 TcpConnection 对象。

    void  removeConnection(const  TcpconnectionPtr  &conn);//removeConnection()：线程安全地销毁连接

        void  removeConnectionInLoop(const  TcpconnectionPtr  &conn);//真正的删除操作，由事件循环执行


    using   ConnectionMap=std::unordered_map<std::string,TcpconnectionPtr>;
    EventLoop  *loop_;//baseLoop用户定义的loop

    const std::string   ipPort_;
    const  std::string   name_;

    std::unique_ptr<Acceptor>acceptor_;//运行在mainloop,监听新连接事件

    std::shared_ptr<EventLoopThreadPool>threadPool_;//one loop per   thread

    ConnectionCallback  connectionCallback_;//新连接时的回调
    MessageCallback  messageCallback_; //有读写消息时的回调
    WriteCompleteCallback writeCompleteCallback_;//消息发送完成的回调
    
    ThreadInitCallback    threadInitCallback_;//loop线程初始化的回调
    std::atomic_int started_;//标记是否启动过，防止 start() 被重复调用

    int  nextConnId_;// 自增连接编号
    ConnectionMap   connections_;//保存所有的连接
};

