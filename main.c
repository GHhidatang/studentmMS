#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <afxres.h>

#include "struct.h"

/*
 * ����������
 * */
void readInfoForomFile(char * fileName, struct Node * listHeadNode);
struct Node * searchNodeByAppoinNum(struct Node * listHeadNode, char * num);
void deleteNodeByAppoinName(struct Node * listHeadNode, char * name);
void insertNodeByHead(struct Node * lisHeadNode, struct student data, int i);
void printNode(struct Node * curNode);
void printList(struct Node * listHeadNode);

struct Node * list = NULL;
int j;

int systemMenu()
{
    int i;
    int t;

    printf("|------------------------ѧ������ϵͳ---------------------------|\n");
    printf("|\t\t\t0.�˳�ϵͳ\t\t\t\t|\n");
    printf("|\t\t\t1.������Ϣ\t\t\t\t|\n");
    printf("|\t\t\t2.�����Ϣ\t\t\t\t|\n");
    printf("|\t\t\t3.ɾ����Ϣ\t\t\t\t|\n");
    printf("|\t\t\t4.�޸���Ϣ\t\t\t\t|\n");
    printf("|\t\t\t5.������Ϣ\t\t\t\t|\n");
    printf("|\t\t\t6.������Ϣ\t\t\t\t|\n");
    printf("|---------------------------------------------------------------|\n");
    for(t=0; t<67; t++)
    {
        printf(">");
        Sleep(12);
    }

    printf("��������Ҫ�Ĺ��ܶ�Ӧ�����(0~6)\n");
    scanf("%d", &i);

    return i;
}

// �����ļ�
void saveInfoToFile(char * fileName, struct Node * listHeadNode)
{
    struct Node * pMove = listHeadNode -> next;

    FILE * fp = fopen(fileName, "w");
    //fprintf(fp, "%s\t%s\t%s\t%s\t%s\n", "����", "ѧ��", "����", "�绰", "��ַ");

    while(pMove)
    {
        fprintf(fp, "%s\t%s\t%d\t%s\t%s\n", pMove -> data.name, pMove -> data.num,
                pMove -> data.age, pMove -> data.tel, pMove -> data.addr);
        pMove = pMove -> next;
    }

    fclose(fp);
}

// ��ȡ�ļ�
void readInfoForomFile(char * fileName, struct Node * listHeadNode)
{
    int i = 0;
    struct student tempData;
    char ch[20];

    FILE * fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        fp = fopen(fileName, "w");
    }

    //fscanf(fp, "%s\n", ch);

    while(fscanf (fp, "%s\t%s\t%d\t%s\t%s\n", tempData.name, tempData.num,
            &tempData.age, tempData.tel, tempData.addr) != EOF)
    {
        insertNodeByHead(listHeadNode, tempData, i);
        memset(&tempData, 0, sizeof(tempData));
        i++;
        j = i;
    }
    fclose(fp);
}

// ������Ϣ
struct Node * searchNodeByAppoinNum(struct Node * listHeadNode, char * num)
{
    struct Node * pMove = listHeadNode -> next;

    if (pMove == NULL)
        return pMove;
    else
    {
        while(strcmp(pMove -> data.num, num))
        {
            pMove = pMove -> next;

            if(pMove == NULL)
            {
                break;
            }
        }
    }
    return pMove;

}

// ɾ����Ϣ
void deleteNodeByAppoinName(struct Node * listHeadNode, char * name)
{
    struct Node * posFrontNode = listHeadNode;
    struct Node * posNode = listHeadNode -> next;

    if (posNode == NULL)
    {
        printf("��������ݣ��޷�ɾ��!\n");
        return;
    }

    while (strcmp (posNode -> data.name, name))
    {
        posFrontNode = posNode;
        posNode = posFrontNode -> next;
        if (posNode == NULL)
        {
            printf("��������ݣ��޷�ɾ��!\n");
            return;
        }
    }

    posFrontNode -> next = posNode -> next;
    free(posNode);

    return;
}

