#include <stdlib.h>
//
// Created by lisen on 24-10-18.
//


struct ListNode {
    int val;
    struct ListNode *next;
};
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode * p1 = list1;
    struct ListNode * p2 = list2;

    struct ListNode * res = (struct ListNode *) malloc(sizeof(struct ListNode));
    if(res == NULL)
        exit(EXIT_FAILURE);

    struct ListNode * head = res;

    while(p1 && p2) {
        if(p1->val < p2->val) {
            head->next = p1;
            head = p1;
            p1 = p1->next;
        }
        else {
            head->next = p2;
            head = p2;
            p2 = p2->next;
        }
    }
    if(p1)
        head->next = p1;
    else {
        head->next = p2;
    }

    return res->next;
}