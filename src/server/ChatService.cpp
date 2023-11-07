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
    // LOG_INFO << "do reg server success!";
    // name password
    string name = js["name"];
    string pswd = js["password"];
    
    User user;
    user.SetName(name);
    user.SetPswd(pswd);
    bool state = _userModel.Insert(user);
    if(state) { // 注册成功
        json response;
        response["msageid"] = REG_MSG_ACK;
        response["errno"] = 0;
        response["id"] = user.GetId();
        conn->send(response.dump());
    } else { // 注册失败
        json response;
        response["msageid"] = REG_MSG_ACK;
        response["errno"] = 1;
        conn->send(response.dump());
    }
}

void ChatService::login(const TcpConnectionPtr &conn, json &js, Timestamp time) {
    // LOG_INFO << "do login server success!";
    // ID password
    int id = js["id"].get<int>();
    string pswd = js["password"];
    User user = _userModel.query(id);
    if(user.GetId() == -1) {
        // 查无此人或者数据库连接失败
        LOG_ERROR << id << ": " << user.GetName() << "\n";
    }
    if(user.GetPswd() == pswd) { // 登录成功
        LOG_ERROR << "用户" << user.GetId() << ": " << user.GetName() << "登录成功" << "\n";
        json response;
        response["msageid"] = LOGIN_MSG_ACK;
        response["errno"] = 0;
        response["id"] = user.GetId();
        response["name"] = user.GetName();
        conn->send(response.dump());
        // 更新用户状态
        user.SetState("online");
        _userModel.updataState(user);
    } else { // 登录失败
        user.SetName("密码错误");
        LOG_ERROR << "用户" << user.GetId() << ": " << user.GetName() << "登录失败" << "\n";
        json response;
        response["msageid"] = LOGIN_MSG_ACK;
        response["errno"] = 1;
        conn->send(response.dump());
    }
}