//
// Created by lisen on 24-8-15.
// https://leetcode.cn/problems/remove-duplicates-from-sorted-list/description/

#include <stdlib.h>
#include <stdio.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* deleteDuplicates(struct ListNode* head) {
    if(head == NULL)
        return NULL;
    if(head->next == NULL)
        return head;

    struct ListNode * cur = head;

    while(cur != NULL && cur->next != NULL) {
        struct ListNode * next = cur->next;
        struct ListNode * prev = cur;
        while(next != NULL) {
            if(cur->val == next->val) {
                prev->next = next->next;
                free(next);
                next = prev->next;
            }
            else {
                prev = next;
                next = next->next;
            }
        }
        cur = cur->next;
    }

    return cur;
}