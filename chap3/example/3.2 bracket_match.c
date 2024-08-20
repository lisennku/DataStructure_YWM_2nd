//
// Created by lisen on 24-8-20.
//
/*
 * 输入括号，以#为结尾，每输入一个括号，进行检查，同时使用标记位标记匹配情况，初始化为1，表示匹配
 *      如果是左括号，入栈
 *      如果是右括号，检查栈不为空且栈顶元素是否匹配，匹配则弹出，不匹配或为空则标记位置为0
 * 最后栈为空且标记位为1，true，否则false
 */

#include <iso646.h>
#include <stdbool.h>
#include <stdio.h>
#include "../ds/linked_stack.h"

#define END_CHAR '#'

bool bracket_match_test();

int main() {
    if(bracket_match_test())
        printf("input brackets matched!\n");
    printf("input brackets not matched!\n");
}

bool bracket_match_test() {
    // 创建并初始化链式栈
    Linked_Stack ls;
    if(linked_stack_init(&ls) != OK)
        exit(ERROR);

    // 初始化标记位
    int flag = 1;
    char ch = getchar();
    // 接收pop函数弹出的元素
    Item e;
    // 当右括号时
    //  判断栈非空，对应 栈为空但是又有右括号输入的不匹配情况
    //  判断栈顶是否为对应左括号，对应 括号本身不匹配情况
    // 最后判断栈非空
    //  判断栈非空，对应 没有输入右括号，但是仍存在未匹配到右括号的左括号的不匹配情况
    while(ch != END_CHAR and flag != 0) {
        switch (ch) {
            case '(' || '[':
                linked_stack_push(&ls, ch);
            break;
            case ')':
                if(!linked_stack_is_empty(ls) and linked_stack_get_top(ls) == '(') {
                    linked_stack_pop(&ls, &e);
                }
                else {
                    flag = 0;
                }
            break;
            case ']':
                if(!linked_stack_is_empty(ls) and linked_stack_get_top(ls) == '[') {
                    linked_stack_pop(&ls, &e);
                }
                else {
                    flag = 0;
                }
            break;
        }
        ch = getchar();
    }
    if(linked_stack_is_empty(ls) and flag == 1)
        return true;
    return false;
}