//
// Created by lisen on 24-10-16.
//
// https://leetcode.cn/problems/kids-with-the-greatest-number-of-candies/description/?envType=study-plan-v2&envId=leetcode-75
// 有 n 个有糖果的孩子。给你一个数组 candies，其中 candies[i] 代表第 i 个孩子拥有的糖果数目，和一个整数 extraCandies
// 表示你所有的额外糖果的数量。
// 返回一个长度为 n 的布尔数组 result，如果把所有的 extraCandies 给第 i 个孩子之后，他会拥有所有孩子中 最多 的糖果，那么 result[i] 为 true，否则为 false。
// 注意，允许有多个孩子同时拥有 最多 的糖果数目。

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool* kidsWithCandies(int* candies, int candiesSize, int extraCandies, int* returnSize) {
    /*
     * 普通算法可以采取循环 每次循环给数组中一个元素加上extraCandies 然后判断该元素加上后是否是整个数组的最大值 但是时间负责度是O(n^2)
     * 另外的算法可以如下思考
     *  如果希望加上extraCandies后 该元素是数组中最大的 可以先行计算 原candies数组中 每个元素和最大元素之间的差值(元素-最大值)
     *  这样如果差异加上extraCandies后可以大于等于0 那么就说明该元素符合要求
     * 如此操作时间复杂度是O(n)
     */
    bool * res = (bool *) calloc(candiesSize, sizeof(bool));
    if(res == NULL)
        exit(EXIT_FAILURE);

    int max_value = -1;
    for(int i = 0; i < candiesSize; i++)
        if(max_value < candies[i])
            max_value = candies[i];

    int gap[candiesSize];

    for(int i = 0; i < candiesSize; i++) {
        gap[i] = candies[i] - max_value;
        if(gap[i] + extraCandies >= 0)
            res[i] = true;
        else
            res[i] = false;
    }

    *returnSize = candiesSize;
    return res;
}

int main() {
    int candies[] = {2, 3, 5, 1, 3};
    int candiesSize = sizeof(candies) / sizeof(int);
    int extraCandies = 3;
    int returnSize;

    bool * res = kidsWithCandies(candies, candiesSize, extraCandies, &returnSize);
    for(int i = 0; i < returnSize; i++)
        printf("%d ", res[i]);
}