//
// Created by lisen on 24-8-6.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "basic.h"
#include "nums_list.h"

void generate_normal_array_list(SqList * la, SqList * lb);
void generate_order_array_list(SqList * la, SqList * lb);

void generate_normal_linked_list(LinkList *la, LinkList *lb);
void generate_order_linked_list(LinkList *la, LinkList *lb);

void show_array_list(SqList l);
void show_linked_list(LinkList l);

int main() {


	return 0;
}

void generate_normal_array_list(SqList * la, SqList * lb) {
	int tmp1[] = {7, 5, 3, 11};
	int tmp2[] = {2, 6, 3};

	int l1 = sizeof(tmp1) / sizeof(int);
	int l2 = sizeof(tmp2) / sizeof(int);
	for(int i = 0; i < l1; i++) {
		la->elem[i] = tmp1[i];
	}

	for(int i = 0; i < l2; i++) {
		lb->elem[i] = tmp2[i];
	}

}

void generate_order_array_list(SqList * la, SqList * lb) {
	int tmp1[] = {3, 5, 8, 11};
	int tmp2[] = {2, 6, 8, 9, 11, 15, 20};

	int l1 = sizeof(tmp1) / sizeof(int);
	int l2 = sizeof(tmp2) / sizeof(int);
	for(int i = 0; i < l1; i++) {
		la->elem[i] = tmp1[i];
	}

	for(int i = 0; i < l2; i++) {
		lb->elem[i] = tmp2[i];
	}
}

void generate_normal_linked_list(LinkList *la, LinkList *lb) {

}

void generate_order_linked_list(LinkList *la, LinkList *lb) {

}

void show_array_list(SqList l) {

}

void show_linked_list(LinkList l) {

}