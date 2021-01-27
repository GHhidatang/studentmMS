#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <afxres.h>

#include "struct.h"

/*
 * 函数的声明
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

    printf("|------------------------学生管理系统---------------------------|\n");
    printf("|\t\t\t0.退出系统\t\t\t\t|\n");
    printf("|\t\t\t1.插入信息\t\t\t\t|\n");
    printf("|\t\t\t2.浏览信息\t\t\t\t|\n");
    printf("|\t\t\t3.删除信息\t\t\t\t|\n");
    printf("|\t\t\t4.修改信息\t\t\t\t|\n");
    printf("|\t\t\t5.查找信息\t\t\t\t|\n");
    printf("|\t\t\t6.保存信息\t\t\t\t|\n");
    printf("|---------------------------------------------------------------|\n");
    for(t=0; t<67; t++)
    {
        printf(">");
        Sleep(12);
    }

    printf("请输入需要的功能对应的序号(0~6)\n");
    scanf("%d", &i);

    return i;
}

// 保存文件
void saveInfoToFile(char * fileName, struct Node * listHeadNode)
{
    struct Node * pMove = listHeadNode -> next;

    FILE * fp = fopen(fileName, "w");
    //fprintf(fp, "%s\t%s\t%s\t%s\t%s\n", "姓名", "学号", "年龄", "电话", "地址");

    while(pMove)
    {
        fprintf(fp, "%s\t%s\t%d\t%s\t%s\n", pMove -> data.name, pMove -> data.num,
                pMove -> data.age, pMove -> data.tel, pMove -> data.addr);
        pMove = pMove -> next;
    }

    fclose(fp);
}

// 读取文件
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

// 查找信息
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

// 删除信息
void deleteNodeByAppoinName(struct Node * listHeadNode, char * name)
{
    struct Node * posFrontNode = listHeadNode;
    struct Node * posNode = listHeadNode -> next;

    if (posNode == NULL)
    {
        printf("无相关内容，无法删除!\n");
        return;
    }

    while (strcmp (posNode -> data.name, name))
    {
        posFrontNode = posNode;
        posNode = posFrontNode -> next;
        if (posNode == NULL)
        {
            printf("无相关内容，无法删除!\n");
            return;
        }
    }

    posFrontNode -> next = posNode -> next;
    free(posNode);

    return;
}

// 插入信息
void insertNodeByHead(struct Node * lisHeadNode, struct student data, int i) // 形参：插入哪个链表；插入的数据是多少
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

// 打印当前节点
void printNode(struct Node * curNode)
{
    printf("姓名\t学号\t年龄\t电话\t住址\n");
    printf("%s\t%s\t%d\t%s\t%s\n", curNode -> data.name, curNode -> data.num, curNode -> data.age, curNode -> data.tel, curNode -> data.addr);
}

// 打印功能
void printList(struct Node * listHeadNode)
{
    struct Node * pMove = listHeadNode -> next;
    printf("姓名\t学号\t年龄\t电话\t住址\n");
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

    system("title 学生信息管理系统");                   //设置窗口标题
    system("mode con cols=67 lines=32");                //设置窗口大小
    system("color f9");                                 //设置窗口颜色(前景色为淡蓝色，背景色为白色)

    readInfoForomFile("data.txt", list);

    while(1)
    {
        switch(systemMenu())
        {
            case 0:
                printf("\t\t 【退出系统】\n");
                return;
            case 1:
                printf("\t\t 【插入系统】\n");
                printf("请输入要保存的学生的姓名，学号，年龄，电话，住址(并用空格隔开)\n");
                scanf("%s%s%d%s%s", tempData.name, tempData.num, &tempData.age, tempData.tel, tempData.addr);
                insertNodeByHead(list, tempData, j);
                saveInfoToFile("data.txt", list);
                j++;
                fflush(stdin);
                break;
            case 2:
                printf("\t\t 【浏览信息】\n");
                printList(list);
                fflush(stdin);
                break;
            case 3:
                printf("\t\t 【删除信息】\n");
                printf("请输入要删除的学生姓名:\n");
                scanf("%s", &tempData);
                deleteNodeByAppoinName(list, tempData.name);
                saveInfoToFile("data.txt", list);
                fflush(stdin);
                break;
            case 4:
                printf("\t\t 【修改信息】\n");
                printf("请输入要查找学生的学号:\n");
                scanf("%s", tempData.num);
                if(searchNodeByAppoinNum(list, tempData.num) == NULL)
                {
                    printf("未找到相关信息!\n");
                } else
                {
                    struct Node * curNode = searchNodeByAppoinNum(list, tempData.num);
                    printf("请输入新学生的姓名，学号，年龄，电话，住址(并用空格隔开)\n");
                    scanf("%s%s%d%s%s", curNode -> data.name, curNode -> data.num, &curNode -> data.age, curNode -> data.tel, curNode -> data.addr);
                };
                saveInfoToFile("data.txt", list);
                fflush(stdin);
                break;
            case 5:
                printf("\t\t 【查找信息】\n");
                printf("请输入要查找学生的学号:\n");
                scanf("%s", tempData.num); // 这里因为tempData.num为char类型的数组 所以不需要加取地址符
                if(searchNodeByAppoinNum(list, tempData.num) == NULL)
                {
                    printf("未找到相关信息!\n");
                } else
                {
                    printNode(searchNodeByAppoinNum(list, tempData.num));
                }
                fflush(stdin);
                break;
            case 6:
                printf("\t\t 【保存信息】\n");
                saveInfoToFile("data.txt", list);
                fflush(stdin);
                break;
            default:
                printf("请输入正确的菜单号:\n");
                fflush(stdin);
                break;
        }

        system("pause");
        system("cls");
    }
}