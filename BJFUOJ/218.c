//
// Created by lisen on 24-10-23.
//

#include <math.h>
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
    strcpy(l->head->isbn, "");
    strcpy(l->head->title, "");
    l->head->price = 0;
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

    int cnt;
    scanf("%d", &cnt);
    while(cnt > 0) {
        scanf("%s %s %lf", tmp_isbn, tmp_title, &tmp_price);
        Node * node = list_node_create(tmp_isbn, tmp_title, tmp_price);
        // 题目要求尾插
        Node * tail = l->head;
        while(tail->next != NULL)
            tail = tail->next;
        tail->next = node;
        l->length ++;

        cnt --;
    }
}

void list_display(List l) {
    // printf("%d\n", l.length);
    Node * node = l.head->next;
    while(node != NULL) {
        printf("%s %s %.2lf\n", node->isbn, node->title, node->price);
        node = node->next;
    }
}

Node * list_most_expensive(List l, int * cnt) {
    double expensive_price = 0.0;
    Node * expensive_node = NULL;

    Node * p = l.head->next;
    while(p != NULL) {
        if(expensive_price < p->price) {
            *cnt = 0; // 重置
            expensive_node = NULL;

            expensive_price = p->price;
            *cnt = 1;
            Node * new = malloc(sizeof(Node));
            new->next = NULL;
            strcpy(new->isbn, p->isbn);
            strcpy(new->title, p->title);
            new->price = p->price;
            expensive_node = new;
        }
        else if(expensive_price == p->price) {
            (*cnt) ++;
            if(expensive_node == NULL)
                expensive_node = p;
            else {
                Node * q = expensive_node;
                while(q->next != NULL) {
                    q = q->next;
                }
                Node * new = malloc(sizeof(Node));
                new->next = NULL;
                strcpy(new->isbn, p->isbn);
                strcpy(new->title, p->title);
                new->price = p->price;

                q->next = new;
            }
        }
        p = p->next;
    }
    return expensive_node;
}


int main() {
    List l;
    list_init(&l);
    list_create(&l);
    // list_display(l);
    int cnt;
    Node * res = list_most_expensive(l, &cnt);
    printf("%d\n", cnt);
    while(res != NULL) {
        printf("%s %s %.2lf\n", res->isbn, res->title, res->price);
        res = res->next;
    }
    return 0;
}


























