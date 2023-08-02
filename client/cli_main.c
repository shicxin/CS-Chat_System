#include <stdio.h>
#include "user.h"
#include "init.h"
#include "tell.h"

int main(int argc, char** argv)
{
	Welcome_Screen();
	USER x;
	bool k = 1;
	while(k)
	{
		puts("你想要执行什么操作：（登录0、注册1、其余任意键退出）");
		char c[2];
		scanf("%s", c);
		if(c[0] != '0' || c[0] != '1') 
		{
			k = 0;
			continue;
		}
		bool x = create_or_login(x, c);
	}
	return 0;
}