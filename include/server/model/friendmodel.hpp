#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H

#include <user.hpp>
#include <vector>
using std::vector;

/// @brief 维护好友信息的操作接口方法
class FriendModel {
public:
    /// @brief 添加好友关系
    /// @param userid 自己的
    /// @param friendid 好友ID
    void insert(int userid, int friendid);

    /// @brief 返回好友信息列表
    /// @param userid 查询的用户ID
    /// @return 好友信息列表
    vector<User> query(int userid);

private:
    
};

#endif // FRIENDMODEL_H