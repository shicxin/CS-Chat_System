#include <stdbool.h>
#include <time.h>
#include"../lib/mysys.h"
#include"../lib/user.h"
#include"../lib/tell.h"

int main()
{
	bool k = 0;
	int sock = call_ser();
	printf("scok = %d\n", sock);
	cJSON* user = cJSON_CreateObject();
	if(sock < 0) puts("服务器开小差了，请联系管理员");
	else k = 1;
	while(k)
	{
		if(log_or_reg(&user, sock))
		{
			k = 0;
		}
	}
	puts("进入系统！"); 
	cJSON_AddNumberToObject(user, "sock", sock);
	// char* temp = cJSON_Print(user);
	// puts(temp);
	// free(temp);
	puts("你不在线时收到的消息：");
	put_other_tell_from_cjson(user);
	int pid;
	pid = fork();
	if(pid == 0)
	{
		lis_ser(sock);
		exit(0);
	}
	if(pid > 0) 
	{
		talk_who(user);
		exit(0);
	}

	// close(sock);
	return 0;
}