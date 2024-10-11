//
// Created by lisen on 24-10-11.
//
// https://leetcode.cn/problems/permutations-ii/description/?envType=problem-list-v2&envId=backtracking

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 41000    // 定义返回的res的第一维长度 全排列的种类是n!种 根据长度最大为8 则最多有40,320
#define HASHSIZE 20      // 定义用来对nums进行哈希的哈希表长度 因为nums中每个元素处于[-10, 10]的范围 为了处理负数将其偏移


void backtrack(
    int *state,
    int state_size,
    int *choices,
    int choices_size,
    int * is_selected,
    int ** res,
    int * return_size,
    int ** return_col_sizes
) {
    if(state_size == choices_size) {
        res[*return_size] = (int *) malloc(sizeof(int) * state_size);
        if (res[*return_size] == NULL)
            exit(EXIT_FAILURE);

        for(int i = 0; i < choices_size; i++)
            res[*return_size][i] = state[i];

        (*return_col_sizes)[*return_size] = choices_size;

        (*return_size) ++;

        return ;
    }

    // 创建哈希表
    // 该哈希表用来判断每个解中是否有重复元素 因此不需要以参数形式传入本函数
    // 每个位置对应choices的值
    int * hash_duplicated = (int *) malloc(sizeof(int) * HASHSIZE);

    if(hash_duplicated == NULL)
        exit(EXIT_FAILURE);
    memset(hash_duplicated, 0, HASHSIZE * sizeof(int));




    for(int i = 0; i < choices_size; i++) {
        // 剪枝1 是否已被选择
        // 剪枝2 是否重复
        if(is_selected[i] == 0 && hash_duplicated[choices[i]+10] == 0) {
            is_selected[i] = 1;
            hash_duplicated[choices[i]+10] = 1;
            state[state_size] = choices[i];
            backtrack(state, state_size + 1, choices, choices_size, is_selected, res, return_size, return_col_sizes);
            is_selected[i] = 0;
        }

    }
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
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

    backtrack(state, 0, nums, numsSize, is_selected, res, returnSize, returnColumnSizes);

    free(state);
    free(is_selected);

    return res;
}

int main() {
    int nums[] = {1, 1, 2};
    int numsSize = 3;
    int returnSize;
    int * returnColumnSizes;

    int ** res = permuteUnique(nums, numsSize, &returnSize, &returnColumnSizes);
    for(int i = 0; i < returnSize; i++)
        printf("%d %d %d\n", res[i][0], res[i][1], res[i][2]);

    return 0;
}
