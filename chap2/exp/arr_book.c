//
// Created by lisen on 24-8-13.
//
// 本代码主要完成与数据结构配套的练习书里的实验部分
// 可以将函数放到https://www.bjfuacm.com/进行测试


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 200
#define MAX_ISBN 20
#define MAX_TITL 200

struct book_info {
	char isbn[MAX_ISBN];
	char titl[MAX_TITL];
	double price;
};

typedef struct book_info Item;

struct book_list {
	Item *elem;
	unsigned int size;
};

typedef struct book_list Booklist;

void init_books(Booklist * list);
void add_books(Booklist * list);
void show_books(Booklist list);
void sort_books_by_price_desc(Booklist *list);

int main() {
	Booklist l;
	init_books(&l);
	add_books(&l);
	// show_books(l);
	sort_books_by_price_desc(&l);
	show_books(l);
}

void init_books(Booklist * list) {
	list->elem = (Item *) malloc(sizeof(Item) * MAX_SIZE);
	if(list->elem == NULL) {
		exit(EXIT_FAILURE);
	}

	list->size = 0;
}
void add_books(Booklist * list) {
	int input_nums;

	char isbn[MAX_ISBN];
	char titl[MAX_TITL];
	double price;

	while((input_nums = scanf("%s %s %lf", isbn, titl, &price)) == 3) {
		if ( !strcmp(isbn, "0") && !strcmp(titl, "0") && price == 0.0) // 都是0停止输入
			break;

		int idx = list->size;
		strcpy(list->elem[idx].isbn, isbn);
		strcpy(list->elem[idx].titl, titl);
		list->elem[idx].price = price;

		list->size ++;
	}

}
void show_books(Booklist list) {
	// printf("%u\n", list.size);
	for(int i = 0; i < list.size; i ++) {
		printf("%s %s %.2lf\n", list.elem[i].isbn, list.elem[i].titl, list.elem[i].price);
	}
}
void sort_books_by_price_desc(Booklist * list) {
	unsigned int n = list->size;
	for (unsigned int i = 0; i < n - 1; i++) {
		for (unsigned int j = 0; j < n - 1 - i; j++) {
			if (list->elem[j].price < list->elem[j + 1].price) {
				// 交换两个元素
				Item temp = list->elem[j];
				list->elem[j] = list->elem[j + 1];
				list->elem[j + 1] = temp;
			}
		}
	}
}