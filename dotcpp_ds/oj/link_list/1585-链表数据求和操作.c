//
// Created by lisen on 24-11-5.
//
// https://www.dotcpp.com/oj/problem1585.html

#include <stdio.h>
#include <stdlib.h>

struct node {
    int real;
    int img;
    struct node * next;
};

typedef struct node Node;

typedef struct node * List;

void list_init(List * l) {
    *l = calloc(1, sizeof(Node));
    if(*l == NULL)
        exit(EXIT_FAILURE);

    (*l)->next = NULL;
}

Node * list_create_node(int real, int img) {
    Node * node = calloc(1, sizeof(Node));
    if(node == NULL)
        exit(EXIT_FAILURE);
    node->next = NULL;
    node->real = real;
    node->img = img;

    return node;
}

void list_create(List * l, int cnt) {
    // 创建时即排序 也即创建后的链表按照sid非递减的顺序
    while(cnt) {
        cnt -- ;
        int real, img;
        scanf("%d %d", &real, &img);
        Node * new = list_create_node(real, img);

        Node * p = (*l);
        while(p->next != NULL) {
            p = p->next;
        }
        p->next = new;
    }
}

void list_complex_sum(List l) {
    int real_part = 0;
    int img_part = 0;

    Node * p = l->next;
    while(p) {
        real_part += p->real;
        img_part += p->img;
        p = p->next;
    }
    printf("%d+%di\n", real_part, img_part);
}

void list_display(List l) {
    Node * p = l->next;
    while(p) {
        printf("%d %d\n", p->real, p->img);
        p = p->next;
    }
}

int main() {

    List l1;
    list_init(&l1);

    list_create(&l1, 10);

    list_complex_sum(l1);

    return 0;
}