#ifndef USERMODEL_H
#define USERMODEL_H

#include <user.hpp>

/// @brief user表的数据操作类
class UserModel {
public:
    /// @brief 向表中添加一个user
    /// @param user 需要添加的user信息
    /// @return 返回是否成功
    bool Insert(User &user);
};

#endif