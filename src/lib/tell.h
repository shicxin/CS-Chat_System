#if !defined(__TELL__)
#define __TELL__

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#if !defined(__CHARSIZE__)
#define __CHARSIZE__
#define CHAR_SIZE 20
#define WHERE_SIZE 50
#endif // __CHARSIZE__


#define PORT_log 8888

/*************clion*******************/
int tell_server_signal(int);//告诉服务器信号
void tell_server_message(void*, long long siz);//告诉服务器消息
void tell_ser(void* message, long long siz);
// tell_the_server_();//告诉服务器



/*************server*******************/
int tell_client_signal();//告诉客户端信号
void tell_ser(void* message, long long siz);
#endif // __TELL__
