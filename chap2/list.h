//
// Created by lisen on 24-8-5.
//

#ifndef SEQUENCE_LIST_H
#define SEQUENCE_LIST_H

#include "basic.h"  // global status definition



#define MAX_SIZE 100

struct item {

};

typedef struct item Item;

// sequence list using array to represent
struct seq_list {
	Item *elem;
	int length;
};

typedef struct seq_list SqList;

// sequence list functions
Status InitialSeqList(SqList * l);

Status ListSeqEmpty(SqList * l);

int ListSeqLength(SqList * L);

Status GetSeqElem(SqList l, int i, Item * e);

int LocateSeqElem(SqList l, Item e);

Status ListSeqInsert(SqList * l, int i, Item e);

Status ListSeqDelete(SqList * l, int i);


// linked list using header pointer to represent
struct linked_node {
	Item item;
	struct linked_node * next;
};

typedef struct linked_ndoe LNode;
typedef struct linked_node * LinkList;

Status InitialLinkList(LinkList * l);

Status ListLinkEmpty(LinkList * l);

int ListLinkLength(LinkList * l);

Status GetLinkElem(LinkList * l, int i, Item * e);

LNode * LocateLinkElem(LinkList * l, Item e);

Status ListLinkInsert(LinkList * l, int i, Item e);

Status ListLinkDelete(LinkList * l, int i);

void CreateLinkList_H(LinkList * l, int n);

void CreateLinkList_T(LinkList * l, int n);



#endif //SEQUENCE_LIST_H
