//
// Created by lisen on 24-8-28.
//

#ifndef BTNODE_QUEUE_H
#define BTNODE_QUEUE_H

#include <stdbool.h>
#include "btnode.h"

struct bt_queue_node {
    BTNode * node;
    struct bt_queue_node * next;
};

typedef struct bt_queue_node BT_QNode;

struct bt_queue {
    BT_QNode * front;
    BT_QNode * rear;
};

typedef struct bt_queue BT_Queue;

// 初始化
void bt_linked_queue_init(BT_Queue * q);

// 判断是否为空
bool bt_linked_queue_is_empty(BT_Queue q);

// 获取长度
int bt_linked_queue_length(BT_Queue q);

// 入队
void bt_linked_queue_enqueue(BT_Queue * q, BTNode * e);

// 出队
void bt_linked_queue_dequeue(BT_Queue * q, BTNode ** e);

// 获取队首元素
BTNode * bt_linked_queue_get_first(BT_Queue q);

#endif //BTNODE_QUEUE_H
