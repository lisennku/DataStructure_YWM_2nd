//
// Created by lisen on 24-10-16.
//
// https://leetcode.cn/problems/greatest-common-divisor-of-strings/?envType=study-plan-v2&envId=leetcode-75
// 对于字符串 s 和 t，只有在 s = t + t + t + ... + t + t（t 自身连接 1 次或多次）时，我们才认定 “t 能除尽 s”
// 给定两个字符串 str1 和 str2 。 返回 最长字符串 x，要求满足 x 能除尽 str1 且 x 能除尽 str2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int calc_gcd(int a, int b) {
    while(b > 0) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

char* gcdOfStrings(char* str1, char* str2) {
    /*
     * 题目意在求出两个字符串最长的公共部分 再次之外 题目还有如下意思
     *  s1/s2若能被同一个字符串x整除 说明s1/s2内的字符去重后相同
     *  且按照xxx..xx的模式反复出现 因此 将两个字符串按照s1s2和s2s1的顺序拼接后必然一样
     * 因此 可以根据s1/s2的长度求出长度上的最大公约数 此公约数也即x的长度
     * 另外判断 如果按照s1s2和s2s1的顺序拼接后的字符串一样 则可按照x返回子字符串
     * 否则返回NULL
     */

    int l1 = strlen(str1);
    int l2 = strlen(str2);

    char * res = (char *) calloc(l1 + l2 + 1, sizeof(char));
    char * s1s2 = (char *) calloc(l1 + l2 + 1, sizeof(char));
    char * s2s1 = (char *) calloc(l1 + l2 + 1, sizeof(char));
    if(res == NULL || s1s2 == NULL || s2s1 == NULL)
        exit(EXIT_FAILURE);
    strcpy(s1s2, str1);
    strcat(s1s2, str2);
    strcpy(s2s1, str2);
    strcat(s2s1, str1);

    int l_gcd = calc_gcd(
        l1 > l2 ? l1 : l2,
        l1 > l2 ? l2 : l1
    );

    if(strcmp(s1s2, s2s1) == 0) {
        for(int i = 0; i < l_gcd; i++)
            res[i] = str1[i];
        return res;
    }
    return "";
}

int main() {
    char * str1 = "ABCABC";
    char * str2 = "ABC";
    char * r = gcdOfStrings(str1, str2);
    printf("%s\n", r);
}