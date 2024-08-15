//
// Created by lisen on 24-8-8.
//

#ifndef LOOP_LIST_H
#define LOOP_LIST_H

#include "basic.h"
#include <stdbool.h>

#if 0
    带有头结点的循环链表
    首元结点, 是链表总的第一个结点
    头结点, 首元结点前的一个结点, 用于统一插入/删除等操作
        头结点的next, 在初始化时, 和单向链表有所区别
            循环链表的头结点的next应初始化为头结点的地址
    头指针, 指向头结点, 存储头结点的地址, 可以表示一个单向链表
#endif

typedef int Item;
struct node {
    Item item;
    struct node * next;
};

// Node * 和 loop_list的效果相同
// Node * 通常用于声明一个指向链表中某个节点的指针
// loop_list 通常用于声明一个头指针
typedef struct node Node;
typedef Node * loop_list;

// 初始化
Status loop_list_initial(loop_list * l);

// 判断是否为空
bool loop_list_is_empty(loop_list l);

// 返回长度
unsigned int loop_list_length(loop_list l);

// 获取指定位置的元素
Status loop_list_get_element(loop_list l, int position, Item * e);

// 返回指定位元素第一次出现的位置，找不到返回0
unsigned int loop_list_locate_element(loop_list l, Item e);

// 指定位置插入元素
Status loop_list_insert_element(loop_list *l, int position, Item e);

// 删除指定位置的元素
Status loop_list_delete_element(loop_list *l, int position);

// 头插法创建循环链表
void loop_list_create_from_head(loop_list *l, int size);

// 尾插法创建循环链表
void loop_list_create_from_tail(loop_list *l, int size);

// 打印链表
void loop_list_display(loop_list l);

#endif //LOOP_LIST_H
