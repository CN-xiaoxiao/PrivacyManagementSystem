#ifndef MYLIST_H_INCLUDED
#define MYLIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <io.h>
//#include <direct.h>

const int NO_DATA = -1;
const int NOT_FIND = 0;
const int SUCCEED = 1;

typedef struct privacy
{
    int num;   //编号
    char host[64]; //网站域名不超过63字符
    char description[30]; //简单描述
    char name[25];  //账户名
    char password[20];  //密码
}DataElem;

typedef struct Node
{
    DataElem data;
    struct Node *next;
}*LinkList, Node;

//创建链表头结点
LinkList createList()
{
    LinkList listHeadNode = (LinkList)malloc(sizeof(Node));
    listHeadNode->next = NULL;

    return listHeadNode;
}

//创建结点
Node* createNode(DataElem data)
{
    Node * newNode = (Node *)malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

//插入结点(尾插法)
int insertNodeByTail(LinkList listHeadNode, DataElem data)
{
    Node *newNode = createNode(data);

    Node *p = listHeadNode->next;
    Node *pre = listHeadNode;

    while(p != NULL) {
        pre = p;
        p = p->next;
    }

    newNode->next = pre->next;
    pre->next = newNode;

    return SUCCEED;
}
//插入结点(头插法)
void insertNodeByHead(LinkList listHeadNode, DataElem data)
{
    Node *newNode = createNode(data);
    newNode->next = listHeadNode->next;
    listHeadNode->next = newNode;
}

//按编号删除
void deleteNodeByAppion(LinkList listHeadNode, int num)
{
    Node *pre = listHeadNode;
    Node *p = listHeadNode->next;

    if (p == NULL) {
        printf("无相关内容！\n");
        return;
    }
    else {
        while (p->data.num != num) {
            pre = p;
            p = p->next;

            if (p == NULL) {
                printf("删除失败！\n");
                return;
            }
        }

        pre->next = p->next;
        free(p);
    }

}

//按账号名称相关查找
int serchNodeByCorrelationName(LinkList listHeadNode, char name[20])
{
    Node *p = listHeadNode->next;
    int flag;
    char temp[20];
    char t2[20];
    //printf("theFactionYouNeedFind = %s\n------", name);
    if (p == NULL) {
        return NO_DATA;
    }
    else {
        //printf("******\n");
        while(p != NULL) {
            if (p == NULL) break;
            strcpy(temp,p->data.name);
            strcpy(t2,name);
            //printf("dataName = %s  needFind = %s---------\n", temp, t2);
            if (strstr(temp,t2) != NULL) {
                printNode(p);
                flag = SUCCEED;
            }
            memset(temp, 0, strlen(temp)*sizeof(char));
            memset(t2, 0, strlen(t2)*sizeof(char));
            p = p->next;
        }
    }
    return flag;
}


//按编号查找
Node *serchNodeByNum(LinkList listHeadNode, int num)
{
    Node *p = listHeadNode->next;
    if (num < 1 || num > lengthOfList(listHeadNode)){
        return NULL;
    }
    else {
        int i = 1;
        while (i != num) {
            i++;
            p = p->next;
        }
    }

    return p;
}


//error!
int serchNodeByFuzzySearch(LinkList listHeadNode, char name[])
{
    //printf("============Fuzzy1==============\n");
    Node *p = listHeadNode->next;
    int flag = NOT_FIND;
    if (p == NULL) {
        return NO_DATA;
    }
    else {
            //printf("============Fuzzy2==============\n");
        while (p) {
            //printf("============Fuzzy3==============\n");
            flag = newSerch(p->data.name,name);
            //printf("============Fuzzy4==============\n");
            if (flag == SUCCEED) {
                printNode(p);
                return flag;
            }
            //else if (flag == NOT_FIND && p == NULL) {
                //return flag;
            //}
            else if (p == NULL) break;

            p = p->next;
        }
    }
    //printf("=====\n");
    return flag;
}

//error！
int newSerch(char *str1, char *str2)
{
    int i, j, k, flag;
    i = strlen(str1);
    j = strlen(str2);
    printf("-------%d %d \n", i, j);
    flag = 0;

    for (k = 0; k < i; k++) {
        if (str1[k] == str2[flag]) {
            flag++;
        }
        if (flag == j) {
            return SUCCEED;
        }
        else {
            printf("no----\n");
            return NOT_FIND;
        }
    }
}
//模糊查找(error!!!!)
int serch(char *str, char *str2)
{
    char *res;
    printf("=============serch1===========\n");
    res = memchr(str, str2[0], strlen(str));   //根据要查找的字符串第一个字符，切割源字符串
    printf("=============serch2===========\n");
    if (res == NULL)
    {
        printf("find nothing...\n");
        return NOT_FIND;
    }

    int n;
    while (1)
    {
        printf("=============serch3===========\n");
        n = memcmp(res, str2, strlen(str2) - 1); //比较
        printf("=============serch4===========\n");
        if (n != 0)
        {
            if (strlen(res) <= strlen(str2))    //切割出的字符串小于要查找字符串的长度
            {
                printf("find nothing...\n");
                return NOT_FIND;
            }
            else
            {
              //根据要查找的第一个字符继续切割
                res = memchr(res + 1, str2[0], strlen(res));
                if (res == NULL)
                {
                    printf("find nothing...\n");
                    return NOT_FIND;
                }

            }
        }
        else
        { //如果n = 0，找到
            printf("%s is found..\n", str2);
            return SUCCEED;
        }
    }
}

//指定账号是否在数据中
int isNameInList(LinkList listHeadNode, char *name)
{
    Node *p = listHeadNode->next;
    int flag = 0;

    if (p == NULL) {
        return NO_DATA;
    }
    else {
        while(1) {
            if (strstr((p->data.name), name) != NULL) {
                flag = 1;
                printNode(p);
                return SUCCEED;
            }
            else if (p == NULL) {
                if (flag == NOT_FIND) return NOT_FIND;
                else {
                    return flag;
                }
            }
            p = p->next;
        }
    }
}

//打印结点数据
void printNode(Node *currentNode)
{
    printf("编号\t账号位置\t账号描述\t账号名\t密码\t\n");
    //int len = strlen(currentNode->data.password);
    //int i;
    //char temp[20];
    //strcpy(temp, currentNode->data.password);
    //for (i = 0; i < len; i++) {
        //temp[i] = temp[i]-12;
    //}
    printf("%d\t%s\t%s\t%s\t%s\t\n", currentNode->data.num, currentNode->data.host, currentNode->data.description, currentNode->data.name, currentNode->data.password);
    //memset(temp, '\0', sizeof(temp));
}

//打印链表
void printList(LinkList listHeadNode)
{
    Node *p = listHeadNode->next;
    printf("编号\t账号位置\t账号描述\t账号名\t\t密码\t\n");
    //char temp[20];
    while(p) {
        //int len = strlen(p->data.password);
        //printf("------text %s--------\n",p->data.password);
        //int i;
        //strcpy(temp, p->data.password);
        //for (i = 0; i < len; i++) {
            //temp[i] = temp[i]-12;
        //}
        //printf("------text %s--------\n",temp);
        printf("%d\t%s\t%s\t\t%s\t%s\t\n", p->data.num, p->data.host, p->data.description, p->data.name, p->data.password);
        //memset(temp, '\0', sizeof(temp));
        p = p->next;
    }

    printf("\n");
}

//读取数据
void readInfoFromFile(char *fileName, LinkList listHeadNode)
{
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        fp = fopen(fileName, "w");
    }

    DataElem tempData;
    while (fscanf(fp,"%d\t%s\t%s\t\t%s\t%s\t\n", &tempData.num, tempData.host, tempData.description, tempData.name, tempData.password) != EOF) {
        insertNodeByTail(listHeadNode, tempData);
        memset(&tempData, 0, sizeof(tempData));
    }

    fclose(fp);
}

//保存数据
void saveInfoToFile(char *fileName, LinkList listHeadNode)
{
    FILE *fp = fopen(fileName, "w");
    Node *p = listHeadNode->next;
    //char temp[20];
    while (p) {
        //char *p = p->data.password;
        //int len = strlen(p->data.password);
        //int i;
        //strcpy(temp, p->data.password);
        //for (i = 0; i < len; i++) {
            //temp[i] = temp[i]+12;
        //}
        fprintf(fp,"%d\t%s\t%s\t\t%s\t%s\t\n", p->data.num, p->data.host, p->data.description, p->data.name, p->data.password);
        p = p->next;
        //memset(temp, '\0', sizeof(temp));
    }

    fclose(fp);
}

//判断链表是否为空
int isEmpty(LinkList listHeadNode)
{
    Node *p = listHeadNode->next;
    if (p == NULL) return 1; //is NULL!
    else return 0;  //
}

//链表长度
int lengthOfList(LinkList listHeadNode)
{
    int i = 0;
    Node *p = listHeadNode->next;

    while(p != NULL) {
        p = p->next;
        i++;
    }

    return i;
}
#endif // MYLIST_H_INCLUDED

