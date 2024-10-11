//
// Created by lisen on 24-10-11.
//
// https://leetcode.cn/problems/combination-sum-ii/?envType=problem-list-v2&envId=backtracking

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
     * 区别于39题 该题要求每个元素只能选择一次 且candidates包含重复元素
     * 修改点1
     *  因为candidates会被排序 所以在for循环中要进行判断 判断当前元素和candidates中的上一个元素是否相同 相同直接continue
     *      要注意此时的位置i要大于开始的位置start
     * 修改点2
     *  因为每个元素只能选择一次 所以下次循环不能从start本身开始 而是它下一位置
     */
    if(state_sum == target) {
        // 将state添加到res 并更新return_column_sizes和return_size
        res[*return_size] = (int *) malloc(sizeof(int) * state_size);
        if (res[*return_size] == NULL)
            exit(EXIT_FAILURE);

        for(int i = 0; i < state_size; i++)
            res[*return_size][i] = state[i];

        (*return_column_sizes)[*return_size] = state_size;

        (*return_size) ++;

        return ;
    }
    for(int i = start; i < choices_size; i++) {
        // 剪枝1 排序后 当前state的和 加上被选元素 的和 大于 target 直接结束循环
        // 因为后续每个元素和state的和的结果都会大于target
        if((state_sum + choices[i]) > target)
            break;

        if(i > start && choices[i] == choices[i-1])
            continue;

        state[state_size] = choices[i];
        state_size ++;


        backtrack(state, state_size, state_sum + choices[i], choices, choices_size, target, res, return_size, return_column_sizes, i+1);

        state_size --;

    }
}

int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
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
    int nums[] = {10, 1, 2, 7, 6, 1, 5};
    int numsSize = 7;
    int returnSize;
    int * returnColumnSizes;
    int target = 8;

    int ** res = combinationSum2(nums, numsSize, target, &returnSize, &returnColumnSizes);

    for(int i = 0; i < returnSize; i++, printf("\n"))
        for(int j = 0; j < returnColumnSizes[i]; j++)
            printf("%d ", res[i][j]);

    return 0;
}
