//
// Created by lisen on 24-10-16.
//
// https://leetcode.cn/problems/increasing-triplet-subsequence/description/?envType=study-plan-v2&envId=leetcode-75
// 给你一个整数数组 nums ，判断这个数组中是否存在长度为 3 的递增子序列。
//
// 如果存在这样的三元组下标 (i, j, k) 且满足 i < j < k ，使得 nums[i] < nums[j] < nums[k] ，返回 true ；否则，返回 false 。

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>


/*
 * 回溯算法会在用例76时超时
 */

// void backtrack(
//     int * state,
//     int state_size,
//     bool * flag,
//     int * nums,
//     int numsSize,
//     int start
// ) {
//     if(*flag == false) {
//         if(state_size == 3) {
//             *flag = true;
//             return ;
//         }
//
//         for(int i = start; i < numsSize; i++) {
//             if(state_size != 0 && nums[i] <= state[state_size-1])
//                 continue;
//
//             state[state_size] = nums[i];
//             state_size ++;
//             backtrack(state, state_size, flag, nums, numsSize, i + 1);
//             if(*flag == false)
//                 state_size--;
//             else
//                 return ;
//         }
//
//
//     }
//
// }
//
// bool increasingTriplet(int* nums, int numsSize) {
//     bool flag = false;
//     int state[3];
//     backtrack(state, 0, &flag, nums, numsSize, 0);
//     return flag;
// }

bool increasingTriplet(int* nums, int numsSize) {
    if(numsSize < 3)
        return false;

    int first = nums[0];
    int second = INT_MAX;

    for(int i = 1; i < numsSize; i++) {
        int num = nums[i];
        if(num > second)
            return true;
        if(num > first)
            second = num;
        else
            first = num;
    }

    return false;
}


int main() {
    // int nums[] = {2, 10, 9, 3, 7, 4, 6};
    // int nums[] = {5, 4, 3, 2, 1};
    // int nums[] = {1, 2, 3, 4, 5};
    int nums[] = {20,100,10,12,5,13};
    int numsSize = sizeof(nums) / sizeof(int);

    bool b = increasingTriplet(nums, numsSize);
    printf("%d\n", b);

    return 0;
}