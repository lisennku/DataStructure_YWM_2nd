//
// Created by lisen on 24-10-9.
//
// https://www.bjfuacm.com/problem/213


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
void drop_duplicated(seq_list l1, seq_list * l2);


int main() {
    seq_list list ;
    seq_list list_distinct;

    fill_seq_list(&list);
    drop_duplicated(list, &list_distinct);
    display_list(list_distinct);

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

void drop_duplicated(seq_list l1, seq_list * l2) {
    // use list2 to store unique item
    l2->length = 0;

    for(int i = 0; i < l1.length; i++) {
        int is_dupliated = 0;
        for(int j = 0; j < l2->length; j++) {
            if(strcmp(l1.list[i].isbn, l2->list[j].isbn) == 0) {
                is_dupliated = 1;
            }
        }
        if(is_dupliated == 0) {
            l2->list[l2->length] = l1.list[i];
            l2->length ++;
        }
    }
    printf("%d\n", l2->length);
}
