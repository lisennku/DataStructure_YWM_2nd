//
// Created by lisen on 24-10-11.
//

// https://leetcode.cn/problems/permutations/description/?envType=problem-list-v2&envId=array

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 800   // 6! = 720

void backtrack(
    int * state, int state_size, int * is_selected,
    int * choices, int choices_size, int * return_size, int ** res, int ** return_column_sizes) {
    /*
     * @params
     *  state
     *      存放当前解的数组
     *  state_size
     *      存放当前解的数组的长度
     *  is_selected
     *      表示对应choices数组中的各位置的元素是否被选中的数组
     *      需要初始化为0 表示未被选中 1表示选中
     *  choices
     *      原始数组 不应该被改变
     *  choices_size
     *      原始数组的长度 不应该被改变
     *  return_size
     *      permute返回的结果res的长度
     *  res
     *      permute返回的结果
     *      二维数组 第一维已在permute函数中动态分配内存
     *  return_column_sizes
     *      permute返回的结果res中 对应各个位置的子数组的长度 的一维数组
     */

    /*
     * @idea
     *  采用回溯算法
     *  尝试将choices里的元素加入到state数组中 但是要进行剪枝 也即判断该元素是否在之前已被选择
     *      如果可以选择 将该元素放入state中 同步将is_selected对应位置置为1
     *  回退 将is_selected置为0
     *  如果choices的长度和state长度相同 说明找到了解 将解加入到返回的结果中
     */

    if(state_size == choices_size) {
        // 为二维数组中 *return_size位置进行动态分配内存
        res[*return_size] = (int *) malloc(sizeof(int) * choices_size);
        // 将此时存有解的state数组数据复制到res[*return_size]
        for(int i = 0; i < choices_size; i++)
            res[*return_size][i] = state[i];
        // return_column_sizes数组添加元素
        (*return_column_sizes)[*return_size] = choices_size;
        // res长度+1
        (*return_size) ++;
    }

    // 尝试和回退部分
    for(int i = 0; i < choices_size; i++) {
        // 判断该元素没有选择
        if(is_selected[i] == 0) {
            // 将该元素放到state里 并更新is_selected
            state[state_size] = choices[i];
            is_selected[i] = 1;
            // 继续回溯
            backtrack(state, state_size+1, is_selected, choices, choices_size, return_size, res, return_column_sizes);
            // 回退
            is_selected[i] = 0;
        }
    }
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int ** res = (int **) malloc(sizeof(int *) * MAXSIZE);
    if(res == NULL)
        exit(EXIT_FAILURE);

    int * state = (int *) malloc(sizeof(int) * numsSize);
    if(state == NULL)
        exit(EXIT_FAILURE);

    int * is_selected = (int *) malloc(sizeof(int) * numsSize);
    if(is_selected == NULL)
        exit(EXIT_FAILURE);
    for(int i = 0; i < numsSize; i++)
        is_selected[i] = 0;

    *returnColumnSizes = (int *) malloc(sizeof(int) * MAXSIZE);
    if(*returnColumnSizes == NULL)
        exit(EXIT_FAILURE);

    (*returnSize) = 0;

    backtrack(state, 0, is_selected, nums, numsSize, returnSize, res, returnColumnSizes);

    free(state);
    free(is_selected);

    return res;
}

int main() {
    int nums[] = {1, 2, 3};
    int numsSize = 3;
    int returnSize;
    int * returnColumnSizes;

    int ** res = permute(nums, numsSize, &returnSize, &returnColumnSizes);
    for(int i = 0; i < returnSize; i++)
        printf("%d %d %d\n", res[i][0], res[i][1], res[i][2]);
}