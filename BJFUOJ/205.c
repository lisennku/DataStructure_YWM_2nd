//
// Created by lisen on 24-10-8.
//
// https://www.bjfuacm.com/problem/205

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXSIZE 200
#define TITL_MAXSIZE 100

typedef struct {
    char isbn[14];
    char title[TITL_MAXSIZE];
    double price;
} seq_book_item;

typedef struct {
    seq_book_item list[MAXSIZE];
    int length;
}seq_list;

void fill_seq_list(seq_list * list);
void display_list(seq_list list);
void bubble_sort_desc(seq_list * list);

int main() {
    seq_list list ;
    fill_seq_list(&list);
    // display_list(list);
    bubble_sort_desc(&list);
    display_list(list);
    return 0;
}

void fill_seq_list(seq_list * list) {
    list->length = 0;
    char tmp_isbn[14];
    char tmp_title[TITL_MAXSIZE];
    double tmp_price;
    while(scanf("%s %s %lf", tmp_isbn, tmp_title, &tmp_price) == 3) {
        if(!strcmp(tmp_isbn, "0") && !strcmp(tmp_title, "0") && tmp_price == 0)
            break;
        int idx = list->length;
        strcpy(list->list[idx].isbn, tmp_isbn);
        strcpy(list->list[idx].title, tmp_title);
        list->list[idx].price = tmp_price;

        list->length ++;
    }
}

void display_list(seq_list list) {
    // printf("%d\n", list.length);
    for(int i = 0; i < list.length; i++)
        printf("%s %s %.2lf\n", list.list[i].isbn, list.list[i].title, list.list[i].price);
}

void bubble_sort_desc(seq_list * list) {
    int n = list->length;
    bool is_swap = true;
    for(int i = n-1; i >= 0 && is_swap; i--) {
        is_swap = false;
        for(int j = 0; j <= i - 1; j++) {
            if(list->list[j].price < list->list[j+1].price) {
                is_swap = true;
                seq_book_item tmp = list->list[j+1];
                list->list[j+1] = list->list[j];
                list->list[j] = tmp;
            }
        }
    }
}