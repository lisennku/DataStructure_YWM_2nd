//
// Created by lisen on 24-8-26.
//
// 描述
// 编写算法，实现下面函数的功能。 函数void insert(char *s, char *t, int pos)将字符串t插入到字符串s中，插入位置为pos（插在第pos个字符前）。
// 假设分配给字符串s的空间足够让字符串t插入。(说明：不得使用任何库函数)
// 输入
// 多组数据，每组数据有三行，第一行为插入的位置pos，第二行为要被插入的字符串s，第三行为待插入的字符串t。 当pos为“ 0” 时输入结束。
// 输出
// 对于每组数据输出一行，为t插入s后的字符串。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

void insert(char *s, char *t, int pos);

int main() {
    while(1) {
        int pos;
        char src[MAX_SIZE];
        char tgt[MAX_SIZE];
        scanf("%d", &pos);
        if (pos == 0)
            break;
        scanf("%s", src);
        scanf("%s", tgt);

        insert(src, tgt, pos);
        printf("%s\n", src);
    }
}

void insert(char *s, char *t, int pos) {

    int len_t = strlen(t);
    int len_s = strlen(s);

    if(pos < 1 || pos > len_s + 1)
        exit(-1);

    for(int i = len_s; i >= pos; i--) {
        s[i+len_t-1] = s[i-1];
    }

    for(int i = 0; i < len_t; i++) {
        s[pos-1+i] = t[i];
    }
    s[len_s + len_t ] = '\0';
}