//
// Created by lisen on 24-10-9.
//
// https://www.bjfuacm.com/problem/211


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
void update_seq_list(seq_list * list, int pos);


int main() {
    seq_list list ;
    char fb[MAXSIZE];
    fill_seq_list(&list);
    int position;
    scanf("%d", &position);
    update_seq_list(&list, position);



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

void update_seq_list(seq_list * list, int pos) {
    seq_book_item insert_item;
    char isbn[14];
    char title[TITL_MAXSIZE];
    double price;
    scanf("%s %s %lf", isbn, title, &price);
    strcpy(insert_item.isbn, isbn);
    strcpy(insert_item.title, title);
    insert_item.price = price;

    if(pos - 1 < 0 || pos > list->length)
        printf("Sorry，the position to be inserted is invalid!\n");
    else {
        list->length ++;
        for(int i = list->length - 1; i > pos - 1; i--)
            list->list[i] = list->list[i-1];
        list->list[pos - 1] = insert_item;

        display_list(*list);
    }
}