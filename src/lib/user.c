#include "user.h"
#include "tell.h"
#include "mycjson.h"

/// @brief 把用户写到文件
/// @param head 用户列表
/// @param user 要写的用户
void write_user_file_list(cJSON* head, cJSON* user)
{
    cJSON_AddItemToObject(head, user->string, user);
}

// /// @brief 向用户发消息时使用
// /// @param head 用户头
// /// @param user 要找的人
// /// @return 找到的人
// cJSON* find_user(HEAD* head, cJSON* user)
// {
//     SOCKNOTE* x = cJSON_CreateObject();
//     x = find_user_online(head->onli_us, user);
//     if(x == NULL)
//     x = find_user_all(head->all_us, user);
//     return user;
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
            char* tem = cJSON_Print(head->user);
            puts("当前节点为：");
            puts(tem);
            free(tem);
            printf("%s$$\n%s$$\n", get_ID_from_cjson(head->user), get_who_from_cjson(user));
        if(strcmp(get_ID_from_cjson(head->user), get_who_from_cjson(user)) == 0)
        {
            x->user = cJSON_Duplicate(head->user, true);
            printf("套接字为%d\n", get_sock_from_cjson(x->user));
            break;
        }
        head = head->next;
        // puts("还是这里有异常");
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
            if(PUT_OK) puts("FIND!!!!!");
            cJSON *copy = cJSON_Duplicate(head, true);
            return copy;
        }
        head = head->next;
        puts("找了一个you一个");
    }
    puts("没有找到");
    return NULL;
}
// void del_user(); //删除用户进程
