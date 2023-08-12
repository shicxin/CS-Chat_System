# cJSON

`cJSON`是一个使用C语言编写的轻量级的`JSON`库，它可以方便地创建、解析和处理`cJSON`数据。`JSON`是一种常用的数据交换格式，它可以表示对象、数组、字符串、数字、布尔值和空值。`JSON`在网络通信和数据存储中广泛使用，因为它具有简洁、易读、跨平台的特点。

## cjson结构体

```c
typedef struct cJSON
{
    /* next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem */
     /* 允许您遍历数组/对象链. 或者, 使用获取数组大小/获取数组项/获取对象项 */
    struct cJSON *next;
    struct cJSON *prev;
    /* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */   
    /* 数组或对象项将有一个指向数组/对象中的项链的子指针。 */
    struct cJSON *child;

    /* The type of the item, as above. */
    /* 项目的类型 */
    int type;

    /* The item's string, if type==cJSON_String  and type == cJSON_Raw */
     /* 项目的字符串，如果type==cJSON_String和type== cJSON_Raw */
    char *valuestring;
    /* writing to valueint is DEPRECATED, use cJSON_SetNumberValue instead */
    /* 写入valueint已被弃用，请使用cJSON_SetNumberValue代替 */
    int valueint;
    /* The item's number, if type==cJSON_Number */
    /* 项目的编号，如果type==cJSON编号r */
    double valuedouble;

    /* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
    /* 如果该项是对象的子项或在对象的子项列表中，则为该项的名称字符串。 */
    char *string;
} cJSON;
```



## 创建JSON对象

-   `cJSON_CreateObject`：这个函数用于创建一个空的JSON对象，返回一个指向根节点的指针。例如：

```c
cJSON *root = cJSON_CreateObject(); // 创建一个空的JSON对象
```

### 创建JSON节点

#### 字符串

-   `cJSON_CreateString`：这个函数用于创建一个字符串类型的JSON节点，传入一个字符串参数，返回一个指向节点的指针。例如：

```c
cJSON *name = cJSON_CreateString("Tom"); // 创建一个字符串类型的节点
if (name == NULL) {
  printf("Create error\n");
  return -1;
}
```

#### 数字

-   `cJSON_CreateNumber`：这个函数用于创建一个数字类型的JSON节点，传入一个数字参数，返回一个指向节点的指针。例如：

```c
cJSON *age = cJSON_CreateNumber(18); // 创建一个数字类型的节点
if (age == NULL) {
  printf("Create error\n");
  return -1;
}
```

#### 布尔

-   `cJSON_CreateBool`：这个函数用于创建一个布尔类型的JSON节点，传入一个布尔参数，返回一个指向节点的指针。例如：

```c
cJSON *male = cJSON_CreateBool(true); // 创建一个布尔类型的节点
if (male == NULL) {
  printf("Create error\n");
  return -1;
}
```

#### 指向一个JSON对象中的某个节点

-   `cJSON_CreateNull`：这个函数用于创建一个空值类型的JSON节点，不需要参数，返回一个指向节点的指针。例如：

```c
cJSON *address = cJSON_CreateNull(); // 创建一个空值类型的节点
if (address == NULL) {
  printf("Create error\n");
  return -1;
}
```

#### 创建一个JSON数组节点

-   `cJSON_CreateArray`：这个函数用于创建一个数组类型的JSON节点，不需要参数，返回一个指向节点的指针。例如：

```c
cJSON *hobbies = cJSON_CreateArray(); // 创建一个数组类型的节点
if (hobbies == NULL) {
  printf("Create error\n");
  return -1;
}
```

## 向JSON对象中添加元素

### 向JSON对象中添加子节点

-   `cJSON_AddItemToObject`：这个函数用于向一个`JSON`对象中添加一个子节点，传入三个参数：一个指向父节点的指针，一个字符串参数表示子节点的名称，一个指向子节点的指针。例如：

```c
cJSON *root = cJSON_CreateObject(); // 创建一个空的JSON对象
cJSON *name = cJSON_CreateString("Tom"); // 创建一个字符串类型的节点
cJSON_AddItemToObject(root, "name", name); // 向root对象中添加name节点
```

### 向JSON数组中添加一个节点

-   `cJSON_AddItemToArray`：这个函数用于向一个`JSON`数组中添加一个元素，传入两个参数：一个指向数组节点的指针，一个指向元素节点的指针。例如：

```c
cJSON *hobbies = cJSON_CreateArray(); // 创建一个空的JSON数组
cJSON *reading = cJSON_CreateString("reading"); // 创建一个字符串类型的节点
cJSON_AddItemToArray(hobbies, reading); // 向hobbies数组中添加reading元素
```

### 向JSON对象中添加元素，类型为Xxx

-   `cJSON_Add-XxxToObject`：这些函数是一些便捷的函数，用于直接向一个`JSON`对象中添加不同类型的子节点，不需要先创建子节点，只需要传入父节点指针、子节点名称和子节点值即可。

```c
cJSON *root = cJSON_CreateObject(); // 创建一个空的JSON对象
cJSON_AddStringToObject(root, "name", "Tom"); // 直接向root对象中添加一个字符串类型的name节点，值为"Tom"
cJSON_AddNumberToObject(root, "age", 18); // 直接向root对象中添加一个数字类型的age节点，值为18
```

### 向JSON数组中添加一个元素

