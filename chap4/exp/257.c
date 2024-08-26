//
// Created by lisen on 24-8-26.
//
// 对应算法设计第一题
// 写一个算法统计在输入字符串中各个不同字符出现的频度并将结果输出(字符串中的合法字符为A-Z之间的26个字母和0-9之间的10个数字)。
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

int main() {
    // char target[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'} ;


    char input[MAX_SIZE];

    while(scanf("%s", input) == 1) {
        int counter[36];  // 前10个表示0-9，后26个表示A-Z
        memset(counter, 0, 36 * sizeof(int));
        if(!strcmp(input, "0"))
            break;
        for(int i = 0; i < strlen(input); i++) {
            if(input[i] >= '0' && input[i] <= '9')
                counter[input[i] - 48]++;  // ASCII中0在第48个

            if(input[i] >= 'A' && input[i] <= 'Z')
                counter[input[i] - 55] ++; // ASCII中A在第65个，但是在counter中脚标为10
        }
        for(int i = 0; i < 36; i ++) {
            if(counter[i] != 0) {
                if(i <=9 && i >= 0)
                    printf("%c:%d\n", i+48, counter[i]);
                else
                    printf("%c:%d\n", i+55, counter[i]);
            }
        }
    }
}