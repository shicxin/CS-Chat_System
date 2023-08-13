#include "mycjson.h"
#include "tell.h"

/// @brief 从cjson对象中解析一个key值为who的值，返回
/// @param obj cjson对象，包含who
/// @return 一个字符串的指针，
char* get_who_from_cjson(cJSON *obj)
{
    cJSON *item = cJSON_GetObjectItem(obj, "who"); // 获取key值为"xxx"的cJSON对象
    if (item == NULL || item->type != cJSON_String) // 判断是否存在且为字符串类型
    {
        return NULL; // 如果不存在或不是字符串类型，返回NULL
    }
    char *str = cJSON_GetStringValue(item); // 获取item所对应的字符串
    return str; // 返回指向该字符串的指针
}

/// @brief 从cjson对象中解析一个key值为time的值，返回
/// @param obj cjson对象，包含time
/// @return 一个时间戳
time_t get_time_from_cjson(cJSON *obj)
{
    time_t result = 0;
    cJSON *item = cJSON_GetObjectItem(obj, "time");
    if (item != NULL) result = item->valueint;
    return result;
}

/// @brief 从cjson对象中解析一个key值为message的值，返回
/// @param obj cjson对象，包含message
/// @return 一个字符串的指针，
char* get_message_from_cjson(cJSON *obj)
{
    cJSON *item = cJSON_GetObjectItem(obj, "message"); // 获取key值为"xxx"的cJSON对象
    if (item == NULL || item->type != cJSON_String) // 判断是否存在且为字符串类型
    {
        return NULL; // 如果不存在或不是字符串类型，返回NULL
    }
    char *str = cJSON_GetStringValue(item); // 获取item所对应的字符串
    return str; // 返回指向该字符串的指针
}

/// @brief 从cjson对象中解析一个key值为len的值，返回下个消息的长度
/// @param obj cjson对象，包含len
/// @return size_t类型的数
size_t get_len_from_cjson(cJSON *obj)
{
    size_t result = 0;
    cJSON *item = cJSON_GetObjectItem(obj, "len");
    if (item != NULL) sscanf(cJSON_GetStringValue(item), "%zu", &result);
    return result;
}

/// @brief 从cjson对象中解析一个key值为DO的值，返回
/// @param obj cjson对象，包含DO
/// @return 一个两位数
int get_DO_from_cjson(cJSON *obj)
{
    int result = -1;
    cJSON *item = cJSON_GetObjectItem(obj, "DO");
    if (item != NULL) result = (int)cJSON_GetNumberValue(item);
    return result;
}

/// @brief 从cjson对象中解析一个key值为sock的值，返回
/// @param obj cjson对象，包含sock
/// @return 一个两位数
int get_sock_from_cjson(cJSON *obj)
{
    int result = -1;
    cJSON *item = cJSON_GetObjectItem(obj, "sock");
    if (item != NULL) result = (int)cJSON_GetNumberValue(item);
    return result;
}

/// @brief 从cjson对象中解析一个key值为ID的值，返回
/// @param obj cjson对象，包含ID
/// @return 一个字符串的指针，
char* get_ID_from_cjson(cJSON *obj)
{
    cJSON *item = cJSON_GetObjectItem(obj, "ID"); // 获取key值为"xxx"的cJSON对象
    if (item == NULL || item->type != cJSON_String) // 判断是否存在且为字符串类型
    {
        return NULL; // 如果不存在或不是字符串类型，返回NULL
    }
    char *str = cJSON_GetStringValue(item); // 获取item所对应的字符串
    return str; // 返回指向该字符串的指针
}

/// @brief 从cjson对象中解析一个key值为name的值，返回
/// @param obj cjson对象，包含name
/// @return 一个字符串的指针，
char* get_name_from_cjson(cJSON *obj)
{
    cJSON *item = cJSON_GetObjectItem(obj, "name"); // 获取key值为"xxx"的cJSON对象
    if (item == NULL || item->type != cJSON_String) // 判断是否存在且为字符串类型
    {
        return NULL; // 如果不存在或不是字符串类型，返回NULL
    }
    char *str = cJSON_GetStringValue(item); // 获取item所对应的字符串
    return str; // 返回指向该字符串的指针
}

/// @brief 从cjson对象中解析一个key值为pasw的值，返回
/// @param obj cjson对象，包含pasw
/// @return 一个字符串的指针，
char* get_pasw_from_cjson(cJSON *obj)
{
    cJSON *item = cJSON_GetObjectItem(obj, "pasw"); // 获取key值为"xxx"的cJSON对象
    if (item == NULL || item->type != cJSON_String) // 判断是否存在且为字符串类型
    {
        return NULL; // 如果不存在或不是字符串类型，返回NULL
    }
    char *str = cJSON_GetStringValue(item); // 获取item所对应的字符串
    return str; // 返回指向该字符串的指针
}

