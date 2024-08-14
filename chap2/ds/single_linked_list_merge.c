//
// Created by lisen on 24-8-12.
//
#include <stdio.h>
#include <stdlib.h>
#include "basic.h"
#include "single_linked_list.h"

void show_single_linked_list(single_linked_list l);

void single_linked_list_create_from_rear_with_array(single_linked_list * l, int arr[], int size);

void single_linked_list_merge(single_linked_list * target, const single_linked_list * source);

void ordered_single_linked_list_merge(const single_linked_list * src1, const single_linked_list * src2, single_linked_list * target);

int main() {
	single_linked_list l1, l2, l3;
	if(single_linked_list_initial(&l1) != OK)
		return OVERFLOW;
	if(single_linked_list_initial(&l2) != OK)
		return OVERFLOW;

	// int arr1[] = {7, 5, 3, 11};
	// int arr2[] = {2, 6, 3};
	int arr1[] = {3, 5, 8, 11};
	int arr2[] = {2, 6, 8, 9, 11, 15, 20};
	single_linked_list_create_from_rear_with_array(&l1, arr1, 4);
	single_linked_list_create_from_rear_with_array(&l2, arr2, 7);
	printf("Original linked list shows below\n");
	show_single_linked_list(l1);
	show_single_linked_list(l2);
	printf("Now merging two list\n");
	// single_linked_list_merge(&l1, &l2);
	ordered_single_linked_list_merge(&l1, &l2, &l3);
	show_single_linked_list(l3);
	//
}
void show_single_linked_list(single_linked_list l) {
	// 此时l是头指针，需要找到首元结点
	Node * p = l->next; // p指向首元结点

	while (p != NULL) {
		printf("%d ", p->item);
		p = p->next;
	}
	putchar('\n');
}

void single_linked_list_create_from_rear_with_array(single_linked_list * l, int arr[], int size) {
	Node * rear = *l ;
	for(int i = 0; i < size; i ++) {
		Node * p = (Node *) malloc(sizeof(Node));
		p->item = arr[i];

		p->next = NULL;
		rear->next = p;
		rear = p;
	}
}

void single_linked_list_merge(single_linked_list * target, const single_linked_list * source) {
	Node * current = (*source)->next;
	unsigned int target_len = single_linked_list_length(*target);

	while(current != NULL) {
		Item e = current->item;
		if(!single_linked_list_locate_element(*target, e)) {
			single_linked_list_insert_element(target, ++target_len, e);
		}
		current = current->next;
	}


}

void ordered_single_linked_list_merge(const single_linked_list * src1, const single_linked_list * src2, single_linked_list * target) {
	Node * pa = (*src1)->next;  // 首元结点
	Node * pb = (*src2)->next;  // 首元结点
	*target = *src1;
	Node * pc = *target;        // pc指向头结点，相当于头指针，但是后续操作类似尾指针

	while(pa && pb) {
		if(pa->item <= pb->item) {
			// 将pa此时的结点更新到pc后
			pc->next = pa;      // 更新后续结点
			pc = pa;            // 移动尾指针
			pa = pa->next;
		}
		else {
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}

	pc->next = pa ? pa : pb;

}


