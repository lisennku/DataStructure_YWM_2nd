//
// Created by lisen on 24-11-4.
//
// https://www.bjfuacm.com/problem/229


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

void list_create(List * l1, int cnt1) {
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

void list_decompose(List l, List *lp, List *ln) {
    Node * positive = *lp;
    Node * negtive = *ln;
    Node * head = l->next;
    while(head != NULL) {
        if(head->val < 0) {
            negtive->next = head;
            negtive = negtive->next;
        }
        else {
            positive->next = head;
            positive = positive->next;
        }
        head = head->next;
    }

    positive->next = negtive->next = NULL;
}

int main() {

    int cnt1;
    while(scanf("%d", &cnt1) == 1) {
        if(cnt1 == 0 )
            break;

        List l1;
        List lp;
        List ln;

        list_init(&l1);
        list_init(&lp);
        list_init(&ln);
        list_create(&l1, cnt1);
        list_decompose(l1, &lp, &ln);
        list_display(ln);
        list_display(lp);

    }
}
