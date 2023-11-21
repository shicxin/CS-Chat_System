#include <offlinemessagemodel.hpp>
#include <db.hpp>

void offlineMsgModel::insert(int userid, string msg) {
    string SQL = "insert into offlinemessage values( " + std::to_string(userid)  + ", '" + msg + "');";

    MySQL mysql;
    if(mysql.connect()) {
        mysql.update(SQL);
    }
}

vector<string> offlineMsgModel::quert(int userid) {
    string SQL = "select message from user where userid = " + to_string(userid) + ";";
    // User user;
    vector<string> set;
    MySQL mysql;
    if(mysql.connect()) {
        MYSQL_RES *res = mysql.query(SQL);
        if(res == nullptr) {
            return set;
        } else {
            MYSQL_ROW row;
            while((row = mysql_fetch_row(res)) != nullptr) {
                set.push_back(row[0]);
            }
            mysql_free_result(res);
        }
    }
    return set;
}

void offlineMsgModel::remove(int userid) {
    string SQL = "delect from offlinemessage where userid = " + std::to_string(userid) + "');";

    MySQL mysql;
    if(mysql.connect()) {
        mysql.update(SQL);
    }
}