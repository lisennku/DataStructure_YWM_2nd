//
// Created by lisen on 24-8-26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int int_compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}


int main() {
    int row, col;

    while(1) {
        scanf("%d %d", &row, &col);
        if(row == 0 && col == 0)
            break;

        int *arr = (int *) malloc(sizeof(int) * row * col);

        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                scanf("%d", arr + col * i + j);
            }
        }

        qsort(arr, row*col, sizeof(int), int_compare);
        int flag = 0;
        for(int i = 1; i < row*col; i++) {
            if(arr[i] - arr[i-1] == 0) {
                flag ++;
            }
        }
        if(flag != 0)
            printf("YES\n");
        else
            printf("NO\n");
    }


    return 0;
}