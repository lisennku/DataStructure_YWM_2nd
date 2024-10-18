//
// Created by lisen on 24-10-17.
//
// https://leetcode.cn/problems/max-consecutive-ones-iii/description/?envType=study-plan-v2&envId=leetcode-75
// 给定一个二进制数组 nums 和一个整数 k，如果可以翻转最多 k 个 0 ，则返回 数组中连续 1 的最大个数

#include <stdio.h>

int longestOnes(int* nums, int numsSize, int k) {
    /*
     * 算法思路
     *  初始滑动窗口 左端从0位开始 右端在第四个零的位置的前一位 记录此时的左右端之差 加1 记为当前的连续1的长度
     *  然后向右滑动窗口 保证滑动后仍有三个零
     * 该滑动窗口的大小不是固定的 而是根据容纳的0 来进行扩大或者缩小
     */
    int i = 0;
    int j = 0;
    int zeros = 0;

    int len = 0;
    int max_len = 0;

    while(j < numsSize) {
        if(zeros == k) {
            len = j - i + 1;
            if(max_len < len)
                max_len = len;
        }

    }
}

int main() {
    int nums[] = {1,1,1,0,0,0,1,1,1,1,0};
    int numsSize = sizeof(nums) / sizeof(int);
    int k = 2;

    printf("%d\n", longestOnes(nums, numsSize, k));

    return 0;
}