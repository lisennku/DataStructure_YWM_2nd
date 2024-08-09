//
// Created by lisen on 24-8-9.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "basic.h"
#include "array_list.h"

// 初始化一个array_list，为elem分配内存空间，将length赋值为0
// 参数传入array_list类型变量的地址，因为需要在函数中修改外部变量的值，C中需要使用指针
Status array_list_initial(array_list * a) {
	a->elem = (Item *) malloc(sizeof(Item) * MAX_SIZE);
	if(a->elem == NULL)
		return OVERFLOW;

	a->length = 0;

	return OK;

}

// 返回array_list是否为空，是返回true， 否则返回false
// 不需要传入指针，因为不涉及到修改
bool array_list_is_empty(array_list a) {
	return a.length == 0 ? true : false;
}

// 返回array_list长度
// 由于length成员本身是unsigned int类型，所以函数返回类型也是unsigned int
// 同样，不涉及修改，不需要传入指针
unsigned int array_list_length(array_list a) {
	return a.length;
}

// 从一个以初始化的array_list中，返回第i个元素的内容，到Item类型的变量里
// position表示从1开始的位置
// 此次涉及到修改外部Item类型变量e的值，所以e以指针形式传入
Status array_list_get_element(array_list a, int position, Item * e) {
	// 检查position是否合法
	if (position < 1 || position > a.length)
		return ERROR;
	// 查找指定位置的元素
	// 由于位置是从1开始，数组是从0开始
	// 因此涉及到position与数组脚标对齐的问题
	*e = a.elem[position - 1];
	return OK;
}

// 在一个以初始化的array_list中，返回第一个与Item e相同的元素的位置
// 返回的位置从1开始
// 查找失败返回0
unsigned int array_list_locate_element(array_list a, Item e) {
	// 返回position，position从1开始
	// 涉及到position与数组脚标对齐的问题

	for(int i = 0; i < a.length; i++) {
		if(a.elem[i] == e) {
			return i + 1; // 只要求第一次找到
		}
	}
	return 0; // 如果执行到这，说明for循环结束，没有查找到指定元素
}

// 向一个以初始化的array_list的某个position位置插入元素
// position从1开始，到array_list.length+1
//		因为要求连续存储，也即position最大也只能在当前最后一个元素后插入
// 涉及到修改array_list，因此以指针传入
// 需要检查数组是否有剩余空间
// 需要更新长度
Status array_list_insert_element(array_list * a, int position, Item e) {
	// 检查position合法性
	if(position < 1 || position > a->length + 1)
		return ERROR;
	// 检查空间是否有剩余
	if(a->length == MAX_SIZE)
		return ERROR;
	// 向位置position插入元素，涉及到position和数据脚标对齐，以及数组元素挪动
	// 位置position，对应数组脚标position - 1
	// 因此，数组中，脚标从position - 1开始，需要向后挪动
	//		以position角度看，共需挪动length - position + 1个元素
	//		以数组脚标角度看，共需挪动(length - 1) - arr_index + 1个元素，length - 1代表当前数组最大的脚标
	// 举例：
	//		数组长度为10， 向position为5的位置插入元素
	//			因此，需要挪动6个元素，10 - 5 + 1 or 9 - 4 + 1
	// 挪动时，需要从后向前开始，否则会导致覆盖
	for(int i = a->length - 1; i >= position - 1; i --) {
		a->elem[i + 1] = a->elem[i];
	}
	// 挪动完成后，向position - 1 位置覆盖新值
	a->elem[position - 1] = e;
	// 长度同样需要更新
	a->length ++;

	return OK;

}

// 在一个以初始化的array_list中，删除position位置的元素
// position从1开始，到array_list.length为止，因为不能删除其他位置的元素，还处于未定义状态
// 涉及到修改array_list，因此以指针传入
// 需要更新长度
Status array_list_delete_element(array_list * a, int position) {
	// 检查position合法性
	if(position < 1 || position > a->length)
		return ERROR;
	// 从position位置删除一个元素，涉及到position和脚标对齐，和向前挪动后续元素
	// 位置position，对应数组脚标position - 1
	// 因此，从位置position + 1开始，也即数组脚标position，后续的元素需要向前挪动
	//		以position的角度来看，共需挪动length - position个元素
	//		以数组脚标角度来看，共需挪动(length - 1) - (position - 1)个元素
	// 挪动时，需要从前向后移动，否则会覆盖
	for(int i = position; i < a->length; i ++) {
		a->elem[i - 1] = a->elem[i];
	}
	// 需要注意，此时数组中，最后一个元素虽然向前挪动，并覆盖了前面一个元素的值
	// 但该位置的值并没有被丢弃
	// 所以需要更新长度，以控制对数组的访问范围
	// 更新length
	a->length --;
	return OK;
}

// 遍历array_list，并将每个元素应用于函数pfun
void array_list_traverse(array_list a, void (*pfun)(Item e)) {
	for(int i = 0; i < a.length; i ++)
		(*pfun)(a.elem[i]);
}
