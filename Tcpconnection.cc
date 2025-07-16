#include"Tcpconnection.h"
#include"Logger.h"
#include"Socket.h"
#include"Buffer.h"
#include"Channel.h"
#include"EventLoop.h"
#include<functional>
#include<errno.h>
#include<memory>
#include<sys/types.h>
#include<sys/socket.h>
#include<strings.h>
#include <netinet/tcp.h>
#include<string>
static  EventLoop*  CheckLoopNotNull(EventLoop*loop)
{
    if(loop==nullptr)
    {
        LOG_FATAL("%s:%s:%d Tcpconnectionloop is null!\n",__FILE__,__FUNCTION__,__LINE__);
    }
    return loop;
}
/**
 * 构造一个 TCP 连接对象。
loop：负责事件处理的 EventLoop 指针（注意是 subloop）。
namearg：连接名称字符串。
sockfd：已经 accept 得到的客户端连接 socket。
localAddr：本地地址（服务器端 IP + 端口）。
peerAddr：对端地址（客户端 IP + 端口）。


 */
  Tcpconnection::Tcpconnection(EventLoop *loop,const std::string &namearg,int sockfd,const InetAddress& LocalAddr,const InetAddress&peerAddr):
  loop_(CheckLoopNotNull(loop)),
  name_(namearg),
  state_(KConnecting),
  reading_(true),
  socket_(new Socket(sockfd)),
  channel_(new Channel(loop,sockfd)),
  localAddr_(LocalAddr),
  peerAddr_(peerAddr),
  highWaterMark_(64*1024*1024)//64MB
  {
    //给channel设置相应的回调函数，poller给channel通知感兴趣的事件发生了，channel会回调相应的操作函数
    channel_->setReadCallback(std::bind(&Tcpconnection::handleRead,this,std::placeholders::_1));
    channel_->setWriteCallback(std::bind(&Tcpconnection::handlewrite,this));
    channel_->setCloseCallback(std::bind(&Tcpconnection::handleClose,this));
    channel_->setErrorCallback(std::bind(&Tcpconnection::handleError,this));
    LOG_INFO("Tcpconnection::ctor[%s] at  fd=%d\n",namearg.c_str(),sockfd);
    socket_->setKeepAlive(true);
  }
    Tcpconnection::~Tcpconnection()
    {
         LOG_INFO("Tcpconnection::dtor[%s] at  fd=%d   state=%d\n",name_.c_str(),channel_->fd(),state_.load());
           //socket_->setKeepAlive(true);
    }


    void   Tcpconnection::handleRead(Timestamp   receiveTime)//收数据
    {
        int  saveErrno=0;
        ssize_t   n=inputBuffer_.readFD(channel_->fd(),&saveErrno);
        if(n>0)
        {
            //已建立连接的用户，有可读事件发生了，调用用户传入的回调操作onMessage(交给上层)
            //如果读取成功（n > 0），说明客户端发来了数据。
            //这时调用用户注册的消息处理回调 messageCallback_
            messageCallback_(shared_from_this(),&inputBuffer_,receiveTime);
        }
        else if(n==0)//客户端断开
        {
            handleClose();
        }
        else
        {
            errno=saveErrno;
            LOG_ERROR("Tcpconnection::handleread");
            handleError();
        }
    }

    //：handlewrite() 是 Channel 在监听到 EPOLLOUT（可写事件）时，调用的回调函数，表示当前 fd 可写，需要把数据写入 socket。
    void   Tcpconnection::handlewrite()//发送数据
    {
            if(channel_->isWriting())//isWriting() 表示是否注册了 EPOLLOUT 到 poller。如果没有监听写事件，就不需要执行后续逻辑（说明之前没有待发送的数据）。
            {
                int   saveErrno=0;
                ssize_t  n=outputBuffer_.writeFD(channel_->fd(),&saveErrno);//发送数据到fd,把 outputBuffer_ 中的数据写入 socket（fd）
                if(n>0)//写入成功
                {
                    outputBuffer_.retrieve(n);// 从 outputBuffer_ 中移除刚刚写出去的 n 字节数据
                    if(outputBuffer_.readableBytes()==0)//发送完毕了
                    {
                        channel_->disableWriting();//发送完成后就不需要监听可写事件了，避免无意义的触发
                        if(writeCompleteCallback_)// 如果用户设置了 “发送完成” 的回调函数 
                        {   
                            //唤醒loop_对应的thread线程，执行回调       
                            loop_->queueInLoop(std::bind(writeCompleteCallback_,shared_from_this()));// 异步地把回调任务加入 loop_ 的事件循环中执行(线程安全，延迟执行)
                        }
                        if(state_==KDisconnecting)//正关闭连接 
                        {
                            shutdownInLoop();
                        }

                    }
                }
                else
                {
                        LOG_ERROR("Tcpconnection::handleWrite");
                }
            }
            else
            {
                LOG_ERROR("Tcp  connection   fd=%d  is  down,no  more  writing\n",channel_->fd());
            }
    }
    void   Tcpconnection::handleClose()
    {
            LOG_INFO("fd=%d  state=%d  \n",channel_->fd(),state_.load());
            setState(KDisconnected);
            channel_->disableAll();

            TcpconnectionPtr  connPtr(shared_from_this());
            connectionCallback_(connPtr);//执行连接回调（ConnectionCallback）,connectionCallback_ 是用户设置的回调函数，一般在连接建立或断开时调用。
            usercloseCallback_(connPtr);// 执行关闭回调（CloseCallback）  tcpserver::removeConnection

    }
    void   Tcpconnection::handleError()
    {
            int optval;// 定义一个整型变量 optval,用来临时存储通过 getsockopt() 获取的 socket 错误代码。
            socklen_t  optlen=sizeof optval;
            int err=0;//定义错误码变量 err

            /**
             *  调用 getsockopt() 获取 socket 错误状态

channel_->fd()：获取当前连接的 socket 文件描述符。

SOL_SOCKET：表示操作 socket 层级。

SO_ERROR：指定获取 socket 的错误码。

optval：用于接收返回的错误码。

optlen：输入输出参数，指明 optval 的长度。
             */
            if(::getsockopt(channel_->fd(),SOL_SOCKET,SO_ERROR,&optval,&optlen)<0)
            {
                err=errno;//系统调用失败时获取 errno
            }
            else
            {
                err=optval;// 系统调用成功时，错误码在 optval 中
            }
            LOG_ERROR("TcpConnection::handleError  name:%s -SO_ERROR:%d  \n",name_.c_str(),err);
    }
      void   Tcpconnection::send(const std::string &buf)
     {
        if(state_==KConnected)
        {
            if(loop_->isInLoopThread())
            //判断当前调用 send 的线程，是否就是 TcpConnection 所属的 EventLoop 线程。因为 TcpConnection 绑定了一个 EventLoop，所有网络操作都要在这个 loop 线程安全执行。
            {
                sendInLoop(buf.c_str(),buf.size());//buf.c_str(),获取 buf 字符串内部的 const char* 指针,如果当前就是 EventLoop 所在线程，直接调用 sendInLoop 函数发送数据。
            }
            else//
            {
                loop_->runInLoop(std::bind(&Tcpconnection::sendInLoop,this,buf.c_str(),buf.size()));
            }
            /**
             * 通过 runInLoop 把任务 封装成回调，提交给 EventLoop 线程执行。
std::bind(&TcpConnection::sendInLoop, this, buf.c_str(), buf.size()) 创建了一个可调用对象，绑定当前对象 this 和参数。
这样确保 sendInLoop 会在正确的 loop 线程中被执行，保证线程安全。
             */
        }
     }

     //在所属线程（I/O线程）中安全地将数据发送出去，如果不能一次性写完就将剩余数据缓存在 outputBuffer_ 中，并注册 EPOLLOUT 事件继续异步发送
      void   Tcpconnection::sendInLoop(const void*data,size_t len)//data: 要发送的数据指针。len: 要发送的数据长度
      {
            ssize_t nwrote=0;//实际写入 socket 的字节数
            size_t  remaining=len;//剩余还未发送的字节数（初始为总长度）
            bool  faultError=false;//标记是否发生致命错误（比如 EPIPE 或 ECONNRESET）。
            //之前调用过connection的shutdown了，不能再进行发送了
            if(state_==KDisconnected)//如果连接已经断开，记录日志并直接返回。防止已关闭连接还尝试发送数据。
            {
                LOG_ERROR("disconnected,give up  writing！");
                return;
            }

            /**
             * 如果当前 channel 没有监听可写事件，且输出缓冲区中没有残留数据，说明之前没有等待发送的数据。
此时尝试直接向 socket 写数据，提高性能（避免不必要的缓冲和事件驱动）。
             */
            if(!channel_->isWriting()&&outputBuffer_.readableBytes()==0)
            {
                nwrote=::write(channel_->fd(),data,len);//::write 是系统调用，尝试写入数据到 socket。
            }
            if(nwrote>=0)//如果写成功（大于等于0）：
            {
                remaining=len-nwrote;//计算剩余未发送的数据量。
                if(remaining==0&&writeCompleteCallback_)//如果一次性写完了，并且设置了写完成回调（例如触发业务逻辑），通过 queueInLoop 异步执行回调，保持线程安全。
                {
                    //既然在这里数据全部发送完成，就不用再给channel设置epollout事件      了
                    loop_->queueInLoop(std::bind(writeCompleteCallback_,shared_from_this()));
                }
            }
            else//remove<0如果写失败：
            {
                nwrote=0;//将写入量重置为 0（防止后续数据指针偏移出错）。
                if(errno!=EWOULDBLOCK)//如果错误不是 EWOULDBLOCK（写缓冲区满，但不是致命错误），记录错误日志。
                {
                    LOG_ERROR("TcpConnection::sendInLoop");
                    if(errno==EPIPE||errno==ECONNRESET)//若是 EPIPE（写端已关闭）或 ECONNRESET（连接重置），标记为致命错误。
                    {
                        faultError=true;
                    }
                }
            }

            if(!faultError&&remaining>0)//如果没有致命错误，而且仍有数据未写完：
            //说明当前这一次write没有把数据全部发送出去，剩余的数据需要保存到缓冲区中，然后给channel
            //注册epollout可写事件，poller发现tcp的发送缓冲区有空间，会通知相应的channel，调用handlewrite回调方法
            //最终调用Tcpconnection::handwrite方法，把发送缓冲区中的数据全部发送完成
            {
                size_t  oldlen=outputBuffer_.readableBytes();//目前发送缓冲区剩余的未发送的数据
                if(oldlen+remaining>=highWaterMark_&& oldlen<highWaterMark_&& highWaterMarkCallback_)//如果剩余数据与现有数据的总量超过高水位阈值，且之前没超过，就触发高水位回调，用于限流或提示（例如：暂停写入）。
                {
                    loop_->queueInLoop(std::bind(highWaterMarkCallback_,shared_from_this(),oldlen+remaining));
                }
                outputBuffer_.append((char*)data+nwrote,remaining);//将未写完的数据追加到 outputBuffer_ 中（注意数据偏移
                if(!channel_->isWriting())//如果当前 channel 没有监听写事件，则调用 enableWriting() 开启 EPOLLOUT，让 Poller 监听 socket 可写事件。
                {
                    channel_->enableWriting();//当 socket 可写时，会触发 handleWrite()，它会继续将 outputBuffer_ 中数据发送出去。
                }

            }
      }

         //连接建立了
        void      Tcpconnection::connectEstablished()
        {
                setState(KConnected);
                channel_->tie(shared_from_this());//将当前 TcpConnection（用 shared_from_this() 获取 shared_ptr<TcpConnection>）绑定给其内部的 Channel，确保 当 Channel 处理事件时 TcpConnection 仍然存在。
                channel_->enableReading();//像poller注册channel的epollin事件

                //新连接建立，执行回调
                connectionCallback_(shared_from_this());
        }
        //连接销毁
        void      Tcpconnection::connectDestroyed()
        {
               if(state_==KConnected)
               {
                 setState(KDisconnected);
                 channel_->disableAll();//把channel的所有感兴趣的事件，从poller中del掉
                  connectionCallback_(shared_from_this());
               }
               channel_->remove();//把channel从poller中删除掉
        }

          //关闭连接
        void    Tcpconnection::shutdown()
        {
            if(state_==KConnected)
            {
                setState(KDisconnecting);
                loop_->runInLoop(std::bind(&Tcpconnection::shutdownInLoop,this));
            }
        }
         void   Tcpconnection::shutdownInLoop()
         {
            if(!channel_->isWriting())//当前outputBuffer中的数据已经全部发送完成
            {
                socket_->showdownWrite();//关闭写端
            }
         }
