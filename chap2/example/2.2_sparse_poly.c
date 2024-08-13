//
// Created by lisen on 24-8-13.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "basic.h"

struct PolyItem {
	double coef;
	int   expo;
	struct PolyItem * next;
};

typedef struct PolyItem PNode;         // PNode * 用来声明一个指向某个结点的指针
typedef struct PolyItem * Polynomial;  // 声明头指针

Polynomial InitialPoly();                                          // 返回头结点的地址，赋值给头指针
void CreateSparsePoly(Polynomial * poly, int n);                   // n指定项数
void SparsePolyPlus(Polynomial * lpoly, Polynomial * rpoly);       // 多项式加法
void SparsePolyMinus(Polynomial * lpoly, Polynomial * rpoly);      // 多项式减法
void SparsePolyMulti(Polynomial * lpoly, Polynomial * rpoly);      // 多项式乘法
void ShowSparsePoly(Polynomial poly);
void DestroySparsePoly(Polynomial * poly);

int main() {
	Polynomial p1 = InitialPoly();
	Polynomial p2 = InitialPoly();
	printf("Now generating lpoly:\n");
	CreateSparsePoly(&p1, 2);
	printf("Now generating rpoly:\n");
	CreateSparsePoly(&p2, 2);
	ShowSparsePoly(p1);
	ShowSparsePoly(p2);

	// SparsePolyPlus(&p1, &p2);
	// printf("Now display merged poly\n");
	// ShowSparsePoly(p1);

	SparsePolyMinus(&p1, &p2);
	printf("Now display minused poly\n");
	ShowSparsePoly(p1);
}

Polynomial InitialPoly() {
	Polynomial ret = (Polynomial) malloc(sizeof(PNode));
	ret->next = NULL;

	return ret;
}

void CreateSparsePoly(Polynomial * poly, int n) {
	// 向多项式链表中插入项
	// 记录当前结点，和当前节点的前一个结点
	// 找到第一个比输入的指数大的结点，或 当前结点为NULL，也即空链表，或者找到最后一个结点的next
	//		如果为NULL则表示
	//			要么作为首元结点插入，要么作为链表的最后一个结点插入
	// 将新增结点插入到该结点之前
	// poly参数此时是头指针的地址，而非头指针

	for(int i = 1; i <= n; i++) {
		PNode * new = (PNode *) malloc(sizeof(PNode)); // 新结点
		PNode * prev = *poly;                              // prev指向头结点
		PNode * cur = (*poly)->next;                       // cur指向首元结点
		if(new == NULL)
			exit(OVERFLOW);
		printf("please input the coef and expo\n");
		scanf("%lf %d", &new->coef, &new->expo);

		if(new->coef == 0)  //系数为0不插入，书上没有
			continue;

		while(cur != NULL && cur->expo < new->expo) {
			// 跳出循环条件有2：
			//	cur为null，说明要么是头结点的next，要么是最后一个结点的next
			//		      对应的，prev要么为头结点，要么为最后一个结点
			//  当前节点的指数大于输入的指数
			//		要将新结点插入到prev后
			//  注意，书上的生成多项式链表的代码并没有处理相同指数的情况，后续自定义系数多项式代码中会处理 2_2.sparse_poly_customized.c
			prev = cur;
			cur = cur->next;
		}

		prev->next = new;
		new->next = cur;
	}
}

void SparsePolyPlus(Polynomial * lpoly, Polynomial * rpoly) {
	// 函数合并两个多项式链表，并以lpoly返回合并后的链表
	// 创建三个指针，p1指向lpoly的首元结点，p2指向rpoly的首元结点
	// p3 赋值为lpoly，也即lpoly的头结点，但是代码中作用相当于尾指针，始终指向当前结点
	// 另外创建del指针，用来释放内存空间
	// 循环，条件为p1p2不为空
	// 此时插入多项式的项目
	//	分为三种情况
	//		1. 两个项的指数相同
	//			合并系数，并判断系数是否等于0，等于0舍弃该项，释放两个结点，
	//			不等于0，则插入p3，释放另外一个节点
	//		2. p1指向结点的指数小于p2指向的结点
	//		3. p1指向结点的指数大于p2指向的结点

	PNode * p1 = (*lpoly)->next;
	PNode * p2 = (*rpoly)->next;
	PNode * p3 = *lpoly;              // 指向lpoly的头结点，后续更新lpoly的next值

	while((p1 != NULL) && (p2 != NULL)) {
		if(p1->expo == p2->expo) {
			double coef_sum = p1->coef + p2->coef;
			if (coef_sum == 0) {   // 释放两个结点
				PNode * del1 = p1;
				p1 = p1->next;     // 在释放之前，先将p1移动到下一个结点
				free(del1);

				PNode * del2 = p2;
				p2 = p2->next;
				free(del2);
			}
			else {  // 更新p1结点的coef
				p1->coef = coef_sum;
				p3->next = p1;  // 将更新后的结点放到p3后
				p3 = p1;        // 更新尾指针位置
				p1 = p1->next;

				PNode * del = p2; // 释放p2结点
				p2 = p2->next;    // 释放前先更新p2
				free(del);
			}
		}
		else if(p1->expo < p2->expo) {  // 将指数小的放到结果多项式内
			p3->next = p1;
			p3 = p1;           // 更新尾指针
			p1 = p1->next;
		}
		else {
			p3->next = p2;
			p3 = p2;           // 更新尾指针
			p2 = p2->next;
		}
	}

	p3->next = p1 == NULL ? p2 : p1;  // 将剩余结点放入结果链表

	free(*rpoly);                      // 不应该将rpoly的每个结点都释放掉
}

void SparsePolyMinus(Polynomial * lpoly, Polynomial * rpoly) {
	// 先将rpoly的coef取反， 然后调用SparsePolyPlus即可
	PNode * oppo = (*rpoly)->next;         // 将oppo指向首元结点
	while(oppo != NULL) {
		oppo->coef = oppo->coef * -1;
		oppo = oppo->next;
	}
	SparsePolyPlus(lpoly, rpoly);
}

void SparsePolyMulti(Polynomial * lpoly, Polynomial * rpoly) {

}

void ShowSparsePoly(Polynomial poly) {
	PNode * p = poly->next;    // 此时p指向首元结点
	int i = 0;
	while(p != NULL) {
		if (i == 0)
			printf("%s%.2lfx^%d", p->coef > 0 ? "" : "", p->coef, p->expo);
		else
			printf("%s%.2lfx^%d", p->coef > 0 ? "+" : "", p->coef, p->expo);
		i++;
		p = p->next;
	}
	putchar('\n');
}

void DestroySparsePoly(Polynomial * poly) {
	PNode * current = *poly;
	PNode * next;
	while(current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}

	*poly = NULL;
}



