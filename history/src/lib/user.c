#include "user.h"
#include "tell.h"
#include "mycjson.h"

/// @brief 把用户写到文件
/// @param head 用户列表
/// @param user 要写的用户
// void write_user_file_list(cJSON* head, cJSON* user)
// {
//     cJSON_AddItemToObject(head, user->string, user);
// }


/// @brief 在在线用户中寻找人
/// @param head 在线用户链表
/// @param user 要找的人
/// @return 找到的信息或者为NULL
SOCKNOTE* find_user_online(SOCKNOTE* head, cJSON* user)
{
    SOCKNOTE* x = (SOCKNOTE*) malloc (sizeof(SOCKNOTE));
    x->user = NULL;
    while(head != NULL)
    {   
        if(strcmp(get_ID_from_cjson(head->user), get_who_from_cjson(user)) == 0)
        {
            x->user = cJSON_Duplicate(head->user, true);
            x->sock = head->sock;
            printf("在线用户中的套接字为%d\n", x->sock);
            break;
        }
        head = head->next;
    }
    if(x->user == NULL) 
    {
        free(x);
        x = NULL;
    }
    return x;
}

/// @brief 在全部用户中寻找人
/// @param head 用户链表
/// @param user 要找的人
/// @return 找到的信息或者为NULL
cJSON* find_user_all(cJSON* head, cJSON* user)
{
    while(head != NULL)
    {
        if(strcmp(get_ID_from_cjson(head), get_ID_from_cjson(user)) == 0)
        {
            cJSON *copy = cJSON_Duplicate(head, true);
            return copy;
        }
        head = head->next;
    }
    return NULL;
}
// void del_user(); //删除用户进程

void ADD_other_tell_obj(cJSON* user, cJSON* head, cJSON* tmp)
{
    while(head != NULL)
    {
        if(strcmp(get_ID_from_cjson(head), get_ID_from_cjson(user)) == 0)
        {
            // cJSON_AddStringToObject(tmp, "tell", get_name_from_cjson(head));
            ADD_other_tell_from_cjson(head, tmp);
        }
        head = head->next;
    }
}