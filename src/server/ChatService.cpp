#include "ChatService.hpp"
#include "public.hpp"

#include <functional>

#include <muduo/base/Logging.h>

using namespace muduo;

using std::placeholders::_1;
using std::placeholders::_3;
using std::placeholders::_2;

ChatService::ChatService() {
    _MsgHandlerMap.insert({LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3)});
    _MsgHandlerMap.insert({REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3)});
}

 ChatService& ChatService::instance() {
    static ChatService service;
    return service;
}

MsgHandler ChatService::GetHandler(int MsgId) {
    // 如果MsgId没有对应的数据处理回调，记录日志
    auto id = _MsgHandlerMap.find(MsgId);
    if(id == _MsgHandlerMap.end()) {
        // 返回一个默认的处理器，这是为了不在此处处理错误
        return [=](const TcpConnectionPtr &conn, json &js, Timestamp time){
            LOG_ERROR << "MsgId: " << MsgId << "can not find in _MsgHandlerMap[]!";
        };
    } else return _MsgHandlerMap[MsgId];
}

void ChatService::reg(const TcpConnectionPtr &conn, json &js, Timestamp time) {
    LOG_INFO << "do reg server success!";
}

void ChatService::login(const TcpConnectionPtr &conn, json &js, Timestamp time) {
    LOG_INFO << "do login server success!";
}