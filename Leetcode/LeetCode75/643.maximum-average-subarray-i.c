//
// Created by lisen on 24-10-17.
//
// https://leetcode.cn/problems/maximum-average-subarray-i/description/?envType=study-plan-v2&envId=leetcode-75
// 给你一个由 n 个元素组成的整数数组 nums 和一个整数 k
// 请你找出平均数最大且 长度为 k 的连续子数组，并输出该最大平均数
// 任何误差小于 10-5 的答案都将被视为正确答案


#include <stdio.h>



double findMaxAverage(int* nums, int numsSize, int k) {
    int sum = 0;
    for(int i = 0; i < k; i++)
        sum += nums[i];
    double max_sum = sum;
    for(int i = 1; i <= numsSize - k; i++) {
        sum = sum - nums[i-1] + nums[i + k - 1];
        if(max_sum < sum)
            max_sum = sum;
    }
    return max_sum/k;
}

int main() {
    int nums[] = {1,12,-5,-6,50,3};
    int numsSize = sizeof(nums) / sizeof(int);
    // int nums[] = {-1};
    // int numsSize = sizeof(nums) / sizeof(int);
    int k = 4;

    printf("%lf\n", findMaxAverage(nums, numsSize, k));
}