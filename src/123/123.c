#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include "../lib/tell.h"

int main(int argc, char** argv)
{
    int ser_sock, cln_sock;
    struct sockaddr_in ser_addr, cln_addr;
    socklen_t cln_addr_size = sizeof(cln_addr);
    ser_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(argc != 2)
    {
        printf("using %s + <port>", argv[0]);
        exit(1);
    }
    ser_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(ser_sock == -1)
    {
        puts("socket error!");
        exit(1);
    }
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(atoi(argv[1]));
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(ser_sock, (const struct sockaddr *) &ser_addr, sizeof(ser_addr)) == -1)
    {
        puts("bind error!");
        exit(1);
    }
    if(listen(ser_sock,2) == -1)
    {
        puts("listen error!");
        exit(1);
    }
    while(1)
    {
        cln_sock = accept(ser_sock, (struct sockaddr *) &cln_addr, &cln_addr_size);
        if(cln_sock == -1)
        {
            puts("accept error!");
            exit(1);
        }
        while(1)
        {
            int DO;
            cJSON* cjson;
            char* message;
            read_DO_message( cln_sock, &DO, &cjson);
            DO = 0;
            message = cJSON_Print(cjson);
            puts(message);
            free(message);
        }
    }
    close(cln_sock);
    close(ser_sock);
    return 0;
}