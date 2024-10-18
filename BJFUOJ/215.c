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
    // printf("%d\n", l.length);
    Node * node = l.head->next;
    while(node != NULL) {
        printf("%s %s %.2lf\n", node->isbn, node->title, node->price);
        node = node->next;
    }
}

void list_bubble_sort(List * l) {
    // 如果是空链表 l.head.next == NULL
    // 如果链表只有一个结点 l.head.next.next == NULL
    // 无需排序 直接返回
    if(l->head->next == NULL || l->head->next->next == NULL)
        return ;

    int is_swapped = 0;         // 优化的冒泡排序 用来表示是否有交换发生 为0则表示没有 跳出循环
    Node * ptr ;                // ptr指向第一个有效结点 最初的判断保证进入该步骤的链表至少有两个结点
    Node * find = NULL;         // 用来指向每次循环找到的排序后的位置 初始为NULL

    do {
        is_swapped = 0;         // 外部循环将其置为0
        ptr = l->head->next;    // 外层循环开始点

        // 内层循环
        while(ptr->next != find) {
            if(ptr->price < ptr->next->price) {  // 需要交换
                // 交换需要更新ptr的前序节点和ptr.next的后继节点
                // 更新后继结点
                Node * tmp = ptr->next->next;  // 先将原后继结点保存
                ptr->next->next = ptr;         // 后继结点更新

                // 更新前序节点 需要特殊判断
                if(ptr == l->head->next)
                    l->head->next = ptr->next;
                else {
                    Node * prev = l->head;
                    while(prev->next != ptr)
                        prev = prev->next;
                    prev->next = ptr->next;
                }

                ptr->next = tmp;
                is_swapped = 1;
            }
            else                                 // 不需要交换
                ptr = ptr->next;
        }
    find = ptr;
    }while(is_swapped != 0);
}


int main() {
    List l;
    list_init(&l);
    list_create(&l);
    list_bubble_sort(&l);
    list_display(l);
    return 0;
}