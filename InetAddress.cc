#include"InetAddress.h"
#include<strings.h>
#include <string.h>
//将 IP 地址和端口号封装到一个 sockaddr_in 结构
InetAddress::InetAddress(uint16_t port,std::string ip)
{
    bzero(&addr_,sizeof addr_);//清零结构体内存
    addr_.sin_family=AF_INET;//将地址族设置为 AF_INET，表示使用 IPv4 地址
    addr_.sin_port=htons(port);//将主机字节序转换为网络字节序，并赋值给 sin_port。这是因为网络传输中使用的是大端字节序。
    addr_.sin_addr.s_addr=inet_addr(ip.c_str());
    // 设置 IP 地址（字符串转整型）
}
std::string  InetAddress::toIp()const// 将二进制 IP 转换为字符串：
{
    //addr
    char buf[64]={0};
    inet_ntop(AF_INET,&addr_.sin_addr,buf,sizeof buf);
    return buf;
}
std::string   InetAddress::toIpPort()const// 返回完整的地址字符串，如 "127.0.0.1:8080"。
{
    //ip::port
    char buf[64]={0};
    inet_ntop(AF_INET,&addr_.sin_addr,buf,sizeof buf);// 将二进制 IP 转换为字符串：
    size_t  end=strlen(buf);
    uint16_t   port=ntohs(addr_.sin_port);//获取主机字节序的端口号（用 ntohs 由网络字节序转回来）。
    sprintf(buf+end,":%u",port);
    return   buf;
}
uint16_t   InetAddress::toPort()const
{
        return   ntohs(addr_.sin_port);
}
#include<iostream>
int main()
{
    InetAddress  addr(8080);
    std::cout<<addr.toIpPort()<<std::endl;
}