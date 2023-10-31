#if !defined(__USER__)
#define __USER__

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "cJSON.h"
#define USER_ID_SIZE 12

typedef struct socknote{
    int sock;
    cJSON* user;
    struct socknote* next;
}SOCKNOTE;

typedef struct head
{
    cJSON* all_us;
    SOCKNOTE* onli_us;
}HEAD;

int git_cjson_sock();
cJSON* find_user_all(cJSON* , cJSON* );
SOCKNOTE* find_user_online(SOCKNOTE* head, cJSON* user);
void write_user_file_list(cJSON*, cJSON*);

void ADD_other_tell_obj(cJSON* user, cJSON* head, cJSON* tmp);
// git_cjson_();

/*
user Related Information：
string          ID
string          name
string          password
int             socket
*/
 
/*
file header
int             DO
char            len
*/

/*
具体消息
*/

#endif // __USER__
