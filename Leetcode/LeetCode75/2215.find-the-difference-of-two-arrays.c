//
// Created by lisen on 24-10-21.
//
#include <stdio.h>
#include <stdlib.h>

int** findDifference(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize, int** returnColumnSizes) {
    *returnSize = 2;

    *returnColumnSizes = calloc(*returnSize, sizeof(int));
    if(*returnColumnSizes == NULL)
        exit(EXIT_FAILURE);

    int ** res = calloc(*returnSize, sizeof(int *));
    if(res == NULL)
        exit(EXIT_FAILURE);

    res[0] = (int *) calloc(nums1Size, sizeof(int));
    res[1] = (int *) calloc(nums2Size, sizeof(int));
    if(res[0] == NULL || res[1] == NULL)
        exit(EXIT_FAILURE);

    int hash1[2001] = {0};  // 哈希表 使用偏移量1000
    int hash2[2001] = {0};  // 哈希表 使用偏移量1000

    // 初始化哈希表
    for(int i = 0; i < nums1Size; i++)
        if(hash1[nums1[i] + 1000] == 0)
            hash1[nums1[i] + 1000] = 1;
    for(int i = 0; i < nums2Size; i++)
        if(hash2[nums2[i] + 1000] == 0)
            hash2[nums2[i] + 1000] = 1;

    int l1 = 0, l2 = 0;

    // 判断nums1中不在nums2中 且不重复元素
    for(int i = 0; i < nums1Size; i++) {
        if(hash2[nums1[i] + 1000] == 0) {
            res[0][l1++] = nums1[i];
            hash2[nums1[i] + 1000] = 1;
        }
    }
    for(int i = 0; i < nums2Size; i++) {
        if(hash1[nums2[i] + 1000] == 0) {
            res[1][l2++] = nums2[i];
            hash1[nums2[i] + 1000] = 1;
        }
    }

    (*returnColumnSizes)[0] = l1;
    (*returnColumnSizes)[1] = l2;
    return res;
}

int main() {
    int nums1[] = {1,2,3,3};
    int nums1Size = sizeof(nums1) / sizeof(int);
    int nums2[] = {1,1,2,2};
    int nums2Size = sizeof(nums1) / sizeof(int);

    int returnSize;
    int * returnColumnSize;

    int ** res = findDifference(nums1, nums1Size, nums2, nums2Size, &returnSize, &returnColumnSize);

    for(int i = 0; i < returnSize; i++, printf("\n"))
        for(int j = 0; j < returnColumnSize[i]; j++)
            printf("%d ", res[i][j]);
}
