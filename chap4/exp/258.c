//
// Created by lisen on 24-8-26.
//
// 写一个递归算法来实现字符串的逆序存储，要求空间复杂度为O(1)。
#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

void reverse(char * src, int start, int end);

int main() {

    char s[MAX_SIZE];
    while(scanf("%s", s) == 1) {
        if(!strcmp(s,"0"))
            break;
        reverse(s, 0, strlen(s) - 1);
        printf("%s\n", s);
    }
}

void reverse(char * src, int start, int end) {
    if(start >= end)
        return ;
    char tmp = src[start];
    src[start] = src[end];
    src[end] = tmp;

    reverse(src, start+1, end-1);
}