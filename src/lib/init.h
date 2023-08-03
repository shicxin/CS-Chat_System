#if !defined(__INIT__)
#define __INIT__

#include<stdbool.h>
#include "user.h"

/*************server*******************/
void init_ser_file();//检查服务器文件是否存在
void init_ser_sys(HEAD* );//初始化系统设置

/*************clion*******************/
void Welcome_Screen();
void init_cln_file();
void init_cln_sys();

#endif // __INIT__
