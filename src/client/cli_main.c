#include <stdio.h>
#include <unistd.h>
#include "../lib/user.h"
#include "../lib/init.h"
#include "../lib/tell.h"

#define PUT_OK 0

int main(int argc, char** argv)
{
	if(PUT_OK)
	{
		printf("一共%d, 分别是",argc);
		for(int i = 0; i < argc; i++)
		{
			printf("%s ", argv[i]);
		}
		printf("\n");
	}
	Welcome_Screen();
	USER x;//保存当前用户信息
	bool k = 0;
	int sock;
	sock = call_ser();
	if(sock < 0) puts("服务器开小差了，请联系管理员");
	else k = 1;
	while(k)
	{
		if(create_or_login(&x, &sock) == 0) k = 0;
	}
	int q = 1;
	while(q)
	{
		write(sock, "hello_ser", 10);
		char message[100];
		read(sock, message, 10);
		puts(message);
		break;
	}
	return 0;
}