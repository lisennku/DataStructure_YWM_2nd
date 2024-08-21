//
// Created by lisen on 24-8-21.
//
// 设从键盘输入一整数的序列：a1，a2，a3，…，an，
// 试编写算法实现：用栈结构存储输入的整数，
//  当ai≠-1时，将ai进栈；当ai=-1时，输出栈顶整数并出栈。
// 算法应对异常情况（入栈满等）给出相应的信息

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../ds/array_stack.h"

#define N 50
void integer_stack_io();

int main() {
    integer_stack_io();

    return 0;
}

void integer_stack_io() {
    Array_Stack st;
    if(array_stack_init(&st) != OK)
        exit(OVERFLOW);
    printf("now please start to input an integer, non-interger will exit the program\n");
    int loop = N;
    while(loop--) {
        int i;
        int ret;
        if ((ret = scanf("%d", &i)) != 1)
            break;
        if(i != -1) {
            if(array_stack_push(&st, i) != OK) {
                printf("stack is full\n");
                exit(OVERFLOW);
            }
            printf("%d has been pushed into stack\n", i);
        }
        else {
            if(array_stack_is_empty(st)) {
                printf("stack is empty now!\n");
                continue;
            }
            Item pop;
            array_stack_pop(&st, &pop);
            printf("stack has poped up a value of %d\n", pop);
        }

    }
}