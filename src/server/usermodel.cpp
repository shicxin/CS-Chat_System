#include <usermodel.hpp>
#include <db.hpp>

bool UserModel::Insert(User &user) {
    // 组装SQL语句
    string SQL = "INSERT INTO User(name, password, state) VALUES ('" + user.GetName() + "', '"  + user.GetPswd() + "', '" + user.GetState() + "');";

    MySQL mysql;
    if(mysql.connect()) {
        if(mysql.update(SQL.c_str())) {
            // 获取主键ID
            user.SetId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
}