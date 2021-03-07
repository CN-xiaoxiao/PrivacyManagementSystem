#include "myList.h"
LinkList L;

void systemMenu()
{
    printf("--------【隐私信息管理系统】--------\n");
    printf("\t1.添加信息\n");
    printf("\t2.浏览信息\n");
    printf("\t3.删除信息\n");
    printf("\t4.修改信息\n");
    printf("\t5.查找信息\n");
    printf("\t0.退出系统\n");
    printf("------------------------------------\n");
    printf("请输入(0-5)：");
}

void keyDown()
{
    int userKey;
    DataElem tempData;
    char tempName[20];
    int flag;
    scanf("%d", &userKey);
    switch (userKey)
    {
    case 0:
        flag = myEncryption(L);
        saveInfoToFile("system.txt", L);
        if (flag == SUCCEED) printf("加密成功！\n");
        printf("感谢您使用本系统，再见！\n");
        system("pause");
        exit(0);
        break;
    case 1:
        printf("\t【添加信息】\n");
        printf("请输入编号，网站地址，该网站的描述，账号，密码\n");
        scanf("%d%s%s%s%s", &tempData.num, &tempData.host, &tempData.description, &tempData.name, &tempData.password);
        flag = insertNodeByTail(L, tempData);
        if (flag == SUCCEED) {
            printf("添加成功！\n");
        }
        saveInfoToFile("system.txt", L);

        break;
    case 2:
        printf("\t【浏览信息】\n");
        printList(L);

        break;
    case 3:
        printf("\t【删除信息】\n");
        if (isEmpty(L) == 1) {
            printf("没有信息，无法删除！\n");
        }
        else {
            printList(L);
            printf("观察上表，请输入你要删除的信息的编号：");
            int tempNum;
            scanf("%d", &tempNum);
            deleteNodeByAppion(L, tempNum);
            printf("已删除!\n");
            saveInfoToFile("system.txt", L);
        }
        break;
    case 4:
        printf("\t【修改信息】\n");
        if (isEmpty(L) == 1) {
            printf("当前没有数据，无法进行操作！\n");
            break;
        }
        else {
            printList(L);
            printf("观察上表，请输入你要修改的数据的编号：");
            int key;
            scanf("%d", &key);
            Node *p = serchNodeByNum(L, key);
            int flag = scanf("%d%s%s%s%s", &p->data.num, &p->data.host, &p->data.description, &p->data.name, &p->data.password);
            if (flag > 0) {
                printf("修改成功！\n");
            }
            else {
                printf("修改失败！\n");
            }
            saveInfoToFile("system.txt", L);
        }

        break;
    case 5:
        printf("\t【查找信息】\n");

        if (L->next == NULL) {
            printf("没有数据，无法进行该操作,请添加后再尝试!\n");
            break;
        }
        else {
            printf("请输入要查找的账号名：");

           // printf("===========1main===============\n");
            scanf("%s", &tempName);
            //printf("============2main==============\n");
            //printf("In the main that need find = %s\n", tempName);
            int flag = serchNodeByCorrelationName(L, tempName);
            //printf("=============3main=============\n");
            if (flag == NOT_FIND) {
                printf("未找到相关信息！\n");
            }
        }
        break;
    default:
        printf("请输入0-5！\n");
        break;
    }
}


int login()
{
    FILE *fp = fopen("admin.txt", "r");
    char name[20];
    char password[20];
    fscanf(fp,"%s\n%s",name,password);

    int len = strlen(password);
    int i;
    for (i = 0; i < len; i++) {
        password[i] = password[i]-12;
    }

    char userName[20];
    char userPassword[20];
    int count = 3;
    while (count--) {
        printf("请输入账号：");
        scanf("%s", &userName);
        printf("请输入密码：");
        scanf("%s", &userPassword);
        if (strcmp(name,userName) == 0 && strcmp(password, userPassword) == 0) {
            printf("登陆成功！\n");
            printf("尊贵的管理员%s，欢迎回来！\n",name);
            fclose(fp);
            return SUCCEED;
        }
        else {
            printf("登陆失败！\n请检查账号密码是否正确！\n");
        }
    }

    if (count < 0) printf("登录失败次数过多，如果忘记密码，请联系制作人员！\n");
    fclose(fp);

    return 0;
}

void myRegister()
{
    FILE *fp = fopen("admin.txt", "w");
    char name[20];
    printf("请输入管理员账号：");
    scanf("%s", &name);
    fprintf(fp,"%s\n",name);

    char password[20];
    printf("请输入密码：");
    scanf("%s", &password);
    int len = strlen(password);
    int i;
    for (i = 0; i < len; i++) {
        password[i] = password[i]+12;
    }
    fprintf(fp,"%s", password);
    fclose(fp);

    printf("注册成功！\n");
}

int myEncryption(LinkList listHeadNode)
{
    printf("正在为你加密\n");
    Node *p = listHeadNode->next;
    if (p == NULL) {
        printf("没有信息，无需加密！\n");
        return 0;
    }
    else {
        int count, i;
        while (p) {
            if (p == NULL) break;
            count=strlen(p->data.password);
            //char cryptograph[22];
            for(i=0;i<count;i++)
            {
                p->data.password[i]=p->data.password[i]+i+5;
            }
            //cryptograph[i]='\0';
            p = p->next;
        }
        return SUCCEED;
    }

}

void myDecrypt(LinkList listHeadNode)
{
    Node *p = listHeadNode->next;
    int count,i;
    if (p == NULL) return;
    while (p) {
        if (p == NULL) {
            printf("解密成功！\n");
            saveInfoToFile("system.txt", L);
            //注意，此处有安全风险.
            return;
        }
        count=strlen(p->data.password);
        for(i=0;i<count;i++)
        {
            p->data.password[i]=p->data.password[i]-i-5;
        }
        //p->data.password[i]='\0';
        p = p->next;
    }
}

int main()
{
    FILE *fp = fopen("admin.txt", "r");
    int flag = 0;
    char ch = fgetc(fp);
    if (fp == NULL || ch==EOF)
    {
        printf("检测到没有注册！\n");
        myRegister();
        printf("为安全起见,请重新运行程序！\n");
        system("pause");
        exit(0);
    }
    else {
        flag = login();
    }
    fclose(fp);

    if (flag == SUCCEED)
    {
        L = createList();
        readInfoFromFile("system.txt", L);
        myDecrypt(L);
        while(1) {
            //readInfoFromFile("system.txt", L);
            systemMenu();
            keyDown();
            system("pause");
            system("cls");
        }

        system("pause");
    }
    return 0;
}
