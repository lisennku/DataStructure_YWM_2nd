//
// Created by lisen on 24-8-9.
//
#include <stdio.h>
void test1(int n);
void test2(int * n);
int main() {
	int a = 10;
	printf("outer address for a is %p\n", &a);

	test1(a);
	printf("outer address for a is %p\n", &a);

	test2(&a);
	printf("outer address for a is %p\n", &a);
}

void test1(int n) {
	n = 20;
	printf("inner pointer pass address for a is %p\n", &n);
}

void test2(int * n) {
	*n = 20;
	printf("inner value pass address for  a is %p\n", n);
	printf("inner value pass address for &a is %p\n", &n);
}