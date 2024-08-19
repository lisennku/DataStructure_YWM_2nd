//
// Created by lisen on 24-8-16.
// https://leetcode.cn/problems/palindrome-linked-list/

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

struct ListNode * halfList(struct ListNode * head) {
    struct ListNode* fast = head;
    struct ListNode* slow = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

bool isPalindrome(struct ListNode* head) {
    if (head == NULL) {
        return true;
    }

    // 找到前半部分链表的尾节点并反转后半部分链表
    struct ListNode* firstHalfEnd = halfList(head);
    struct ListNode* secondHalfStart = reverseList(firstHalfEnd->next);

    // 判断是否回文
    struct ListNode* p1 = head;
    struct ListNode* p2 = secondHalfStart;
    bool result = true;
    while (result && p2 != NULL) {
        if (p1->val != p2->val) {
            result = false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    // 还原链表并返回结果
    firstHalfEnd->next = reverseList(secondHalfStart);
    return result;
}