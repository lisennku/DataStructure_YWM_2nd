//
// Created by lisen on 24-8-19.
//

#ifndef ARRAY_LOOP_QUEUE_H
#define ARRAY_LOOP_QUEUE_H
#if 0
    采取少用一个元素空间实现的循环队列
    为空条件 rear == front
    满队列条件 (front + 1) % size == front
#endif

#include "basic.h"
#include <stdbool.h>

#define MAX_SIZE 100

typedef int Item;

struct loop_queue {
    Item * elem;
    int front;
    int rear;
    int queue_size;
};

typedef struct loop_queue Loop_Queue;

// 初始化
Status loop_queue_init(Loop_Queue * q);

// 判断是否为空
bool loop_queue_is_empty(Loop_Queue q);

// 获取长度
int loop_queue_length(Loop_Queue q);

// 入队
Status loop_queue_enqueue(Loop_Queue * q, Item e);

// 出队
Status loop_queue_dequeue(Loop_Queue * q, Item * e);

// 获取队首元素
Item loop_queue_get_first(Loop_Queue q);

// 遍历队列
void loop_queue_traverse(Loop_Queue q, void (*pfun)(Item e)) ;

#endif //ARRAY_LOOP_QUEUE_H
