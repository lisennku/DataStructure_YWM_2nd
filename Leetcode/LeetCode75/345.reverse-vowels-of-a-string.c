//
// Created by lisen on 24-10-16.
//
// https://leetcode.cn/problems/reverse-vowels-of-a-string/description/?envType=study-plan-v2&envId=leetcode-75
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* reverseVowels(char* s) {
    /*
     * 对于一个字符串而言 反转的本质就是使用头尾指针指向头尾位置 然后对调 头指针+1 尾指针-1 继续对调 直到头尾指针相遇或头指针大于尾指针(针对奇偶长度)
     */
    char vowels[] = "AEIOUaeiou";
    int head = 0;
    int tail = strlen(s) - 1;

    char * res = (char *) calloc(strlen(s) + 1, sizeof(char));
    if(res == NULL)
        exit(EXIT_FAILURE);
    strcpy(res, s);

    while(head < tail) {
        char * h_vowel = strchr(vowels, s[head]);
        char * t_vowel = strchr(vowels, s[tail]);

        if(h_vowel != NULL && t_vowel != NULL) {
            res[head] = s[tail];
            res[tail] = s[head];
            head ++;
            tail --;
        }

        if (h_vowel == NULL) {
            head ++;
        }
        if (t_vowel == NULL) {
            tail --;
        }
    }
    return res;
}

int main() {
    char s[] = "a.";
    char * res = reverseVowels(s);

    printf("%s\n", res);

    return 0;
}
