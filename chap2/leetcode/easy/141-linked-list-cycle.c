//
// Created by lisen on 24-8-15.
// https://leetcode.cn/problems/linked-list-cycle/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

// bool hasCycle(struct ListNode *head) { // stupid algorithm
//     // 链表无结点，或者只有一个结点
//     if(head == NULL || head->next == NULL)
//         return false;
//
//     struct ListNode * cur = head;
//     // 由于链表长度至多为10000，因此采取苯办法
//     // 从链表头开始遍历
//     // 循环10001次，每次循环判断next的地址是否和cur地址相同，相同则表示遇到了环
//     // 另外还需判断next是否为NULL，为NULL表示没有环
//     // 另外针对外层循环是否会导致死循环，根据题意是不会发生的，因为在遇到死循环之前，已经return了
//     while(cur != NULL) {
//         struct ListNode * next = cur->next;
//         int loop = 10001;
//         while(loop > 0) {
//             if(next == cur)
//                 return true;
//             if(next == NULL)
//                 return false;
//             next = next->next;
//             loop --;
//         }
//         cur = cur->next;
//     }
//     return false;
// }

bool hasCycle(struct ListNode *head) { // Floyd Cycle Detection Algorithm
    // 链表无结点，或者只有一个结点
    if(head == NULL || head->next == NULL)
        return false;

    struct ListNode * fast = head;
    struct ListNode * slow = head;
    while(fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
        if(slow == fast)
            return true;
    }
    return false;
}