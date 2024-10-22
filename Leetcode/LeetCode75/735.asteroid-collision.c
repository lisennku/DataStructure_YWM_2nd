//
// Created by lisen on 24-10-22.
//
#include <stdio.h>
#include <stdlib.h>

int get_digit_sign(int num) {
    return num > 0 ? 1 : -1;
}

int* asteroidCollision(int* asteroids, int asteroidsSize, int* returnSize) {

    int * arr = calloc(asteroidsSize, sizeof(int));
    if(arr == NULL)
        exit(EXIT_FAILURE);

    int top = 0;
    for(int i = 0; i < asteroidsSize; i++) {
        // 依次入栈
        arr[top++] = asteroids[i];
        // top>=2时就有可能发生碰撞 且此时 top-1 < 0 top-2 > 0
        while(top >= 2 && arr[top-1] < 0 && arr[top-2] > 0) {
            int collision = arr[top-1] + arr[top-2];
            if(collision > 0)
                top--;
            else if(collision < 0) {
                arr[top-2] = arr[top-1];
                top--;
            }
            else
                top -= 2;
        }
    }

    *returnSize = top;
    return arr;
}

int main() {
    int asteroids[] = {10,2,-5};
    int asteroidsSize = sizeof(asteroids) / sizeof(int);
    int returnSize;

    int * res = asteroidCollision(asteroids, asteroidsSize, &returnSize);
    printf("%d\n", returnSize);
    for(int i = 0; i < returnSize; i++)
        printf("%d ", res[i]);
    putchar('\n');

    return 0;
}
