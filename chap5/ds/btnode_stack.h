//
// Created by lisen on 24-8-28.
//

#ifndef BTNODE_STACK_H
#define BTNODE_STACK_H

#include <stdbool.h>
#include "btnode.h"

struct bt_stack_node {
    BTNode * node;
    struct bt_stack_node * next;
};

typedef struct bt_stack_node BT_SNode;
typedef struct bt_stack_node * BT_SStack;

// 初始化栈
void bt_linked_stack_init(BT_SStack *s);
// 栈是否为空
bool bt_linked_stack_is_empty(BT_SStack s);
// 返回栈的长度
int bt_linked_stack_length(BT_SStack s);
// 获取栈顶元素
BTNode * bt_linked_stack_get_top(BT_SStack s);
// 入栈
void bt_linked_stack_push(BT_SStack * s, BTNode * e);
// 出栈
void bt_linked_stack_pop(BT_SStack * s, BTNode ** e);








#endif //BTNODE_STACK_H
