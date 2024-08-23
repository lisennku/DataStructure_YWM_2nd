//
// Created by lisen on 24-8-23.
//
// 因为患者的DNA和病毒DNA均是由一些字母组成的字符串序列，要检测某种病毒DNA序列是否在患者的DNA序列中出现过，实际上就是字符串的模式匹配问题。
// 可以利用BF算法，也可以利用更高效的KMP算法。
// 但与一般的模式匹配问题不同的是，此案例中病毒的DNA序列是环状的，这样需要对传统的BF算法或KMP算法进行改进

// 因为病毒DNA长度为m，并且是环状的，所以可以将存储病毒DNA的数组扩大一倍，将其存储2次
// 然后从头开始循环，循环m次，得到了病毒DNA所有的可能性字符串，以此为模式串，并依次比较

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <iso646.h>
#include "basic.h"

#define MAX_SIZE 100
#define FILE_PATH "../chap4/example/virus.txt"

struct static_string {
    char ch[MAX_SIZE+1];
    unsigned int length;
};

typedef struct static_string SString;

Status static_string_init(SString * s) {
    memset(s->ch, '\0', MAX_SIZE + 1);
    s->length = 0;
    return OK;
}
void static_string_copy(SString * s, const char * source, int len) {
    int i ;
    for(i = 1; i <= len; i ++) {
        s->ch[i] = source[i-1];
    }
    s->ch[i] = '\0';

    s->length = len;
}

int index_bf(SString S, SString T, int pos) {
    int i = pos;
    int j = 1;
    while(i <= S.length and j <= T.length) {
        if (S.ch[i] == T.ch[j]) {
            i++;
            j++;
        }
        else {
            i = i - j + 2;
            j = 1;
        }
    }
    if(j > T.length)
        return i - T.length;
    return 0;
}
void calculate_kmp_nextval(SString T, int * nextval) {
    int i = 1;
    nextval[1] = 0;
    int j = 0;

    while(i < T.length) {
        if(j == 0 || (T.ch[i] == T.ch[j])) {
            ++i;
            ++j;
            if(T.ch[i] != T.ch[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        }
        else
            j = nextval[j];
    }
}
int index_kmp(SString S, SString T, int pos, int * nextval) {
    int i = pos;
    int j = 1;
    while(i <= S.length && j <= T.length) {
        if(j == 0 || (S.ch[i] == T.ch[j])) {
            i++;
            j++;
        }
        else
            j = nextval[j];
    }
    if(j > T.length)
        return i - T.length;
    return 0;
}

void expand_virus_dna(char * target, SString virus) {  // 第一位不存内容
    for(int i = 1; i <= virus.length; i++)
        target[i] = virus.ch[i];
    for(int i = 1; i <= virus.length ; i++ )
        target[i + virus.length] = virus.ch[i];
    target[2 * virus.length + 1] = '\0';
}

int main() {
    FILE * file = fopen(FILE_PATH, "r");
    if (file == NULL)
        return ERROR;

    char buff[MAX_SIZE + 1] ;

    // 读取第一行，获取循环次数
    fgets(buff, MAX_SIZE + 1, file);
    int nums = atoi(buff);

    // 循环读取文件内容
    while(nums --) {
        SString virus;
        SString human;

        // 读取整行数据，替换掉最后的换行符，然后以空格' '，将该行数据分割
        fgets(buff, MAX_SIZE +1, file);
        buff[strcspn(buff, "\n")] = '\0';   // 替换换行符
        char * token = strtok(buff, " ");
        if (token != NULL) {
            static_string_copy(&virus, token, strlen(token));
            token = strtok(NULL, " ");
            if(token != NULL) {
                static_string_copy(&human, token, strlen(token));
            }
        }

        char tmp_virus[2*virus.length + 2];          // +2 是因为从索引1开始插入
        expand_virus_dna(tmp_virus, virus);
        printf("Human's DNA is %s: \n", human.ch+1);
        printf("tmp virus DNA is %s\n", tmp_virus+1);

        int loop = 1;
        printf("    Now looping %d times to get Virus's DNA\n", virus.length);

        while(loop <= virus.length) {
            SString cur;
            static_string_copy(&cur, tmp_virus + loop, virus.length);
            printf("        loop time %d's Virus's DNA is %s: \n", loop, cur.ch+1);

            int nextval[cur.length + 1];
            calculate_kmp_nextval(cur, nextval);

            int pos;
            // if (pos = index_bf(human, cur, 1))
            if (pos = index_kmp(human, cur, 1, nextval))
                printf("        Matched! the index starts from position %d\n", pos);
            else
                printf("        NO Match!\n");
            loop ++;
        }
    }

    return 0;
}