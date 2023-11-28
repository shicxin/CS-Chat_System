#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <unordered_map>
#include <functional>
#include <mutex>

#include <json.hpp>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>

#include "usermodel.hpp"
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"

#include <redis.hpp>

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

    /// @brief 记录用户连接信息
    unordered_map<int, TcpConnectionPtr> _UserConnMap;

    /// @brief 定义互斥锁保证_UserConnMap的线程安全
    mutex _connMutex;

    /// @brief 数据操作类对象
    UserModel _userModel;

    /// @brief 离线消息对象，处理离线消息
    offlineMsgModel _offlineMsgModel;

    /// @brief 好友消息处理对像
    FriendModel _friendModel;

    /// @brief 群组消息处理对象
    GroupModel _groupModel;

    Redis _redis;

    //封装为单例的构造函数
    ChatService();
public:
    /// @brief 获取单例的接口函数
    /// @return 返回唯一的服务器业务对象
    static ChatService& instance();

    /// @brief 处理注册业务
    /// @param conn 管理TCP连接的智能指针
    /// @param js JSON消息
    /// @param time 收到消息的时间
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);

    /// @brief 处理登录业务
    /// @param conn 管理TCP连接的智能指针
    /// @param js JSON消息
    /// @param time 收到消息的时间
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);

    /// @brief 处理注销业务
    /// @param conn 管理TCP连接的智能指针
    /// @param js JSON消息
    /// @param time 收到消息的时间
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);

    /// @brief 客户端异常退出
    /// @param conn 客户端连接
    void clientCloseException(const TcpConnectionPtr &conn);
    
    /// @brief 重置客户端登录状态
    void reset();
    
    /// @brief 获取消息对应的处理器
    /// @param MsgId 
    /// @return 
    MsgHandler GetHandler(int MsgId); 

    /// @brief 一对一聊天业务
    /// @param conn 管理TCP连接的智能指针
    /// @param js JSON消息
    /// @param time 收到消息的时间
    void OneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);

    /// @brief 添加好友业务
    /// @param conn 管理TCP连接的智能指针
    /// @param js JSON消息
    /// @param time 收到消息的时间
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);

    /// @brief 创建群组业务
    /// @param conn 管理TCP连接的智能指针
    /// @param js JSON消息
    /// @param time 收到消息的时间
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);

    /// @brief 加入群组业务
    /// @param conn 管理TCP连接的智能指针
    /// @param js JSON消息
    /// @param time 收到消息的时间
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    
    /// @brief 群组聊天业务
    /// @param conn 管理TCP连接的智能指针
    /// @param js JSON消息
    /// @param time 收到消息的时间
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);

    /// @brief 从redis消息队列中获取订阅的消息
    /// @param userid 
    /// @param msg 
    void handleRedisSubscribeMessage(int userid, string msg);
};

#endif // CHATSERVICE_H