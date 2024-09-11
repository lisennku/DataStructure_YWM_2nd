//
// Created by lisen on 24-9-11.
//
// https://www.bjfuacm.com/problem/287
// 请编写一个递归的折半查找算法，查找给定有序数组中的某一元素。
// 多组数据，每组数据有三行。第一行为数组长度n，第二行为n个递增排列的数字，第三行为需要查找的数字k。当n=0时输入结束。

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool binary_search_recursive(int * arr, int low, int high, int k) {
    if(low > high )
        return false;
    int mid = (low + high) / 2;
    if(arr[mid] == k)
        return true;

    if(arr[mid] < k)
        binary_search_recursive(arr, mid+1, high, k);
    else
        binary_search_recursive(arr, low, mid-1, k);
}

void search_result_output(bool flag) {
    if(flag)
        printf("YES\n");
    else
        printf("NO\n");
}


int main() {
    int arr_len;
    int * arr;
    int target;

    while(scanf("%d", &arr_len) == 1) {
        if(arr_len == 0)
            break;
        arr = (int *) malloc(sizeof(int) * arr_len);
        if(arr == NULL)
            exit(-1);

        for(int i = 0; i < arr_len; i++)
            scanf("%d", arr+i);

        scanf("%d", &target);

        bool flag = binary_search_recursive(arr, 0, arr_len-1, target);
        search_result_output(flag);
    }

    return 0;
}