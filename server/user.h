#if !defined(__USER__)
#define __USER__
#include<arpa/inet.h>
#include<sys/socket.h>

    #if !defined(__CHARSIZE__)
    #define __CHARSIZE__
    #define CHAR_SIZE 20
    #define WHERE_SIZE 50
    #endif // __CHARSIZE__

typedef struct head{
    int all_num;//总用户人数
    // int onli_USER;
    struct user* all_ur;//全部用户
    struct user* onli_ur;//在线用户
}HEAD;

typedef struct Basic_user_information{
    char ID[CHAR_SIZE];//用户ID或群聊ID
    char name[CHAR_SIZE];//用户名或群聊名
    struct Basic_user_information* next;
}Fred_and_Grp;

typedef struct user{
    char ID[CHAR_SIZE];//用户ID或群聊ID
    char name[CHAR_SIZE];//用户名或群聊名
    char pasw[CHAR_SIZE];//用户密码
    char IP[CHAR_SIZE];//当前客户端地址
    struct user *next;
    // struct Basic_user_information *r, *l;
    union {struct Basic_user_information *frdliste, *gropfrd}r;
    union {struct Basic_user_information *groplist, *parent_son}l;
    /*
        当结构体作为系统初始化信息存储时，
            l.frdliste是好友列表，
            r.groplist是群聊列表
            next是下一个用户
        当结构体作为群聊人员时，
            l.gropfrd表示拉自己到群里的人拉的人，
            r.parent_son表示自己拉到群聊中的人拉进群的其他人
    */
}USER;

void writ_neus_to_fi(USER* );//write the new user to the file
void Allocation_ID(USER* , char* ); //分配未被占用的ID,原理：找到目前最大的ID，加一赋值
void add_user(HEAD* );//添加用户
USER* create_user(char* , char* , char* ) ;//创建用户
USER* find_user(USER* );//找用户，找到返回指向该用户节点的指针，否则返回NULL；
USER* logout_user(USER* );//删除用户，参数为指向要删除的用户节点的节点地址，返回删除用户所指的用户的内存节点节点




#endif // __USER__

/////////////////////////////////////////////////////////////////////////////////
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_SIZE 20 //定义字符数组的大小
#define LH +1 //定义左高的平衡因子
#define EH 0 //定义等高的平衡因子
#define RH -1 //定义右高的平衡因子

//定义用户结点的结构体
typedef struct user{
    char ID[CHAR_SIZE];
    char name[CHAR_SIZE];
    char pasw[CHAR_SIZE];
    // 描述 Internet 套接字地址的结构。
     struct sockaddr_in addr;
    char IP[CHAR_SIZE];
    int bf; //balance factor 平衡因子
    struct user *r, *l; //right and left child 右孩子和左孩子
}USER;

//创建一个新的用户结点，并初始化其数据域和指针域
USER* create_user(char* ID, char* name, char* pasw, struct sockaddr_in addr, char* IP) {
    USER* new_user = (USER*)malloc(sizeof(USER)); //分配内存空间
    if (new_user == NULL) { //检查内存分配是否成功
        printf("Memory allocation failed.\n");
        return NULL;
    }
    strcpy(new_user->ID, ID); //复制 ID 到新结点的数据域
    strcpy(new_user->name, name); //复制 name 到新结点的数据域
    strcpy(new_user->pasw, pasw); //复制 pasw 到新结点的数据域
    new_user->addr = addr; //复制 addr 到新结点的数据域
    strcpy(new_user->IP, IP); //复制 IP 到新结点的数据域
    new_user->bf = EH; //初始化平衡因子为 0
    new_user->r = NULL; //初始化右孩子为空
    new_user->l = NULL; //初始化左孩子为空
    return new_user; //返回新结点的指针
}

//计算一个用户结点的高度，如果为空则返回 -1
int height(USER* user) {
    if (user == NULL) {
        return -1;
    }
    else {
        return user->bf;
    }
}

//获取两个数中较大的一个
int max(int a, int b) {
    return (a > b) ? a : b;
}

//对以 p 为根结点的二叉树做右旋处理，令 p 指针指向新的树根结点
void R_Rotate(USER** p) {
    USER* lc = (*p)->l; //获取 p 的左孩子 lc
    (*p)->l = lc->r; //将 lc 的右孩子作为 p 的左孩子
    lc->r = *p; //将 p 作为 lc 的右孩子
    *p = lc; //将 lc 作为新的根结点

    //更新 p 和 lc 的高度和平衡因子
    (*p)->bf = max(height((*p)->l), height((*p)->r)) + 1;
    (*p)->r->bf = max(height((*p)->r->l), height((*p)->r->r)) + 1;
}

