//
// Created by lisen on 24-10-17.
//
// https://leetcode.cn/problems/is-subsequence/description/?envType=study-plan-v2&envId=leetcode-75
// 给定字符串 s 和 t ，判断 s 是否为 t 的子序列。
// 字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。 （例如，"ace"是"abcde"的一个子序列，而"aec"不是）。

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool isSubsequence(char* s, char* t) {
    int i = 0;
    int j = 0;
    int find = 0;
    for(i = 0; i < strlen(s); i++) {           // loop s
        for(j = find; j < strlen(t); j++) {    // loop t
            if(s[i] == t[j]) {
                find = j + 1;
                break;
            }
        }
        if(j == strlen(t))
            return false;
    }
    return true;
}

int main() {
    char s[] = "axc";
    char t[] = "ahbgdc";
    bool flag = isSubsequence(s, t);
    printf("%d\n", flag);

    return 0;
}