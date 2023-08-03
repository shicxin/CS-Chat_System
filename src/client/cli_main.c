#include <stdio.h>
#include "../lib/user.h"
#include "../lib/init.h"

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
	USER x;
	bool k = 1;
	int flag = 11;
	while(k)
	{
		puts("你想要执行什么操作：（登录0、注册1、其余任意键退出）");
		char c[2];
		scanf("%s", c);
		int key = atoi(&c[0]);
		printf("%d\n", key);
		if(key != 0 && key != 1) 
		{
			k = 0;
			continue;
		}
		flag = create_or_login(&x, c);
	}
	while(flag < 11 && flag >= 0)
	{
		puts("登录功能");
	}
	return 0;
}