#pragma  once
#include<memory>
#include<functional>
class   Buffer;
class   Tcpconnection;
class  Timestamp;
using  TcpconnectionPtr=std::shared_ptr<Tcpconnection>;
using  ConnectionCallback=std::function<void (const  TcpconnectionPtr&)>;
using  CloseCallback=std::function<void (const  TcpconnectionPtr&)>;
using  WriteCompleteCallback=std::function<void (const  TcpconnectionPtr&)>;
using  MessageCallback=std::function<void (const  TcpconnectionPtr&,Buffer*,Timestamp)>;
using HighWaterMarkCallback = std::function<void(const TcpconnectionPtr&, size_t)>;

