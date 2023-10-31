#include "tell.h"

/// @brief 初始化服务器套接字
/// @param sock 服务器套接字
/// @param ser_adr 服务器端口，协议信息
void server_sock_init(int* sock, struct sockaddr_in* ser_adr)
{
    memset(ser_adr, 0, sizeof(*ser_adr));
    ser_adr->sin_family = AF_INET;
    int port;
    puts("监听端口：");
    scanf("%d", &port);
    ser_adr->sin_port = htons(port);
    ser_adr->sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(*sock, (const struct sockaddr *) ser_adr, sizeof(*ser_adr)) == -1)
    {
        puts("bind error!");
        exit(1);
    }
    if(listen(*sock,2) == -1)
    {
        puts("listen error!");
        exit(1);
    }
}

/// @brief 创建多进程套接字
/// @param ser_sock 服务器套接字
/// @param addr 保存客户端地址信息
/// @param addr_size 客户端地址长度
/// @return 一个套接字
int get_sock_with_cline(int ser_sock, struct sockaddr_in* addr, socklen_t* addr_size)
{
    int cln_sock = accept(ser_sock, (struct sockaddr *) addr, addr_size);
    if(cln_sock == -1)
    {
        puts("accept error!");
        exit(1);
    }
    return cln_sock;
}

/// @brief 创建与服务器连接的套接字
/// @return 套接字
int call_ser()
{
	int sock;
	struct sockaddr_in serv_addr;
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1) 
	{
		puts("socket error!");
		exit(1);
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	// serv_addr.sin_port = htons(PORT_log);//绑定端口
	printf("监听端口为：");
	int port;
	scanf("%d", &port);
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
	{
		puts("connect error!");
		exit(1);
	}
	return sock;
}

/// @brief 将要发的消息和干的事情发给要发的程序
/// @param fd 要使用文件描述符
/// @param DO 要干的事
/// @param message 消息
void talk_DO_message(int fd, int DO, cJSON* message)
{
    char* temp = cJSON_Print(message);
    char* header = make_cjson_header(DO, strlen(temp));
    write(fd, header, HEADER_SIZE);
    write(fd, temp, strlen(temp));
    if(PUT_OK) puts(header);
    if(PUT_OK) puts(temp);
    if(PUT_OK) puts("");
    if(PUT_OK) puts("");
    free(temp);
    // free(header);puts("??????");
}

/// @brief 接收要干的事与收到的消息
/// @param fd 要使用文件描述符
/// @param DO 接收的要干的事
/// @param message 接收的消息
void read_DO_message(int fd, int* DO, cJSON** message)
{
    char* header = (char*) malloc (sizeof(char) * HEADER_SIZE);
    read(fd, header, HEADER_SIZE);
    cJSON* x = cJSON_Parse(header);
    *DO = get_DO_from_cjson(x);
    // free(message);
    char* temp = (char*)malloc(sizeof(char) * get_len_from_cjson(x));
    if(read(fd, temp, get_len_from_cjson(x)) == 0) exit(0);
    if(PUT_OK) puts(header);
    if(PUT_OK) puts(temp);
    if(PUT_OK) puts("");
    if(PUT_OK) puts("");
    *message = cJSON_Parse(temp);
            // puts("??");
    cJSON_Delete(x);
    free(temp);
    free(header);
            // puts("??");
}

/// @brief 定义一个函数，用来发送文件描述符
/// @param fd 写入描述符
/// @param fd_to_send 要发送的套接字
void send_fd( int fd, int fd_to_send )
{
    struct iovec iov[1];
    struct msghdr msg;
    char buf[0];

    // 设置消息的数据部分，使用一个空字符作为占位符
    iov[0].iov_base = buf;
    iov[0].iov_len = 1;
    // 设置消息的基本信息，不包含任何地址信息
    msg.msg_name    = NULL;
    msg.msg_namelen = 0;
    // 设置消息的数据部分，使用iov数组指定
    msg.msg_iov     = iov;
    msg.msg_iovlen = 1;

    // 定义一个cmsghdr结构体，用来存储辅助数据
    struct cmsghdr cm;
    // 设置辅助数据的长度、级别和类型
    cm.cmsg_len = CONTROL_LEN;
    cm.cmsg_level = SOL_SOCKET;
    cm.cmsg_type = SCM_RIGHTS;
    // 将要发送的文件描述符复制到辅助数据的内容中
    *(int *)CMSG_DATA( &cm ) = fd_to_send;
    // 设置消息的控制部分，使用cm结构体指定
    msg.msg_control = &cm;
    msg.msg_controllen = CONTROL_LEN;

    // 调用sendmsg函数，将消息发送给指定的套接字
    sendmsg( fd, &msg, 0 );
}


/// @brief 定义一个函数，用来接收文件描述符
/// @param fd 读取位置
/// @return 读到的套接字
int recv_fd( int fd )
{
    struct iovec iov[1];
    struct msghdr msg;
    char buf[0];
    // char buf[0];

    // 设置消息的数据部分，使用一个空字符作为占位符
    iov[0].iov_base = buf;
    iov[0].iov_len = 1;
    // 设置消息的基本信息，不包含任何地址信息
    msg.msg_name    = NULL;
    msg.msg_namelen = 0;
    // 设置消息的数据部分，使用iov数组指定
    msg.msg_iov     = iov;
    msg.msg_iovlen = 1;

    // 定义一个cmsghdr结构体，用来存储辅助数据
    struct cmsghdr cm;
    // 设置消息的控制部分，使用cm结构体指定
    msg.msg_control = &cm;
    msg.msg_controllen = CONTROL_LEN;

    // 调用recvmsg函数，从指定的套接字接收消息
    recvmsg( fd, &msg, 0 );

    // 从辅助数据的内容中提取出文件描述符，并返回它
    int fd_to_read = *(int *)CMSG_DATA( &cm );
    return fd_to_read;
}
