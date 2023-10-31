#if !defined(__TELL__)
#define __TELL__

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <time.h>
#include "mycjson.h"

#define CHAR_SIZE 20
#define PUT_OK 0

#define USER_MANAGE_FIRE "./data/sys/USER_manage"


void server_sock_init(int* sock, struct sockaddr_in* ser_adr);

int get_sock_with_cline(int ser_sock, struct sockaddr_in* addr, socklen_t* addr_size);

int call_ser();
void read_DO_message(int fd, int* DO, cJSON** message);

void talk_DO_message(int fd, int DO, cJSON* message);

static const int CONTROL_LEN = CMSG_LEN( sizeof(int) );

int recv_fd( int fd );
void send_fd( int fd, int fd_to_send );

#endif // __TELL__
