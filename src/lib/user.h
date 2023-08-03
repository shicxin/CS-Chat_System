#if !defined(__USER__)
#define __USER__
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdbool.h>

	#if !defined(__CHARSIZE__)
	#define __CHARSIZE__
	#define CHAR_SIZE 20
	#define WHERE_SIZE 50
	#endif // __CHARSIZE__

typedef struct head{
	int all_num;//总用户人数
	// int onli_USER;
	struct user* all_ur;//全部用户
	struct user* onli_ur;//在线用户
}HEAD;

typedef struct Basic_user_information{
	char ID[CHAR_SIZE];//用户ID或群聊ID
	char name[CHAR_SIZE];//用户名或群聊名
	struct Basic_user_information* next;
}Fred_and_Grp;

typedef struct user{
	char ID[CHAR_SIZE];//用户ID或群聊ID
	char name[CHAR_SIZE];//用户名或群聊名
	char pasw[CHAR_SIZE];//用户密码
	char IP[CHAR_SIZE];//当前客户端地址
	struct user *next;
	// struct Basic_user_information *r, *l;
	union {struct Basic_user_information *frdliste, *gropfrd;} r;
	union {struct Basic_user_information *groplist, *parent_son;} l;
	/*
		当结构体作为系统初始化信息存储时，
			l.frdliste是好友列表，
			r.groplist是群聊列表
			next是下一个用户
		当结构体作为群聊人员时，
			l.gropfrd表示拉自己到群里的人拉的人，
			r.parent_son表示自己拉到群聊中的人拉进群的其他人
	*/
}USER;


/************************server******************************/
bool create_or_login(USER* ,char* );//选择创建或登录
void writ_neus_to_fi(USER* );//将新用户写入文件
void Allocation_ID(USER* , char* ); //分配未被占用的ID,原理：找到目前最大的ID，加一赋值
void add_user(HEAD* );//添加用户
USER* create_user(char* , char* , char* ) ;//创建用户
USER* find_user(USER* );//找用户，找到返回指向该用户节点的指针，否则返回NULL；
USER* logout_user(USER* );//删除用户，参数为指向要删除的用户节点的节点地址，返回删除用户所指的用户的内存节点节点

/************************clion******************************/


#endif // __USER__
