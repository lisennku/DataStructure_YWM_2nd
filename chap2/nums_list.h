//
// Created by lisen on 24-8-5.
//

#ifndef SEQUENCE_LIST_H
#define SEQUENCE_LIST_H

#include "basic.h"  // global status definition
#include <stdbool.h>



#define MAX_SIZE 100

// struct item {
//
// };
//
// typedef struct item Item;

typedef int Item;

// sequence list using array to represent
struct seq_list {
	Item *elem;
	int length;
};

typedef struct seq_list SqList;

// sequence list functions prototype
Status InitialSeqList(SqList * l);

bool ListSeqEmpty(SqList l);

int ListSeqLength(SqList l);

Status GetSeqElem(SqList l, int i, Item * e);

int LocateSeqElem(SqList l, Item e);

Status ListSeqInsert(SqList * l, int i, Item e);

Status ListSeqDelete(SqList * l, int i);


// linked list using header pointer to represent
struct linked_node {
	Item item;
	struct linked_node * next;
};

typedef struct linked_node LNode;
typedef struct linked_node * LinkList;

// linked list functions prototype
Status InitialLinkList(LinkList * l);

bool ListLinkEmpty(LinkList * l);

int ListLinkLength(LinkList * l);

Status GetLinkElem(LinkList * l, int i, Item e);

LNode * LocateLinkElem(LinkList * l, Item e);

Status ListLinkInsert(LinkList * l, int i, Item e);

Status ListLinkDelete(LinkList * l, int i);

void CreateLinkList_H(LinkList * l, int n);

void CreateLinkList_T(LinkList * l, int n);






#endif //SEQUENCE_LIST_H
