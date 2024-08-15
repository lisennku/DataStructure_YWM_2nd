1. Floyd判圈算法
   - 英文名称为Floyd Cycle Detection Algorithm， 也加快慢指针、龟兔赛跑算法。
2. 算法功能
   - 能够检测链表中是否有环
   - 能够检测环的开始位置
   - 能够检测环的长度
3. 算法思想
   - 检测是否有环
      - 采用两个指针
        - 一个指针每次移动一个结点，称为慢指针，建议变量名为slow/tortoise
        - 另一个指针每次移动两个结点，称为快指针，建议变量名为fast/hare
      - 如果两个指针指向的地址相同，则说明有环
      - 如果两个指针指向的地址不同，则说明没有环
   - 检测环的起点
     - 在检测到有环的情况下，将快指针指向头结点，或慢指针指向头结点，此处假定快指针
     - 然后两个指针同时以相同的速度移动，
     - 当两个指针指向的地址相同时，则说明环的起点
   - 检测环的长度
     - 从环的起点出发，用指针绕环一周
     - 计算经过的节点数即是环的长度
4. 算法实现
```C++
#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
struct ListNode {
    int val;
    struct ListNode *next;
};
// Floyd 判圈算法
struct ListNode* detectCycle(struct ListNode* head) {
    struct ListNode *tortoise, *hare;
    
    // 初始化两个指针
    tortoise = hare = head;
    
    // 检测环
    while (hare != NULL && hare->next != NULL) {
        hare = hare->next->next;  // 快指针移动两步
        tortoise = tortoise->next;  // 慢指针移动一步
        if (hare == tortoise) {  // 如果快指针追上了慢指针
            break;
        }
    }
    
    // 如果没有环
    if (hare == NULL || hare->next == NULL) {
        return NULL;  // 无环
    }
    
    // 寻找环的起始点
    tortoise = head;  // 将慢指针移回链表头部
    while (tortoise != hare) {  // 两个指针以相同速度移动
        tortoise = tortoise->next;
        hare = hare->next;
    }
    
    // 返回环的起始点
    return tortoise;  // 或者 hare, 因为两者现在指向同一节点


```