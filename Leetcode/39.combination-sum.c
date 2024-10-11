//
// Created by lisen on 24-10-11.
//
// https://leetcode.cn/problems/combination-sum/?envType=problem-list-v2&envId=backtracking&

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 151
#define MAXCOLSIZE 41

int cmp(const void * a, const void * b) {
    return (*(int *)a - *(int *)b);
}

void backtrack(
    int * state,                          // 存放解的数组
    int state_size,                       // 当前存放解的数组的长度
    int state_sum,                        // 当前存放解的数组的和
    int * choices,                        // 给定的数组
    int choices_size,                     // 给定数组的长度
    int target,                           // 目标值
    int ** res,                           // 主函数返回的结果
    int * return_size,                    // res的第一维长度
    int ** return_column_sizes,           // res第二维的各个子数组对应的长度组成的一维数组
    int start                             // 遍历起始点
) {
    /*
     * 参数start的作用是，避免出现重复组合
     * 以[2, 3, 6, 7]为例
     * 如果for循环每次都从0开始 会导致重复解
     * 当i=0时 出现2 2 3
     * 当i=1时 出现2 2 3
     * 导致重复
     * 画图可知 正确解中 每个元素所在candidates数组内的下标 应该以非递减的性质体现
     * 所以增加start参数 每次从当前选择的位置开始遍历 而不是每次都从头遍历
     * 从当前位置开始 是因为每个元素可以重复选择
     */
    if(state_sum == target) {
        // 记录解 并更新 return_column_sizes 和 return_size
        res[*return_size] = (int *) malloc(sizeof(int) * state_size);
        if(res[*return_size] == NULL)
            exit(EXIT_FAILURE);

        for(int i = 0; i < state_size; i ++)
            res[*return_size][i] = state[i];

        (*return_column_sizes)[*return_size] = state_size;

        (*return_size)++;

        return ;
    }

    for(int i = start; i < choices_size; i++) {
        // 剪枝 当此时的state_sum + choices[i] 大于target时 意味着后面所有的都会大于 直接退出
        if(state_sum + choices[i] > target)
            break;

        state[state_size] = choices[i];
        state_size ++;


        backtrack(state, state_size, state_sum + choices[i], choices, choices_size, target, res, return_size, return_column_sizes, i);

        state_size --;
    }
}

int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {

    // 先对candidates排序 方便剪枝
    qsort(candidates, candidatesSize, sizeof(int), cmp);

    // 初始化returnColumnSizes
    * returnColumnSizes = (int *) malloc(sizeof(int) * MAXSIZE);
    if(*returnColumnSizes == NULL)
        exit(EXIT_FAILURE);

    // 初始化returnSize
    (*returnSize) = 0;

    // 定义函数返回的二维数组
    int ** res = (int **) malloc(sizeof(int *) * MAXSIZE);
    if(res == NULL)
        exit(EXIT_FAILURE);

    // 定义存放解的数组
    int * state = (int *) malloc(sizeof(int) * MAXCOLSIZE);
    if(state == NULL)
        exit(EXIT_FAILURE);

    backtrack(state, 0, 0, candidates, candidatesSize, target, res, returnSize, returnColumnSizes, 0);

    return res;
}

int main() {
    int nums[] = {2, 3, 6, 7};
    int numsSize = 4;
    int returnSize;
    int * returnColumnSizes;
    int target = 7;

    int ** res = combinationSum(nums, numsSize, target, &returnSize, &returnColumnSizes);

    for(int i = 0; i < returnSize; i++, printf("\n"))
        for(int j = 0; j < returnColumnSizes[i]; j++)
            printf("%d ", res[i][j]);


    return 0;
}
