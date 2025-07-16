#include"Socket.h"
#include<unistd.h>
#include"Logger.h"
#include"InetAddress.h"
#include<sys/types.h>
#include<sys/socket.h>
#include <fcntl.h>
#include<strings.h>
#include <netinet/tcp.h>
        Socket::~Socket()
        {
            close(sockfd_);
        } 


        void    Socket::bindaddress(const  InetAddress&localaddr)
        {
                if(0!=::bind(sockfd_,(sockaddr*)localaddr.getSockAddr(),sizeof(sockaddr_in)))
                {
                    LOG_FATAL("bind  sockfd:%d fail\n",sockfd_);
                }
        }
 
        void   Socket::listen()
        {
            if(0!=::listen(sockfd_,1024))
            {
                LOG_FATAL("listen  sockfd:%d fail\n",sockfd_);

            }
        }

      int Socket::accept(InetAddress *peeraddr)
{
    sockaddr_in addr;          // 用于存储客户端地址
    socklen_t len = sizeof(addr); // 内核写入实际地址长度
    bzero(&addr, sizeof(addr));   // 清零，避免脏数据

    int connfd = ::accept(sockfd_, (sockaddr*)&addr, &len);
    if (connfd < 0)
    {
        perror("accept error");  // accept 调用失败，打印错误信息
        return -1;
    }

    // 连接成功，保存客户端地址
    peeraddr->setSockAddr(addr);

    // 设置connfd为非阻塞
    int flags = fcntl(connfd, F_GETFL, 0);
    if (flags == -1)
    {
        perror("fcntl F_GETFL error");
        // 这里仍然返回connfd，但说明非阻塞设置失败
        return connfd;
    }
    if (fcntl(connfd, F_SETFL, flags | O_NONBLOCK) == -1)
    {
        perror("fcntl F_SETFL O_NONBLOCK error");
        // 设置非阻塞失败，返回connfd
        return connfd;
    }
    printf("accept new connection: fd=%d, set non-blocking OK\n", connfd);
    return connfd;
}

        void   Socket::showdownWrite()
        {
            if(::shutdown(sockfd_,SHUT_WR)<0)
            {
                LOG_ERROR("shutdownWrite  error");
            }
        }


        /**
         * 这是 Socket 类的成员函数，用于设置是否关闭 Nagle 算法。
    on 是布尔类型参数，表示：
    true（或 1）→ 禁用 Nagle（启用 TCP_NODELAY），小数据包立刻发送，降低延迟。
    false（或 0）→ 启用 Nagle（默认），延迟发送小数据包，提高吞吐。
    参数	含义
sockfd_	当前 Socket 对象持有的 socket 文件描述符
IPPROTO_TCP	协议层，表示设置 TCP 层的选项
TCP_NODELAY	选项名称，表示是否启用 Nagle 算法
&optval	指向 1 或 0 的指针，控制开关
sizeof optval	指定参数大小（通常是 int 的大小）
         */
        void   Socket::setTcpNoDelay(bool on)
        {
            int  optval=on?1:0;
            ::setsockopt(sockfd_,IPPROTO_TCP,TCP_NODELAY,&optval,sizeof  optval);
        }


        /**
         * 允许重用本地地址（端口），解决“Address already in use”错误，通常服务端在重启时用。
SOL_SOCKET 表示在套接字层设置选项。
SO_REUSEADDR 允许绑定一个已处于 TIME_WAIT 状态的端口。
         */
        void   Socket::setReuseAddr(bool  on)
        {
              int  optval=on?1:0;
            ::setsockopt(sockfd_,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof  optval);
        }

        
/**
 * 允许多个进程/线程绑定同一个端口，提高负载均衡（Linux 支持）。
SO_REUSEPORT 选项。
 */
        void   Socket::setReusePort(bool  on)
        {
             int  optval=on?1:0;
            ::setsockopt(sockfd_,SOL_SOCKET,SO_REUSEPORT,&optval,sizeof  optval);
        }


        /**
         * 开启 TCP 保活机制，长连接空闲时发送探测包检测连接状态，防止死连接。
SO_KEEPALIVE 选项。
         */
        void   Socket::setKeepAlive(bool on)
        {

             int  optval=on?1:0;
            ::setsockopt(sockfd_,SOL_SOCKET,SO_KEEPALIVE,&optval,sizeof  optval);
        }