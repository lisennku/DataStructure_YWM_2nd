//
// Created by lisen on 24-8-26.
//
// 医学研究者最近发现了某些新病毒，通过对这些病毒的分析，得知它们的DNA序列都是环状的。
// 现在研究者收集了大量的病毒DNA和人的DNA数据，想快速检测出这些人是否感染了相应的病毒。
// 为方便研究，研究者将人的DNA和病毒的DNA均表示成由一些小写字母组成的字符串，然后检测某种病毒的DNA序列是否在患者的DNA序列中出现过，
// 如果出现过，则此人感染了病毒，否则没有感染。
// 注意：人的DNA序列是线性的，而病毒的DNA序列是环状的。

#include <iso646.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

struct static_string {
    char ch[MAX_SIZE+1];
    unsigned int length;
};
typedef struct static_string SString;

void static_string_init(SString * s) {
    memset(s->ch, '\0', MAX_SIZE + 1);
    s->length = 0;
}
void static_string_copy(SString * s, const char * source, int len) {
    int i ;
    for(i = 1; i <= len; i ++) {
        s->ch[i] = source[i-1];
    }
    s->ch[i] = '\0';

    s->length = len;
}

void calc_kmp_nextval(SString t, int * arr) {
    int i = 1;
    arr[1] = 0;
    int j = 0;
    while(i < t.length) {
        if(j==0 || (t.ch[i] == t.ch[j])) {
            ++i; ++j;
            if(t.ch[i] == t.ch[j])
                arr[i] = arr[j];
            else
                arr[i] = j;
        }
        else
            j = arr[j];
    }
}
int index_kmp(SString s, SString t, int pos, int *arr) {
    int i = pos;
    int j = 1;
    while(i <= s.length && j <= t.length) {
        if(j == 0 || (s.ch[i] == t.ch[j])) {
            ++i;
            ++j;
        }
        else
            j = arr[j];
    }
    if(j > t.length)
        return 1;
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
    char main_s[MAX_SIZE];
    char pattern[MAX_SIZE];

    while(scanf("%s %s", pattern, main_s) == 2) {
        if(!strcmp(main_s, "0") && !strcmp(pattern, "0"))
            break;
        SString human, virus;
        static_string_copy(&human, main_s, strlen(main_s));
        static_string_copy(&virus, pattern, strlen(pattern));

        char tmp_virus_str[2*virus.length+2];
        expand_virus_dna(tmp_virus_str, virus);

        int loop = 1;
        int match = 0;
        while (loop <= virus.length) {
            SString cur;
            static_string_copy(&cur, tmp_virus_str+loop, virus.length);
            int nextval[cur.length + 1];
            calc_kmp_nextval(cur, nextval);

            if (index_kmp(human, cur, 1, nextval))
                match ++;
            loop ++;
        }
        if(match > 0)
            printf("YES\n");
        else
            printf("NO\n");

    }
}