//
// Created by lisen on 24-11-4.
//
// https://www.dotcpp.com/oj/problem1052.html

#include <stdio.h>
#include <stdlib.h>

struct node {
    int sid;
    int score;
    struct node * next;
};

typedef struct node Node;

typedef struct node * List;

void list_init(List * l) {
    *l = calloc(1, sizeof(Node));
    if(*l == NULL)
        exit(EXIT_FAILURE);

    (*l)->next = NULL;
    (*l)->sid = (*l)->score = -1;
}

Node * list_create_node(int sid, int score) {
    Node * node = calloc(1, sizeof(Node));
    if(node == NULL)
        exit(EXIT_FAILURE);
    node->next = NULL;
    node->sid = sid;
    node->score = score;

    return node;
}

void list_create(List * l, int cnt) {
    // 创建时即排序 也即创建后的链表按照sid非递减的顺序
    while(cnt) {
        cnt -- ;
        int sid, score;
        scanf("%d %d", &sid, &score);
        Node * new = list_create_node(sid, score);

        Node * prev = *l;
        Node * q = (*l)->next;
        while(q != NULL && q->sid < new->sid) {
            prev = q;
            q = q->next;
        }
        prev->next = new;
        new->next = q;

    }
}

List list_merge(List l1, List l2) {
    Node * p = l1->next;
    Node * q = l2->next;
    List l;
    list_init(&l);
    Node * head = l;

    while(p && q) {
        if(p->sid <= q->sid) {
            head->next = p;
            head = head->next;
            p = p->next;
        }
        else {
            head->next = q;
            head = head->next;
            q = q->next;
        }
    }
    if(p)
        head->next = p;
    if(q)
        head->next = q;

    return l;
}

void list_display(List l) {
    Node * p = l->next;
    while(p) {
        printf("%d %d\n", p->sid, p->score);
        p = p->next;
    }
}

int main() {
    int cnt1;
    int cnt2;
    scanf("%d %d", &cnt1, &cnt2);
    List l1, l2;
    List l;
    list_init(&l1);
    list_init(&l2);

    list_create(&l1, cnt1);
    list_create(&l2, cnt2);

    l = list_merge(l1, l2);
    list_display(l);
}