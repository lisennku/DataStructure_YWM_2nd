//
// Created by lisen on 24-8-9.
//

#include "basic.h"
#include "single_linked_list.h"
#include <stdbool.h>
#include <stdlib.h>

// 初始化带有头结点的单向链表
// 由于函数需要修改外部header变量，所以参数要以指针形式传入
// 使用动态内存分配一个头结点，将头结点的地址赋值给header，也即指向该头结点的地址
// 在使用该函数前，需要声明single_linked_list header;
//		此时header的内容并没有具体化，所以我们需要在初始化函数中传入header的地址
//		以便能改变header内存储的值
Status single_linked_list_initial(single_linked_list * l) {
	*l = (Node *) malloc(sizeof(Node));
	if((*l) == NULL)
		return OVERFLOW;
	(*l) -> next = NULL;
	return OK ;
}

// 返回单向链表是否为空
// 该函数与书中参数保持相同类型
// 该函数不涉及修改链表，所以可以不以指针形式传入
bool single_linked_list_empty(single_linked_list l) {
	// 此时传入的l，是头指针
	// 所以判断头指针指向的头结点的next是否为空即可
	return l->next == NULL ? true : false;
}

// 返回单向链表是否为空
// 使用const修饰指针，确保函数中不会修改该指针
// 该函数与C Primer Plus中保持一致
bool single_linked_list_empty_ptr(const single_linked_list * l) {
	// 此时l是头指针的地址，而不是头指针
	return (*l)->next == NULL ? true : false;
}

// 返回单向链表长度
// 该函数不涉及修改链表，所以可以不以指针形式传入
unsigned int single_linked_list_length(single_linked_list l) {
	// 带有头结点的链表
	// l此时是头指针
	Node * p = l->next;  // 此时p指向首元结点

	unsigned int cnt = 0;

	while(p != NULL) {   // 因为此处已经指向了首元结点，所以不要用p->next != NULL进行判断
		cnt ++;
		p = p->next;
	}

	return cnt;
}

// 返回单向链表长度
// 使用const修饰指针，确保函数中不会修改该指针
// 该函数与C Primer Plus中保持一致
unsigned int single_linked_list_length_ptr(const single_linked_list * l) {
	// 此时l是头指针的地址，而不是头指针
	Node * p = (*l)->next;  // 此时p指向首元结点
	unsigned int cnt = 0;

	while(p != NULL) {      // 因为此处已经指向了首元结点，所以不要用p->next != NULL进行判断
		cnt ++;
		p = p->next;
	}

	return cnt;

}

// 获取对应位置的结点元素，并传入Item * e变量内
// 该函数不涉及修改链表，所以可以不以指针形式传入
// 该函数与书中参数保持相同类型
Status single_linked_list_get_element(single_linked_list l, int position, Item * e) {
	// 此时l是头指针
	// position指的是，以首元结点为编号1开始的序号
	Node * p = l->next;
	int i = 1;
	while(p != NULL && i < position) { // 当i=position时，此时p已经指向了指定位置的结点
		p = p->next;
		i ++;
	}

	// 需要判断p不为null且i在合法范围内
	// 因为不能确定上边while的条件是因何退出的
	if((p == NULL) || i > position)
		return ERROR;

	*e = p->item;

	return OK;
}

// 获取对应位置的结点元素，并传入Item * e变量内
// 使用const修饰指针，确保函数中不会修改该指针
// 该函数与C Primer Plus中保持一致
Status single_linked_list_get_element_ptr(const single_linked_list * l, int position, Item * e) {
	// 此时l是头指针的地址，而不是头指针
	// position指的是，以首元结点为编号1开始的序号
	Node * p = (*l)->next;
	int i = 1;
	while(p != NULL && i < position) { // 当i=position时，此时p已经指向了指定位置的结点
		p = p->next;
		i ++;
	}

	// 需要判断p不为null且i在合法范围内
	// 因为不能确定上边while的条件是因何退出的
	if((p == NULL) || i > position)
		return ERROR;

	*e = p->item;

	return OK;
}

