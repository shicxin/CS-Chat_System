#include "mysys.h"

// void read_childproc(int sig)
// {
//     pid_t pid;
//     int status;
//     pid = waitpid(-1, &status, WNOHANG);
//     printf("removed proc id : %d \n", pid);
// }

/// @brief 一个进程专门管理用户
void manage_user(int red_fd, int wrt_fd)
{
    HEAD head;
    head.all_us = NULL;
    head.onli_us = NULL;
    // int fd = open(USER_MANAGE_FIRE, O_RDWR);
    puts("子进程打开管道，等待接收维护请求");
    cJSON *json;
    SOCKNOTE* user;
    int DO;
    // char* message;
    while (1)
    {
        puts("子进程收到消息：");
        read_DO_message(red_fd, &DO, &json);
        if(DO == 10)
        {
            json->next = head.all_us;
            head.all_us = json;
            char str[USER_ID_SIZE];
            sprintf(str, "%ld", time(NULL)%10000 + time(NULL)/10000);
            cJSON_AddStringToObject(json, "ID", str);
            DO = 98;
        }
        else if(DO == 11)
        {
            user = (SOCKNOTE*) malloc (sizeof(SOCKNOTE));
            puts("接收套接字！");
            user->sock = recv_fd(red_fd);///???????????????????///////////??????????????????
    cJSON* messa = cJSON_CreateObject();
    cJSON_AddStringToObject(messa, "message", "客户端你好, 我是用户管理进程！！\0");
    talk_DO_message(user->sock, 55,messa);
    cJSON_Delete(messa);
            puts("准备找人");
            cJSON* tmp = find_user_all(head.all_us, json);
            if(tmp != NULL && strcmp(get_pasw_from_cjson(tmp), get_pasw_from_cjson(json)) == 0)
            {
                user->user = cJSON_Duplicate(json, 1);
                user->next = head.onli_us;
                head.onli_us = user;
                DO = 98;
                // puts("告诉所有人有人登录！");
                // tell_all(33, head.onli_us, json);
            }
            else 
            {
                free(user);
                DO = 99;
            }
            tmp = NULL;
        }
        else if(DO == 31)
        {
            puts("子进程准备发送中····················");
    char* tmp = cJSON_Print(json);
    puts(tmp);
    free(tmp);
            SOCKNOTE* tep = find_user_online(head.onli_us, json);
            if(tep == NULL) puts("？？？？？？？？？？user为空？？？？？？？？？？");
            // char* tem = cJSON_Print(user);
            // puts(tem);
            // free(tem);
            if(tep != NULL)
            {
                printf("准备给%s发送内容%s，套接字为%d", get_ID_from_cjson(tep->user), get_message_from_cjson(json), get_sock_from_cjson(tep->user));
                puts("子进程转发消息中··············：");
                DO = 97;
                talk_DO_message(tep->sock, DO, tep->user);
            }
            else 
            {
                ///暂存
                puts("用户未上线");
            }
        }
        else if(DO == 32)
        {
            DO = 31;
            // cJSON* user = head.onli_us;
            tell_all(DO, head.onli_us, json);
            DO = 98;
            puts("返回消息");
            talk_DO_message(get_sock_from_cjson(json), DO, json);
            // cjson
            // while()?????????????????????????????????????????????
        }
    puts("子进程发的消息：");
    talk_DO_message(wrt_fd, DO, json);
    puts("全部用户链表：");
    look_all_list(head.all_us);
    puts("在线用户链表：");
    look_online_list(head.onli_us);
        // writ_file_user(head.all_us);
    }
}


/// @brief 服务端接收客户端的登录请求以及其他功能
/// @param sock 当前客户端的socket
void Client_functionality (int sock, int wrt_fd, int red_fd)
{
    bool k1 = 1, k2 = 0;
    while(k1)
    {
        if(Login_registered(sock, wrt_fd, red_fd))
        {
            k1 = 0;
            k2 = 1;
        }
    }
    //进入程序功能
    while(k2)
    {
        puts("可以接收信息了");
        forward_message(sock, wrt_fd, red_fd);
    }
}

/// @brief 服务端登录或注册
/// @param sock 当前客户端的socket
/// @param wrt_fd 通讯管道，用于写
/// @param read_fd 通讯管道，用于读
/// @return 是否成功登录
bool Login_registered( int sock, int wrt_fd, int read_fd)
{
    // int fd = open(USER_MANAGE_FIRE, O_RDWR);
    bool check = 0;
    char* message = (char*) malloc (sizeof(char) * HEADER_SIZE + 1);
    int DO;
    cJSON* x;
    puts("收到：");
    read_DO_message(sock, &DO, &x);
    if(DO == 11) 
    {
        cJSON_AddNumberToObject(x, "sock", sock);
    }
    int sig = DO;
    free(message);
    message = (char*)malloc(sizeof(*message) * HEADER_SIZE);
    // printf("套接字为%d", sock);
    puts("发给子进程：");
    talk_DO_message(wrt_fd, DO, x);
    if(DO == 11) 
    {
        send_fd(wrt_fd, sock);
    }
    puts("接收的消息");
    read_DO_message(read_fd, &DO, &x);
    puts("发给客户端：");
    talk_DO_message(sock, DO, x);
    if(sig == 11 && DO == 98) check = 1;
    return check;
}

