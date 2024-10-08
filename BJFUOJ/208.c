//
// Created by lisen on 24-10-8.
//
// https://www.bjfuacm.com/problem/208


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
double find_most_expensive_price(seq_list list);
void display_most_expensive_price(seq_list list, double price);

int main() {
    seq_list list ;

    fill_seq_list(&list);
    double most_exp_price = find_most_expensive_price(list);
    display_most_expensive_price(list, most_exp_price);

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

double find_most_expensive_price(seq_list list) {
    double tmp = 0;
    for(int i = 0; i < list.length; i++) {
        if (list.list[i].price > tmp)
            tmp = list.list[i].price;
    }

    return tmp;
}
void display_most_expensive_price(seq_list list, double price) {
    int cnt = 0;
    for(int i = 0; i < list.length; i++) {
        if(list.list[i].price == price)
            cnt ++;
    }
    printf("%d\n", cnt);
    for(int i = 0; i < list.length; i++) {
        if(list.list[i].price == price)
            printf("%s %s %.2lf\n", list.list[i].isbn, list.list[i].title, list.list[i].price);
    }
}