//对以 p 为根结点的二叉树做左旋处理，令 p 指针指向新的树根结点
void L_Rotate(USER** p) {
    USER* rc = (*p)->r; //获取 p 的右孩子 rc
    (*p)->r = rc->l; //将 rc 的左孩子作为 p 的右孩子
    rc->l = *p; //将 p 作为 rc 的左孩子
    *p = rc; //将 rc 作为新的根结点

    //更新 p 和 rc 的高度和平衡因子
    (*p)->bf = max(height((*p)->l), height((*p)->r)) + 1;
    (*p)->l->bf = max(height((*p)->l->l), height((*p)->l->r)) + 1;
}

//对以指针 T 所指向结点为根结点的二叉树作左子树的平衡处理，令指针 T 指向新的根结点
void LeftBalance(USER** T) {
    USER* lc, *rd;
    lc = (*T)->l; //获取 T 的左孩子 lc
    switch (lc->bf) { //判断 lc 的平衡因子
        case LH: //如果为 LH，说明在 lc 的左子树上插入了结点，需要进行单向右旋处理
            (*T)->bf = lc->bf = EH; //更新 T 和 lc 的平衡因子为 EH
            R_Rotate(T); //对 T 进行右旋操作
            break;
        case RH: //如果为 RH，说明在 lc 的右子树上插入了结点，需要进行双向旋转（先左后右）处理
            rd = lc->r; //获取 lc 的右孩子 rd
            switch (rd->bf) { //判断 rd 的平衡因子
                case LH: //如果为 LH，说明在 rd 的左子树上插入了结点，需要更新 T 和 lc 的平衡因子
                    (*T)->bf = RH;
                    lc->bf = EH;
                    break;
                case EH: //如果为 EH，说明在 rd 上插入了结点，不需要更新 T 和 lc 的平衡因子
                    (*T)->bf = lc->bf = EH;
                    break;
                case RH: //如果为 RH，说明在 rd 的右子树上插入了结点，需要更新 T 和 lc 的平衡因子
                    (*T)->bf = EH;
                    lc->bf = LH;
                    break;
            }
            rd->bf = EH; //更新 rd 的平衡因子为 EH
            L_Rotate(&(*T)->l); //对 T 的左孩子进行左旋操作
            R_Rotate(T); //对 T 进行右旋操作
            break;
    }
}

//对以指针 T 所指向结点为根结点的二叉树作右子树的平衡处理，令指针 T 指向新的根结点
void RightBalance(USER** T) {
    USER* rc, *ld;
    rc = (*T)->r; //获取 T 的右孩子 rc
    switch (rc->bf) { //判断 rc 的平衡因子
        case RH: //如果为 RH，说明在 rc 的右子树上插入了结点，需要进行单向左旋处理
            (*T)->bf = rc->bf = EH; //更新 T 和 rc 的平衡因子为 EH
            L_Rotate(T); //对 T 进行左旋操作
            break;
        case LH: //如果为 LH，说明在 rc 的左子树上插入了结点，需要进行双向旋转（先右后左）处理
            ld = rc->l; //获取 rc 的左孩子 ld
            switch (ld->bf) { //判断 ld 的平衡因子
                case RH: //如果为 RH，说明在 ld 的右子树上插入了结点，需要更新 T 和 rc 的平衡因子
                    (*T)->bf = LH;
                    rc->bf = EH;
                    break;
                case EH: //如果为 EH，说明在 ld 上插入了结点，不需要更新 T 和 rc 的平衡因子
                    (*T)->bf = rc->bf = EH;
                    break;
                case LH: //如果为 LH，说明在 ld 的左子树上插入了结点，需要更新 T 和 rc 的平衡因子
                    (*T)->bf = EH;
                    rc->bf = RH;
                    break;
            }
            ld->bf = EH; //更新 ld 的平衡因子为 EH
            R_Rotate(&(*T)->r); //对 T 的右孩子进行右旋操作
            L_Rotate(T); //对 T 进行左旋操作
            break;
    }
}

