//
// Created by lisen on 24-10-18.
//
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 1000


typedef struct node{
    int val;
    struct node * next;
}Node;

typedef Node * List;

void list_init(List * l) {
    *l = (Node *) malloc(sizeof(Node));
    if(*l == NULL)
        exit(EXIT_FAILURE);

    (*l)->next = NULL;
}

void list_create(List * l1, List * l2, int cnt1, int cnt2) {

    int num1;
    while(cnt1 > 0 && scanf("%d", &num1) == 1) {
        Node * new = malloc(sizeof(Node));
        new->val = num1;
        new->next = NULL;

        Node * tail = (*l1);
        while(tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = new;

        cnt1 --;
    }

    int num2;
    while(cnt2 > 0 && scanf("%d", &num2) == 1) {
        Node * new = malloc(sizeof(Node));
        new->val = num2;
        new->next = NULL;

        Node * tail = (*l2);
        while(tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = new;

        cnt2 --;
    }

}

List list_merge_reverse(List l1, List l2) {
    // 原想采取头插法 但是空间复杂度不是O(1)
    // 使用栈 以数组模拟栈
    Node * stack1[STACK_SIZE];
    Node * stack2[STACK_SIZE];
    int top1 = 0;
    int top2 = 0;

    Node * p1 = l1->next;
    Node * p2 = l2->next;

    while(p1 != NULL) {
        stack1[top1++] = p1;
        p1 = p1->next;
    }
    while(p2 != NULL) {
        stack2[top2++] = p2;
        p2 = p2->next;
    }

    Node * res = malloc(sizeof(Node));
    Node * head = res;

    top1--;
    top2--;

    while(top1 >= 0 && top2 >= 0) {
        if(stack1[top1]->val > stack2[top2]->val)
            head->next = stack1[top1--];
        else
            head->next = stack2[top2--];
        head = head->next;
    }
    while(top1 >= 0) {
        head->next = stack1[top1--];
        head = head->next;
    }
    while(top2 >= 0) {
        head->next = stack2[top2--];
        head = head->next;
    }
}

void list_display(List l) {
    Node * n = l->next;
    while(n != NULL) {
        if(n->next == NULL)
            printf("%d\n", n->val);
        else
            printf("%d ", n->val);
        n = n->next;
    }
}

int main() {

    int cnt1;
    int cnt2;
    while(scanf("%d %d", &cnt1, &cnt2) == 2) {
        if(cnt1 == 0 && cnt2 == 0)
            break;

        List l1;
        List l2;

        list_init(&l1);
        list_init(&l2);
        list_create(&l1, &l2, cnt1, cnt2);
        List l = list_merge_reverse(l1, l2);
        // list_display(l1);
        // list_display(l2);
        list_display(l);
    }



}
