//
// Created by lisen on 24-8-19.
//
#include <stdlib.h>
#include <stdbool.h>
#include "basic.h"
#include "linked_queue.h"


// 初始化
Status linked_queue_init(Linked_Queue * q) {
    /*
     * 为头结点分配内存空间
     * 并将rear和front指向头结点
     */
    q->front = (QNode *) malloc(sizeof(QNode));   // 分配内存空间并将front指向该地址
    if(q->front == NULL)
        return OVERFLOW;
    q->front->next = NULL;                            // 头结点的next初始化
    q->rear = q->front;                               // rear指针初始化

    return OK;
}

// 判断是否为空
bool linked_queue_is_empty(Linked_Queue q) {
    /*
     * 通过判断头结点的next是否为null判断
     * 也可以使用front==rear判断
     */
    return q.rear == q.front ? true : false;
}

// 获取长度
int linked_queue_length(Linked_Queue q) {
    /*
     * 获取长度时不能使用rear-front，因为此时是链表，无法确定内存上是连续的
     */
    int len = 0;
    QNode * p = q.front->next;
    while(p) {
        len ++;
        p = p->next;
    }
    return len;
}

// 入队
Status linked_queue_enqueue(Linked_Queue * q, Item e) {
    /*
     * 不需要做长度检查
     */
    QNode * new = (QNode *) malloc(sizeof(QNode));
    if(new == NULL)
        return OVERFLOW;
    new->data = e;
    // 链表更新
    new->next = NULL;                // 新结点的next更新为NULL
    q->rear->next = new;             // 尾指针此时的next更新为插入结点
    q->rear = new;                   // 尾指针更新为插入结点

    return OK;
}

// 出队
Status linked_queue_dequeue(Linked_Queue * q, Item * e) {
    /*
     * 需要检查队列是否为空
     */
    if(q->rear == q->front)
        return ERROR;
    QNode *del = q->front->next;    // 待删除结点的指针指向首元结点
    *e = del->data;
    q->front->next = del->next;     // 头结点的next属性更新为待删除结点的下一个结点
    // 注意当弹出的是最后一个结点，此时尾指针失效，需要判断并重新赋值
    if(q->rear == del)
        q->rear = q->front;
    free(del);

    return OK;
}

// 获取队首元素
Item linked_queue_get_first(Linked_Queue q) {
    if (q.rear != q.front)
        return q.front->next->data;
}

// 遍历队列
void linked_queue_traverse(Linked_Queue q, void (*pfun)(Item e)) {
    QNode * cur = q.front->next; // cur 指向首元结点
    while(cur) {
        (*pfun)(cur->data);
        cur = cur->next;
    }
}