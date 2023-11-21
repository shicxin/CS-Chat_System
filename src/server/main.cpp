#include "ChatServer.hpp"
#include <iostream>

#include <signal.h>
#include <ChatService.hpp>

// #define

using namespace std;

/// @brief 捕获服务器异常退出并处理服务器中遗留消息
void reseHandler(int) {
    ChatService::instance().reset();
    exit(0);
}

int main() {

    signal(SIGINT, reseHandler);

    EventLoop loop;
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "CharServer");
    server.start();
    loop.loop();
    return 0;
}