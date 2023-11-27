#include <friendmodel.hpp>
#include <db.hpp>

void FriendModel::insert(int userId, int friendId) {
    string SQL = "INSERT INTO friend VALUES ('" + std::to_string(userId) + ", "  + std::to_string(friendId) +  ");";

    MySQL mysql;
    if(mysql.connect()) {
        mysql.update(SQL);
    }
}

vector<User> FriendModel::query(int userid) {
    vector<User> set;
    string SQL = " select friend.friendid, user. from friend, user where userid = " + to_string(userid) + ";";
    // User user;
    MySQL mysql;
    if(mysql.connect()) {
        MYSQL_RES *res = mysql.query(SQL);
        if(res == nullptr) {
            return set;
        } else {
            MYSQL_ROW row;
            while((row = mysql_fetch_row(res)) != nullptr) {
                User x;
                x.SetId(stoi(row[0]));
                // set.push_back(row[0]);
            }
            mysql_free_result(res);
        }
    }
    return set;
}