//
// Created by lisen on 24-10-8.
//
// https://www.bjfuacm.com/problem/207

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
void reverse_store(seq_list list1, seq_list * list2);

int main() {
    seq_list list ;
    seq_list rev_list;
    fill_seq_list(&list);
    reverse_store(list, &rev_list);
    display_list(rev_list);
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
void reverse_store(seq_list list1, seq_list * list2) {
    list2->length = list1.length;
    int j = list2->length;
    for(int i = list1.length; i >= 1; i--) {
        list2->list[j - i] = list1.list[i-1];
    }
}