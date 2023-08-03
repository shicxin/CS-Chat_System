#include "tell.h"

int tell_server_signal(int sig)
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[] = {"0123456789"};;
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1) 
    {
        puts("socket error!");
        exit(1);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT_log);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    {
        puts("connect error!");
        exit(1);
    }
    write(sock, &message[sig], 1);
    close(sock);
    return message[sig] - '0';
}
 
int tell_client_signal()
{
    int ser_sock, cln_sock;
    struct sockaddr_in ser_addr, cln_addr;
    char message[] = "0123456789";
    ser_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(ser_sock == -1) 
    {
        puts("socket error!");
        exit(1);
    }
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(PORT_log);
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(ser_sock, (struct sockaddr*)&ser_addr, sizeof(ser_addr)) == -1)
    {
        puts("bind error!");
        exit(1);
    }
    if(listen(ser_sock, 1) == -1)
    {
        puts("listen error!");
        exit(1);
    }
    socklen_t cln_addr_size = sizeof(cln_addr);
    cln_sock = accept(ser_sock, (struct sockaddr *)&cln_addr, &cln_addr_size);
    if(cln_sock == -1)
    {
        puts("accept error!");
        exit(1);
    }
    char c;
    read(cln_sock, &c, 1);
    write(cln_sock, &message[c - '0'], 1);
    close(ser_sock);
    close(cln_sock);
}

void tell_server_message(void* message, long long siz)
{
    int sock;
    struct sockaddr_in serv_addr;
}

void tell_ser(void* message, long long siz)
{
    int sock;
    struct sockaddr_in serv_addr;
    // char message[] = {"0123456789"};;
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1) 
    {
        puts("socket error!");
        exit(1);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT_log);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    {
        puts("connect error!");
        exit(1);
    }
    write(sock, &message, siz);
    close(sock);
    // return message[sig] - '0';
}

int tell_cln()
{
    int ser_sock, cln_sock;
    struct sockaddr_in ser_addr, cln_addr;
    char message[100];// = "0123456789";
    ser_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(ser_sock == -1) 
    {
        puts("socket error!");
        exit(1);
    }
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(PORT_log);
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(ser_sock, (struct sockaddr*)&ser_addr, sizeof(ser_addr)) == -1)
    {
        puts("bind error!");
        exit(1);
    }
    if(listen(ser_sock, 1) == -1)
    {
        puts("listen error!");
        exit(1);
    }
    socklen_t cln_addr_size = sizeof(cln_addr);
    cln_sock = accept(ser_sock, (struct sockaddr *)&cln_addr, &cln_addr_size);
    if(cln_sock == -1)
    {
        puts("accept error!");
        exit(1);
    }
    char c;
    read(cln_sock, &c, 1);
    write(cln_sock, &message[c - '0'], 1);
    close(ser_sock);
    close(cln_sock);
}