#include "myList.h"
LinkList L;

void systemMenu()
{
    printf("--------����˽��Ϣ����ϵͳ��--------\n");
    printf("\t1.�����Ϣ\n");
    printf("\t2.�����Ϣ\n");
    printf("\t3.ɾ����Ϣ\n");
    printf("\t4.�޸���Ϣ\n");
    printf("\t5.������Ϣ\n");
    printf("\t0.�˳�ϵͳ\n");
    printf("------------------------------------\n");
    printf("������(0-5)��");
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
        if (flag == SUCCEED) printf("���ܳɹ���\n");
        printf("��л��ʹ�ñ�ϵͳ���ټ���\n");
        system("pause");
        exit(0);
        break;
    case 1:
        printf("\t�������Ϣ��\n");
        printf("�������ţ���վ��ַ������վ���������˺ţ�����\n");
        scanf("%d%s%s%s%s", &tempData.num, &tempData.host, &tempData.description, &tempData.name, &tempData.password);
        flag = insertNodeByTail(L, tempData);
        if (flag == SUCCEED) {
            printf("��ӳɹ���\n");
        }
        saveInfoToFile("system.txt", L);

        break;
    case 2:
        printf("\t�������Ϣ��\n");
        printList(L);

        break;
    case 3:
        printf("\t��ɾ����Ϣ��\n");
        if (isEmpty(L) == 1) {
            printf("û����Ϣ���޷�ɾ����\n");
        }
        else {
            printList(L);
            printf("�۲��ϱ���������Ҫɾ������Ϣ�ı�ţ�");
            int tempNum;
            scanf("%d", &tempNum);
            deleteNodeByAppion(L, tempNum);
            printf("��ɾ��!\n");
            saveInfoToFile("system.txt", L);
        }
        break;
    case 4:
        printf("\t���޸���Ϣ��\n");
        if (isEmpty(L) == 1) {
            printf("��ǰû�����ݣ��޷����в�����\n");
            break;
        }
        else {
            printList(L);
            printf("�۲��ϱ���������Ҫ�޸ĵ����ݵı�ţ�");
            int key;
            scanf("%d", &key);
            Node *p = serchNodeByNum(L, key);
            int flag = scanf("%d%s%s%s%s", &p->data.num, &p->data.host, &p->data.description, &p->data.name, &p->data.password);
            if (flag > 0) {
                printf("�޸ĳɹ���\n");
            }
            else {
                printf("�޸�ʧ�ܣ�\n");
            }
            saveInfoToFile("system.txt", L);
        }

        break;
    case 5:
        printf("\t��������Ϣ��\n");

        if (L->next == NULL) {
            printf("û�����ݣ��޷����иò���,����Ӻ��ٳ���!\n");
            break;
        }
        else {
            printf("������Ҫ���ҵ��˺�����");

           // printf("===========1main===============\n");
            scanf("%s", &tempName);
            //printf("============2main==============\n");
            //printf("In the main that need find = %s\n", tempName);
            int flag = serchNodeByCorrelationName(L, tempName);
            //printf("=============3main=============\n");
            if (flag == NOT_FIND) {
                printf("δ�ҵ������Ϣ��\n");
            }
        }
        break;
    default:
        printf("������0-5��\n");
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
        printf("�������˺ţ�");
        scanf("%s", &userName);
        printf("���������룺");
        scanf("%s", &userPassword);
        if (strcmp(name,userName) == 0 && strcmp(password, userPassword) == 0) {
            printf("��½�ɹ���\n");
            printf("���Ĺ���Ա%s����ӭ������\n",name);
            fclose(fp);
            return SUCCEED;
        }
        else {
            printf("��½ʧ�ܣ�\n�����˺������Ƿ���ȷ��\n");
        }
    }

    if (count < 0) printf("��¼ʧ�ܴ������࣬����������룬����ϵ������Ա��\n");
    fclose(fp);

    return 0;
}

void myRegister()
{
    FILE *fp = fopen("admin.txt", "w");
    char name[20];
    printf("���������Ա�˺ţ�");
    scanf("%s", &name);
    fprintf(fp,"%s\n",name);

    char password[20];
    printf("���������룺");
    scanf("%s", &password);
    int len = strlen(password);
    int i;
    for (i = 0; i < len; i++) {
        password[i] = password[i]+12;
    }
    fprintf(fp,"%s", password);
    fclose(fp);

    printf("ע��ɹ���\n");
}

int myEncryption(LinkList listHeadNode)
{
    printf("����Ϊ�����\n");
    Node *p = listHeadNode->next;
    if (p == NULL) {
        printf("û����Ϣ��������ܣ�\n");
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
            printf("���ܳɹ���\n");
            saveInfoToFile("system.txt", L);
            //ע�⣬�˴��а�ȫ����.
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
        printf("��⵽û��ע�ᣡ\n");
        myRegister();
        printf("Ϊ��ȫ���,���������г���\n");
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
