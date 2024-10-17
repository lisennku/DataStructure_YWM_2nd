//
// Created by lisen on 24-10-16.
//
// https://leetcode.cn/problems/string-compression/description/?envType=study-plan-v2&envId=leetcode-75
// 给你一个字符数组 chars ，请使用下述算法压缩：
// 从一个空字符串 s 开始。对于 chars 中的每组 连续重复字符 ：
// 如果这一组长度为 1 ，则将字符追加到 s 中。
// 否则，需要向 s 追加字符，后跟这一组的长度。
// 压缩后得到的字符串 s 不应该直接返回 ，需要转储到字符数组 chars 中。需要注意的是，如果组长度为 10 或 10 以上，则在 chars 数组中会被拆分为多个字符。
// 请在 修改完输入数组后 ，返回该数组的新长度。
// 你必须设计并实现一个只使用常量额外空间的算法来解决此问题。

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 2001

int compress(char* chars, int charsSize){
    int base = 0;             // 基准指针
    int offset = 1;           // 快速指针 用于判断是否有重复元素
    int new_pos = 0;          // 原地修改数组的指针

    if(charsSize == 1) {      // 特殊判断 长度为1 直接返回
        return 1;
    }
    while(offset <= charsSize) {          // 边界判断 当offset等于字符串长度时 base可能指向最后一个字符的位置 所以要判断
        while(offset < charsSize && chars[base] == chars[offset]) {
            offset ++;
        }
        chars[new_pos++] = chars[base];
        if(offset - base > 1) {
            char tmp[10];
            sprintf(tmp, "%d", offset - base);
            for(int i = 0; i < strlen(tmp); i++)
                chars[new_pos++] = tmp[i];
        }
        base = offset;
        offset++;
    }

    return new_pos;
}

int main() {
    char chars[] = "abc";
    int charsSize = strlen(chars);

    int new_len = compress(chars, charsSize);
    for(int i = 0; i < new_len; i++)
        printf("%c", chars[i]);
    printf("\n%d\n", new_len);
    return 0;
}