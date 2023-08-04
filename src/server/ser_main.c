#include<stdio.h>
#include"../lib/init.h"
#include"../lib/user.h"
#include"../lib/tell.h"

#define PUT_OK 0

int main(int argc, char** argv)
{
	// bool* ID_linked_list;
	if(PUT_OK)
	{
		printf("一共%d, 分别是",argc);
		for(int i = 0; i < argc; i++)
		{
			printf("%s ", argv[i]);
		}
	}
	HEAD head;
	init_ser_file();
	init_ser_sys(&head);
	//开始监听端口
	int ser_sock, cln_sock[30];
    struct sockaddr_in ser_addr, cln_addr;
    ser_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(ser_sock == -1) 
    {
        puts("socket error!");
        exit(1);
    }
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    // ser_addr.sin_port = htons(PORT_log);
    printf("监听端口为：");
    int port;
    scanf("%d", &port);
    ser_addr.sin_port = htons(port);
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(ser_sock, (struct sockaddr*)&ser_addr, sizeof(ser_addr)) == -1)
    {
        puts("bind error!");
        exit(1);
    }
    if(listen(ser_sock, 30) == -1)
    {
        puts("listen error!");
        exit(1);
    }
	int i = 0;
	cln_sock[0] = wait_cln(&ser_sock, cln_addr);
	char message[11];
	read(cln_sock[0], message, sizeof(message));
	puts(message);
	strcpy(message, "hello_cln");
	write(cln_sock[0], message, sizeof(message) - 1);
	close(cln_sock[0]);
    close(ser_sock);
	return 0;
}