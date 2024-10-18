//
// Created by lisen on 24-10-18.
//
//
// Created by lisen on 24-10-18.
//

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
    printf("%d\n", l.length);
    Node * node = l.head->next;
    while(node != NULL) {
        printf("%s %s %.2lf\n", node->isbn, node->title, node->price);
        node = node->next;
    }
}

void list_drop_duplicates(List * l) {
    Node * curr = l->head->next;
    // 每次循环链表的一个结点A
    // 以该结点A为准 找到他的下一个结点B 查询从B开始到链表末尾 判断是否有重复
    // 如果有重复
    // 则更改B的前序节点的next 和 B的next

    while(curr != NULL && curr->next != NULL) {
        Node * prev = curr;
        Node * next = curr->next;

        while(next != NULL) {
            if(strcmp(curr->isbn, next->isbn) == 0) {
                prev->next = next->next;
                free(next);
                next = prev->next;
                l->length --;
            }
            else {
                prev = next;
                next = next->next;
            }
        }
        curr = curr->next;
    }

}

int main() {
    List l;
    list_init(&l);
    list_create(&l);
    list_drop_duplicates(&l);
    list_display(l);
    return 0;
}