-   `cJSON_InsertItemInArray`：这个函数用于向一个`JSON`数组中插入一个元素，传入三个参数：一个指向数组节点的指针，一个整数参数表示插入的位置，一个指向元素节点的指针。例如：

```c
cJSON *hobbies = cJSON_CreateArray(); // 创建一个空的JSON数组
cJSON *reading = cJSON_CreateString("reading"); // 创建一个字符串类型的节点
cJSON *music = cJSON_CreateString("music"); // 创建一个字符串类型的节点
cJSON_AddItemToArray(hobbies, reading); // 向hobbies数组中添加reading元素
cJSON_InsertItemInArray(hobbies, 0, music); // 向hobbies数组中在第0个位置插入music元素
```

### 替换JSON数组中的一个元素

-   `cJSON_ReplaceItemInArray`：这个函数用于替换一个`JSON`数组中的一个元素，传入三个参数：一个指向数组节点的指针，一个整数参数表示替换的位置，一个指向新元素节点的指针。例如：

```c
cJSON *hobbies = cJSON_CreateArray(); // 创建一个空的JSON数组
cJSON *reading = cJSON_CreateString("reading"); // 创建一个字符串类型的节点
cJSON *music = cJSON_CreateString("music"); // 创建一个字符串类型的节点
cJSON *sports = cJSON_CreateString("sports"); // 创建一个字符串类型的节点
cJSON_AddItemToArray(hobbies, reading); // 向hobbies数组中添加reading元素
cJSON_AddItemToArray(hobbies, music); // 向hobbies数组中添加music元素
cJSON_ReplaceItemInArray(hobbies, 1, sports); // 替换hobbies数组中第1个位置的元素为sports元素
```

### 替换一个JSON节点

-   `cJSON_ReplaceItemInObject`：这个函数用于替换一个`JSON`对象中的一个子节点，传入三个参数：一个指向父节点的指针，一个字符串参数表示子节点的名称，一个指向新子节点的指针。例如：

```c
cJSON *root = cJSON_CreateObject(); // 创建一个空的JSON对象
cJSON *name = cJSON_CreateString("Tom"); // 创建一个字符串类型的节点
cJSON *age = cJSON_CreateNumber(18); // 创建一个数字类型的节点
cJSON *gender = cJSON_CreateString("male"); // 创建一个字符串类型的节点
cJSON_AddItemToObject(root, "name", name); // 向root对象中添加name节点
cJSON_AddItemToObject(root, "age", age); // 向root对象中添加age节点
cJSON_ReplaceItemInObject(root, "age", gender); // 替换root对象中age节点为gender节点
```

## 将JSON对象转化为JSON格式的字符串

```c
const char *json = "{\"name\":\"Tom\",\"age\":18}";
cJSON *root = cJSON_Parse(json); // 解析json字符串
if (root == NULL) {
  printf("Parse error\n");
  return -1;
}
```

## 将JSON格式的字符串转化为JSON对象

```c
cJSON *root = cJSON_CreateObject(); // 创建一个空的json对象
cJSON_AddStringToObject(root, "name", "Tom"); // 添加一个字符串类型的键值对
cJSON_AddNumberToObject(root, "age", 18); // 添加一个数字类型的键值对
char *json = cJSON_Print(root); // 转换成格式化的json字符串
if (json == NULL) {
  printf("Print error\n");
  return -1;
}
printf("%s\n", json); // 输出json字符串
```

## 根据键值提取JSON中的某一个元素

```c
cJSON_GetObjectItem(cJSON, key);//传入cJSON对象与想要分离的键值，返回一个被分离的JSON对象
```

### 判断子节点的类型与值

```c
//判断其类型是否为字符串
cJSON *name = cJSON_GetObjectItem(root, "name");
if (name == NULL || name->type != cJSON_String)
{
    printf("Invalid name\n");
    return -1;
}
//判断其类型是否为数字
cJSON *age = cJSON_GetObjectItem(root, "age");
if (age == NULL || age->type != cJSON_Number)
{
    printf("Invalid age\n");
    return -1;
}
//并判断其类型是否为布尔值
cJSON *male = cJSON_GetObjectItem(root, "male");
if (male == NULL || male->type != cJSON_True)
{
    printf("Invalid male\n");
    return -1;
}
```



## 释放JSON对象

-   当你使用`cJSON_Print`函数将一个`cJSON`对象转换成一个`JSON`字符串时，它也会动态分配内存来创建一个字符串。当你不再需要这个字符串时，你应该使用`free`函数释放它占用的内存，否则也会造成内存泄漏；

-   当你使用`cJSON_Parse`函数解析一个`JSON`字符串时，它会动态分配内存来创建一个`cJSON`对象。当你不再需要这个对象时，你应该使用`cJSON_Delete`函数释放它占用的内存，否则会造成内存泄漏。

```c
cJSON *root = cJSON_CreateObject(); // 创建一个空的json对象
cJSON_AddStringToObject(root, "name", "Tom"); // 添加一个字符串类型的键值对
cJSON_AddNumberToObject(root, "age", 18); // 添加一个数字类型的键值对
char *json = cJSON_Print(root); // 转换成格式化的json字符串
printf("%s\n", json); // 输出json字符串
free(json); // 释放内存

const char *json = "{\"name\":\"Tom\",\"age\":18}";
cJSON *root = cJSON_Parse(json); // 解析json字符串
// do something with root
cJSON_Delete(root); // 释放内存
```

