//
// Created by lisen on 24-8-19.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "basic.h"
#include "array_stack.h"

// 初始化栈
Status array_stack_init(Array_Stack *s) {
    /*
     * 为base动态分配内存
     * base指针和top指针指向同一位置
     * stack_size 设置为MAX_SIZE
    */
    s->base = (Item *) malloc(sizeof(Item) * MAX_SIZE);
    if(s->base == NULL)
        return OVERFLOW;
    s->top = s->base;
    s->stack_size = MAX_SIZE;

    return  OK;
}

// 栈是否为空
bool array_stack_is_empty(Array_Stack s) {
    /*
     * 栈为空条件 top == base
     */
    return s.base == s.top ? true : false;
}

// 返回栈的长度
int array_stack_length(Array_Stack s) {
    return s.top - s.base;
}

// 获取栈顶元素
Item array_stack_get_top(Array_Stack s) {
    /*
     * 获取栈顶元素，不改变top指针的位置
     * 所以不能使用自减符号--，会改变top的位置
     * 要先判断栈不为空
     */
    if(s.base != s.top)
        return *(s.top - 1);
}

// 入栈
Status array_stack_push(Array_Stack * s, Item e) {
    /*
     * 入栈操作
     * 需判断是否超过容量
     * 入栈需要对top增加
    */
    if((s->top - s->base) == s->stack_size)
        return ERROR;
    *(s->top++) = e; // 先赋值然后自增
    return OK;
}
// 出栈
Status array_stack_pop(Array_Stack * s, Item * e) {
    /*
     * 出栈操作
     * 需判断是否为空
     * 出栈后top减一
     * 但是有个问题，出栈元素其实并未被实际删除，只是通过top指针忽略了该元素
     */
    if(s->base == s->top)
        return ERROR;
    *e = *(--s->top);  // 先减，然后赋值
}
// 遍历栈
void array_stack_traverse(Array_Stack s, void (*pfun)(Item e)) {
    for (int i = 0; i < s.top - s.base; i++) {
        (*pfun)(*(s.base + i));
    }
}
