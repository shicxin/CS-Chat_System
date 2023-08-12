#if !defined(__MYCJSON__)
#define __MYCJSON__

#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


#include "user.h"
#include "cJSON.h"

#define HEADER_SIZE 35

/*

双向接收cjson字符串解决方案

先发一个定长的头信息

DO      长度为2的数字
len     下条消息的的长度，定长字符串，长度为

*/

/**********************************************/
char* make_cjson_header(int , size_t );

/********************解析key值为“xxx”的cjson对象*********************/

char* get_who_from_cjson(cJSON *obj);
time_t get_time_from_cjson(cJSON *obj);
char* get_message_from_cjson(cJSON *obj);
size_t get_len_from_cjson(cJSON *obj);
int get_DO_from_cjson(cJSON *obj);
int get_sock_from_cjson(cJSON *obj);

char *get_ID_from_cjson(cJSON *obj);
char *get_name_from_cjson(cJSON *obj);
char *get_pasw_from_cjson(cJSON *obj);
char* get_tell_from_cjson(cJSON *obj);
// char *get__from_cjson(cJSON *obj);


void writ_file_user(cJSON* );
void read_file_user(HEAD* );
void look_all_list(cJSON* );
void look_online_list(SOCKNOTE* );
#endif // __MYCJSON__ 