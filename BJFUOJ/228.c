//
// Created by lisen on 24-11-4.
//

//
// Created by lisen on 24-10-31.
//
// https://www.bjfuacm.com/problem/228


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

void list_diff(List * l1, List l2) {
    Node * p1 = (*l1)->next;

    List res;
    list_init(&res);
    Node * r = res;
    // 也可以使用哈希 此处为了方便直接两次遍历
    while(p1) {
        Node * p2 = l2->next;
        while(p2) {
            if(p1->val == p2->val)
                break;
            p2 = p2->next;
        }
        if(p2 == NULL) {
            r->next = p1;
            r = r->next;
        }
        p1 = p1->next;
    }
    r->next = NULL;

    *l1 = res;

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
        list_diff(&l1, l2);
        list_display(l1);
        Node * l = l1->next;
        int cnt = 0;
        while(l != NULL) {
            cnt ++;
            l = l->next;
        }
        printf("%d\n", cnt);
    }
}
