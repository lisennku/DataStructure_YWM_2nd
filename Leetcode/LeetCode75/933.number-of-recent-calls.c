//
// Created by lisen on 24-10-22.
//
// 维护队列 每次请求时遍历队列 将**小于**本次请求t-3000的队首元素移出队列

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int * queue;
    int size;
    int head;
    int rear;
} RecentCounter;


RecentCounter* recentCounterCreate() {
    RecentCounter * counter = malloc(sizeof(RecentCounter));
    counter->size = 10001;
    counter->head = counter->rear = 0;
    counter->queue = calloc(counter->size, sizeof(int));

    return counter;
}

int recentCounterPing(RecentCounter* obj, int t) {
    obj->queue[obj->rear ++] = t;
    while(obj->queue[obj->head] < t - 3000)
        obj->head ++;

    return obj->rear - obj->head;
}

void recentCounterFree(RecentCounter* obj) {
    free(obj->queue);
    free(obj);
}