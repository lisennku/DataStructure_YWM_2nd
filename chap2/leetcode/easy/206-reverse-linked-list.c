//
// Created by lisen on 24-8-16.
// https://leetcode.cn/problems/reverse-linked-list/description/


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

struct ListNode* reverseList(struct ListNode* head) {
    Node * prev = NULL;
    Node * cur = head;
    Node * next = NULL;

    while(cur) {
        next = cur->next;   // 记录当前节点的下一个结点
        cur->next = prev;   // 将前一个结点作为当前结点的next
        prev = cur;         // 更新prev
        cur = next;
    }

    return prev;
}
