//
// Created by lisen on 24-8-21.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "basic.h"


#define MAX_SIZE 100

typedef char Item;

struct stack {
    Item * base;              // 永远指向栈底
    Item * top ;              // 指向栈顶
    unsigned int stack_size;  // 栈的大小
};
typedef struct stack Array_Stack;
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


bool palin_judge() {
    char palin[MAX_SIZE] = "ab";
    int  len = strlen(palin);
    int  half = len / 2;

    Array_Stack s;
    if(array_stack_init(&s) != OK)
        exit(ERROR);

    // 将后半部分入栈，然后依次弹出，每次弹出和数组前半部分比较
    // 如果是偶数长度，则从half开始将后半部分入栈
    // 如果是奇数长度，则从half+1开始将后半部分入栈
    int idx = len % 2 == 0 ? half : half+1;
    for(int i = idx; i < len; i ++) {
        array_stack_push(&s, palin[i]);
    }


    for (int i = 0; i < half; i ++) {
        Item c ;
        array_stack_pop(&s, &c);
        if (c != palin[i])
            return false;
    }
    return true;
}

// int main() {
//     bool p = palin_judge();
//     if(p)
//         printf("it's true\n");
//     else
//         printf("it's false");
//     return 0;
// }
