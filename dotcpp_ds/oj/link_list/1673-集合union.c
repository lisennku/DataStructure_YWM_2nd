//
// Created by lisen on 24-11-5.
//

#include <stdlib.h>
#include <stdio.h>

#define HASHSIZE 100001

typedef struct Node {
    int data;
    struct Node * next;
}Node, * List;

void list_init(List *l) {
    (*l) = calloc(1, sizeof(Node));
    if(*l == NULL)
        exit(EXIT_FAILURE);
    (*l)->next = NULL;
}

Node * create_node(int data) {
    Node * new = calloc(1, sizeof(Node));
    if(new == NULL)
        exit(EXIT_FAILURE);

    new->data = data;
    new->next = NULL;

    return new;
}

void list_create(List * l, int cnt) {
    int num;

    while(cnt > 0) {
        cnt -- ;
        scanf("%d", &num);
        Node * new = create_node(num);
        Node * p = *l;
        while(p->next != NULL) {
            p = p->next;
        }
        p->next = new;
    }
}

int list_length(List l) {
    int len = 0;
    Node * p = l->next;
    while(p != NULL) {
        len ++;
        p = p->next;
    }

    return len;
}

void list_display(List l) {
    Node * p = l->next;
    while(p) {
        if(p->next == NULL)
            printf("%d\n", p->data);
        else
            printf("%d ", p->data);
        p = p->next;
    }
}

void list_merge(List * l1, List l2) {
    int hash1[HASHSIZE] = {0};
    Node * p = (*l1)->next;
    while(p) {
        hash1[p->data] = 1;
        p = p->next;
    }

    Node * tail = (*l1)->next;
    while(tail->next)
        tail = tail->next;

    Node * q = l2->next;
    while(q) {
        if(hash1[q->data] == 0) {
            Node * next = q->next;
            q->next = NULL;
            tail->next = q;
            tail = tail->next;
            q = next;
            list_display(*l1);
        }
        else {
            q = q->next;
            list_display(*l1);
        }

    }
}



int main() {
    int cnt1, cnt2;

    while(scanf("%d", &cnt1) != EOF) {
        List l1, l2;
        list_init(&l1);
        list_init(&l2);

        list_create(&l1, cnt1);
        scanf("%d", &cnt2);
        list_create(&l2, cnt2);
        list_display(l1);
        list_display(l2);

        list_merge(&l1, l2);
        putchar('\n');
    }
}
