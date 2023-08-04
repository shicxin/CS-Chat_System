#if !defined(__TELL__)
#define __TELL__

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#include "user.h"
#include "cJSON.h"

#if !defined(__CHARSIZE__)
#define __CHARSIZE__
#define CHAR_SIZE 20
#define WHERE_SIZE 50
#endif // __CHARSIZE__


#define PORT_log 8888

typedef struct signal
{
    int DO;
    unsigned int len; //下次接收文件长度
    time_t tim;//时间
}SIG;


/*************clion*******************/
int call_ser();
//与客户端发起连接，获得聊天套接字

/*************server*******************/
int wait_cln(int* ser_sock, struct sockaddr_in cln_addr);
//服务器监听端口并等待客户端消息


/****************cjson****************/
char* signal_to_json(SIG* );
void json_to_signal(SIG* , char*);

char* user_to_json(USER* );
void json_to_user(USER* , char* );
#endif // __TELL__
