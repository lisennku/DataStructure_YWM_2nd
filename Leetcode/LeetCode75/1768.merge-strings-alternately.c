//
// Created by lisen on 24-10-16.
//
// https://leetcode.cn/problems/merge-strings-alternately/description/?envType=study-plan-v2&envId=leetcode-75
// 给你两个字符串 word1 和 word2 。请你从 word1
// 开始，通过交替添加字母来合并字符串。如果一个字符串比另一个字符串长，就将多出来的字母追加到合并后字符串的末尾。
// 返回 合并后的字符串

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char * mergeAlternately(char * word1, char * word2){
    int l1 = strlen(word1);
    int l2 = strlen(word2);

    int common = l1 > l2 ? l2 : l1;

    char * res = (char *) calloc(l1 + l2 + 1, sizeof(char));
    if(res == NULL)
        exit(EXIT_FAILURE);
    int res_idx = 0;
    int i ;
    for(i = 0; i < common; i ++) {
        res[res_idx++] = word1[i];
        res[res_idx++] = word2[i];
    }

    while (i < l1)
        res[res_idx++] = word1[i++];
    while (i < l2)
        res[res_idx++] = word2[i++];

    return res;
}

int main() {
    char * s1 = "ab";
    char * s2 = "pqrs";

    char * m = mergeAlternately(s1, s2);
    for(int i = 0; i < strlen(m); i++)
        printf("%c", m[i]);

    return 0;
}
