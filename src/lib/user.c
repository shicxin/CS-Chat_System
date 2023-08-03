#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "user.h"
#include "tell.h"

bool create_or_login(USER* x, char* c) 
{
	if(c[0] == '1')
	{
		USER x;
		printf("请输入用户名:\t");
		scanf("%s", x.name);
		bool k = 1;
		while(k)
		{
			char pas[CHAR_SIZE];
			printf("请输密码:\t");
			scanf("%s", x.pasw);
			printf("请确认密码:\t");
			scanf("%s", pas);
			if(strcmp(pas, x.pasw) == 0) k = 0;
			else puts("two different passwords");
			
		//发送到服务器
			tell_server_signal(0);//注册信号
		//接收服务器是否创建成功的消息
		// int flag = 
		}
	}
	if(c[0] == '0')
	{
		USER x;
		printf("请输入用户名:\t");
		scanf("%s", x.name);
		printf("请输密码:\t");
		scanf("%s", x.pasw);
			
		//发送到服务器
		char c[2] = "1\0";
		tell_ser((void*)&c, sizeof(c));//登录信号
		// tell_server_message((void*)&x, sizeof(USER));
		//接收服务器是否创建成功的消息
		if(x.ID != "")
		{}
	}
	//返回是否登录成功
}

void add_user(HEAD* head)
{
	char name[CHAR_SIZE], pasw[CHAR_SIZE], password[CHAR_SIZE], id[CHAR_SIZE];
	printf("请输入你的用户名字");
	scanf("%s", name);
	while(1)
	{
		printf("请输入你的密码：");
		scanf("%s", password);
		printf("确认你的密码：");
		scanf("%s", pasw);
		if(strcmp(password, pasw) == 0) 
		{
			puts("设置密码成功");
			break;
		}
		else 
		{
			puts("两次密码不一样（请重新输入）");
		}
	}
	Allocation_ID(head->all_ur, id);
	USER* new_user = create_user(name, pasw, id);
	new_user->next = head->all_ur;
	head->all_ur = new_user;
	writ_neus_to_fi(new_user);
	puts("write ok!");
}

/// @brief 更据用户名、密码创建一个用户，自动分配ID
/// @param name 用户名
/// @param pasw 密码
/// @return 用户在内存中的位置
USER* create_user(char* name, char* pasw, char* ID) 
{
	USER* user = (USER*) malloc(sizeof(USER));
	if(user == NULL) puts("创建节点申请内存失败失败！");
	strcpy(user->ID, ID); //复制 ID 到新结点的数据域
	strcpy(user->name, name); //复制 name 到新结点的数据域
	strcpy(user->pasw, pasw); //复制 pasw 到新结点的数据域
	strcpy(user->IP, "\0");//初始化ip
	user->r.frdliste = NULL; //初始化friend为空
	user->l.groplist = NULL; //初始化群聊为空
	return user; //返回新结点的指针
}

/// @brief 分配未被占用的ID
/// @param head 系统用户列表
/// @param id 分配到的ID
void Allocation_ID(USER* head, char* id)
{
	int max = 1000000;
	while(head != NULL)
	{
		max = atoi(head->ID);//找到目前最大的ID
		head = head->next;
	}
	max++;//创建新的最大ID
	sprintf(id, "%d", max);
}

/// @brief 将用户信息写入文件
/// @param user 用户信息
void writ_neus_to_fi(USER* user)
{
	char fnm[WHERE_SIZE] = "./data/user/\0";
	strcat(fnm, user->ID);
	mkdir(fnm, 0777);//创建用户文件夹
	char frdnm[WHERE_SIZE];
	strcpy(frdnm, fnm);
	FILE* fd = NULL, *frdfd = NULL, *grofd = NULL;

	strcat(frdnm, "/firend");//用户好友信息文件
	strcat(fnm, "/group");//用户群聊信息文件
	// puts(frdnm);
	// puts(fnm);
	frdfd = fopen(frdnm, "w");
	grofd = fopen(fnm, "w");
	fd = fopen("./data/sys/all_user", "a");
	if(fd == NULL)
	{
		puts("打开总用户文件夹失败！");
		exit(1);
	}
	if(frdfd == NULL)
	{
		puts("创建新用户文件夹失败！");
		exit(1);
	}
	if(grofd == NULL)
	{
		puts("创建新用户文件夹失败！");
		exit(1);
	}
	fprintf(fd, "%s %s %s\n", user->ID, user->name, user->pasw);//用户ID、用户名、用户密码、
	Fred_and_Grp *f = user->r.frdliste, *g = user->l.groplist;
	while(f != NULL)
	{
		fprintf(frdfd, "%s\n", f->ID);//好友ID
		f = f->next;
	}
	while(g != NULL)
	{
		fprintf(grofd, "%s\n", g->ID);//群聊ID
		g = g->next;
	}
	fclose(fd);
	fclose(frdfd);
	fclose(grofd);

	// user->son.x;
}
