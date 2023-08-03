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
	int sig = 10;
	// pid_t pid;
	while(sig >= 0 && sig <= 10)
	{
		sig = tell_client_signal();//接收信号
		// switch (sig)
		// {
		// case 0:
		// 	puts("有客户端注册！");
		// 	pid = fork();
		// 	break;
		// default:
		// 	puts("接收到的消息不合法");
		// 	break;
		// }
		// if(pid<0)break;
	}
	//子进程内容
	// if(pid<0)
	// {
	// 	puts("进入子进程");
	// 	switch (sig)
	// 	{
	// 	case 0:
	// 		puts("注册进程启动");
	// 		pid = fork();
	// 		break;
	// 	case 1:
	// 		puts("有客户端登录！");
	// 		pid = fork();
	// 		break;
	// 	default:
	// 		puts("接收到的消息不合法");
	// 		break;
	// 	}
	// }
	// else 
	// {
	// 	puts("服务端崩溃！");
	// }
	// add_user(&head);
	return 0;
}