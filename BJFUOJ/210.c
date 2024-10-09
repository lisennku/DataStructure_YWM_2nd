//
// Created by lisen on 24-10-9.
//
// https://www.bjfuacm.com/problem/210

#include <stdio.h>
#include <string.h>

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
void display_best_position_book(seq_list list, char fb[MAXSIZE], int n);

int main() {
    seq_list list ;
    char fb[MAXSIZE];
    fill_seq_list(&list);
    int fb_cnt ;
    scanf("%d", &fb_cnt);
    display_best_position_book(list, fb, fb_cnt);

    return 0;
}

void fill_seq_list(seq_list * list) {
    list->length = 0;
    char tmp_isbn[14];
    char tmp_title[TITL_MAXSIZE];
    double tmp_price;

    int count;
    scanf("%d", &count);

    while(count >= 1) {
        if(scanf("%s %s %lf", tmp_isbn, tmp_title, &tmp_price)== 3) {
            int idx = list->length;
            strcpy(list->list[idx].isbn, tmp_isbn);
            strcpy(list->list[idx].title, tmp_title);
            list->list[idx].price = tmp_price;

            list->length ++;
            count--;
        }
    }
}

void display_list(seq_list list) {
    for(int i = 0; i < list.length; i++)
        printf("%s %s %.2lf\n", list.list[i].isbn, list.list[i].title, list.list[i].price);
}

void display_best_position_book(seq_list list, char fb[MAXSIZE], int n) {
    for(int i = 0; i < n; i++)
        scanf("%d", &fb[i]);

    for(int i = 0; i < n; i ++) {
        int idx = fb[i] - 1;
        if(idx < 0 || idx >= list.length)
            printf("Sorry，the book on the best position doesn't exist!\n");
        else
            printf("%s %s %.2lf\n", list.list[idx].isbn, list.list[idx].title, list.list[idx].price);
    }
}

