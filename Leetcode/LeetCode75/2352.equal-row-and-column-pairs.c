//
// Created by lisen on 24-10-22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 3

int equalPairs(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    int res = 0;
    int tmp[n];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            tmp[j] = grid[j][i];
        for(int j = 0; j < n; j++)
            res += (memcmp(tmp, grid[j], n * sizeof(int)) == 0);
    }
    return res;
}

int main() {

    int tmp[SIZE][SIZE] = {
        {3,2,1},
        {1,7,6},
        {2,7,7}
    };

    int ** grid = malloc(sizeof(int *) * SIZE);
    for(int i = 0; i < SIZE; i++) {
        grid[i] = malloc(sizeof(int) * SIZE);
        for(int j = 0; j < SIZE; j++)
            grid[i][j] = tmp[i][j];
    }


    int gridSize = SIZE;
    int gridColSize[SIZE] = {SIZE, SIZE, SIZE};

    int cnt = equalPairs(grid, gridSize, gridColSize);
    printf("%d\n", cnt);

    return 0;
}
