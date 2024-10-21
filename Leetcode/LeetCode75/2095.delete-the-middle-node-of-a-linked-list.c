//
// Created by lisen on 24-10-21.
//
// 给你一个链表的头节点 head 。删除 链表的 中间节点 ，并返回修改后的链表的头节点 head
//长度为 n 链表的中间节点是从头数起第 ⌊n / 2⌋ 个节点（下标从 0 开始），其中 ⌊x⌋ 表示小于或等于 x 的最大整数
//对于 n = 1、2、3、4 和 5 的情况，中间节点的下标分别是 0、1、1、2 和 2

// 采取快慢指针
// 快指针一次走两步 慢指针一次走一步 这样快指针速度是慢指针的2倍
// 当快指针到达链表尾部 则慢指针正好达到中点

#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};
struct ListNode* deleteMiddle(struct ListNode* head) {
    struct ListNode * prev = NULL;
    struct ListNode * slow = head;
    struct ListNode * fast = head;

    if(head == NULL || head->next == NULL)  // 题目保证至少一个结点 如果只有一个结点 去掉后返回的应该是NULL
        return NULL;

    while(fast != NULL && fast->next != NULL) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    prev->next = slow->next;

    return head;
}