//
// Created by lisen on 24-8-19.
//

#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#if 0
    使用无头结点的链表 表示栈
    以链表的头部作为栈顶
#endif

#include "basic.h"
#include <stdlib.h>

typedef int Item;

struct stack_node {
    Item data;
    struct  stack_node * next;
};

typedef struct stack_node SNode;
typedef struct stack_node * Linked_Stack;

// 初始化栈
Status linked_stack_init(Linked_Stack *s);
// 栈是否为空
bool linked_stack_is_empty(Linked_Stack s);
// 返回栈的长度
int linked_stack_length(Linked_Stack s);
// 获取栈顶元素
Item linked_stack_get_top(Linked_Stack s);
// 入栈
Status linked_stack_push(Linked_Stack * s, Item e);
// 出栈
Status linked_stack_pop(Linked_Stack * s, Item * e);
// 遍历栈
void linked_stack_traverse(Linked_Stack s, void (*pfun)(Item e));


#endif //LINKED_STACK_H
