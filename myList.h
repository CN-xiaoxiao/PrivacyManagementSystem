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
    int num;   //���
    char host[64]; //��վ����������63�ַ�
    char description[30]; //������
    char name[25];  //�˻���
    char password[20];  //����
}DataElem;

typedef struct Node
{
    DataElem data;
    struct Node *next;
}*LinkList, Node;

//��������ͷ���
LinkList createList()
{
    LinkList listHeadNode = (LinkList)malloc(sizeof(Node));
    listHeadNode->next = NULL;

    return listHeadNode;
}

//�������
Node* createNode(DataElem data)
{
    Node * newNode = (Node *)malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

//������(β�巨)
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
//������(ͷ�巨)
void insertNodeByHead(LinkList listHeadNode, DataElem data)
{
    Node *newNode = createNode(data);
    newNode->next = listHeadNode->next;
    listHeadNode->next = newNode;
}

//�����ɾ��
void deleteNodeByAppion(LinkList listHeadNode, int num)
{
    Node *pre = listHeadNode;
    Node *p = listHeadNode->next;

    if (p == NULL) {
        printf("��������ݣ�\n");
        return;
    }
    else {
        while (p->data.num != num) {
            pre = p;
            p = p->next;

            if (p == NULL) {
                printf("ɾ��ʧ�ܣ�\n");
                return;
            }
        }

        pre->next = p->next;
        free(p);
    }

}

//���˺�������ز���
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


//����Ų���
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

//error��
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
//ģ������(error!!!!)
int serch(char *str, char *str2)
{
    char *res;
    printf("=============serch1===========\n");
    res = memchr(str, str2[0], strlen(str));   //����Ҫ���ҵ��ַ�����һ���ַ����и�Դ�ַ���
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
        n = memcmp(res, str2, strlen(str2) - 1); //�Ƚ�
        printf("=============serch4===========\n");
        if (n != 0)
        {
            if (strlen(res) <= strlen(str2))    //�и�����ַ���С��Ҫ�����ַ����ĳ���
            {
                printf("find nothing...\n");
                return NOT_FIND;
            }
            else
            {
              //����Ҫ���ҵĵ�һ���ַ������и�
                res = memchr(res + 1, str2[0], strlen(res));
                if (res == NULL)
                {
                    printf("find nothing...\n");
                    return NOT_FIND;
                }

            }
        }
        else
        { //���n = 0���ҵ�
            printf("%s is found..\n", str2);
            return SUCCEED;
        }
    }
}

//ָ���˺��Ƿ���������
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

//��ӡ�������
void printNode(Node *currentNode)
{
    printf("���\t�˺�λ��\t�˺�����\t�˺���\t����\t\n");
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

//��ӡ����
void printList(LinkList listHeadNode)
{
    Node *p = listHeadNode->next;
    printf("���\t�˺�λ��\t�˺�����\t�˺���\t\t����\t\n");
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

//��ȡ����
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

//��������
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

//�ж������Ƿ�Ϊ��
int isEmpty(LinkList listHeadNode)
{
    Node *p = listHeadNode->next;
    if (p == NULL) return 1; //is NULL!
    else return 0;  //
}

//������
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

