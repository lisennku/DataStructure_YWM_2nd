//
// Created by lisen on 24-10-17.
//
// https://leetcode.cn/problems/container-with-most-water/description/?envType=study-plan-v2&envId=leetcode-75
// 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
// 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
// 返回容器可以储存的最大水量。

#include <stdio.h>

int min(int a, int b) {
    return a <= b ? a : b;
}
/*
 * 双循环超时
int maxArea(int* height, int heightSize) {
    int max_area = -1;
    for(int i = 0; i < heightSize; i++)
        for(int j = 1; j < heightSize; j++) {
            int area = min(height[i], height[j]) * (j - i);
            if(area > max_area)
                max_area = area;
        }
    return max_area;
}
*/

int maxArea(int* height, int heightSize) {
    // 面积等于 min(h1, h2) * (h2 - h1)
    // 指针指向数组两端
    // 如果移动数值较大的 那么面积会变小
    // 因此只能移动数值较小的
    int max_area = -1;
    int front = 0;
    int rear = heightSize - 1;
    while(front < rear) {
        int area = min(height[front], height[rear]) * (rear - front);
        if(area > max_area)
            max_area = area;
        if(height[front] < height[rear])
            front ++;
        else
            rear --;
    }
    return max_area;
}


int main() {
    int height[] = {1,8,6,2,5,4,8,3,7};
    int heightSize = sizeof(height) / sizeof(int);
    printf("%d\n", maxArea(height, heightSize));

    return 0;
}