//
// Created by lisen on 24-10-18.
//
// https://leetcode.cn/problems/sort-list/description/

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};
typedef struct ListNode Node;

/*
struct ListNode* sortList(struct ListNode* head) {
    // 冒泡排序的时间复杂度是O(n^2) 导致测试用例24超时
    struct ListNode * res = (struct ListNode*) malloc(sizeof(struct ListNode));
    if(head == NULL || head->next == NULL) {
        res = head;
        return res;
    }

    struct ListNode * ptr;
    int is_swapped;
    struct ListNode * find = NULL;

    do {
        is_swapped = 0;
        ptr = head;

        while(ptr->next != find) {
            if(ptr->val > ptr->next->val) {
                struct ListNode * tmp = ptr->next->next;
                ptr->next->next = ptr;
                if(ptr == head) {
                    head = ptr->next;
                }
                else {
                    struct ListNode * prev = head;
                    while(prev->next != ptr)
                        prev = prev->next;
                    prev->next = ptr->next;
                }
                ptr->next = tmp;
                is_swapped = 1;
            }
            else {
                ptr = ptr->next;
            }
        }
        find = ptr;
    }while(is_swapped != 0);

    res = head;
    return res;
}
 */

struct ListNode * two_way_merge(struct ListNode * list1, struct ListNode * list2) {
    struct ListNode * p1 = list1;
    struct ListNode * p2 = list2;
    struct ListNode * res = (struct ListNode *) malloc(sizeof(struct ListNode));
    if(res == NULL)
        exit(EXIT_FAILURE);
    struct ListNode * head = res;

    while(p1 && p2) {
        if(p1->val < p2->val) {
            head->next = p1;
            head = p1;
            p1 = p1->next;
        }
        else {
            head->next = p2;
            head = p2;
            p2 = p2->next;
        }
    }
    if(p1)
        head->next = p1;
    else
        head->next = p2;

    return res->next;
}

struct ListNode* sortList(struct ListNode* head) {
    // 使用时间复杂度为O(nlogn)的二路归并排序
    // 自底向上的二路归并排序

    // 如果链表为空或者只有一个结点 直接返回
    if(head == NULL || head->next == NULL)
        return head;

    // 计算链表长度
    struct ListNode * node = head;
    int length = 0;
    while(node != NULL) {
        length ++;
        node = node->next;
    }

    struct ListNode * dummyHead = (struct ListNode *) malloc(sizeof(struct ListNode));
    dummyHead->next = head;


    // 从分组长度sub_len为1开始 逐次产生长度为sub_len的两个链表 然后合并
    for(int sub_len = 1; sub_len < length; sub_len *= 2) {
        struct ListNode * head1;   // 二路中的第一路
        struct ListNode * head2;   // 二路中的第二路
        struct ListNode * sorted = dummyHead;         // 保存每次循环后合并的链表
        struct ListNode * curr = dummyHead->next;     // 每次循环开始的位置 此处不能是head 因为head链表是原始的未排序的

        while(curr != NULL) {
            // 遍历sub_len次 此时head1的链表就是符合要求的第一路
            head1 = curr;
            for(int i = 1; i < sub_len && curr->next != NULL; i++)
                curr = curr->next;

            // 此处要特殊处理 一方面 head1所包含的链表 在遍历sub_len次后 最后一个结点的next应该是NULL
            // 而curr本身在对应head1的最后一个结点时 其值不是NULL
            // 因此此处需要先将curr.next保存到head2 （虽然本身head2 也应该从curr.next开始）
            // 然后设置curr.next=NULL 确保head1的结点数量正确
            // 然后再将head2的值重新赋值给curr
            head2 = curr->next;
            curr->next = NULL;                // 确保head1的链表长度正确
            curr = head2;

            for(int i = 1; i < sub_len && curr != NULL && curr->next != NULL; i++)
                curr = curr->next;

            // 使用next变量 处理和刚才相同的问题
            struct ListNode * next = NULL;
            if(curr != NULL) {
                next = curr->next;
                curr->next = NULL;             // 确保head2的链表长度正确
            }

            struct ListNode *merge = two_way_merge(head1, head2);

            sorted->next = merge;    // 每次进行外循环时 第一次子循环时 合并后的位置插入到头结点的下一个位置
            // 找到next位置 放置每次外循环时剩余的子循环产生的merge
            while(sorted->next != NULL)
                sorted = sorted->next;

            // 因为前面将curr.next设置为NULL  此处需要恢复以便继续子循环
            curr = next;
        }
    }
    return dummyHead->next;
}

void createList(struct ListNode * l, int * nums, int numsSize) {
    int i = 0;
    while(i < numsSize) {
        l->val = nums[i];
        if(i == numsSize - 1)
            l->next = NULL;
        else
            l->next = (struct ListNode *) malloc(sizeof(Node));
        l = l->next;

        i++;
    }
}

void display(const struct ListNode * l) {
    while(l != NULL) {
        printf("%d ", l->val);
        l = l->next;
    }
}

int main() {
    struct ListNode l;
    int nums[] = {-1,5,3,4,0} ;
    int numsSize = sizeof(nums) / sizeof(int);
    createList(&l, nums, numsSize);
    display(&l);
    Node * res = sortList(&l);
    display(res);
}
