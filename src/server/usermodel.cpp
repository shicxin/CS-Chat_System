#include <usermodel.hpp>
#include <db.hpp>

bool UserModel::Insert(User &user) {
    // 组装SQL语句
    string SQL = "INSERT INTO user(name, password) VALUES ('" + user.GetName() + "', '"  + user.GetPswd() +  "');";

    MySQL mysql;
    if(mysql.connect()) {
        if(mysql.update(SQL)) {
            // 获取刚刚插入的主键ID，并将ID赋值回user
            user.SetId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
}

bool UserModel::updataState(User& user) {
    string SQL = "UPDATE user SET state = '" + user.GetState() + "' WHERE id = " + to_string(user.GetId()) + ";" ;

    MySQL mysql;
    if(mysql.connect()) {
        if(mysql.update(SQL)) {
            return true;
        }
    }
    return false;
}

// {"msgid":1,"id":13,"password":"123456"}

User UserModel::query(int id) {
    // 组装SQL
    string SQL = "select * from user where id = " + to_string(id) + ";";
    User user;
    MySQL mysql;
    if(mysql.connect()) {
        MYSQL_RES *res = mysql.query(SQL);
        if(res == nullptr) {
            user.SetId(-1);
        user.SetName("没有这个用户!");
        } else {
            MYSQL_ROW row = mysql_fetch_row(res); 
            if(row != nullptr) {
                user.SetId(atoi(row[0]));
                user.SetName(row[1]);
                user.SetPswd(row[2]);
                user.SetState(row[3]);
            }
            mysql_free_result(res);
        }
    } else {
        user.SetId(-1);
        user.SetName("数据库连接失败!");
    }
    return user;
}

void UserModel::resetState() {
    string SQL = "UPDATE user SET state = 'offline' WHERE state = 'online';";

    MySQL mysql;
    if(mysql.connect()) {
        mysql.update(SQL);
    }
}