//
// Created by lisen on 24-10-23.
//
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

char ** list_create_most_popular_books_arr(int * n) {
    int cnt;
    scanf("%d", &cnt);
    *n = cnt;

    char ** res = malloc(sizeof(char *) * cnt);
    for(int i = 0; i < cnt; i++) {
        res[i] = calloc(TITLE_LEN, sizeof(char));
        char tmp_title[TITLE_LEN];
        scanf("%s", tmp_title);
        strcpy(res[i], tmp_title);
    }

    return res;
}

void list_display_most_popular_books(char ** popular, int n, List l) {
    for(int i = 0; i < n; i ++) {
        Node * pop = NULL;
        int cnt = 0;

        Node * p = l.head->next;
        while(p != NULL) {
            if(strcmp(popular[i], p->title) == 0) {
                cnt ++;
                Node * next = p->next;
                if(pop == NULL) {
                    pop = p;
                    pop->next = NULL;
                }
                else {
                    Node * q = pop;
                    while(q->next != NULL)
                        q = q->next;
                    q->next = p;
                    q->next->next = NULL;
                }
                p = next;
            }
            p = p->next;
        }

        if(cnt == 0)
            printf("Sorry，there is no your favourite!\n");
        else {
            printf("%d\n", cnt);
            while(pop != NULL) {
                printf("%s %s %.2lf\n", pop->isbn, pop->title, pop->price);
                pop = pop->next;
            }
        }
    }
}


int main() {
    List l;
    list_init(&l);
    list_create(&l);

    int n ;
    char ** res = list_create_most_popular_books_arr(&n);

    list_display_most_popular_books(res, n, l);

}


























