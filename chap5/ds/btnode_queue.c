//
// Created by lisen on 24-8-28.
//
#include <stdlib.h>
#include <stdbool.h>
#include "btnode_queue.h"

// 初始化
void bt_linked_queue_init(BT_Queue * q) {
    q->front = (BT_QNode *) malloc(sizeof(BT_QNode));
    if(q->front == NULL)
        exit(EXIT_FAILURE);
    q->front->next = NULL;
    q->rear = q->front;
}

// 判断是否为空
bool bt_linked_queue_is_empty(BT_Queue q) {
    return q.front == q.rear ? true : false;
}

// 获取长度
int bt_linked_queue_length(BT_Queue q) {
    int len = 0;
    BT_QNode * p = q.front->next;
    while(p) {
        len ++;
        p = p->next;
    }
    return len;
}

// 入队
void bt_linked_queue_enqueue(BT_Queue * q, BTNode * e) {
    BT_QNode * new = (BT_QNode *) malloc(sizeof(BT_QNode));
    if(new == NULL)
        exit(EXIT_FAILURE);
    new->node = e;
    new->next = NULL;
    q->rear->next = new;
    q->rear = new;
}

// 出队
void bt_linked_queue_dequeue(BT_Queue * q, BTNode ** e) {
    if(q->rear == q->front)
        *e = NULL;
    else {
        BT_QNode * del = q->front->next;
        *e = del->node;
        q->front->next = del->next;
        if(q->rear == del)
            q->rear = q->front;
        free(del);
    }
}

// 获取队首元素
BTNode * bt_linked_queue_get_first(BT_Queue q) {
    if(q.rear == q.front)
        return NULL;
    return q.front->next->node;
}