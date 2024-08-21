//
// Created by lisen on 24-8-21.
//

//从键盘上输入一个后缀表达式，试编写算法计算表达式的值。
//规定：后缀表达式的长度不超过一行，
//  以“$”作为输入结束，
//  操作数之间用空格分隔，
//  操作符只可能有+、-、*、/四种运算
// 后缀表达式计算，操作数直接入栈，遇到操作符，弹出两个操作数进行计算，计算结果再次入栈，直到表达式结尾

#include <stdio.h>
#include <stdlib.h>
#include "../../ds/array_stack.h"
#include "basic.h"

void calc_postfix_expression();

int main() {
    calc_postfix_expression();

    return 0;
}

void calc_postfix_expression() {
    printf("please input a expression in postfix mode\n");

    Array_Stack nums;    // 栈，用来存储操作数及计算结果
    if(array_stack_init(&nums) != OK)
        exit(OVERFLOW);

    char ch = getchar();
    while(ch != '$') {
        char digits[100] ;   // 存储数字字符串
        int i = 0;   // 用于digits脚标
        // 拼接数字
        while((ch >= '0' && ch <= '9') || ch == '.') {
            digits[i] = ch;
            i ++;
            ch = getchar();
        }

        if(i != 0) {    // 输入不在0-9.范围内，digits为0，如果不判断会被压入栈内
            digits[i] = '\0';

            double num = atof(digits);
            // 操作数入栈
            array_stack_push(&nums, num);
        }

        Item a, b;
        Status sa, sb;

        switch (ch) {
            case '+':
                sb = array_stack_pop(&nums, &b);
                sa = array_stack_pop(&nums, &a);
                if(sa != OK || sb != OK) {
                    printf("error in post-fix expression for +\n");
                    exit(EXIT_FAILURE);
                }
                array_stack_push(&nums, a+b);
                break;
            case '-':
                sb = array_stack_pop(&nums, &b);
                sa = array_stack_pop(&nums, &a);
                if(sa != OK || sb != OK) {
                    printf("error in post-fix expression for -\n");
                    exit(EXIT_FAILURE);
                }
                array_stack_push(&nums, a-b);
                break;
            case '*':
                sb = array_stack_pop(&nums, &b);
                sa = array_stack_pop(&nums, &a);
                if(sa != OK || sb != OK) {
                    printf("error in post-fix expression for *\n");
                    exit(EXIT_FAILURE);
                }
                array_stack_push(&nums, a*b);
                break;
            case '/':
                sb = array_stack_pop(&nums, &b);
                sa = array_stack_pop(&nums, &a);
                if(sa != OK || sb != OK) {
                    printf("error in post-fix expression for /\n");
                    exit(EXIT_FAILURE);
                }
                array_stack_push(&nums, a/b);
                break;
            case ' ':
                break;
        }
        ch = getchar();
    }
    printf("value of post-fix expr is %lf\n", array_stack_get_top(nums));
}



























