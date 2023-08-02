#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "init.h"

void Welcome_Screen()
{
	puts("welcome to cs-chat-system");
}

void init_file()
{
	if(access("./data", F_OK) != 0)//判断数据文件夹是否存在
	{
		mkdir("./data", 0777);
	}
	if(access("./data/sys", F_OK) != 0)//判断系统文件夹是否存在
	{
		mkdir("./data/sys", 0777);
	}
	if(access("./data/user", F_OK) != 0)//判断用户文件夹是否存在
	{
		mkdir("./data/user", 0777);
	}
	if (access("./data/system", F_OK) == -1) 
	{
		FILE *fp = fopen("./data/system", "w");
		fclose(fp);
	}
	if (access("./data/sys/all_user", F_OK) == -1) 
	{
		FILE *fp = fopen("./data/sys/all_user", "w");
		fclose(fp);
	}
	//将现有用户存储在链表中，初始化用户聊天记录文件夹
	// if (access("../data/", F_OK) == -1) 
	// {
	//	 FILE *fp = fopen("../data/", "w");
	//	 fclose(fp);
	// }
}

void init_sys(HEAD* head)
{
	head->all_num = 0;
	head->onli_ur = NULL;
	head->all_ur = NULL;
	//打开系统配置文件将配置加载到内存中
	//打开用户文件将用户加载到内存中
	FILE* fd = NULL;
	if((fd = fopen("./data/sys/all_user", "r")) == NULL)
	{
		puts("打开已注册用户文件错误！");
		exit(1);
	}
	USER* usr;
	usr = (USER*)malloc(sizeof(USER));
	while (fscanf(fd, "%s %s %s", usr->ID, usr->name, usr->pasw) != EOF)
	{
		//初始化指针
		usr->next = NULL;
		usr->r.frdliste = NULL;
		usr->l.groplist = NULL;

		char fnm[WHERE_SIZE] = "./data/user/\0";
		strcat(fnm, usr->ID);
		//检测是否存在某个用户的文件夹，不存在则创建
		if(access(fnm, F_OK) != 0)
			mkdir(fnm, 0777);//创建用户文件夹
		char frdnm[WHERE_SIZE];
		strcpy(frdnm, fnm);
		strcat(frdnm, "/firend");//用户好友信息文件
		strcat(fnm, "/group");//用户群聊信息文件
		FILE* fd = NULL, *frdfd = NULL, *grofd = NULL;
		// puts(frdnm);
		// puts(fnm);
		//分别打开好友与群聊文件，不存在则创建
		frdfd = fopen(frdnm, "w");
		grofd = fopen(fnm, "w");

		Fred_and_Grp *frd = NULL, *grop = NULL;
		frd = (Fred_and_Grp*)malloc(sizeof(frd));
		while (fscanf(frdfd, "%s", frd->ID) != EOF)
		{
			frd->next = usr->r.frdliste;
			usr->r.frdliste = frd;
			frd = (Fred_and_Grp*)malloc(sizeof(frd));
		}

		grop = (Fred_and_Grp*)malloc(sizeof(grop));
		while (fscanf(grofd, "%s", grop->ID) != EOF)
		{
			grop->next = usr->l.groplist;
			usr->l.groplist = grop;
			grop = (Fred_and_Grp*)malloc(sizeof(grop));
		}

		free(frd); free(grop);
		usr = (USER*)malloc(sizeof(USER));
	}
	free(usr);
}