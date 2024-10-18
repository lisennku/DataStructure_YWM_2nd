//
// Created by lisen on 24-10-17.
//
// https://www.bjfuacm.com/problem/214

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TITLE_LEN 100
#define ISBN_LEN 14

typedef struct list_node{
    char isbn[ISBN_LEN];
    char title[TITLE_LEN];
    double price;
    struct list_node * next;
} Node;

typedef struct list {
    Node * head;
    int length;
}List;

void list_init(List * l) {
    l->length = 0;
    l->head = (Node *) malloc(sizeof(Node));
    if(l->head == NULL)
        exit(EXIT_FAILURE);

    l->head->next = NULL;
}

Node * list_node_create(char * isbn, char * title, double price) {
    Node * new = (Node *) malloc(sizeof(Node));
    if(new == NULL)
        exit(EXIT_FAILURE);

    new->next = NULL;
    strcpy(new->isbn, isbn);
    strcpy(new->title, title);
    new->price = price;

    return new;
}

void list_create(List * l) {
    char tmp_isbn[ISBN_LEN];
    char tmp_title[TITLE_LEN];
    double tmp_price;

    while(scanf("%s %s %lf", tmp_isbn, tmp_title, &tmp_price) == 3) {
        if(!strcmp(tmp_isbn, "0") && !strcmp(tmp_title, "0") && tmp_price == 0)
            break;
        Node * node = list_node_create(tmp_isbn, tmp_title, tmp_price);
        // 题目要求尾插
        Node * tail = l->head;
        while(tail->next != NULL)
            tail = tail->next;
        tail->next = node;
        l->length ++;
    }
}

void list_display(List l) {
    printf("%d\n", l.length);
    Node * node = l.head->next;
    while(node != NULL) {
        printf("%s %s %.2lf\n", node->isbn, node->title, node->price);
        node = node->next;
    }
}

int main() {
    List l;
    list_init(&l);
    list_create(&l);
    list_display(l);
    return 0;
}