//向 AVL 树中插入一个新的用户结点，并返回是否成功和是否长高的标志位
int InsertAVL(USER** T, USER* new_user, int* taller) {
    if (*T == NULL) { //如果当前结点为空，说明找到了插入位置
        *T = new_user; //将新结点插入到当前位置
        *taller = 1; //设置长高标志位为 1
    }
    else { //如果当前结点不为空，继续递归查找插入位置
        if (strcmp(new_user->ID, (*T)->ID) == 0) { //如果新结点的 ID 与当前结点的 ID 相同，说明已经存在相同 ID 的用户，无法插入
            printf("The user with ID %s already exists.\n", new_user->ID);
            *taller = 0; //设置长高标志位为 0
            return 0; //返回失败标志位 0
        }
        else if (strcmp(new_user->ID, (*T)->ID) < 0) { //如果新结点的 ID 小于当前结点的 ID，说明应该在当前结点的左子树中插入
            if (!InsertAVL(&(*T)->l, new_user, taller)) { //递归地在左子树中插入新结点，并返回是否成功和是否长高的标志位
                return 0; //如果插入失败，返回失败标志位 0
            }
            if (*taller) { //如果插入成功并且左子树长高了，需要检查当前结点的平衡因子
                switch ((*T)->bf) { //判断当前结点的平衡因子
                    case LH: //如果为 LH，说明在当前结点的左子树上插入了结点，导致左子树更高，需要进行左子树的平衡处理
                        LeftBalance(T); //对当前结点进行左子树的平衡处理
                        *taller = 0; //设置长高标志位为 0
                        break;
                    case EH: //如果为 EH，说明在当前结点的左子树上插入了结点，导致左右子树等高，只需要更新当前结点的平衡因子
                        (*T)->bf = LH; //更新当前结点的平衡因子为 LH
                        *taller = 1; //设置长高标志位为 1
                        break;
                    case RH: //如果为 RH，说明在当前结点的左子树上插入了结点，导致左右子树平衡，只需要更新当前结点的平衡因子
                        (*T)->bf = EH; //更新当前结点的平衡因子为 EH
                        *taller = 0; //设置长高标志位为 0
                        break;
                }
            }
        }
        else { //如果新结点的 ID 大于当前结点的 ID，说明应该在当前结点的右子树中插入
            if (!InsertAVL(&(*T)->r, new_user, taller)) { //递归地在右子树中插入新结点，并返回是否成功和是否长高的标志位
                return 0; //如果插入失败，返回失败标志位 0
            }
            if (*taller) { //如果插入成功并且右子树长高了，需要检查当前结点的平衡因子
                switch ((*T)->bf) { //判断当前结点的平衡因子
                    case LH: //如果为 LH，说明在当前结点的右子树上插入了结点，导致左右子树平衡，只需要更新当前结点的平衡因子
                        (*T)->bf = EH; //更新当前结点的平衡因子为 EH
                        *taller = 0; //设置长高标志位为 0
                        break;
                    case EH: //如果为 EH，说明在当前结点的右子树上插入了结点，导致右子树更高，只需要更新当前结点的平衡因子
                        (*T)->bf = RH; //更新当前结点的平衡因子为 RH
                        *taller = 1; //设置长高标志位为 1
                        break;
                    case RH: //如果为 RH，说明在当前结点的右子树上插入了结点，导致右子树更高，需要进行右子树的平衡处理
                        RightBalance(T); //对当前结点进行右子树的平衡处理
                        *taller = 0; //设置长高标志位为 0
                        break;
                }
            }
        }
    }
    return 1; //返回成功标志位 1
}

