#if !defined(__INIT___)
#define __INIT___

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>


#include "cJSON.h"
#include "mycjson.h"
#include "user.h"
#include "tell.h"

#define WHERE_SIZE 50

void init_ser_file();//初始化文件
// void init_user_and_file();//初始化系统链表中的用户与其文件

#endif // __INIT___
 