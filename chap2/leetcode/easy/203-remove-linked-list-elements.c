//
// Created by lisen on 24-8-15.
// https://leetcode.cn/problems/remove-linked-list-elements/description/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};
typedef struct ListNode Node;
typedef struct ListNode * List;

struct ListNode* removeElements(struct ListNode* head, int val) {
    List tail = NULL;                 // 新链表，初始化为NULL，尾指针
    List ret_head = tail;             // 和tail表示同一个链表，头指针
    List cur = head;

    while(cur) {
        if(cur->val != val) {        // 不等于，放入新链表
            if(tail == NULL) {
                tail = ret_head = cur;
            }
            else {
                tail->next = cur;
                tail = cur;
            }
        }
        cur = cur->next;             // 等于的情况直接找下一个结点，不等于处理完后也要找下一个结点
    }
    // 当tail不为空，说明新链表里有结点
    // 此时需要注意的是，新链表的尾结点的next属性存在两种情况
    //  - 为NULL，说明是从旧链表里拿到的最后一个结点，且结点值和val不同
    //  - 不为NULL，说明是从就有链表里拿到的非最后一个结点，而旧链表该节点后的结点值和val相同，所以没有加到新链表
    //      - 此时需要将新链表的尾结点的next属性置为空
    if(tail != NULL)
        tail->next = NULL;
    return ret_head;
}