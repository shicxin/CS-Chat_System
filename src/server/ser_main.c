#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <asm/signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include"../lib/mysys.h"
#include"../lib/user.h"
#include"../lib/tell.h"
#include"../lib/init.h"

int main()
{
    init_ser_file();//初始化文件夹
    int wrt_fd[2], red_fd[2];
    socketpair( PF_UNIX, SOCK_DGRAM, 0, wrt_fd);
    socketpair( PF_UNIX, SOCK_DGRAM, 0, red_fd);
    puts("初始化文件夹成功");
    // struct sigaction act;
    // act.sa_handler = read_childproc;
    // sigemptyset(&act.sa_mask);
    // act.sa_flags = 0;
    // int state = sigaction(SIGCHLD, &act, 0);
	pid_t pid;
    pid = fork();
    if(pid == 0)
    {
        manage_user(wrt_fd[0], red_fd[1]);
        exit(0);
    }

    int ser_sock;
    struct sockaddr_in ser_addr;
    ser_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(ser_sock == -1)
    {
        puts("socket error!");
        exit(1);
    }
    server_sock_init(&ser_sock, &ser_addr);
    //accept前的准备
    while(1)
    {
        struct sockaddr_in cln_addr;
        socklen_t cln_addr_size = sizeof(cln_addr);
        int sock = get_sock_with_cline(ser_sock, &cln_addr, &cln_addr_size);
        puts("创建一个进程");
        pid = fork();
        if (pid == 0)
        {
            Client_functionality(sock, wrt_fd[1], red_fd[0]);
            puts("关闭套接字");
            close(sock);
            exit(1);
        }
        else if (pid < 0)
        {
            // fork失败
            perror("fork");
            return 1;
        }
        else
        {
            setpgid(pid, 0);
        }
        puts("准备创建下一个进程");
    }

    // 父进程休眠10秒后退出
    sleep(10);
    close(ser_sock);
    printf("server exiting\n");
	return 0;
}