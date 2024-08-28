//
// Created by lisen on 24-8-28.
//
#include "btnode_stack.h"
#include <stdbool.h>
#include <stdlib.h>


// 初始化栈
void bt_linked_stack_init(BT_SStack *s) {
    *s = NULL;
}
// 栈是否为空
bool bt_linked_stack_is_empty(BT_SStack s) {
    return s == NULL ? true : false;
}
// 返回栈的长度
int bt_linked_stack_length(BT_SStack s) {
    int len = 0;
    while(s != NULL) {
        len ++;
        s = s->next;
    }
    return len;
}
// 获取栈顶元素
BTNode * bt_linked_stack_get_top(BT_SStack s) {
    if(s != NULL)
        return s->node;
}
// 入栈
void bt_linked_stack_push(BT_SStack * s, BTNode * e) {
    BT_SNode * new = (BT_SNode *) malloc(sizeof(BT_SNode));
    if(new == NULL)
        exit(EXIT_FAILURE);
    new->node = e;
    new->next = *s;  // 将新结点的next设置为当前链表的第一个结点
    *s = new;

}
// 出栈
void bt_linked_stack_pop(BT_SStack * s, BTNode ** e){
    // 由于栈元素是指针，因此此处传入的是指针的地址，所以是**
    if(*s == NULL)
        return ;
    *e = (*s)->node;
    BT_SNode * del = *s;
    *s = (*s)->next;
    free(del);
}