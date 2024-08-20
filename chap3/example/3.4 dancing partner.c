//
// Created by lisen on 24-8-20.
//
// 使用顺序队列实现，不循环

#include <stdio.h>
#include <stdbool.h>
#include <iso646.h>
#include <string.h>
#include <stdlib.h>
#include "basic.h"

#define MAX_SIZE 100
#define MAX_NAME 100

// 数据结点
struct person {
    char name[MAX_NAME];
    char gender;
};

typedef struct person Person;

struct dance_queue {
    Person *elem;
    int front;
    int rear;
    int queue_size;
};

typedef struct dance_queue DP_queue;

Status dp_array_queue_init(DP_queue * q) {
    q->elem = (Person *) malloc(sizeof(Person) * MAX_SIZE);
    if(q->elem == NULL)
        return OVERFLOW;

    q->front = q->rear = 0;
    q->queue_size = MAX_SIZE;

    return OK;
}

bool dp_array_queue_is_empty(DP_queue q) {
    return q.rear == q.front ? true : false;
}

Person dp_array_queue_get_top(DP_queue q) {
    if(q.rear != q.front)
        return q.elem[q.front];
}

Status dp_array_queue_push(DP_queue * q, Person p) {
    if(q->rear == q->queue_size)
        return ERROR;
    q->elem[q->rear] = p;
    q->rear++;
    return OK;
}

Status dp_array_queue_pop(DP_queue *q, Person *p) {
    if(q->rear == q->front)
        return ERROR;

    *p = q->elem[q->front];
    q->front ++;
    return OK;
}

void read_dances_file(char * filename, Person p[], int * n);

int main() {
    int dance_num;
    Person dance[100];
    Person p;             // 接收pop出来的元素

    read_dances_file("../chap3/example/dances.txt", dance, &dance_num);
    printf("Read file completed, and here is the name list\n");
    for(int i = 0; i < dance_num; i++)
        printf("name %10s, gender %c\n", dance[i].name, dance[i].gender);

    DP_queue male;
    DP_queue female;

    if(dp_array_queue_init(&male) != OK)
        exit(OVERFLOW);
    if(dp_array_queue_init(&female) != OK)
        exit(OVERFLOW);

    for(int i = 0; i < dance_num; i++) {
        if(dance[i].gender == 'M')
            dp_array_queue_push(&male, dance[i]);
        else
            dp_array_queue_push(&female, dance[i]);
    }

    printf("Dancing partners are\n");
    while(!dp_array_queue_is_empty(male) and !dp_array_queue_is_empty(female)) {
        dp_array_queue_pop(&male, &p);
        printf("Mr. %10s ", p.name);

        dp_array_queue_pop(&female, &p);
        printf("Miss %10s\n", p.name);
    }
    printf("Now next person who is waiting for partner is \n");
    if(!dp_array_queue_is_empty(male)) {
        dp_array_queue_pop(&male, &p);
        printf("Mr. %s\n", p.name);
    }

    if(!dp_array_queue_is_empty(female)) {
        dp_array_queue_pop(&female, &p);
        printf("Miss %10s\n", p.name);
    }
}

void read_dances_file(char * filename, Person p[], int * n) {
    char buff[sizeof(Person)+10] ;   // 文件读取缓冲区，+10确保缓冲区足够大
    int len = 0;                       // 记录文件长度
    FILE * fp ;                        // 文件指针
    fp = fopen(filename, "r");
    if(!fp)
        exit(EXIT_FAILURE);

    while(fgets(buff, sizeof(Person)+10, fp)) {
        // fgets保留换行符，此处将buff数组内换行符位置的字符替换为'\0'
        // strcspn返回指定字符串遇到第二个参数里任意字符为止的长度
        buff[strcspn(buff, "\n")] = '\0';
        // strtok分割字符串并返回指针，多次调用只需要传入分隔符即可
        char * token = strtok(buff, " ");
        if(token != NULL) {
            strcpy(p[len].name, token);
            token = strtok(NULL, " ");
            if(token != NULL) {
                p[len].gender = *token;
                len++;
            }
        }
    }

    fclose(fp);

    *n = len;
}