//从 AVL 树中删除一个用户结点，并返回是否成功和是否缩短的标志位
int DeleteAVL(USER** T, char* ID, int* shorter) {
    if (*T == NULL) { //如果当前结点为空，说明没有找到要删除的用户，无法删除
        printf("The user with ID %s does not exist.\n", ID);
        *shorter = 0; //设置缩短标志位为 0
        return 0; //返回失败标志位 0
    }
    else { //如果当前结点不为空，继续递归查找要删除的用户
        if (strcmp(ID, (*T)->ID) == 0) { //如果当前结点的 ID 与要删除的 ID 相同，说明找到了要删除的用户
            USER* q = NULL; //定义一个临时指针 q
            if ((*T)->l == NULL) { //如果当前结点没有左孩子，只需要用右孩子替换当前结点
                q = *T; //将当前结点赋值给 q
                *T = (*T)->r; //将右孩子赋值给 T
                free(q); //释放 q 所指向的内存空间
                *shorter = 1; //设置缩短标志位为 1
            }
            else if ((*T)->r == NULL) { //如果当前结点没有右孩子，只需要用左孩子替换当前结点
                q = *T; //将当前结点赋值给 q
                *T = (*T)->l; //将左孩子赋值给 T
                free(q); //释放 q 所指向的内存空间
                *shorter = 1; //设置缩短标志位为 1
            }
            else { //如果当前结点既有左孩子又有右孩子，需要用左子树中最大的结点或右子树中最小的结点来替换当前结点，并删除原来的那个结点
                q = (*T)->l; //将左孩子赋值给 q
                while (q->r != NULL) { //循环找到左子树中最大的结点 q
                    q = q->r;
                }
                strcpy((*T)->ID, q->ID); //复制 q 的 ID 到当前结点的数据域
                strcpy((*T)->name, q->name); //复制 q 的 name 到当前结点的数据域
                strcpy((*T)->pasw, q->pasw); //复制 q 的 pasw 到当前结点的数据域
                (*T)->addr = q->addr; //复制 q 的 addr 到当前结点的数据域
                strcpy((*T)->IP, q->IP); //复制 q 的 IP 到当前结点的数据域
                DeleteAVL(&(*T)->l, q->ID, shorter); //递归地在左子树中删除 q 结点，并返回是否成功和是否缩短的标志位
            }
        }
        else if (strcmp(ID, (*T)->ID) < 0) { //如果要删除的 ID 小于当前结点的 ID，说明应该在当前结点的左子树中删除
            if (!DeleteAVL(&(*T)->l, ID, shorter)) { //递归地在左子树中删除用户，并返回是否成功和是否缩短的标志位
                return 0; //如果删除失败，返回失败标志位 0
            }
            if (*shorter) { //如果删除成功并且左子树缩短了，需要检查当前结点的平衡因子
                switch ((*T)->bf) { //判断当前结点的平衡因子
                    case LH: //如果为 LH，说明在当前结点的左子树上删除了结点，导致左右子树平衡，只需要更新当前结点的平衡因子
                        (*T)->bf = EH; //更新当前结点的平衡因子为 EH
                        *shorter = 1; //设置缩短标志位为 1
                        break;
                    case EH: //如果为 EH，说明在当前结点的左子树上删除了结点，导致右子树更高，只需要更新当前结点的平衡因子
                        (*T)->bf = RH; //更新当前结点的平衡因子为 RH
                        *shorter = 0; //设置缩短标志位为 0
                        break;
                    case RH: //如果为 RH，说明在当前结点的左子树上删除了结点，导致右子树更高，需要进行右子树的平衡处理
                        RightBalance(T); //对当前结点进行右子树的平衡处理
                        if ((*T)->r->bf == EH) { //如果右孩子的平衡因子为 EH，说明删除后不会缩短
                            *shorter = 0; //设置缩短标志位为 0
                        }
                        else { //否则，说明删除后会缩短
                            *shorter = 1; //设置缩短标志位为 1
                        }
                        break;
                }
            }
        }
        else { //如果要删除的 ID 大于当前结点的 ID，说明应该在当前结点的右子树中删除
            if (!DeleteAVL(&(*T)->r, ID, shorter)) { //递归地在右子树中删除用户，并返回是否成功和是否缩短的标志位
                return 0; //如果删除失败，返回失败标志位 0
            }
            if (*shorter) { //如果删除成功并且右子树缩短了，需要检查当前结点的平衡因子
                switch ((*T)->bf) { //判断当前结点的平衡因子
                    case LH: //如果为 LH，说明在当前结点的右子树上删除了结点，导致左子树更高，需要进行左子树的平衡处理
                        LeftBalance(T); //对当前结点进行左子树的平衡处理
                        if ((*T)->l->bf == EH) { //如果左孩子的平衡因子为 EH，说明删除后不会缩短
                            *shorter = 0; //设置缩短标志位为 0
                        }
                        else { //否则，说明删除后会缩短
                            *shorter = 1; //设置缩短标志位为 1
                        }
                        break;
                    case EH: //如果为 EH，说明在当前结点的右子树上删除了结点，导致左右子树等高，只需要更新当前结点的平衡因子
                        (*T)->bf = LH; //更新当前结点的平衡因子为 LH
                        *shorter = 0; //设置缩短标志位为 0
                        break;
                    case RH: //如果为 RH，说明在当前结点的右子树上删除了结点，导致左右子树平衡，只需要更新当前结点的平衡因子
                        (*T)->bf = EH; //更新当前结点的平衡因子为 EH
                        *shorter = 1; //设置缩短标志位为 1
                        break;
                }
            }
        }
    }
    return 1; //返回成功标志位 1
}
*///////////////////////////////////////////////////////////////////////