/// @brief 从cjson对象中解析一个key值为tell的值，返回
/// @param obj cjson对象，包含tell
/// @return 一个字符串的指针，
char* get_tell_from_cjson(cJSON *obj)
{
    cJSON *item = cJSON_GetObjectItem(obj, "tell"); // 获取key值为"xxx"的cJSON对象
    if (item == NULL || item->type != cJSON_String) // 判断是否存在且为字符串类型
    {
        return NULL; // 如果不存在或不是字符串类型，返回NULL
    }
    char *str = cJSON_GetStringValue(item); // 获取item所对应的字符串
    return str; // 返回指向该字符串的指针
}

/// @brief 读出消息
/// @param obj 消息对象
void put_other_tell_from_cjson(cJSON* obj)
{
    cJSON* message = cJSON_GetObjectItem(obj, "other_tell");
	int n = cJSON_GetArraySize(message);
    char name[10];
	for(int i = 1; i <= n; i++)
    {
        sprintf(name, "message%d", i);
        cJSON* mes = cJSON_GetObjectItem(message, name);
        time_t tim = get_time_from_cjson(mes);
        char *mess_time = ctime(&tim);
        printf("%s  %s  发给你  %s\n", mess_time, get_tell_from_cjson(mes), get_message_from_cjson(mes));
    }
}


void ADD_other_tell_from_cjson(cJSON* obj, cJSON* message)
{
    cJSON* mes = cJSON_GetObjectItem(obj, "other_tell");
	int n = cJSON_GetArraySize(mes);
    char name[10];
    sprintf(name, "message%d", n+1);
    cJSON_AddItemToObject(mes, name, message);
}

/// @brief 将要发送的cjson格式的头信息解析为cjson对象
/// @param DO 做事情的信号
/// @param len 下条消息的长度
/// @return 可以直接发送的定长消息
char* make_cjson_header(int DO, size_t len)
{
    char* len_str = malloc(sizeof(char) * 10);
    sprintf(len_str, "%0*zu", 9, len + 1);
    cJSON* obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(obj, "DO", DO);
    cJSON_AddStringToObject(obj, "len", len_str);
    char* x = cJSON_Print(obj);
    return x;
}

/// @brief 把cjson用户链表转换为一个cjson对象，写到文件中
/// @param head cjson链表的头结点
void writ_file_user(cJSON* head)
{
    int i = 1;
    char name[10];
    cJSON *cjson = cJSON_CreateObject();
    while (head != NULL) 
    {
        sprintf(name, "user%d", i++);
        cJSON_AddItemToObject(cjson, name, cJSON_Duplicate(head, 1));
        head = head->next;
    }
    char *json_str = cJSON_Print(cjson);
    FILE *fd = fopen("data/test.json", "w");
    fprintf(fd, "%s", json_str);
    fclose(fd);
    cJSON_Delete(cjson);
    free(json_str);
}

/// @brief 把cjson文件加载到cjson链表中
/// @param head cjson链表的头结点
void read_file_user(HEAD* head)
{
    char* json_str;
    FILE* fp = fopen("data/test.json", "r");
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);//根据文件指针位移计算文件大小
    rewind(fp);
    json_str = (char *)malloc(size);
    fread(json_str, 1, size, fp);
    cJSON* cjson = cJSON_Parse(json_str);
    char name[10];
    int n = cJSON_GetArraySize(cjson);
    cJSON* p;
    for(int i = 1; i <= n; i++)
    {
        sprintf(name, "user%d", i);
        p = cJSON_Duplicate(cJSON_GetObjectItem(cjson, name), 1);
        p->next = head->all_us;
        head->all_us = p;
    }
    free(json_str);
    cJSON_Delete(cjson);
}

/// @brief 查看在线链表
/// @param head 链表的头结点
void look_online_list(SOCKNOTE* head)
{
    while(head != NULL)
    {
        printf("Sock = %d\n", head->sock);
        char* json_str = cJSON_Print(head->user);
        puts(json_str);
        free(json_str);
        head = head->next;
    }
if(PUT_OK) puts("over!");
}


/// @brief 查看已注册链表
/// @param head 链表的头结点
void look_all_list(cJSON* head)
{
    while(head != NULL)
    {
        char* json_str = cJSON_Print(head);
        puts(json_str);
        free(json_str);
        head = head->next;
    }
if(PUT_OK) puts("over!");
}


