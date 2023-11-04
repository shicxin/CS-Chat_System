#include "ChatServer.hpp"
#include <functional>

using namespace std;
using namespace placeholders;

ChatServer::ChatServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr, const string& nameArg)
  : server_(loop, listenAddr, "EchoServer"), loop_(loop)// TcpServer的构造函数
{
    server_.setConnectionCallback(std::bind(&ChatServer::onConnection, this, std::placeholders::_1));
    server_.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
    server_.setThreadNum(4);
}

void ChatServer::start() {
    server_.start();
}
void ChatServer::onConnection(const TcpConnectionPtr& conn) {}
void ChatServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time) {}