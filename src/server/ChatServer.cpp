#include "ChatServer.hpp"
#include <functional>
#include <string>
#include "json.hpp"

using namespace std;
using namespace placeholders;
using json = nlohmann::json;

ChatServer::ChatServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr, const string& nameArg)
  : _server(loop, listenAddr, "EchoServer"), _loop(loop)// TcpServer的构造函数
{
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, std::placeholders::_1));
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
    _server.setThreadNum(4);
}

void ChatServer::start() {
    _server.start();
}
void ChatServer::onConnection(const TcpConnectionPtr& conn) {
  // 用户断开连接
  if(!conn->connected()) {
    conn->shutdown();
  }
}
void ChatServer::onMessage(const TcpConnectionPtr& conn, Buffer* buffer, Timestamp time) {
  string buf = buffer->retrieveAllAsString();
  json js = json::parse(buf);
}