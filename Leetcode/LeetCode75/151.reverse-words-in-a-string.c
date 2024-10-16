//
// Created by lisen on 24-10-16.
//
// https://leetcode.cn/problems/reverse-words-in-a-string/description/?envType=study-plan-v2&envId=leetcode-75
// 给你一个字符串 s ，请你反转字符串中 单词 的顺序。
// 单词 是由非空格字符组成的字符串。 s 中使用至少一个空格将字符串中的 单词 分隔开。
// 返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。
// 注意：输入字符串 s中可能会存在前导空格、 尾随空格或者单词间的多个空格。 返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SPACE ' '

char * trim_and_distinct_space(char * s) {
    /*
     * 用于清除字符串两端的空格 和 保留一个中间重复的空格
     */
    int ls = strlen(s);
    char * new_s = (char *) calloc(ls+1, sizeof(char));
    int lnew = 0;

    int i = 0;
    while(s[i] == SPACE)      // 从开始处查找 直到第一个非空字符
        i++;

    while(s[ls-1] == SPACE)   // 从结尾处查找 直到第一个非空字符
        ls--;

    for(; i < ls; i++)        // 处理中间重复的空格
        if(s[i] != SPACE || (i < ls-1 && s[i+1] != SPACE))  // 如果当前位置不为空 或者 当前位置为空但是下一个位置不为空 则保留
            new_s[lnew++] = s[i];

    return new_s;
}
char * reverse_whole_str(char * s) {
    /*
     * 反转整个字符串
     */
    char * new = (char *) calloc(strlen(s) + 1, sizeof(char));
    if (new == NULL)
        exit(EXIT_FAILURE);
    strcpy(new, s);

    int start = 0;
    int end = strlen(s) - 1;
    while(start < end) {
        new[start] = s[end];
        new[end] = s[start];
        start ++;
        end --;
    }

    return new;
}
char* reverseWords(char* s) {
    /*
     * 按照空格识别每个单词 并将单词反转
     */
    char * new = reverse_whole_str(trim_and_distinct_space(s));
    int l = strlen(new);
    int sub_start = 0;                    // 存储每个单词的开始位置
    for(int i = 0; i < l; i++) {
        if(new[i] == SPACE || i == l-1) { // 此处要注意边界判断 因为此时字符串两端已无空格 所以要特殊识别
            // ss 表示单词的开始
            // se 表示单词的结束
            int ss = sub_start;
            int se = i == l-1 ? i : i-1;  // 如果是末尾的单词 则不减1
            while(ss < se) {              // 反转单词
                char tmp = new[se];
                new[se] = new[ss];
                new[ss] = tmp;
                ss ++;
                se --;
            }
            sub_start = i + 1;
        }
    }
    return new;
}

int main() {
    char s[] = "the sky is blue";
    char * new = reverseWords(s);
    printf("%s", new);
}