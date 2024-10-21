//
// Created by lisen on 24-10-21.
//
#include <stdlib.h>
#include <stdio.h>

int pivotIndex(int* nums, int numsSize) {

    int * prefix_sum = calloc(numsSize, sizeof(int));
    int * postfix_sum = calloc(numsSize, sizeof(int));

    int s = 1;
    int e = numsSize - 2;

    prefix_sum[0] = nums[0];
    postfix_sum[numsSize-1] = nums[numsSize-1];

    while(s < numsSize) {
        prefix_sum[s] = prefix_sum[s-1] + nums[s];
        s++;
    }

    while(e >= 0) {
        postfix_sum[e] = postfix_sum[e+1] + nums[e];
        e--;
    }

    for(int i = 0; i < numsSize; i++)
        printf("%d ", prefix_sum[i]);
    putchar('\n');
    for(int i = 0; i < numsSize; i++)
        printf("%d ", postfix_sum[i]);
    putchar('\n');

    for(int i = 0; i < numsSize; i++)
        if(prefix_sum[i] == postfix_sum[i])
            return i;
    return -1;
}

int main() {
    int nums[] = {-1,-1,-1,-1,0,0};
    int numsSize = sizeof(nums) / sizeof(int);

    int i = pivotIndex(nums, numsSize);

    printf("%d\n", i);
}
