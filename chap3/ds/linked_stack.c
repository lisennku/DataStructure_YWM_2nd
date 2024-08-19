//
// Created by lisen on 24-8-19.
//

#include <stdlib.h>
#include <stdbool.h>
#include "basic.h"
#include "linked_stack.h"

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