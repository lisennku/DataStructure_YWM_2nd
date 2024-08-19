//
// Created by lisen on 24-8-19.
//
#include <stdlib.h>
#include <stdbool.h>
#include "basic.h"
#include "array_loop_queue.h"

// 初始化
Status loop_queue_init(Loop_Queue * q) {
    /*
     * 为elem成员动态分配内存
     * 初始化front和rear为0
     */
    q->elem = (Item *) malloc(sizeof(Item) * MAX_SIZE);
    if(q->elem == NULL)
        return OVERFLOW;
    q->front = q->rear = 0;
    q->queue_size = MAX_SIZE;

    return OK;
}

// 判断是否为空
bool loop_queue_is_empty(Loop_Queue q) {
    return q.front == q.rear ? true : false;
}

// 获取长度
int loop_queue_length(Loop_Queue q) {
    /*
     * 返回长度
     * 由于采用循环队列，在rear-front的基础上需要加上队列长度后再对队列长度求模
     */
    return (q.rear - q.front + q.queue_size) % q.queue_size;
}

// 入队
Status loop_queue_enqueue(Loop_Queue * q, Item e) {
    /*
     * 判断队列是否满了
     * 满队列条件 (front + 1) % size == front
     * 从队尾入队
     */
    if((q->rear + 1) % q->queue_size == q->front)
        return ERROR;
    q->elem[q->rear] = e;
    // q->rear ++;   // 因为是循环队列，因此不能简单的自增
    q->rear = (q->rear + 1) % q->queue_size;

    return OK;
}

// 出队
Status loop_queue_dequeue(Loop_Queue * q, Item * e) {
    /*
     * 判断队列非空
     * 空队列条件 front == rear
     * 从队首出队
     */
    if(q->front == q->rear)
        return ERROR;
    *e = q->elem[q->front];
    q->front = (q->front + 1) % q->queue_size;

    return OK;
}

// 获取队首元素
Item loop_queue_get_first(Loop_Queue q) {
    /*
     * 判断队列非空
     */
    if(q.front != q.rear)
        return q.elem[q.front];
}

// 遍历队列
void loop_queue_traverse(Loop_Queue q, void (*pfun)(Item e)) {
    for(int i = q.front; i != q.rear; i = (i + 1) % q.queue_size) {
        (*pfun)(q.elem[i]);
    }
}