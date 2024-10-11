//
// Created by lisen on 24-10-11.
//

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10000

void backtrack(
    int * state,
    int state_size,
    int choices,
    int k,
    int ** res,
    int * return_size,
    int ** return_col_size,
    int start
) {
    if(state_size == k) {
        res[*return_size] = (int *) malloc(sizeof(int) * k);
        if(res[*return_size] == NULL)
            exit(EXIT_FAILURE);

        for(int i = 0; i < k; i ++)
            res[*return_size][i] = state[i];

        (*return_col_size)[*return_size] = k;

        (*return_size) ++;

        return ;
    }

    for(int i = start; i <= choices; i ++ ) {
        state[state_size] = i;
        state_size ++;
        backtrack(state, state_size, choices, k, res, return_size, return_col_size, start + 1);
        state_size --;

    }
}

int** combine(int n, int k, int* returnSize, int** returnColumnSizes) {
    (*returnSize) = 0;

    *returnColumnSizes = (int *) malloc(sizeof(int) * MAXSIZE);
    if(*returnColumnSizes == NULL)
        exit(EXIT_FAILURE);

    int ** res = (int **) malloc(sizeof(int *) * MAXSIZE);
    if(res == NULL)
        exit(EXIT_FAILURE);

    int * state = (int *) malloc(sizeof(int) * k);
    if(state == NULL)
        exit(EXIT_FAILURE);

    backtrack(state, 0, n, k, res, returnSize, returnColumnSizes, 1);

    free(state);

    return res;
}

int main() {
    int n = 4;
    int k = 2;
    int returnSize;
    int * returnColSizes;

    int ** res = combine(n, k, &returnSize, &returnColSizes);

    for(int i = 0; i < returnSize; i++, printf("\n"))
        for(int j = 0; j < k; j++)
            printf("%d ", res[i][j]);

    return 0;
}
