//
// Created by lisen on 24-11-5.
//
// https://www.dotcpp.com/oj/problem1680.html

#include <stdio.h>
#include <stdlib.h>

#define STACK 1000

int base_convert(int dec, int base) {
    int stack[STACK];
    int top = 0;

    int remainder = dec % base;
    stack[top++] = remainder;
    dec = dec / base;

    while(dec != 0) {
        stack[top++] = dec % base;
        dec = dec / base;
    }

    int res = 0;
    while(top > 0)
        res = res * 10 + stack[--top];

    return res;

}

int main() {
    int num;
    while(scanf("%d", &num) != EOF)
        printf("%d\n", base_convert(num, 8));
}
