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
    
    /// @brief 更新user单路状态
    /// @param user 需要更新的user信息
    /// @return 返回是否成功
    bool updataState(User &user);

    /// @brief 根据ID在数据库中查找user
    /// @param id 查找用户ID
    /// @return 查到返回user结构体，，没查到将返回结构体id置为-1
    User query(int id);
};

#endif