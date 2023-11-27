#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include "group.hpp"
#include <string>
#include <vector>
using namespace std;

/// @brief 维护群组信息的操作接口方法
class GroupModel
{
public:
    /// @brief 创建群组
    /// @param group 群组信息
    /// @return 是否成功
    bool createGroup(Group &group);

    /// @brief 加入群组
    /// @param userid 待查用户
    /// @param groupid 群组ID
    /// @param role 群成员角色
    void addGroup(int userid, int groupid, string role);

    /// @brief 查询用户所在群组信息
    /// @param userid 待查用户
    /// @return 群组成员列表
    vector<Group> queryGroups(int userid);

    /// @brief 根据指定的groupid查询群组用户id列表，除userid自己，主要用户群聊业务给群组其它成员群发消息
    /// @param userid 发消息用户ID
    /// @param groupid 发消息的群
    /// @return 群组中其他用户列表
    vector<int> queryGroupUsers(int userid, int groupid);
};

#endif