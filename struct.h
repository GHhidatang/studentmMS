//
// Created by 32119 on 2021/1/26.
//

#ifndef STUDENTMMS_STRUCT_H
#define STUDENTMMS_STRUCT_H

struct student
{
    char name[20]; // 姓名
    char num[10]; // 学号
    int age; // 年龄
    char tel[20]; // 电话
    char addr[20]; // 家庭住址
};

struct Node
{
    struct student data;
    struct Node* next;
};

struct Node * creatList()
{
    struct Node * listHeadNode = (struct Node*)malloc(sizeof(struct Node));
    listHeadNode -> next = NULL;

    return listHeadNode;
}

struct Node * creatNode(struct student data)
{
    struct Node * listHeadNode = (struct Node*)malloc(sizeof(struct Node));
    listHeadNode -> data = data;
    listHeadNode -> next = NULL;

    return listHeadNode;
};

// 递归函数实现根据指定次数从头结点找到尾结点
void Recursion(struct Node _head, struct student data, int i)
{
    i-=1;
    if(i == 0)
        (*(_head.next)).next = creatNode(data);
    else
        Recursion(*(_head.next), data, i);
}

#endif //STUDENTMMS_STRUCT_H