//
// Created by lisen on 24-8-8.
//

#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

typedef int Item;
struct node {
	Item item;
	struct node * next;
};

typedef struct node Node;
typedef struct node * Single_linked_list;

#endif //SINGLE_LINKED_LIST_H
