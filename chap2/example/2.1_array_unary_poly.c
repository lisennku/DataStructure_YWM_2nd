//
// Created by lisen on 24-8-12.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "basic.h"

#define MAX_SIZE 100

typedef int Item;

struct array_poly {
	Item * elem;
	unsigned int size;
};

typedef struct array_poly Array_Poly;

void InitArrayPoly(Array_Poly * apoly);
void CreateArrayPoly(Array_Poly *apoly, int arr[], int n);
void AddArrayPoly(Array_Poly *a, Array_Poly b);
void PrintArrayPoly(Array_Poly apoly);

int main() {
	Array_Poly a, b;
	int arr1[] = {10, 5, -4, 3, 2};
	int arr2[] = {0, 0, 6, 2, 0, 10};

	InitArrayPoly(&a);
	InitArrayPoly(&b);

	CreateArrayPoly(&a, arr1, 5);
	CreateArrayPoly(&b, arr2, 6);

	// for(int i = 0; i < a.size; i ++)
	// 	printf("%d", a.elem[i]);
	//
	// putchar('\n');
	// for(int i = 0; i < a.size; i ++)
	// 	printf("%d", a.elem[i]);
	// putchar('\n');

	printf("Respective poly is \n");
	PrintArrayPoly(a);
	PrintArrayPoly(b);

	printf("Now merge two polys\n");
	AddArrayPoly(&a, b);
	printf("Merging finished\n");
	PrintArrayPoly(a);

	return 0;
}

void InitArrayPoly(Array_Poly * apoly) {
	apoly->elem = (Item *) malloc(sizeof(Item) * MAX_SIZE);
	if(apoly->elem == NULL)
		exit(OVERFLOW);
	apoly->size = 0;
}
void CreateArrayPoly(Array_Poly *apoly, int arr[], int n) {
	if((MAX_SIZE - apoly->size) < n)
		exit(OVERFLOW);
	for(int i = 0; i < n; i++) {
		apoly->elem[i] = arr[i];
		apoly->size ++;
	}
}
void AddArrayPoly(Array_Poly *a, Array_Poly b) {
	unsigned int la = a->size;
	unsigned int lb = b.size;

	unsigned int lc = la < lb ? la : lb; // 找到长度较小的那个
	int i ;
	for(i = 0; i < lc; i++) {
		a->elem[i] += b.elem[i];
	}
	while (i < la) ;  // 如果本身a长，无需变动后边的元素

	while (i < lb) {  // 如果本身b长，说明需要增加a的数组长度，则elem和size对应变化
		a->elem[i] = b.elem[i];
		a->size ++;
		i++;
	}
}
void PrintArrayPoly(Array_Poly apoly) {
	printf("y = ");
	for(int i = 0; i < apoly.size; i ++) {
		if(apoly.elem[i] != 0) {
			printf("%dx^%d", apoly.elem[i], i);
			if(i < apoly.size - 1)
				printf("%s", apoly.elem[i+1] < 0 ? "" : "+");
		}
	}
	printf("\n");
}