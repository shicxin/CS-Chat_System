#include "init.h"
#include "mycjson.h"

void init_ser_file()
{
    if(access("data", F_OK) != 0)//判断数据文件夹是否存在
	{
		mkdir("data", 0777);
        char *err = strerror(errno);
        printf("mkdir failed: %s\n", err);
	}

	// read_file_user(head);

}
