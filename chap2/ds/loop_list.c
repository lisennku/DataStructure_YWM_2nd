//
// Created by lisen on 24-8-15.
//
#include "basic.h"
#include "loop_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 初始化
Status loop_list_initial(loop_list * l) {
/*
 * 初始化带有头结点的循环链表
 * 头结点的next指针指向头指针本身
 * 传入的是头指针的地址
 */
    Node * head_node = (Node *) malloc(sizeof(Node));
    if(head_node == NULL)
        exit(OVERFLOW);
    head_node->next = head_node;
    *l = head_node;

    return OK;
}

// 判断是否为空
bool loop_list_is_empty(loop_list l) {
/*
 * 判断循环链表是否为空
 * 为空返回true，否则返回false
 * 传入的是头指针
 */
    return l->next == l ? true : false;
}

// 返回长度
unsigned int loop_list_length(loop_list l) {
/*
 * 返回链表长度
 */
    unsigned int len = 0;
    Node * p = l->next;  // 指向首元结点

    while(p != l) {
        len++;
        p = p->next;
    }

    return len;
}

// 获取指定位置的元素
Status loop_list_get_element(loop_list l, int position, Item * e) {
/*
 * 位置指的是以首元结点为1开始的编号
 * 传入的是头指针
 */
    Node * p = l->next;  // 首元结点
    int i = 1;

    while(p != l && i < position) {
        // 1. 判断是否到达链表尾部
        // 2. 判断找寻位置，因为 i = position-1时进入循环体，p赋值为当前节点的下一个结点，也即position位置的结点，因此要判断是i<position
        i++;
        p = p->next;
    }

    if(p == l)
        return ERROR;

    *e = p->item;

    return OK;
}

// 返回指定位元素第一次出现的位置，找不到返回0
unsigned int loop_list_locate_element(loop_list l, Item e) {
/*
 * 判断条件，p结点没有回到头结点，且p结点的值不是查找的值
 * 返回时需判断
 *      p指向l，则说明链表已经遍历完一次，没有找到，返回0
 *          因为如果找到了，就不会让p指向头结点
 *      p没指向l，返回position的值
 */
    unsigned int position = 1;
    Node * p = l->next;  // 首元结点

    while(p != l && p->item != e) {
        position ++;
        p = p->next;
    }

    if(p == l) // 没找到返回0
        return 0;
    return position;
}

// 指定位置插入元素
Status loop_list_insert_element(loop_list *l, int position, Item e) {
/*
 * 在指定位置插入，需要先判断待插入位置编码是否合法，也即 大于等于1，且小于等于len+1,
 *      请注意，插入时是可以允许position等于len+1的，表示在末尾插入
 * 在position位置插入，需要找到position-1位置的结点，并将新结点插入其后
 *      找到该位置，满足的情况为p != l && i < position - 1
 *          因为当i=position-2时，进入循环，p此时已经指向了position-1位置的结点
 */
    if(position < 1 || position > loop_list_length(*l) + 1)
        return ERROR;

    Node * new = (Node *) malloc(sizeof(Node));
    if (new == NULL)
        exit(OVERFLOW);
    new->item = e;

    if(position == 1) {
        new->next = (*l)->next;
        (*l)->next = new;
        return OK;
    }

    Node * p = (*l)->next;
    int i = 1;

    while(p != (*l) && i < position - 1) {
        i ++;
        p = p->next;
    }

    new->next = p->next;
    p->next = new;

    return OK;
}

// 删除指定位置的元素
Status loop_list_delete_element(loop_list *l, int position) {
/*
 * 删除指定位置的元素，先判断位置是否合法，position >=1 and position <= len
 *  请注意，删除时是不可以允许position等于len+1的
 *  在position位置删除，需要找到position-1位置的结点，用额外指针指向position
 *      找到该位置，满足的情况为p->next != l && i < position - 1
 *          因为当i=position-2时，进入循环，p此时已经指向了position-1位置的结点
 *          p->next != l确保不会找到最后一个结点
 *          代码中可简化条件
 */
    if(position < 1 || position > loop_list_length(*l))
        return ERROR;

    if (position == 1) {
        Node * del = (*l)->next;
        (*l)->next = del->next;
        free(del);
        return OK;
    }

    Node * p = (*l)->next;
    int i = 1;
    while(p->next != (*l) && i < position - 1) {
        i ++;
        p = p->next;
    }

    Node * del = p->next;
    p->next = del->next;
    free(del);
    return OK;
}

// 头插法创建循环链表
void loop_list_create_from_head(loop_list *l, int size);

// 尾插法创建循环链表
void loop_list_create_from_tail(loop_list *l, int size);

// 打印链表
void loop_list_display(loop_list l) {
    Node * p = l->next;
    while(p != l) {
        printf("%d ", p->item);
        p = p->next;
    }
    putchar('\n');
}