//
// Created by lisen on 24-8-14.
//
// https://leetcode.cn/problems/merge-two-sorted-lists/description/


 // Definition for singly-linked list.
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    // list1/list2视为无头结点的链表
    // 由于res是一个带有头结点的，所以返回的是res->next
    // 使用尾指针！
    struct ListNode * p1 = list1;
    struct ListNode * p2 = list2;
    struct ListNode * res = (struct ListNode *) malloc(sizeof(struct ListNode));
    struct ListNode * tail = res;

    if(p1 == NULL)
        return p2;
    if(p2 == NULL)
        return p1;

    while(p1 && p2) {
        if(p1->val < p2->val) {
            tail->next = p1;
            tail = p1;
            p1 = p1->next;
        }
        else {
            tail->next = p2;
            tail = p2;
            p2 = p2->next;
        }
    }

    if(p1)
        tail->next = p1;
    else {
        tail->next = p2;
    }

    return res->next;
}
