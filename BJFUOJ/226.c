//
// Created by lisen on 24-10-18.
//

/*
 * 先逆向链表 再合并
 */

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

List list_reverse(List * l) {
    Node * curr = (*l)->next;
    Node * prev = NULL;
    Node * next = NULL;
    while(curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    List res;
    list_init(&res);
    res->next = prev;

    return res;
}

List list_merge(List l1, List l2) {
    Node * p1 = l1->next;
    Node * p2 = l2->next;
    List res ;
    list_init(&res);

    List head = res;

    while(p1 != NULL && p2 != NULL) {
        if(p1->val > p2->val) {
            head->next = p1;
            head = head->next;
            p1 = p1->next;
        }
        else {
            head->next = p2;
            head = head->next;
            p2 = p2->next;
        }
    }

    while(p1) {
        head->next = p1;
        head = head->next;
        p1 = p1->next;
    }

    while(p2) {
        head->next = p2;
        head = head->next;
        p2 = p2->next;
    }
    return res;
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
        List r1 = list_reverse(&l1);
        List r2 = list_reverse(&l2);

        List res = list_merge(r1, r2);
        list_display(res);
    }
}
