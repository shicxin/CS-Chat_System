#include "tell.h"
#include "user.h"
#include "cJSON.h"

/// @brief 创建与服务器连接的套接字
/// @return 套接字
int call_ser()
{
    int sock;
    struct sockaddr_in serv_addr;
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1) 
    {
        puts("socket error!");
        exit(1);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // serv_addr.sin_port = htons(PORT_log);
    printf("监听端口为：");
    int port;
    scanf("%d", &port);
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    {
        puts("connect error!");
        exit(1);
    }
    return sock;
}

/// @brief 服务器等待客户端的连接
/// @param ser_sock 服务端套接字，用于监听端口，同时保存完成三次握手的客户端信息
/// @param cln_addr 
/// @return 与客户端连接的套接字
int wait_cln(int* ser_sock, struct sockaddr_in cln_addr)
{
    int sock;
    socklen_t cln_addr_size = sizeof(cln_addr);
    sock = accept(*ser_sock, (struct sockaddr *)&cln_addr, &cln_addr_size);
    if(sock == -1)
    {
        puts("accept error!");
        exit(1);
    }
    return sock;
}

/// @brief 将发给服务器的信号转换为json格式的字符串
/// @param signal 信号，包含做什么、下次接收内容长度、以及一个时间戳
/// @return json格式的字符串
char* signal_to_json(SIG* signal)
{
    cJSON* js = cJSON_CreateObject();
    cJSON_AddNumberToObject(js, "DO", signal->DO);
    cJSON_AddNumberToObject(js, "len", signal->len);
    cJSON_AddNumberToObject(js, "tim", signal->tim);
    return cJSON_Print(js);
}

/// @brief 将发来的json格式字符串转换为一个信号
/// @param signal 信号
/// @param message 返回字符串
void json_to_signal(SIG* signal, char* message)
{
    cJSON* js = cJSON_Parse(message);
    cJSON* DO = cJSON_GetObjectItem(js, "DO");
    cJSON* len = cJSON_GetObjectItem(js, "len");
    cJSON* tim = cJSON_GetObjectItem(js, "tim");
}

/// @brief 将发给服务器的用户节点转换为json格式的字符串
/// @param user 用户节点
/// @return json格式的字符串
char* user_to_json(USER* user)
{
    cJSON* js = cJSON_CreateObject();
    cJSON_AddStringToObject(js, "ID", user->ID);
    cJSON_AddStringToObject(js, "name", user->name);
    cJSON_AddStringToObject(js, "pasw", user->pasw);
    return cJSON_Print(js);
}

/// @brief 将接收到的json格式的字符串转化为用户信息
/// @param user 
/// @param message 
void json_to_user(USER* user, char* message)
{
    cJSON* js = cJSON_Parse(message);
    cJSON *ID = cJSON_GetObjectItem(js, "ID");
    cJSON *name = cJSON_GetObjectItem(js, "name");
    cJSON *pasw = cJSON_GetObjectItem(js, "pasw");
    strcpy(user->ID, ID->valuestring);
    strcpy(user->name, name->valuestring);
    strcpy(user->pasw, pasw->valuestring);
}