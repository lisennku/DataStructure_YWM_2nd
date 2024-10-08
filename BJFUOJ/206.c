//
// Created by lisen on 24-10-8.
//
// https://www.bjfuacm.com/problem/206
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXSIZE 100
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
double calc_avg_price(seq_list list);
void update_list_price(seq_list * list);

int main() {
    seq_list list;
    fill_seq_list(&list);
    double avg = calc_avg_price(list);
    printf("%.2lf\n", avg);
    update_list_price(&list);
    display_list(list);
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
    for(int i = 0; i < list.length; i++)
        printf("%s %s %.2lf\n", list.list[i].isbn, list.list[i].title, list.list[i].price);
}
double calc_avg_price(seq_list list) {
    double sum = 0;
    for(int i = 0; i < list.length; i++)
        sum += list.list[i].price;
    return sum / list.length;
}
void update_list_price(seq_list * list) {
    double avg = calc_avg_price(*list);
    for(int i = 0; i < list->length; i++) {
        if(list->list[i].price < avg)
            list->list[i].price *= 1.2;
        else
            list->list[i].price *= 1.1;
    }
}