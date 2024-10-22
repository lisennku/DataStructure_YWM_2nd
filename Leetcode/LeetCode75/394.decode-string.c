//
// Created by lisen on 24-10-22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACKSIZE 10001

char * repeat_str(char * src, int repeat) {
    char * res = calloc(strlen(src) * repeat + 1, sizeof(char));
    if(res == NULL)
        exit(EXIT_FAILURE);

    for(int i = 0; i < repeat; i++)
        strcat(res, src);

    return res;
}

int str_num_to_int(char * num) {
    int len = strlen(num);
    int digits = 0;
    for (int i = 0; i < len; i++) {
        digits = digits * 10 + (num[i] - '0');
    }
    return digits;
}

char* decodeString(char* s) {

    char * stack = calloc(STACKSIZE, sizeof(char));
    int top = 0;

    for(int i = 0; i < strlen(s); i++) {
        // 非]直接入栈
        if(s[i] != ']')
            stack[top++] = s[i];
        else {
            // 获取重复字符串
            top--;                            // 先找到栈中最后一个元素的位置
            int bracket_end = top;            // 记录方括号内最后一个元素的位置 也即此时的top
            while(stack[top] != '[')          // 循环直到第一个[位置 此时top指向[
                top -- ;
            int inner_bracket_str_len = bracket_end - top;   // 括号内字符串的长度
            // 记录括号内字符串
            char * inner_bracket_str = calloc(inner_bracket_str_len + 1, sizeof(char));
            strncpy(inner_bracket_str, stack+top+1, inner_bracket_str_len);
            // 获取重复次数
            top--;                            // 因为在上面过程结束时 top指向的是[ 所以需要减一
            int digit_end = top;              // 记录数字字符串的最后一个位置 也即此时的top
            // 此处 top >= 0 的判断是因为可能遍历到位置0 进入循环后top = -1 导致数据越界
            // 不必担心top = -1会影响tmp_merge的合并 因为是++top
            while(top >= 0 && stack[top] <= '9' && stack[top] >= '0')  // 循环找到非数字字符的位置
                top--;
            int bracket_repeat_num_str_len = digit_end - top ;
            char * bracket_repeat_num_str = calloc(bracket_repeat_num_str_len + 1, sizeof(char));
            strncpy(bracket_repeat_num_str, stack+top+1, bracket_repeat_num_str_len);

            int repeat = str_num_to_int(bracket_repeat_num_str);
            char * tmp_merge = repeat_str(inner_bracket_str, repeat);
            for(int i = 0; i < strlen(tmp_merge); i++) {
                stack[++top] = tmp_merge[i]; // 第一次进入循环时 top指向非数字字符 因此避免覆盖 需要先加再赋值
            }
            // 循环后top指向最后一个字符 需要加1 指向可用位置 并赋值空字符 表示字符串结束
            top++;
            stack[top] = '\0';
        }

    }

    return stack;
}

int main() {

    char s[] = "2[a]";
    printf("%s\n", decodeString(s));


    return 0;
}
