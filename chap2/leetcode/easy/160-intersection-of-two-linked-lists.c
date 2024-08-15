//
// Created by lisen on 24-8-15.
// https://leetcode.cn/problems/intersection-of-two-linked-lists/description/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct ListNode * List;

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    // 使用尾指针
    // 遍历时，计算长度
    // 原理：
    // 在确定链表相交后， 将两个链表变为相同长度
    // 如果变化呢？  使用一个指针，将长的那条链表，走n步，n为两个链表长度之差
    // 此时同时遍历，找到相同的即可
    // 为什么变为长度相同后，同时遍历即可找到交点呢？
    // 假设，A链表长度为n,B链表长度为m, 相交部分长度为h，不失一般性，假设n>m
    // 考虑这样一个场景，将两个链表底部对齐，到交点处两条链表分开
    // 在往上m-h个结点，A和B还是同样高
    // 所以将A截断到和B一样高，保持相同步长即可找到交点

    List rearA = headA;
    List rearB = headB;
    int la = 1;
    int lb = 1;
    while(rearA->next) {
        la++;
        rearA = rearA->next;
    }
    while(rearB->next) {
        lb++;
        rearB = rearB->next;
    }

    if (rearA != rearB)
        return NULL;

    int gap = la > lb ? la - lb : lb - la;

    List longer = la > lb ? headA : headB;
    List shorter = la > lb ? headB : headA;

    while(gap--)
        longer = longer->next;

    while(longer != shorter) {
        longer = longer->next;
        shorter = shorter->next;
    }

    return shorter;


}