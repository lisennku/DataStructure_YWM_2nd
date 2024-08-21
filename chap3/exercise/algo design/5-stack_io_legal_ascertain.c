//
// Created by lisen on 24-8-21.
//
// 5．假设以I和O分别表示入栈和出栈操作。
//      栈的初态和终态均为空
// 入栈和出栈的操作序列可表示为仅由I和O组成的序列，称可以操作的序列为合法序列，否则称为非法序列。
// （1）下面所示的序列中哪些是合法的？
//      A．IOIIOIOO  legal
//      B．IOOIOIIO  illegal
//      C．IIIOIOIO  illegal
//      D．IIIOOIOO  legal
// （2）通过对（1）的分析，写出一个算法，判定所给的操作序列是否合法。
//      若合法，返回true，否则返回false（假定被判定的操作序列已存入一维数组中）。

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool stack_io_ascertain(char *s, int n);

int main() {
    char s[] = "IOOIOIIO";
    int len = strlen(s);
    bool flag = stack_io_ascertain(s, len);
    if(flag)
        printf("%s is a legal stack io string\n", s);
    else
        printf("%s is not a legal stack io string\n", s);

    return 0;
}

bool stack_io_ascertain(char *s, int n) {
    /*
     * 算法思路
     *  栈在初始和终止都为空，说明入栈的元素都已出栈
     *  设计一个整型标记flag，初始值为0
     *      遍历io字符串，I 入栈，flag+1， O 出栈，flag-1
     *      每次遍历过程中判断flag是否小于0，小于0说明在空栈状态下出栈，直接停止遍历，返回False
     *      遍历结束后判断flag是否为0，不为0说明终态的栈不为空，返回False
     *      没有上述情况后返回True
     */

    int flag = 0;
    for (int i = 0; i < n; i++) {
        s[i] == 'I' ? flag ++ : flag --;
        if(flag < 0)
            return false;
    }
    if(flag != 0)
        return false;
    return true;
}