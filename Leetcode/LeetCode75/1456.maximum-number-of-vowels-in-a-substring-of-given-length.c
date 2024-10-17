//
// Created by lisen on 24-10-17.
//
// https://leetcode.cn/problems/maximum-number-of-vowels-in-a-substring-of-given-length/description/?envType=study-plan-v2&envId=leetcode-75

// 给你字符串 s 和整数 k
// 请返回字符串 s 中长度为 k 的单个子字符串中可能包含的最大元音字母数
// 英文中的 元音字母 为（a, e, i, o, u）

#include <stdio.h>
#include <string.h>

int maxVowels(char* s, int k) {
    int cnt = 0;
    char vowels[] = "aeiou";

    for(int i = 0; i < k; i++)
        if(strchr(vowels, s[i]) != NULL)
            cnt++;
    int max_cnt = cnt;

    for(int i = 1; i <= strlen(s) - k; i++) {
        if(strchr(vowels, s[i-1]) != NULL)
            cnt --;
        if(strchr(vowels, s[i + k - 1]) != NULL)
            cnt ++;
        if(max_cnt < cnt)
            max_cnt = cnt;
    }

    return max_cnt;
}

int main() {
    char s[] = "abciiidef";
    int k = 3;

    printf("%d\n", maxVowels(s, k));

    return 0;
}