// ������Ϣ
void insertNodeByHead(struct Node * lisHeadNode, struct student data, int i) // �βΣ������ĸ���������������Ƕ���
{
//    struct Node * newNode = creatNode(data);
//    lisHeadNode -> next = newNode;
//    newNode -> next = lisHeadNode;

    if(i == 0)
        lisHeadNode -> next = creatNode(data);
    else
        Recursion(*lisHeadNode, data, i);

    return;
}

// ��ӡ��ǰ�ڵ�
void printNode(struct Node * curNode)
{
    printf("����\tѧ��\t����\t�绰\tסַ\n");
    printf("%s\t%s\t%d\t%s\t%s\n", curNode -> data.name, curNode -> data.num, curNode -> data.age, curNode -> data.tel, curNode -> data.addr);
}

// ��ӡ����
void printList(struct Node * listHeadNode)
{
    struct Node * pMove = listHeadNode -> next;
    printf("����\tѧ��\t����\t�绰\tסַ\n");
    while(pMove)
    {
        printf("%s\t%s\t%d\t%s\t%s\n", pMove -> data.name, pMove -> data.num, pMove -> data.age, pMove -> data.tel, pMove -> data.addr);
        pMove = pMove -> next;
    }
    printf("\n");

    return;
}


void main()
{
    list = creatList();
    struct student tempData;

    system("title ѧ����Ϣ����ϵͳ");                   //���ô��ڱ���
    system("mode con cols=67 lines=32");                //���ô��ڴ�С
    system("color f9");                                 //���ô�����ɫ(ǰ��ɫΪ����ɫ������ɫΪ��ɫ)

    readInfoForomFile("data.txt", list);

    while(1)
    {
        switch(systemMenu())
        {
            case 0:
                printf("\t\t ���˳�ϵͳ��\n");
                return;
            case 1:
                printf("\t\t ������ϵͳ��\n");
                printf("������Ҫ�����ѧ����������ѧ�ţ����䣬�绰��סַ(���ÿո����)\n");
                scanf("%s%s%d%s%s", tempData.name, tempData.num, &tempData.age, tempData.tel, tempData.addr);
                insertNodeByHead(list, tempData, j);
                saveInfoToFile("data.txt", list);
                j++;
                fflush(stdin);
                break;
            case 2:
                printf("\t\t �������Ϣ��\n");
                printList(list);
                fflush(stdin);
                break;
            case 3:
                printf("\t\t ��ɾ����Ϣ��\n");
                printf("������Ҫɾ����ѧ������:\n");
                scanf("%s", &tempData);
                deleteNodeByAppoinName(list, tempData.name);
                saveInfoToFile("data.txt", list);
                fflush(stdin);
                break;
            case 4:
                printf("\t\t ���޸���Ϣ��\n");
                printf("������Ҫ����ѧ����ѧ��:\n");
                scanf("%s", tempData.num);
                if(searchNodeByAppoinNum(list, tempData.num) == NULL)
                {
                    printf("δ�ҵ������Ϣ!\n");
                } else
                {
                    struct Node * curNode = searchNodeByAppoinNum(list, tempData.num);
                    printf("��������ѧ����������ѧ�ţ����䣬�绰��סַ(���ÿո����)\n");
                    scanf("%s%s%d%s%s", curNode -> data.name, curNode -> data.num, &curNode -> data.age, curNode -> data.tel, curNode -> data.addr);
                };
                saveInfoToFile("data.txt", list);
                fflush(stdin);
                break;
            case 5:
                printf("\t\t ��������Ϣ��\n");
                printf("������Ҫ����ѧ����ѧ��:\n");
                scanf("%s", tempData.num); // ������ΪtempData.numΪchar���͵����� ���Բ���Ҫ��ȡ��ַ��
                if(searchNodeByAppoinNum(list, tempData.num) == NULL)
                {
                    printf("δ�ҵ������Ϣ!\n");
                } else
                {
                    printNode(searchNodeByAppoinNum(list, tempData.num));
                }
                fflush(stdin);
                break;
            case 6:
                printf("\t\t ��������Ϣ��\n");
                saveInfoToFile("data.txt", list);
                fflush(stdin);
                break;
            default:
                printf("��������ȷ�Ĳ˵���:\n");
                fflush(stdin);
                break;
        }

        system("pause");
        system("cls");
    }
}