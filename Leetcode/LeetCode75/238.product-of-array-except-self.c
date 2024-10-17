//
// Created by lisen on 24-10-16.
//
// https://leetcode.cn/problems/product-of-array-except-self/description/?envType=study-plan-v2&envId=leetcode-75
// 给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积 。
// 题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。
// 请 不要使用除法，且在 O(n) 时间复杂度内完成此题。

/*
 * 使用前缀积和后缀积
 */

#include <stdio.h>
#include <stdlib.h>


int * prefix_product(int * nums, int numSize, int * pre_len) {
    int * pre = (int *) calloc(numSize, sizeof(int));
    if(pre == NULL)
        exit(EXIT_FAILURE);

    pre[0] = nums[0];

    int i = 1;
    while(i < numSize) {
        pre[i] = nums[i] * pre[i-1];
        i++;
    }

    *pre_len = numSize;
    return pre;
}
int * postfix_product(int * nums, int numSize, int * pst_len) {
    int * post = (int *) calloc(numSize, sizeof(int));
    if(post == NULL)
        exit(EXIT_FAILURE);

    post[numSize-1] = nums[numSize-1];

    int i = numSize - 2;
    while(i >= 0) {
        post[i] = nums[i] * post[i+1];
        i--;
    }

    *pst_len = numSize;
    return post;
}

int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int * res = (int *) calloc(numsSize, sizeof(int));
    if(res == NULL)
        exit(EXIT_FAILURE);

    int pre_len;
    int pst_len;
    int * pre = prefix_product(nums, numsSize, &pre_len);
    int * pst = postfix_product(nums, numsSize, &pst_len);

    for(int i = 0; i < numsSize; i++) {
        int pre_value = (i == 0 ? 1 : pre[i-1]);
        int pst_value = (i == numsSize-1 ? 1 : pst[i+1]);

        res[i] = pre_value * pst_value;
    }
    *returnSize = numsSize;
    return res;
}

int main() {
    int nums[] = {2, 3, 4, 5, 6};
    int numSize = 5;
    int returnSize;
    // int pre_len;
    // int pst_len;
    //
    // int * pre = prefix_product(nums, numSize, &pre_len);
    // int * pst = postfix_product(nums, numSize, &pst_len);
    //
    // for(int i = 0; i < pre_len; i++)
    //     printf("%d ", pre[i]);
    // printf("\n");
    // for(int i = 0; i < pst_len; i++)
    //     printf("%d ", pst[i]);

    int * res = productExceptSelf(nums, numSize, &returnSize);
    for(int i = 0; i < numSize; i++)
        printf("%d ", res[i]);

    putchar('\n');

    return 0;
}