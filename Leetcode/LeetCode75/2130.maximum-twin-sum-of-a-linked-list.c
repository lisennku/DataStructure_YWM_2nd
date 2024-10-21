//
// Created by lisen on 24-10-21.
//
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

int pairSum(struct ListNode* head) {
    struct ListNode * start = head;
    struct ListNode * slow = head;
    struct ListNode * fast = head;
    struct ListNode * mid = NULL;

    if(head->next->next == NULL)
        return (head->val + head->next->val);

    // 找到中点 slow
    while (fast != NULL && fast->next != NULL) {
        mid = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    // 逆转slow后的链表
    struct ListNode * curr = slow;
    struct ListNode * next = NULL;
    struct ListNode * prev = NULL;
    while(curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    int max_sum = -1;
    while (prev != NULL) {
        if(prev->val + start->val > max_sum)
            max_sum = prev->val + start->val;
        prev = prev->next;
        start = start->next;
    }

    return max_sum;
}

int main() {
    int nums[] = {5,4,2,1};
    int numsSize = sizeof(nums) / sizeof(int);

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
    putchar('\n');

    printf("%d\n", pairSum(head));

    return 0;
}
