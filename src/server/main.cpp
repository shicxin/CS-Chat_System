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

int main(int argc, char** argv) {

    if(argc != 3) {
        cout << "please use " << argv[0] << " like " << argv[0] << " xx.xx.xx.xx port\n";
    }

    signal(SIGINT, reseHandler);

    EventLoop loop;
    char *ip = argv[1];
    uint16_t port = atoi(argv[2]);
    InetAddress addr(ip, port);
    ChatServer server(&loop, addr, "CharServer");
    server.start();
    loop.loop();
    return 0;
}