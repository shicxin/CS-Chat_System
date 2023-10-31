#if !defined(__SYS__)
#define __SYS__

#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>

#include "cJSON.h"
#include "tell.h"
#include "user.h"
// #include

 

// void read_childproc(int sig);
void manage_user(int red_fd, int wrt_fd);

// cJSON* find_user(cJSON* , cJSON*);//专门查找用户
// void del_user(); //删除用户进程

void Client_functionality (int, int, int);
bool Login_registered(int, int, int);

bool log_or_reg(cJSON** , int);//客户端登录注册

// void talk_who(cJSON* user, int wrt_fd, int read_fd);
// void lis_ser(cJSON* user, int wrt_fd, int read_fd);
void talk_who(cJSON* user);
void lis_ser(int sock);

void forward_message( int sock, int wrt_fd, int read_fd);

#endif // __SYS__
