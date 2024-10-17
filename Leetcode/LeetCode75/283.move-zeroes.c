//
// Created by lisen on 24-10-17.
//
// https://leetcode.cn/problems/move-zeroes/description/?envType=study-plan-v2&envId=leetcode-75
// 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
// 请注意 ，必须在不复制数组的情况下原地对数组进行操作。

#include <stdio.h>

void moveZeroes(int* nums, int numsSize) {
    for(int i = numsSize-1; i >= 0; i--) {
        for(int j = 0; j < i; j++) {
            if(nums[j] != 0)
                continue;
            int tmp = nums[j];
            nums[j] = nums[j + 1];
            nums[j + 1] = tmp;
        }
    }
}

int main() {
    int nums[] = {0,1,0,3,12};
    int numsSize = sizeof(nums) / sizeof(int);
    moveZeroes(nums, numsSize);

    for(int i = 0; i < numsSize; i++)
        printf("%d", nums[i]);
}