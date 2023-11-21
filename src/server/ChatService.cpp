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
    _MsgHandlerMap.insert({ONE_CHAT_MSG, std::bind(&ChatService::OneChat, this, _1, _2, _3)});
    _MsgHandlerMap.insert({ADD_FRIEND_MSG, std::bind(&ChatService::addFriend, this, _1, _2, _3)});
}

void ChatService::reset() {
    _userModel.resetState();
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
    LOG_INFO << "do login server success!";
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
        {
            // 记录已登录用户连接
            lock_guard<mutex> lock(_connMutex);
            _UserConnMap.insert({id, conn});
        }
        // 查询是否有离线消息
        vector<string> MsgSet = _offlineMsgModel.quert(id);
        if(!MsgSet.empty()) response["offlinemsg"] = MsgSet; 
        _offlineMsgModel.remove(id);
    } else { // 登录失败
        user.SetName("密码错误");
        LOG_ERROR << "用户" << user.GetId() << ": " << user.GetName() << "登录失败" << "\n";
        json response;
        response["msageid"] = LOGIN_MSG_ACK;
        response["errno"] = 1;
        conn->send(response.dump());
    }
}

void ChatService::loginout(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int userid = js["id"].get<int>();

    {
        lock_guard<mutex> lock(_connMutex);
        auto it = _UserConnMap.find(userid);
        if (it != _UserConnMap.end())
        {
            _UserConnMap.erase(it);
        }
    }
}


void ChatService::clientCloseException(const TcpConnectionPtr &conn) {
    User user;
    user.SetId(0);
    { // 该作用域加锁
        lock_guard<mutex> lock(_connMutex);
        // _UserConnMap.erase_if(conn {
        //     return p.second == conn; // 删除条件
        // });
        // 注释方法同下，但是需要C++20特性
        for(auto it = _UserConnMap.begin(); it != _UserConnMap.end(); ) {
            if(it->second == conn) {
                user.SetId(it->first);
                // 删除用户的连接信息
                it = _UserConnMap.erase(it); // 更新迭代器
                break;
            } else {
                ++it; // 增加迭代器
            }
        }
    }
    // 修改数据库中用户的状态
    if(user.GetId()) {
        user.SetState("offline");
        _userModel.updataState(user);
    }
}

void ChatService::OneChat(const TcpConnectionPtr &conn, json &js, Timestamp time) {
    int toID = js["toid"].get<int>();
    // bool UserState = false;
    // TcpConnectionPtr toConn;
    {
        lock_guard<mutex> lock(mutex);
        auto it = _UserConnMap.find(toID);
        if(it != _UserConnMap.end()) { // 直接转发消息
            it->second->send(js.dump());
            return;
        }
    }
    // 代码运行至此，说明用户不在线，记录离线消息
    string msg = js.dump();
    _offlineMsgModel.insert(toID, msg);
}

void ChatService::addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time) {
    int userid = js["id"].get<int>();
    int friendid = js["friendid"].get<int>();

    // 存储好友信息
    _friendModel.insert(userid, friendid);
}

void ChatService::createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int userid = js["id"].get<int>();
    string name = js["groupname"];
    string desc = js["groupdesc"];

    // 存储新创建的群组信息
    Group group(-1, name, desc);
    if (_groupModel.createGroup(group))
    {
        // 存储群组创建人信息
        _groupModel.addGroup(userid, group.getId(), "creator");
    }
}

void ChatService::addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int userid = js["id"].get<int>();
    int groupid = js["groupid"].get<int>();
    _groupModel.addGroup(userid, groupid, "normal");
}

void ChatService::groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int userid = js["id"].get<int>();
    int groupid = js["groupid"].get<int>();
    vector<int> useridVec = _groupModel.queryGroupUsers(userid, groupid);

    lock_guard<mutex> lock(_connMutex);
    for (int id : useridVec)
    {
        auto it = _UserConnMap.find(id);
        if (it != _UserConnMap.end())
        {
            // 转发群消息
            it->second->send(js.dump());
        }
        else
        {
            // 查询toid是否在线 
            User user = _userModel.query(id);
            if (user.GetState() == "online")
            {
                // 发消息
            }
            else
            {
                // 存储离线群消息
                _offlineMsgModel.insert(id, js.dump());
            }
        }
    }
}