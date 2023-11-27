#ifndef USER_H
#define USER_H

#include <string>
using std::string;
/// @brief 匹配User表中的映射字段类
class User {
    int id_;
    string name_;
    string password_;
    string state_;
public:
    User(int id = -1, string nm = "", string pswd = "", string state = ""):id_(id), name_(nm), password_(pswd), state_(state) {}

    void SetId(int id) {id_ = id;}
    void SetName(string name) {name_ = name;}
    void SetPswd(string pswd) {password_ = pswd;}
    void SetState(string state) {state_ = state;}

    int GetId() { return id_; }
    string GetName() { return name_; }
    string GetPswd() { return password_; }
    string GetState() { return state_; }
};

#endif // USER_H