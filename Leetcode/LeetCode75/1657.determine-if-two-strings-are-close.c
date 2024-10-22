//
// Created by lisen on 24-10-22.
//
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void * a, const void * b) {
    return (*(int *)a - *(int *)b);
}

bool closeStrings(char* word1, char* word2) {
    // 两个字符串相近 说明
    // 1. 长度相同 且 字符串内的字符相同
    // 2. 每个字符出现的次数 组成的列表相同
    //      "cabbba" a:2 b:3 c:1
    //      "abbccc" a:1 b:2 c:3
    // 长度判断
    if(strlen(word1) != strlen(word2))
        return false;

    int len = strlen(word1);

    // 字符哈希表
    int hash1[26] = {0};
    int hash2[26] = {0};

    for(int i = 0; i < len; i++) {
        hash1[word1[i] - 'a'] ++;
        hash2[word2[i] - 'a'] ++;
    }
    // 相同字符判断
    for(int i = 0; i < 26; i++)
        if((hash1[i] == 0 && hash2[i] != 0) || (hash1[i] != 0 && hash2[i] == 0))
            return false;

    // // 次数判断
    // // 出现次数的哈希表
    // int hash_cnt1[100000] = {0};
    // int hash_cnt2[100000] = {0};
    //
    // for(int i = 0; i < 26; i++) {
    //     if(hash1[i] != 0)
    //         hash_cnt1[hash1[i]] ++;
    //     if(hash2[i] != 0)
    //         hash_cnt2[hash2[i]] ++;
    // }
    //
    // for(int i = 0; i < 100000; i++)
    //     if(hash_cnt1[i] != hash_cnt2[i])
    //         return false;
    //
    // return true;

    // 对于出现次数的判断 可以对两个哈希表排序后逐个比较
    qsort(hash1, 26, sizeof(int), cmp);
    qsort(hash2, 26, sizeof(int), cmp);
    for(int i = 0; i < 26; i++)
        if(hash1[i] != hash2[i])
            return false;
    return true;
}

int main() {
    char word1[] = "cabbba";
    char word2[] = "abbccc";

    bool flag = closeStrings(word1, word2);

    printf("%d\n", flag);

    return 0;
}
