//
// Created by lisen on 24-10-17.
//
// https://leetcode.cn/problems/max-number-of-k-sum-pairs/description/?envType=study-plan-v2&envId=leetcode-75
// 给你一个整数数组 nums 和一个整数 k
// 每一步操作中，你需要从数组中选出和为 k 的两个整数，并将它们移出数组
// 返回你可以对数组执行的最大操作数
#include <stdio.h>
#include <stdlib.h>

/*
int maxOperations(int* nums, int numsSize, int k){
    // 测试用例45超时！！
    int count = 0;
    // 记录对应nums位置的元素是否被选择
    int * is_selected = (int *) calloc(numsSize, sizeof(int));
    if(is_selected == NULL)
        exit(EXIT_FAILURE);

    for(int i = 0; i < numsSize; i++)
        if(is_selected[i] == 0) { // 外层选择不能是之前已经处理过的
            is_selected[i] = 1;
            int diff = k - nums[i];
            for(int j = i + 1; j < numsSize; j++) {
                if(diff == nums[j] && is_selected[j] == 0) {  // 符合要求的位置也不能是之前处理过的
                    is_selected[j] = 1;
                    count ++;
                    break;
                }
            }
        }

    return count ;
}
 */

int cmp(const void * a, const void * b) {
    return (*(int *)a - *(int *)b);;
}

int maxOperations(int* nums, int numsSize, int k){
    /*
     * 先将数组正序排序 然后front指针指向数组头部 rear指针指向数组尾部
     * 计算头尾两个位置的数值的和
     *  如果大于k 此时如果移动头指针 由于数组已经排序 所以和会更大 因此只能移动尾指针
     *  如果小于k 此时如果移动尾指针 由于数组已经排序 所以和会更小 因此只能移动头指针
     *  如果等于k 此时应将头尾指针分别向右向左移动 并使count+1
     */
    int count = 0;
    int front = 0;
    int rear = numsSize - 1;

    qsort(nums, numsSize, sizeof(int), cmp);

    while (front < rear) {

            int tmp = nums[front] + nums[rear];
            if(tmp == k) {
                count ++;
                rear--;
                front ++;
            }
            else if(tmp < k)
                front ++;
            else
                rear --;
        }


    return count;
}

int main() {
    int nums[] = {3,1,5,1,1,1,1,1,2,2,3,2,2};
    int numsSize = sizeof(nums) / sizeof(int);
    int k = 1;
    printf("%d\n", maxOperations(nums, numsSize, k));

    return 0;
}