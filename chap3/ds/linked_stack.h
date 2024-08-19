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
Status linked_stack_init(Linked_Stack *s) {
    *s = NULL;   // 直接将头指针设置为NULL 不是用头结点
    return OK;
}
// 栈是否为空
bool linked_stack_is_empty(Linked_Stack s) {
    return s == NULL ? true : false;
}
// 返回栈的长度
int linked_stack_length(Linked_Stack s) {
    int len = 0;
    while(s != NULL) {
        len ++;
        s = s->next;
    }
    return len;
}
// 获取栈顶元素
Item linked_stack_get_top(Linked_Stack s) {
    /*
     * 获取栈顶元素，不需要修改栈顶的位置
     */
    if(s != NULL)
        return s->data;
}
// 入栈
Status linked_stack_push(Linked_Stack * s, Item e) {
    /*
     * 不需要像array_stack那样判断是否超出最大长度
     */
    SNode * new = (SNode *) malloc(sizeof(SNode));
    if(new == NULL)
        return ERROR;
    new->data = e;
    new->next = *s;  // 将新结点的next设置为当前链表的第一个结点
    *s = new;
    return OK;
}
// 出栈
Status linked_stack_pop(Linked_Stack * s, Item * e) {
    /*
     * 判断是否空栈
     * 需要释放删除结点的内存空间
     */
    if(*s == NULL)
        return ERROR;
    *e = (*s)->data;
    SNode * del = *s;
    free(del);
    *s = (*s)->next;
    return OK;
}
// 遍历栈
void linked_stack_traverse(Linked_Stack s, void (*pfun)(Item e)) {
    while(s != NULL) {
        (*pfun)(s->data);
        s = s->next;
    }

}


#endif //LINKED_STACK_H
