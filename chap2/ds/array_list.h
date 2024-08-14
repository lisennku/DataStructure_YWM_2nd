//
// Created by lisen on 24-8-8.
//

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#if 0
	使用数组表示顺序表, 用宏定义MAX_SIZE表示数组的最大容量
#endif

#include <stdbool.h>
#include "basic.h"
#define MAX_SIZE 100

typedef int Item;

struct node {
	Item * elem;
	unsigned int length;
	};

typedef struct node array_list;  // 不需要像链表那样再定义一个指针，因为数组类的顺序表可以直接访问

// 初始化一个array_list，为elem分配内存空间，将length赋值为0
// 参数传入array_list类型变量的地址，因为需要在函数中修改外部变量的值，C中需要使用指针
Status array_list_initial(array_list * a);

// 返回array_list是否为空，是返回true， 否则返回false
// 不需要传入指针，因为不涉及到修改
bool array_list_is_empty(array_list a);

// 返回array_list长度
// 由于length成员本身是unsigned int类型，所以函数返回类型也是unsigned int
// 同样，不涉及修改，不需要传入指针
unsigned int array_list_length(array_list a);

// 从一个以初始化的array_list中，返回第i个元素的内容，到Item类型的变量里
// position表示从1开始的位置
// 此次涉及到修改外部Item类型变量e的值，所以e以指针形式传入
// 查找到的元素已经直接赋值给了外部变量Item e，因此函数返回值只需要是状态即可
Status array_list_get_element(array_list a, int position, Item * e);

// 在一个以初始化的array_list中，返回第一个与Item e相同的元素的位置
// 返回的位置从1开始
// 查找失败返回0
unsigned int array_list_locate_element(array_list a, Item e);

// 向一个以初始化的array_list的某个position位置插入元素
// position从1开始，到array_list.length+1
//		因为要求连续存储，也即position最大也只能在当前最后一个元素后插入
// 涉及到修改array_list，因此以指针传入
// 需要检查数组是否有剩余空间
// 需要更新长度
Status array_list_insert_element(array_list * a, int position, Item e);

// 在一个以初始化的array_list中，删除position位置的元素
// position从1开始，到array_list.length为止，因为不能删除其他位置的元素，还处于未定义状态
// 涉及到修改array_list，因此以指针传入
// 需要更新长度
Status array_list_delete_element(array_list * a, int position);

// 遍历array_list，并将每个元素应用于函数pfun
void array_list_traverse(array_list a, void (*pfun)(Item e));

#endif //ARRAY_LIST_H
