//
// Created by lisen on 24-10-9.
//
// https://www.bjfuacm.com/problem/212


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

    if(pos - 1 < 0 || pos >= list->length)
        printf("Sorry，the position to be deleted is invalid!\n");
    else {
        for(int i = pos; i < list->length; i++)
            list->list[i-1] = list->list[i];
        list->length --;
        display_list(*list);
    }
}