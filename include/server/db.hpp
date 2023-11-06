#ifndef DB_H
#define DB_H

#include <mysql/mysql.h>
#include <string>
using namespace std;

// 数据库操作类
class MySQL
{
public:
    /// @brief 初始化数据库连接
    MySQL();

    /// @brief 释放数据库连接资源
    ~MySQL();

    /// @brief 连接数据库
    /// @return 返回连接是否成功
    bool connect();

    /// @brief 更新操作
    /// @param sql 需要执行的语句
    /// @return 返回是否执行成功
    bool update(string sql);

    /// @brief 查询操作
    /// @param sql 查询SQL语句
    /// @return 查询结果
    MYSQL_RES *query(string sql);

    /// @brief 获取连接
    /// @return 一个mysql连接
    MYSQL* getConnection();
private:
    MYSQL *_conn;
};

#endif