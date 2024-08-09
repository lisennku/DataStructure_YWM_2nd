//
// Created by lisen on 24-8-8.
//

#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#if 0
	带有头结点的单向链表
	首元结点, 是链表总的第一个结点
	头结点, 首元结点前的一个结点, 用于统一插入/删除等操作
	头指针, 指向头结点, 存储头结点的地址, 可以表示一个单向链表
#endif

#include "basic.h"
#include <stdbool.h>

typedef int Item;
struct node {
	Item item;
	struct node * next;
};

// Node * 和 single_linked_list的效果相同
// Node * 通常用于声明一个指向链表中某个节点的指针
// single_linked_list 通常用于声明一个头指针
typedef struct node Node;
typedef Node * single_linked_list;

// 初始化带有头结点的单向链表
// 由于函数需要修改外部header变量，所以参数要以指针形式传入
// 使用动态内存分配一个头结点，将头结点的地址赋值给header，也即指向该头结点的地址
// 在使用该函数前，需要声明single_linked_list header;
//		此时header的内容并没有具体化，所以我们需要在初始化函数中传入header的地址
//		以便能改变header内存储的值
Status single_linked_list_initial(single_linked_list * l);

// 返回单向链表是否为空
// 该函数与书中参数保持相同类型
// 该函数不涉及修改链表，所以可以不以指针形式传入
bool single_linked_list_empty(single_linked_list l);

// 返回单向链表是否为空
// 使用const修饰指针，确保函数中不会修改该指针
// 该函数与C Primer Plus中保持一致
bool single_linked_list_empty_ptr(const single_linked_list * l);

// 返回单向链表长度
// 该函数不涉及修改链表，所以可以不以指针形式传入
unsigned int single_linked_list_length(single_linked_list l);

// 返回单向链表长度
// 使用const修饰指针，确保函数中不会修改该指针
// 该函数与C Primer Plus中保持一致
unsigned int single_linked_list_length_ptr(const single_linked_list * l);

// 获取对应位置的结点元素，并传入Item * e变量内
// 该函数不涉及修改链表，所以可以不以指针形式传入
// 该函数与书中参数保持相同类型
Status single_linked_list_get_element(single_linked_list l, int position, Item * e);

// 获取对应位置的结点元素，并传入Item * e变量内
// 使用const修饰指针，确保函数中不会修改该指针
// 该函数与C Primer Plus中保持一致
Status single_linked_list_get_element_ptr(const single_linked_list * l, int position, Item * e);

// 返回指定元素，没有返回NULL
// 该函数不涉及修改链表，所以可以不以指针形式传入
// 该函数与书中参数保持相同类型
Node * single_linked_list_locate_element(single_linked_list l, Item e);

// 返回指定元素，没有返回NULL
// 使用const修饰指针，确保函数中不会修改该指针
// 该函数与C Primer Plus中保持一致
Node * single_linked_list_locate_element_ptr(const single_linked_list * l, Item e);

// 返回指定元素在链表中的位置，位置以首元结点为1开始编号，没找到返回0
// 该函数不涉及修改链表，所以可以不以指针形式传入
// 该函数与书中参数保持相同类型
unsigned int single_linked_list_locate_element_position(single_linked_list l, Item e);

// 返回指定元素在链表中的位置，位置以首元结点为1开始编号，没找到返回0
// 使用const修饰指针，确保函数中不会修改该指针
// 该函数与C Primer Plus中保持一致
unsigned int single_linked_list_locate_element_position_ptr(const single_linked_list * l, Item e);

// 在位置position插入结点
// 涉及到修改header，所以以指针形式传入
Status single_linked_list_insert_element(single_linked_list * l, int position, Item e);

// 在位置position删除结点
// 涉及到修改header，所以以指针形式传入
Status single_linked_list_delete_element(single_linked_list * l, int position);

// 创建单向链表，采取前插法，也即新增节点插入到头结点后
void single_linked_list_create_from_head(single_linked_list * l, int size);

// 创建单向链表，采取后插法，也即新增节点插入到尾部
void single_linked_list_create_from_tail(single_linked_list * l, int size);


#endif //SINGLE_LINKED_LIST_H