/// @brief 客户端登录注册界面
/// @param head 系统头结点
/// @return 是否登录成功
bool log_or_reg(cJSON* cln, int sock)
{
    cJSON* user = cJSON_CreateObject();
    puts("你想要执行什么操作：（登录0、注册1、其余任意键无效）");
	char c[2];
	memset(c, 0, sizeof(c));
	scanf("%s", c);
	int sig = c[0] - '0';
//！！！！！！！！！！收集信息！！！！！！！！！！！！！
	if(sig == 1)//注册信号
	{
		bool k = 1;sig = 10;
        char pas1[CHAR_SIZE];
        char pas2[CHAR_SIZE];
        char name[CHAR_SIZE];
        printf("请输入用户名:\t");
        scanf("%s", name);
		while(k)
		{
			printf("请输密码:\t");
			scanf("%s", pas2);
			printf("请确认密码:\t");
			scanf("%s", pas1);
			if(strcmp(pas1, pas2) == 0) k = 0;
			else puts("two different passwords");
		}
        cJSON_AddStringToObject(user, "name", name);
        cJSON_AddStringToObject(user, "pasw", pas1);
	}
	else if(sig == 0)//登录
	{
        char ID[CHAR_SIZE];
        char pas[CHAR_SIZE];
		sig = 11;
		printf("请输入用户ID:\t");
		scanf("%s", ID);
		printf("请输密码:\t");
		scanf("%s", pas);
        cJSON_AddStringToObject(user, "ID", ID);
        cJSON_AddStringToObject(user, "pasw", pas);
	}
    int DO = sig;
    puts("发客户端：");
    talk_DO_message(sock, sig, user);
    if(DO == 11)
    {
        puts("管理进程发：");
        read_DO_message(sock, &sig, &cln);
    }
    puts("客户端收：");
    read_DO_message(sock, &sig, &cln);
    printf("DO = %d, sig = %d\n",DO, sig);
    if(sig == 98 && DO == 10)
    {
        puts("注册成功！");
    } 
    else if(sig == 98 && DO == 11) 
    {
        puts("客户端登录成功！");
        return 1;
    }
    return 0;
}

/// @brief 客户端监听系统
/// @param user 当前用户
/// @param wrt_fd 写管道
/// @param read_fd 读管道
// void lis_ser(cJSON* user, int wrt_fd, int read_fd)
void lis_ser(int sock)
{
    int DO;
    cJSON* json;
    while(1)
    {
        read_DO_message(sock, &DO, &json);
char* tep = cJSON_Print(json);
puts(tep);
free(tep);
        if(DO == 98) puts("发送成功！");
        if(DO == 99) puts("对方不在线！已暂存");
        if(DO == 97) 
        {
            char* who = get_who_from_cjson(json);
            char* message = get_message_from_cjson(json);
            printf("%s发给你%s", who, message);
            cJSON_Delete(json);
        }
        if(DO == 33) puts("有好友上线！");
    }
}

/// @brief 客户端聊天系统
// void talk_who(cJSON* user, int wrt_fd, int read_fd)
void talk_who(cJSON* user)
{
    while(1)
    {
        puts("你想和谁聊天：\n（6个6为所有人）\b\b\b\b\b\b\b\b\b\b\b");
        char ID[CHAR_SIZE];
        scanf("%s", ID);
        puts("你要发的消息是：");
        char* message = (char*) malloc(sizeof(char) * 1000000);
        scanf("%s", message);
        puts("转发中······");
        int DO = 31;
        if(strcmp(ID, "666666") == 0) DO = 32;
        cJSON* json = cJSON_CreateObject();
        cJSON_AddStringToObject(json, "who", ID);
        cJSON_AddStringToObject(json, "message", message);
        cJSON_AddStringToObject(json, "name", get_name_from_cjson(user));
            puts("想看一下nmae, ID, who");
            char* tem = cJSON_Print(json);
            puts(tem);
            free(tem);
        talk_DO_message(get_sock_from_cjson(user), DO, json);
        cJSON_Delete(json);
    }
}

/// @brief 服务端消息转发
/// @param sock 当前客户端的socket
/// @param wrt_fd 通讯管道，用于写
/// @param read_fd 通讯管道，用于读
void forward_message( int sock, int wrt_fd, int read_fd)
{
    int DO;
    cJSON* x;
    puts("收到转发消息：");
    read_DO_message(sock, &DO, &x);
    puts("转发给子进程：");
    talk_DO_message(wrt_fd, DO, x);

    puts("接收子进程的消息");
    read_DO_message(read_fd, &DO, &x);
    puts("发回给客户端：");
    talk_DO_message(sock, DO, x);
}
