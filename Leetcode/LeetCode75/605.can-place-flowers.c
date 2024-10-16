//
// Created by lisen on 24-10-16.
//
// https://leetcode.cn/problems/can-place-flowers/?envType=study-plan-v2&envId=leetcode-75
// 假设有一个很长的花坛，一部分地块种植了花，另一部分却没有。可是，花不能种植在相邻的地块上，它们会争夺水源，两者都会死去。
// 给你一个整数数组 flowerbed 表示花坛，由若干 0 和 1 组成，其中 0 表示没种植花，1 表示种植了花。
// 另有一个数 n ，能否在不打破种植规则的情况下种入 n 朵花？能则返回 true ，不能则返回 false

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n) {
    /*
     * 从头遍历数组 查找可种植的位置
     *  如果当前位置是0 那么需要判断下一位是否是0
     *      如果下一位是0 说明该位置可以种植 可种植数-1 将位置挪到+2 的位置 因为+1位置一定不可种
     *          此处有个边界判断 如果当前位置是数组末尾 直接种植
     *      如果下一位是1 说明该位置不可以种植 将位置挪到+3 因为当前位置的下一位是1 说明下一位的下一位一定不可种 所以要+3
     *  如果当前位置是1 那么直接加2
     *  遍历的条件应是位置的下标小于数组长度 且 可种植数大于0
     * 注意 之所以没判断前一位 是因为给定数组保证了合法性
     */
    int pos = 0;
    while (pos < flowerbedSize && n > 0) {
        if(flowerbed[pos] == 1)
            pos += 2;
        else {
            if(pos == flowerbedSize - 1 || flowerbed[pos+1] == 0 ) { // 找到可种植的位置
                n --;
                pos += 2;
            }
            else {
                pos += 3;
            }
        }
    }
    return n <= 0;
}

int main() {
    int flowerbed[] = {1,0,0,0,1,0,0};
    int flowerbedSize = sizeof(flowerbed) / sizeof(int);
    int n = 2;

    bool flag = canPlaceFlowers(flowerbed, flowerbedSize, n);
    printf("%d", flag);

    return 0;
}