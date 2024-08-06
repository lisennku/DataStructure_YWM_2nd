//
// Created by lisen on 24-8-6.
//

#include "nums_list.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "basic.h"

// sequence list function declare
Status InitialSeqList(SqList * l) {
	l->elem = (Item *) malloc(sizeof(Item) * MAX_SIZE);
	if(l->elem == NULL)
		exit(OVERFLOW);
	l->length = 0;
	return OK;
}

bool ListSeqEmpty(SqList l) {
	return l.length == 0;
}

int ListSeqLength(SqList l) {
	return l.length;
}

Status GetSeqElem(SqList l, int i, Item * e) {
	if (i < 1 || i > l.length)
		return ERROR;
	* e = l.elem[i - 1];
	return OK;
}

int LocateSeqElem(SqList l, Item e) {
	for(int i = 0; i < l.length; i ++) {
		if(l.elem[i] == e)
			return i + 1;
	}
	return 0;
}

Status ListSeqInsert(SqList * l, int i, Item e) {
	//判断插入位置
	if(i < 1 || i > l->length + 1)
		return ERROR;
	if(l->length == MAX_SIZE)
		return OVERFLOW;
	// 将位置i到最后一个位置，向后移动
	for(int j = l->length - 1; j >= i - 1; j--) {
		l->elem[j + 1] = l->elem[j];
	}

	l->elem[i - 1] = e;

	// 长度+1
	l->length ++;

	return OK;
}

Status ListSeqDelete(SqList * l, int i) {
	//判断删除位置
	if(i < 1 || i > l->length)
		return ERROR;

	// 共移动n-i个元素
	// 删除位置是i，则对应脚标i-1，将脚标i开始向前移动一位
	for(int j = i; j < l->length; j++)
		l->elem[j - 1] = l->elem[j];
	l->length -- ;
	 return OK;
}

// linked list functions prototype
Status InitialLinkList(LinkList * l) {
	// with header node
	LNode * node = (LNode *) malloc(sizeof(LNode));
	if(node == NULL)
		return OVERFLOW;
	node->next = NULL;

	*l = node;

	return OK;
}

bool ListLinkEmpty(LinkList * l) {
	LNode * p = (*l)->next;  // point to first node
	return p == NULL;
}

int ListLinkLength(LinkList * l) {
	LNode * p = (*l)->next;  // point to first node
	int count = 0;
	while(p != NULL) {
		count ++;
		p = p->next;
	}


	return count;
}

Status GetLinkElem(LinkList * l, int i, Item e) {
	int flag = 1;
	LNode * p = (*l)->next;
	while(p != NULL && flag < i) {
		p = p->next;
		flag ++;
	}
	if(!p || flag > i)
		return ERROR;

	e = p->item;

	return OK;

}

LNode * LocateLinkElem(LinkList * l, Item e) {
	LNode * p = (*l)->next;
	while(p != NULL && p->item != e) {
		p = p->next;
	}
	return p;
}

Status ListLinkInsert(LinkList * l, int i, Item e) {
	// 在第i个位置插入
	// 需要找到i-1的位置，然后将新节点的next赋值为该位置的next，再将该位置的next改为新节点
	int flag = 1;
	LNode * p = (*l)->next;

	while((p != NULL) && (flag < i - 1)) {
		p = p->next;
		flag++;
	}

	if((!p) || (flag > i - 1))
		return ERROR;

	LNode * new = (LNode *) malloc(sizeof(LNode));
	new->item = e;

	new->next = p->next;
	p->next = new;
}

Status ListLinkDelete(LinkList * l, int i) {
	int flag = 1;
	LNode * p = (*l)->next;

	while((p != NULL) && (flag < i - 1)) {
		p = p->next;
		flag++;
	}

	if(!(p->next) || (flag > i - 1))
		return ERROR;

	LNode * del = p->next;

	p->next = del->next;
	free(del);

	return OK;


}

void CreateLinkList_H(LinkList * l, int n) {
	Status s = InitialLinkList(l);
	if(s != OK)
		printf("Error when initializing linked list\n");
	else
		printf("Successfully initialized linked list\n");

	srand(0);
	for(int i = 0; i < n; i++) {
		int r = rand() % 20 + 1;
		printf("Now inserting %d\n", r);
		LNode * new = (LNode *) malloc(sizeof(LNode));
		if(new == NULL) {
			printf("error allocating memory\n");
			exit(EXIT_FAILURE);
		}
		new->item = r;
		new->next = (*l)->next;  // new node's next point to header'next
		(*l)->next = new;
	}

}

void CreateLinkList_T(LinkList * l, int n) {
	Status s = InitialLinkList(l);
	if(s != OK)
		printf("Error when initializing linked list\n");
	else
		printf("Successfully initialized linked list\n");

	LNode * tail = *l;   // tail pointer

	srand(0);
	for(int i = 0; i < n; i++) {
		int r = rand() % 20 + 1;
		printf("Now inserting %d\n", r);
		LNode * new = (LNode *) malloc(sizeof(LNode));
		if(new == NULL) {
			printf("error allocating memory\n");
			exit(EXIT_FAILURE);
		}

		new->item = r;
		new->next = NULL;

		tail->next = new;
		tail = new;

	}
}