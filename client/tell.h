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

void tell_server_to_signal(int);//告诉服务器信号
void tell_server_message(void*, int);//告诉服务器消息
// tell_the_server_to_();//告诉服务器

void tell_client_signal();

#endif // __TELL__
