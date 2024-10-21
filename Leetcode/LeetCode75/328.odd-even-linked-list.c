//
// Created by lisen on 24-10-21.
//
// 给定单链表的头节点 head ，将所有索引为奇数的节点和索引为偶数的节点分别组合在一起，然后返回重新排序的列表
// 第一个节点的索引被认为是 奇数 ， 第二个节点的索引为 偶数 ，以此类推
// 请注意，偶数组和奇数组内部的相对顺序应该与输入时保持一致
// 你必须在 O(1) 的额外空间复杂度和 O(n) 的时间复杂度下解决这个问题

#include <stdlib.h>
#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* oddEvenList(struct ListNode* head) {
    if(head == NULL || head->next == NULL || head->next->next == NULL) // 空链表或只有1-2个结点的链表 结果是其本身 直接返回
        return head;
    // 其他情况
    struct ListNode * odd = head;
    struct ListNode * even = head->next;
    struct ListNode * even_head = head->next;

    while(even != NULL && even->next != NULL) {
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }
    odd->next = even_head;
    return head;
}

int main() {
    int nums[] = {1,2,3,4,5};
    int numsSize = sizeof(nums) / sizeof(int);
    /* // 带有头结点的链表创建
    struct ListNode * head = malloc(sizeof(struct ListNode)) ;
    head->next = NULL;

    for(int i = 0; i < numsSize; i++) {
        struct ListNode * p = head;
        while(p->next != NULL)
            p = p->next;
        struct ListNode * new = malloc(sizeof(struct ListNode));
        new->val = nums[i];
        new->next = NULL;

        p->next = new;
    }
    */
    // 无头结点的链表
    struct ListNode * head = NULL;
    for(int i = 0; i < numsSize; i++) {
        struct ListNode * new = malloc(sizeof(struct ListNode));
        new->val = nums[i];
        new->next = NULL;
        if(head == NULL)
            head = new;
        else {
            struct ListNode * p = head;
            while(p->next != NULL)
                p = p->next;
            p->next = new;
        }
    }

    struct ListNode * q = head;
    while(q != NULL) {
        printf("%d ", q->val);
        q = q->next;
    }

    struct ListNode * res = oddEvenList(head);
    while(res != NULL) {
        printf("%d ", res->val);
        res = res->next;
    }
}