// 返回指定元素，没有返回NULL
// 该函数不涉及修改链表，所以可以不以指针形式传入
// 该函数与书中参数保持相同类型
Node * single_linked_list_locate_element(single_linked_list l, Item e) {
	// 此时l是头指针
	Node * p = l->next;
	while(p != NULL && p->item != e) {
		p = p->next;
	}

	return p;   // 如果没查到则返回NULL
}

// 返回指定元素，没有返回NULL
// 使用const修饰指针，确保函数中不会修改该指针
// 该函数与C Primer Plus中保持一致
Node * single_linked_list_locate_element_ptr(const single_linked_list * l, Item e) {
	// 此时l是头指针
	Node * p = (*l)->next;
	while(p != NULL && p->item != e) {
		p = p->next;
	}

	return p;   // 如果没查到则返回NULL
}

// 返回指定元素在链表中的位置，位置以首元结点为1开始编号，没找到返回0
// 该函数不涉及修改链表，所以可以不以指针形式传入
// 该函数与书中参数保持相同类型
unsigned int single_linked_list_locate_element_position(single_linked_list l, Item e) {
	unsigned int position = 1;
	Node *p = l->next;
	while(p != NULL) {
		if(p->item == e)
			return position;
		p = p->next;
		position ++;
	}

	return 0;  // 没找到返回0
}

// 返回指定元素在链表中的位置，位置以首元结点为1开始编号，没找到返回0
// 使用const修饰指针，确保函数中不会修改该指针
// 该函数与C Primer Plus中保持一致
unsigned int single_linked_list_locate_element_position_ptr(const single_linked_list * l, Item e) {
	unsigned int position = 1;
	Node *p = (*l)->next;
	while(p != NULL) {
		if(p->item == e)
			return position;
		p = p->next;
		position ++;
	}

	return 0;  // 没找到返回0
}

// 在位置position插入结点
// 涉及到修改header，所以以指针形式传入
Status single_linked_list_insert_element(single_linked_list * l, int position, Item e) {
	Node *p = *l;
	int i = 0;     // 如果Node *p = (*l)->next，则此处应该为1
	// 需要找到position - 1的位置，因为此时p指向该位置的结点
	// 新增节点在该节点后，需要该节点的next更改为新节点
	// 所以 i < position - 1，因为此时进入循环，p指向position - 1位置的结点， i = position - 1
	while(p != NULL && i < position - 1) {
		p = p->next;
		i ++;
	}

	if(p == NULL || i > position - 1)
		return ERROR;

	// 此时p已经指向了position-1
	Node * new = (Node *) malloc(sizeof(Node));

	// 将position - 1位置的下一个位置的地址，赋值给new->next
	// ！！如下两步的顺序不可能改！！
	new->next = p->next;
	p->next = new;

	return OK;
}

// 在位置position删除结点
// 涉及到修改header，所以以指针形式传入
Status single_linked_list_delete_element(single_linked_list * l, int position) {
	Node * p = *l ;
	int i = 0;

	// 由于需要用额外指针存储待删除的结点，所以需要在while跳出后，使用额外指针，被赋值为p->next
	// 所以此处应判断p->next，而不是p
	// 否则会超过现有结点数量n
	while((p->next != NULL) && i < position - 1) {
		p = p->next;
		i ++;
	}

	if (p == NULL || i > position - 1)
		return ERROR;

	Node * q = p->next;

	// 更新删除节点前面一个结点的next属性
	p->next = q->next;

	// 释放删除结点
	free(q);

	return OK;
}

// 创建单向链表，采取前插法，也即新增节点插入到头结点后
void single_linked_list_create_from_head(single_linked_list * l, int size);

// 创建单向链表，采取后插法，也即新增节点插入到尾部
void single_linked_list_create_from_tail(single_linked_list * l, int size);
