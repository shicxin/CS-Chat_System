#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <unordered_map>
#include <functional>
#include <json.hpp>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include "usermodel.hpp"

using namespace std;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

/// @brief 处理消息的事件回调方法类型
using MsgHandler = 
        std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp time)>;

/// @brief 聊天服务器业务类
class ChatService {
    /// @brief  map映射表，存储消息ID和其对应的业务处理函数
    unordered_map<int, MsgHandler> _MsgHandlerMap;
    /// @brief 数据操作类对象
    UserModel _userModel;
    //封装为单例的构造函数
    ChatService();
public:
    /// @brief 获取单例的接口哈数
    /// @return 返回唯一的服务器业务对象
    static ChatService& instance();

    /// @brief 处理注册业务
    /// @param conn 一个TCP连接的引用计数智能指针
    /// @param js 一个JSON对象
    /// @param time 收到消息的时间
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);

    /// @brief 处理登录业务
    /// @param conn 一个TCP连接的引用计数智能指针
    /// @param js 一个JSON对象
    /// @param time 收到消息的时间
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    
    MsgHandler GetHandler(int MsgId); 
};

#endif // CHATSERVICE_H