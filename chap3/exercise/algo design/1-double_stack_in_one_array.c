//
// Created by lisen on 24-8-21.
//
// 1．将编号为0和1的两个栈存放于一个数组空间V[m]中，栈底分别处于数组的两端。
// 当第0号栈的栈顶指针top[0]等于-1时该栈为空；当第1号栈的栈顶指针top[1]等于m时，该栈为空。
// 两个栈均从两端向中间增长（见图3.2）。
// 试编写双栈初始化，判断栈空、栈满、进栈和出栈等算法的函数。双栈数据结构的定义如下：
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "basic.h"

#define MAX_SIZE 100

typedef int Item;

struct dbl_stack {
    int top[2], bot[2] ;         // top表示两个栈的栈顶，bot表示两个栈的栈底
    Item *V;                     // 栈数组
    int m;                       // 数组长度
};

typedef struct dbl_stack DblStack;

// 初始化函数
Status double_stack_init(DblStack * ds) {
/*
 * 双栈的初始化，按照题意要求，需要操作如下步骤：
 *  1. 为数组V动态分配内存空间
 *  2. 初始化栈长度，也即数组长度m
 *  3. 初始化栈顶和栈底的位置，0号栈，栈顶栈底初始化时指向位置-1,1号栈，栈顶栈底初始化时指向位置m
 */
    ds->V = (Item *) malloc(sizeof(Item) * MAX_SIZE);
    if(ds->V == NULL)
        return OVERFLOW;

    ds->m = MAX_SIZE;

    ds->top[0] = ds->bot[0] = -1;
    ds->top[1] = ds->bot[1] = ds->m;

    return OK;
}

// 栈空判断
bool double_stack_is_empty(DblStack ds, int i) {
/*
 * 判断双栈是否为空，变量i为双栈的序号，0 或 1
 *  按照编号判断是因为可能只有双栈中一个栈进行进出操作，另外一个没有进出，因此需要分别判断
 * 判断思路：
 *  双栈各自的栈顶从两端向中间增长，栈底位置不变
 *  因此如果某个栈为空，只需判断对应的栈顶栈底位置即可
 */
    return ds.top[i] == ds.bot[i] ? true : false;
}

// 栈满判断
bool double_stack_is_full(DblStack ds) {
/*
 * 判断双栈是否栈满
 *  当双栈栈满时，说明0号的栈顶的右侧，是1号栈顶
 *  同时因为双栈，一个栈满时，另外一个栈也没有空间进行入栈，因此不需要分别判断
 */
    return ds.top[0] + 1 == ds.top[1] ? true : false;
}

// 入栈操作
Status double_stack_push(DblStack *ds, int i, Item e) {
/*
 * 入栈操作，需要指定入栈的具体是双栈中的哪一个，通过参数i指定，取值范围0 或 1
 * 入栈时
 *  判断栈是否已满，满返回ERROR，未满进行入栈操作
 *  由于双栈的栈顶初始化时分别为-1 和 m，在数组合法范围外，需要先改变栈顶位置，然后入栈
 *      对于0号栈，栈顶++，入栈
 *      对于1号栈，栈顶--，入栈
 */
    if(double_stack_is_full(*ds))
        return ERROR;
    if(i == 0) {
        ds->top[0]++;
        ds->V[ds->top[0]] = e;
    }
    else {
        ds->top[1]--;
        ds->V[ds->top[1]] = e;
    }
    return OK;
}

// 出栈操作
Status double_stack_pop(DblStack * ds, int i, Item *e ) {
/*
 * 出栈操作，需要指定出栈的具体是双栈中的哪一个，通过参数i指定，取值范围0 或 1
 * 出栈时
 *  判断栈是否为空，空则返回ERROR，非空则进行出栈操作
 *  只改变栈顶位置，具体位置的元素因为是数组，无法直接删除
 */
    if(double_stack_is_empty(*ds, i))
        return ERROR;
    if(i == 0) {
        *e = ds->V[ds->top[0]];
        ds->top[0] --;
    }
    else {
        *e = ds->V[ds->top[1]];
        ds->top[1] ++;
    }

    return OK;
}