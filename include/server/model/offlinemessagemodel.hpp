#ifndef OFFLINEMESSAGEMODEL_H
#define OFFLINEMESSAGEMODEL_H

#include <string>
#include <vector>

using std::string;
using std::vector;

/// @brief 提供离线消息的
class offlineMsgModel {
public:
    /// @brief 将离线消息插入数据库
    /// @param userid 用户id
    /// @param msg 消息
    void insert(int userid, string msg);
    /// @brief 查询用户的离线消息
    /// @param userid 待查ID
    /// @return 消息链表
    vector<string> quert(int userid);
    /// @brief 删除该用户的离线消息
    /// @param userid 用户ID
    void remove(int userid);

};

#endif //OFFLINEMESSAGEMODEL_H