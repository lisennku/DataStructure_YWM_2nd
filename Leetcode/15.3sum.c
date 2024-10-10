//
// Created by lisen on 24-10-10.
//
// https://leetcode.cn/problems/3sum/description/?envType=problem-list-v2&envId=array

#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 1000000

int cmpFunc(const void * a, const void * b) {
    return (*(int *)a - *(int *)b);
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    // returnSize 是返回的二维数组的长度 意思是第一维数组的长度 整数
    // returnColumnSizes 是返回的二维数组第二维数组的长度(其实就是3) 是一维数组 长度和returnSize一致
    // 先排序
    qsort(nums, numsSize, sizeof(int), cmpFunc);

    // 声明返回的二维数组
    // 此处是声明了第一维 第二维的malloc在具体函数内部声明
    int ** res = (int **) malloc(sizeof(int *) * MAXSIZE);
    if (res == NULL)
        exit(EXIT_FAILURE);

    // 初始化returnSize为0
    // returnSize = (int *) malloc(sizeof(int));
    (*returnSize) = 0;

    // 初始化returnColumnSize
    * returnColumnSizes = (int *) malloc(sizeof(int) * MAXSIZE);
    if(returnColumnSizes == NULL)
        exit(EXIT_FAILURE);

    // 特殊判断条件 当长度numsSize 小于 3 返回空
    if (numsSize < 3)
        return NULL;

    // 算法以每次遍历的位置为依据
    // 从其后一个位置作为左指针 数组结尾作为右指针 从两边逼近
    // 因此需要注意以下两部分逻辑
    // 1. 外部循环
    //      需要注意本次循环的数值 是否和上一次相等 如果相等则应该跳过
    // 2. 内层循环
    //      1) 左右指针相等时结束循环
    //      2) 判断当前遍历的位置 与左右指针指向的值的和
    //          - 如果等于0 记录位置
    //              - 然后同时移动左右指针
    //                  - 左移时要注意是否和之前指向的值相同 相同应该跳过
    //                  - 右移时要注意是否和之前指向的值相同 相同应该跳过
    //          - 如果大于0 说明右指针应该左移
    //          - 如果小于0 说明左指针应该右移
    for(int i = 0; i < numsSize; i++) {
        // C语言此处不应该直接返回结果 因为可能存在i=0时就是大于0的数字 此时如果直接返回res 会有问题
        // // 如果此时i位置的数字大于0 直接返回结果 因为数组已经正序排序 此时定不存在符合要求的结果
        // if(nums[i] > 0)
        //     return res;

        // 判断当前遍历值和上一次的值是否相同 相同则跳过 需要注意的是i = 0时不应该做该判断 因此要限制i的值
        if(i > 0 && nums[i] == nums[i-1])
            continue;

        int lptr = i + 1;
        int rptr = numsSize - 1;
        while(lptr < rptr) {
            int tmp_sum = nums[i] + nums[lptr] + nums[rptr];
            if (tmp_sum == 0) {
                // 此时符合要求 应该将i/lptr/rptr作为子数组放入返回值内
                // returnSize作为下标
                res[*returnSize] = (int *) malloc(sizeof(int) * 3);
                if(res[*returnSize] == NULL)
                    exit(EXIT_FAILURE);
                res[*returnSize][0] = nums[i];
                res[*returnSize][1] = nums[lptr];
                res[*returnSize][2] = nums[rptr];
                // 两个引用传递的参数要处理
                (*returnColumnSizes)[*returnSize] = 3; // 必须在 (*returnSize) ++ 前处理
                (*returnSize) ++;

                // 左右指针移动
                while(lptr < rptr && nums[lptr] == nums[lptr+1])
                    lptr ++;
                while(lptr < rptr && nums[rptr] == nums[rptr-1])
                    rptr --;
                // 跳出循环时 左右指针指向的位置其实是最后一个重复值的下标 因此仍需要自增/自减
                lptr ++;
                rptr --;
            }
            else if (tmp_sum > 0)
                rptr --;
            else
                lptr ++;
        }
    }

    return res;
}

int main() {
    int nums[] = {-1,0,1,2,-1,-4};
    int numsSize = 6;
    int returnSize;
    int * returnColumnSizes;

    int ** res = threeSum(nums, numsSize, &returnSize, &returnColumnSizes);
    for(int i = 0; i < returnSize; i++) {
        if(i != 0)
            printf("\n");
        for(int j = 0; j < 3; j++) {
            printf("%d ", res[i][j]);
        }
    }

}