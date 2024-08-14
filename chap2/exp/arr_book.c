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
void add_books_with_n(Booklist *list, int n);
void show_books(Booklist list);
void reverse_show_books(Booklist list);
void sort_books_by_price_desc(Booklist *list);
double calc_books_avg_price(Booklist l);
void change_books_price(Booklist *l);
double find_most_expensive_price(Booklist l);
void show_most_expensive_books(Booklist l);
void input_find_books_name(int n, char arr[n][MAX_TITL]);
void show_most_favourite_books(Booklist l, int n, char arr[n][MAX_TITL]);
void input_best_position(int n, int arr[]);
void show_best_position_book(Booklist l, int n, int arr[]);
void new_book_insert(Booklist *l );
void delete_book(Booklist *l);
void drop_duplicated(Booklist *l);

int main() {
	Booklist l;
	init_books(&l);
	// add_books(&l);
	// // show_books(l);
	// // sort_books_by_price_desc(&l);
	// double avg = calc_books_avg_price(l);
	// change_books_price(&l);
	// printf("%.2lf\n", avg);
	// show_books(l);
	int nums ;
	scanf("%d", &nums);
	add_books_with_n(&l, nums);
	// reverse_show_books(l);
	// show_most_expensive_books(l);
	// int loop;
	// scanf("%d", &loop);
	// char books_name[loop][MAX_TITL];
	// input_find_books_name(loop, books_name);
	// show_most_favourite_books(l, loop, books_name);
	// int arr[loop];
	// input_best_position(loop, arr);
	// show_best_position_book(l, loop, arr);
	// new_book_insert(&l);

	// delete_book(&l);
	drop_duplicated(&l);
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
double calc_books_avg_price(Booklist l) { // 问题3
	double total_price = 0.0;
	for(int i = 0; i < l.size; i ++)
		total_price += l.elem[i].price;
	return total_price / l.size;
}
void change_books_price(Booklist *l) {  // 问题3
	double avg = calc_books_avg_price(*l);
	for(int i = 0; i < l->size; i++) {
		if(l->elem[i].price < avg)
			l->elem[i].price *= 1.2;
		else {
			l->elem[i].price *= 1.1;
		}
	}
}
void add_books_with_n(Booklist *list, int n) {
	int input_nums;

	for (int i = 0; i < n; i ++) {
		char isbn[MAX_ISBN];
		char titl[MAX_TITL];
		double price;

		if((input_nums = scanf("%s %s %lf", isbn, titl, &price)) == 3) {
			if ( !strcmp(isbn, "0") && !strcmp(titl, "0") && price == 0.0) // 都是0停止输入
				break;

			int idx = list->size;
			strcpy(list->elem[idx].isbn, isbn);
			strcpy(list->elem[idx].titl, titl);
			list->elem[idx].price = price;

			list->size ++;
		}
	}
}
void reverse_show_books(Booklist l) { // 问题4
	for(int i = l.size - 1; i >=0; i--) {
		printf("%s %s %.2lf\n", l.elem[i].isbn, l.elem[i].titl, l.elem[i].price);
	}
}
double find_most_expensive_price(Booklist l) {  // 问题5
	double most_exp = 0.0;
	for(int i = 0; i < l.size; i++) {
		if(most_exp < l.elem[i].price)
			most_exp = l.elem[i].price;
	}

	return most_exp;
}
void show_most_expensive_books(Booklist l) { // 问题5
	double most_exp = find_most_expensive_price(l);
	int count = 0;
	for(int i = 0; i < l.size; i++) {
		if(l.elem[i].price == most_exp)
			count ++;
	}
	printf("%d\n",count);
	for(int i = 0; i < l.size; i++) {
		if(l.elem[i].price == most_exp)
			printf("%s %s %.2lf\n", l.elem[i].isbn, l.elem[i].titl, l.elem[i].price);
	}
}
void input_find_books_name(int n, char arr[n][MAX_TITL]) { // 问题6
	for(int i = 0; i < n; i++) {
		char tmp[MAX_TITL] ;
		scanf("%s", tmp);
		strcpy(arr[i], tmp);
	}
}
void show_most_favourite_books(Booklist l, int n, char arr[n][MAX_TITL]) { // 问题6
	for(int i = 0; i < n; i++) {

		int cnt = 0;
		for(int j = 0; j < l.size; j++) {
			if(strcmp(arr[i], l.elem[j].titl) == 0) {
				cnt++;
			}
		}
		if(cnt == 0)
			printf("Sorry，there is no your favourite!\n");  // 该字符串从OJ拷贝，否则会导致WA，因为OJ里的逗号是中文
		else {
			printf("%d\n", cnt);
			for(int j = 0; j < l.size; j++) {
				if(strcmp(arr[i], l.elem[j].titl) == 0) {
					printf("%s %s %.2lf\n", l.elem[j].isbn, l.elem[j].titl, l.elem[j].price);
				}
			}

		}


	}
}
void input_best_position(int n, int arr[]) { // 问题7
	for(int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}
void show_best_position_book(Booklist l, int n, int arr[]) { // 问题7
	for(int i = 0; i < n; i++) {
		if (arr[i] <= 0 || arr[i] > l.size)
			printf("Sorry，the book on the best position doesn't exist!\n");
		else
			printf("%s %s %.2lf\n", l.elem[arr[i] - 1].isbn, l.elem[arr[i] - 1].titl, l.elem[arr[i] - 1].price);
	}
}
void new_book_insert(Booklist *l) { // 问题8
	int position;
	char isbn[MAX_ISBN];
	char titl[MAX_TITL];
	double price;

	scanf("%d", &position);
	scanf("%s %s %lf", isbn, titl, &price);

	if(position <= 0 || position > l->size + 1)
		printf("Sorry，the position to be inserted is invalid!\n");
	else {
		for(int i = l->size - 1; i >= position - 1; i--) {
			l->elem[i+1] = l->elem[i];
		}

		l->elem[position - 1].price = price;
		strcpy(l->elem[position - 1].isbn, isbn);
		strcpy(l->elem[position - 1].titl, titl);

		l->size ++;
		show_books(*l);
	}

}
void delete_book(Booklist *l) {  // 问题9
	int position;
	scanf("%d", &position);
	if(position <= 0 || position > l->size)
		printf("Sorry，the position to be deleted is invalid!");
	else {
		for(int i = position; i < l->size; i++) {
			l->elem[i - 1] = l->elem[i];
		}
		l->size--;
		show_books(*l);
	}
}
void drop_duplicated(Booklist *l) {
	// 不在循环中删除，删除会导致长度变短，而两次循环时长度是固定的，会导致访问到没有赋值的数组元素
	// 记录要删除的位置，最后统一删除
	int position[MAX_SIZE];
	int idx = 0;
	for(int i = 0; i < l->size; i++) {
		for(int j = i + 1; j < l->size; j++) {
			if(strcmp(l->elem[i].isbn, l->elem[j].isbn) == 0) {
				strcpy(l->elem[j].isbn, "to be deleted");
			}
		}
	}

	for(int i = 0; i < l->size; i ++) {
		if(strcmp(l->elem[i].isbn, "to be deleted") == 0) {
			position[idx] = i+1;
			idx++;
		}
	}

	for(int i = 0; i < idx; i ++) {
		for(int j = position[i]; j < l->size; j++) {
			l->elem[j - 1] = l->elem[j];
		}
		l->size --;
	}
	printf("%d\n", l->size);
}















