//
// Created by lisen on 24-8-19.
//

#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include <stdbool.h>
#include "basic.h"

typedef int Item;
struct node {
    Item data;
    struct node * next;
};
typedef struct node QNode;
typedef struct node * QueuePtr;

struct queue {
    QueuePtr front;
    QueuePtr rear;
};

typedef struct queue Linked_Queue;

// 初始化
Status linked_queue_init(Linked_Queue * q);

// 判断是否为空
bool linked_queue_is_empty(Linked_Queue q);

// 获取长度
int linked_queue_length(Linked_Queue q);

// 入队
Status linked_queue_enqueue(Linked_Queue * q, Item e);

// 出队
Status linked_queue_dequeue(Linked_Queue * q, Item * e);

// 获取队首元素
Item linked_queue_get_first(Linked_Queue q);

// 遍历队列
void linked_queue_traverse(Linked_Queue q, void (*pfun)(Item e)) ;

#endif //LINKED_QUEUE_H
