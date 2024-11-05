//
// Created by lisen on 24-11-5.
//
// https://www.dotcpp.com/oj/problem1676.html

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode * next;
}LNode, *LinkList;

void list_init(LinkList *l) {
    *l = calloc(1, sizeof(LNode));
    if(*l == NULL)
        exit(EXIT_FAILURE);
    (*l)->next = NULL;
}

LNode * create_node(ElemType data) {
    LNode * new = calloc(1, sizeof(LNode));
    if(new == NULL)
        exit(EXIT_FAILURE);

    new->data = data;
    new->next = NULL;

    return new;
}

void list_create(LinkList * l, int cnt) {
    for(int i = 0; i < cnt; i++) {
        int num;
        scanf("%d", &num);
        LNode * new = create_node(num);
        new->next = (*l)->next;
        (*l)->next = new;
    }
}

int list_length(LinkList l) {
    int len = 0;
    LNode * p = l->next;
    while(p != NULL) {
        len ++;
        p = p->next;
    }

    return len;
}

void list_delete_pos(LinkList * l, int pos) {
    int len = list_length(*l);
    if(pos > len || pos < 1) {
        printf("delete fail\n");
        return ;
    }

    LNode * curr = (*l)->next;
    LNode * prev = (*l);

    int i = 1;
    while(i < pos){
        prev = curr;
        curr = curr->next;
        i ++;
    }
    prev->next = curr->next;
    free(curr);
    printf("delete OK\n");
}

void list_insert_before_pos(LinkList * l, int pos, ElemType data) {
    int len = list_length(*l);
    if(pos > len + 1 || pos < 1) {
        printf("insert fail\n");
        return ;
    }
    LNode * curr = (*l)->next;
    LNode * prev = (*l);

    int i = 1;

    while(i < pos) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    LNode * new = create_node(data);

    prev->next = new;
    new->next = curr;
    printf("insert OK\n");

}

void list_get_pos(LinkList l, int pos) {
    int len = list_length(l);
    if(pos > len || pos < 1) {
        printf("get fail\n");
        return ;
    }
    int i = 1;
    LNode * p = l->next;
    while(i < pos) {
        p = p->next;
        i++;
    }
    printf("%d\n", p->data);
}

void list_display(LinkList l) {
    LNode * p = l->next;
    if(p == NULL)
        printf("Link list is empty\n");
    while(p) {
        if (p->next)
            printf("%d ", p->data);
        else
            printf("%d\n", p->data);

        p = p->next;
    }
}

int order_cmp(char * order, char * pattern) {
    if(strcmp(order, pattern) == 0)
        return 1;
    return 0;
}

int main() {
    LinkList l;
    list_init(&l);

    int num_cnt;
    scanf("%d", &num_cnt);

    list_create(&l, num_cnt);

    int op_cnts;
    int pos;
    scanf("%d", &op_cnts);

    while(op_cnts > 0) {
        op_cnts --;
        char pattern[10];
        scanf("%s", pattern);
        if(order_cmp("show", pattern) == 1)
            list_display(l);
        else if(order_cmp("delete", pattern) == 1) {
            scanf("%d", &pos);
            list_delete_pos(&l, pos);
        }
        else if(order_cmp("get", pattern) == 1) {
            scanf("%d", &pos);
            list_get_pos(l, pos);
        }
        else if(order_cmp("insert", pattern) == 1){
            int data;
            scanf("%d %d", &pos, &data);
            list_insert_before_pos(&l, pos, data);
        }
    }

    return 0;
}
