//
// Created by lisen on 24-10-18.
//
#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 1000

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

List list_merge(List l1, List l2) {
    List res = (Node *) malloc(sizeof(Node));
    if(res == NULL)
        exit(EXIT_FAILURE);

    int * hash_table = calloc(HASH_SIZE, sizeof(int));
    if (hash_table == NULL)
        exit(EXIT_FAILURE);

    Node * p1 = l1->next;
    Node * p2 = l2->next;
    Node * head = res;

    while(p1 && p2) {
        if(p1->val < p2->val) {
            if(hash_table[p1->val] == 0) {
                hash_table[p1->val] = 1;

                head->next = p1;
                head = head->next;

                p1 = p1->next;
            }
            else
                p1 = p1->next;
        }
        else {
            if(hash_table[p2->val] == 0) {
                hash_table[p2->val] = 1;
                head->next = p2;
                head = head->next;
                p2 = p2->next;
            }
            else
                p2 = p2->next;
        }
    }

    while(p1) {
        if(hash_table[p1->val] == 0) {
            hash_table[p1->val]++;
            head->next = p1;
            head = head->next;
        }
        p1 = p1->next;
    }

    while(p2) {
        if(hash_table[p2->val] == 0) {
            hash_table[p2->val]++;
            head->next = p2;
            head = head->next;
        }
        p2 = p2->next;
    }
    head->next = NULL;
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
        List l = list_merge(l1, l2);
        // list_display(l1);
        // list_display(l2);
        list_display(l);
    }



}
