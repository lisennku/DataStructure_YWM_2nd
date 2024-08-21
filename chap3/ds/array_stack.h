//
// Created by lisen on 24-8-19.
//

#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H
#include <stdbool.h>
#include "basic.h"

#define MAX_SIZE 2

typedef int Item;
// typedef double Item;

struct stack {
    Item * base;              // 永远指向栈底
    Item * top ;              // 指向栈顶
    unsigned int stack_size;  // 栈的大小
};

typedef struct stack Array_Stack;

// 初始化栈
Status array_stack_init(Array_Stack *s);
// 栈是否为空
bool array_stack_is_empty(Array_Stack s);
// 返回栈的长度
int array_stack_length(Array_Stack s);
// 获取栈顶元素
Item array_stack_get_top(Array_Stack s);
// 入栈
Status array_stack_push(Array_Stack * s, Item e);
// 出栈
Status array_stack_pop(Array_Stack * s, Item * e);
// 遍历栈
void array_stack_traverse(Array_Stack s, void (*pfun)(Item e));

#endif //ARRAY_STACK_H
