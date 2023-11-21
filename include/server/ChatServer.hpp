#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

using namespace muduo;
using namespace muduo::net;

/// @brief 聊天服务器主类
class ChatServer {
    // muduo库中提供的server服务器
    TcpServer _server; 
    
    // 指向事件循环的指针
    EventLoop *_loop; 

    /// @brief 回调函数，响应客户端与服务器的连接、断开
    /// @param  连接
    void onConnection(const TcpConnectionPtr&);

    /// @brief 回调函数，上报读写事件相关信息
    /// @param  连接
    /// @param  消息
    /// @param  时间
    void onMessage(const TcpConnectionPtr&, Buffer*, Timestamp);

public:
    /// @brief 构造函数
    /// @param loop 反应器
    /// @param listenAddr IPv4地址相关信息
    /// @param nameArg 服务器名
    ChatServer(EventLoop* loop, const InetAddress& listenAddr, const string& nameArg ); 
    
    /// @brief 启动服务
    void start();
};

#endif