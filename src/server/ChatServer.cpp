#include "ChatServer.hpp"
#include "ChatService.hpp"

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
  // 用户端断开连接
  if(!conn->connected()) {
    conn->shutdown();
  }
}
void ChatServer::onMessage(const TcpConnectionPtr& conn, Buffer* buffer, Timestamp time) {
  string buf = buffer->retrieveAllAsString();
  // 在此处必须保证buf是一个JSON对象，负责会有异常
  json js;
  try{
  js = json::parse(buf);
  } catch (json::parse_error& e)
  {
    return ; // 暂时不做处理
      // 输出异常信息
      // << "Parse error: " << e.what() << "\n";
  }
  // 获取消息对应的消息处理器
  if(!js.contains("msgid")) return ;
  auto msgHandler = ChatService::instance().GetHandler(js["msgid"].get<int>());
  // 绑定相应的处理器，响应响应的业务
  msgHandler(conn, js, time);
}