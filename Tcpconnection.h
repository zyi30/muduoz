#pragma  once

#include"noncopyable.h"
#include"InetAddress.h"
#include"Callbacks.h"
#include"Buffer.h"
#include<memory>
#include<string>
#include<atomic>
#include"Timestamp.h"
/**
 * Tcpserver通过Acceptor有一个新用户连接，通过accept函数拿到connfd;
 * TcpConnection设置回调->Channel->Poller->Channel的回调操作
 * 
 */


class  Channel;
class  EventLoop;
class  Socket;
class  Tcpconnection:noncopyable,public std::enable_shared_from_this<Tcpconnection> //std::enable_shared_from_this<T> 的作用是让类的对象内部能获得自己的 shared_ptr，从而在异步操作、延迟回调中安全地管理自己的生命周期，防止悬空指针和提前析构。
{
private:
/**
 * 表示连接的状态：
KDisconnected：未连接
KConnecting：正在连接中
KConnected：连接建立成功
KDisconnecting：正在关闭连接
 */
    enum StateE { KDisconnected, KConnecting,KConnected,KDisconnecting };

public:
        Tcpconnection(EventLoop *loop,const std::string &name,int sockfd,const InetAddress& LocalAddr,const InetAddress&peerAddr);//sockfd 来自 accept()，表示这个连接的 fd。

        ~Tcpconnection();

        EventLoop*getLoop()const {return loop_;}

        const std::string&name()const{return  name_;}//不能通过这个返回值修改 name_ 的内容。

        const   InetAddress&localAddr()const{return   localAddr_;}

        const   InetAddress&peerAddr()const{return  peerAddr_;}

        bool   connected()const{return  state_==KConnected;}

            //发送数据(给客户端发送数据)异步发送数据，会加入 outputBuffer_，并在 loop 线程中发出。
        void  send(const std::string &buf);
        //关闭连接
        void   shutdown();

        //注册回调
        void   setConnectionCallback(const  ConnectionCallback&cb)
        {
            connectionCallback_=cb;
        }
        void   setMessageCallback(const  MessageCallback&cb)
        {
            messageCallback_=cb;
        }                            
         void   setWriteCompleteCallback(const   WriteCompleteCallback&cb)
        {
            writeCompleteCallback_=cb;
        }
         void   setHighWaterMarkCallback(const  HighWaterMarkCallback&cb,size_t  highWaterMark)
        {
            highWaterMarkCallback_=cb;
            highWaterMark_=highWaterMark;
        }
        void     setCloseCallback(const  CloseCallback&cb)
        {
            usercloseCallback_=cb;
        }
        //连接建立了
        void     connectEstablished();
        //连接销毁
        void     connectDestroyed();

        void    setState(StateE state)
        {
            state_=state;
        }
       

  private:      
       // enum  StateE{KDisconnected,KConnecting,KConnected,KDisconnecting};

        void  handleRead(Timestamp   receiveTime);
        void  handlewrite();
        void  handleClose();
        void  handleError();

        void  sendInLoop(const void*data,size_t len);

       
        void  shutdownInLoop();



        EventLoop  *loop_;//不是baseloop,因为Tcpconnection都是在subloop管理的
        const std::string  name_;//当前连接的名字（通常由 TcpServer 指定，用于日志或识别）
        std::atomic_int   state_;//当前连接的状态，由上面的 StateE 表示，使用 std::atomic 是为了线程安全。
        bool  reading_;//标志是否正在读数据。

        std::unique_ptr<Socket>socket_;
        std::unique_ptr<Channel>channel_;//因为 Socket 和 Channel 的生命周期应该严格由 Tcpconnection 独占管理，其他任何人不应该拥有或复制它们的所有权。这就是 unique_ptr 最适合的场景。

        //这里和acceptor类似    acceptor->main                 tcpconnection->sunloop
        const  InetAddress  localAddr_;
        const  InetAddress   peerAddr_;
        

     ConnectionCallback  connectionCallback_;//新连接时的回调·
    MessageCallback  messageCallback_; //有读写消息时的回调
    WriteCompleteCallback writeCompleteCallback_;//消息发送完成的回调
    HighWaterMarkCallback   highWaterMarkCallback_;
    CloseCallback   usercloseCallback_;
    size_t   highWaterMark_;

    Buffer   inputBuffer_;//	存储从 socket 读出来的数据（接收缓冲区）
    Buffer   outputBuffer_;  //	存储准备写入 socket 的数据（发送缓冲区）
};