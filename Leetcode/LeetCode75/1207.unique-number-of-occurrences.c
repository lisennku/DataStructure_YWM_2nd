//
// Created by lisen on 24-10-21.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool uniqueOccurrences(int* arr, int arrSize) {
    int * hash1 = calloc(2001, sizeof(int));
    if(hash1 == NULL)
        exit(EXIT_FAILURE);

    for(int i = 0; i < arrSize; i++)
        hash1[arr[i] + 1000] += 1;

    int * hash2 = calloc(2001, sizeof(int));
    if(hash2 == NULL)
        exit(EXIT_FAILURE);

    for(int i = 0; i < 2001; i++) {
        if(hash1[i] != 0) {   // 排除没有出现的次数的数字影响
            if(hash2[hash1[i]] == 0) {
                hash2[hash1[i]] = 1;
            }
            else
                return false;
        }
    }
    return true;
}

int main() {
    int nums1[] = {-3,0,1,-3,1,1,1,-3,10,0};
    int nums1Size = sizeof(nums1) / sizeof(int);

    bool flag = uniqueOccurrences(nums1, nums1Size);

    printf("%d\n", flag);

    return 0;
}
