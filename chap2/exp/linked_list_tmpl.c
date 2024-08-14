//
// Created by lisen on 24-8-14.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ISBN 20
#define MAX_TITL 200

struct book_info {
	char isbn[MAX_ISBN];
	char titl[MAX_TITL];
	double price;
	struct  book_info *next;
};

typedef struct book_info Node;
typedef struct book_info * Book;

void InitialList(Book * list);
void CreateNode(Node * node, const char * isbn, const char * title, const double price);
void AppendNodeToList(Book * list, Node * node);
void ShowList(Book list);
void GenerateList(Book * list);
unsigned int GetListLength(Book list);


int main() {

	return 0;
}

void InitialList(Book * list) {  // 初始化带有头结点的链表
	*list = (Node *) malloc(sizeof(Node));
	if((*list) == NULL)
		exit(EXIT_FAILURE);
	strcpy((*list)->isbn, "");
	strcpy((*list)->titl, "");
	(*list)->next = NULL;
}
void CreateNode(Node * node, const char * isbn, const char * title, const double price) {
	strcpy(node->isbn, isbn);
	strcpy(node->titl, title);
	node->price = price;
	node->next = NULL;
}
void AppendNodeToList(Book * list, Node * node) { // 从尾部插入
	Node * p = * list;   // p为头指针，指向头结点
	while(p->next != NULL) {
		p = p->next;
	}
	p->next = node;

}
void ShowList(Book list) {
	Node * p = list->next;
	while(p != NULL) {
		printf("%s %s %.2lf\n", p->isbn, p->titl, p->price);
		p = p->next;
	}
}

void GenerateList(Book * list) {
	int input_nums;
	char isbn[MAX_ISBN];
	char titl[MAX_TITL];
	double price;

	while((input_nums = scanf("%s %s %lf", isbn, titl, &price)) == 3) {
		if ( !strcmp(isbn, "0") && !strcmp(titl, "0") && price == 0.0) // 都是0停止输入
			break;
		Node * node = (Node *) malloc(sizeof(Node));
		if(node == NULL)
			exit(EXIT_FAILURE);
		CreateNode(node, isbn, titl, price);
		AppendNodeToList(list, node);
	}
}

unsigned int GetListLength(Book list) {
	unsigned int length = 0;
	Node * p = list->next;

	while(p != NULL) {
		length ++;
		p = p->next;
	}

	return length;
}



















