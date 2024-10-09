//
// Created by lisen on 24-10-9.
//
// https://www.bjfuacm.com/problem/209


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
void fill_polular_book_array(char fb[MAXSIZE][TITL_MAXSIZE], int n);
void display_popular_book(seq_list list, char fb[MAXSIZE][TITL_MAXSIZE], int n);

int main() {
    seq_list list ;
    char fb[MAXSIZE][TITL_MAXSIZE];
    fill_seq_list(&list);
    int fb_cnt ;
    scanf("%d", &fb_cnt);
    fill_polular_book_array(fb, fb_cnt);
    display_popular_book(list, fb, fb_cnt);

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

void fill_polular_book_array(char fb[MAXSIZE][TITL_MAXSIZE], int n) {
    for(int i = 0; i < n; i++) {
        char tmp[TITL_MAXSIZE];
        scanf("%s", tmp);
        strcpy(fb[i], tmp);
    }
}

void display_popular_book(seq_list list, char fb[MAXSIZE][TITL_MAXSIZE], int n) {
    for(int i = 0; i < n; i++) {
        int tmp_cnt = 0;
        int tmp_index[MAXSIZE];
        for(int j = 0; j < list.length; j++) {
            if(strcmp(list.list[j].title, fb[i]) == 0) {
                tmp_index[tmp_cnt] = j;
                tmp_cnt ++;

            }
        }
        if(tmp_cnt == 0)
            printf("Sorry，there is no your favourite!\n");
        else {
            printf("%d\n", tmp_cnt);
            for(int j = 0; j < tmp_cnt; j++)
                printf("%s %s %.2lf\n", list.list[tmp_index[j]].isbn, list.list[tmp_index[j]].title, list.list[tmp_index[j]].price);
        }
    }
}

