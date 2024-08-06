//
// Created by lisen on 24-8-6.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "nums_list.h"

int main() {
// using array
	/*
	SqList l ;
	Status s;
	s = InitialSeqList(&l);
	if (s != 1)
		printf("error when initialize sequence list\n");
	else
		printf("successfully initialized sequence list\n");

	printf("now sequence list has %d elements\n", l.length);
	printf("Adding 10 elements\n");

	srand(0);
	for(int i = 0; i < 10; i ++) {
		Item e = rand() % 20 +1 ;
		ListSeqInsert(&l, i + 1, e);
	}

	printf("now sequence list has %d elements\n", l.length);
	printf("elements are\n");
	for(int i = 0; i < l.length; i++)
		printf("%d ", l.elem[i]);
	printf("\n");

	printf("Now deleting 4th element\n");
	ListSeqDelete(&l, 4);

	printf("now sequence list has %d elements\n", l.length);
	printf("elements are\n");
	for(int i = 0; i < l.length; i++)
		printf("%d ", l.elem[i]);
	printf("\n");
	*/
// using linked
	LinkList l;
	Status s;
	CreateLinkList_T(&l, 10);

	printf("Now linked list has %d elements\n", ListLinkLength(&l));

	LNode *p = l->next;
	while(p != NULL) {
		printf("%d ", p->item);
		p = p->next;
	}
	printf("Now insert an element in position 11\n");
	ListLinkInsert(&l, 11, 10);
	// printf("Now delete an element in position 9\n");
	// ListLinkDelete(&l, 9);
	printf("Now linked list has %d elements\n", ListLinkLength(&l));
	LNode *q = l->next;
	while(q != NULL) {
		printf("%d ", q->item);
		q = q->next;
	}
}
