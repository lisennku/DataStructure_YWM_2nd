//
// Created by lisen on 24-8-9.
//
// used to test array list merge

#include <stdio.h>
#include <stdlib.h>

#include "basic.h"
#include "array_list.h"

// 涉及到修改目标，因此以指针传入
void array_list_merge(array_list * target, array_list source);

// 涉及到修改目标，因此以指针传入
// array_list并没有实现按照顺序插入，只是根据有序数组为array_list赋值时，实现array_list内部的有序
// 计划实现ordered_array_list.h，
void ordered_array_list_merge(array_list src1, array_list src2, array_list * result);

void show_array_list(array_list a);

void ArrayCopyToList(Item arr[], int n, array_list * a);

int main() {
	array_list target;
	array_list source;

	array_list result;

	// Item tmp1[] = {7, 5, 3, 11};
	// Item tmp2[] = {2, 6, 3};

	Item tmp1[] = {3, 5, 8, 11};
	Item tmp2[] = {2, 6, 8, 9, 11, 15, 20};

	// 初始化
	if(array_list_initial(&target) != OK) {
		printf("Error when initializing array list. Variable name target\n");
		exit((EXIT_FAILURE));
	}

	if(array_list_initial(&source) != OK) {
		printf("Error when initializing array list. Variable name source\n");
		exit((EXIT_FAILURE));
	}

	ArrayCopyToList(tmp1, 4, &target);
	ArrayCopyToList(tmp2, 7, &source);

	printf("Now the array list is \n");
	printf("target is: ");
	show_array_list(target);
	printf("source is: ");
	show_array_list(source);

	// array_list_merge(&target, source); 无序
	ordered_array_list_merge(target, source, &result); // 有序

	printf("Now the merged array list target is: \n");
	show_array_list(result);

	return 0;
}

void show_array_list(array_list a) {
	for(int i = 0; i < a.length; i++)
		printf("%d ", a.elem[i]);
	putchar('\n');
}

void ArrayCopyToList(Item arr[], int n, array_list * a) {
	for(int i = 1; i <= n; i++) {
		array_list_insert_element(a, i, arr[i - 1]);
	}
}

void array_list_merge(array_list * target, array_list source) {
	// 两个array_list合并
	// 时间复杂度为m*n，get_element和insert_element和长度无关
	//		虽然insert_element的时间复杂度为O(n)，但此时在数组末尾插入，不需要循环，因此为O(1)
	// 因此时间复杂度考虑循环source的长度，和locate_element(target)的长度
	// 需要遍历source，检查当前元素是否在target中
	//		是，忽略
	//		否，插入到target
	unsigned int lt = target->length;
	unsigned int ls = source.length;
	// 循环source
	for(int i = 1; i <= ls; i ++) {
		Item e;
		array_list_get_element(source, i, &e);
		if(!array_list_locate_element(*target, e)) // target是指针，locate_element函数要求传入一个array_list对象，因此解引用
			array_list_insert_element(target, ++lt, e);
	}
}

void ordered_array_list_merge(array_list src1, array_list src2, array_list * result) {
	// result不要初始化，需要人为指定长度和分配内存空间
	// 以便用指针来实现排序和赋值
	unsigned int l1 = src1.length;
	unsigned int l2 = src2.length;
	unsigned int lr = l1 + l2;

	// 初始化
	result->elem = (Item *) malloc(sizeof(Item) * lr);
	result->length = lr;

	// 使用指针表示，方便赋值等操作
	Item * p1 = src1.elem;
	Item * p2 = src2.elem;
	Item * pr = result->elem;

	// 最后一个元素的指针指向的地址，指针+1，是按照指向的类型的字节数*1增加
	Item * p1_last = src1.elem + l1 - 1;
	Item * p2_last = src2.elem + l2 - 1;
	Item * pr_last = result->elem + lr - 1;

	while((p1 <= p1_last) && (p2 <= p2_last)) {
		if(*p1 <= *p2)
			*pr++ = *p1++;
		else
			*pr++ = *p2++;
	}

	// 前述while循环，当p1到达最后或者p2到达最后，跳出
	// 下面两个while循环，将剩余的一个没有循环完毕的指针继续循环，直到完毕

	while (p1 <= p1_last)
		*pr++ = *p1++;

	while (p2 <= p2_last)
		*pr++ = *p2++;
}