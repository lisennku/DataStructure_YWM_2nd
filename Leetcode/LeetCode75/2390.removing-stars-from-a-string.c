//
// Created by lisen on 24-10-22.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeStars(char* s) {
    char * stack = calloc(strlen(s) + 1, sizeof(char));
    int top = 0;

    int pos = 0;
    while (pos < strlen(s)) {
        if(s[pos] == '*')
            top--;
        else {
            stack[top++] = s[pos];
        }
        pos++;
    }
    if(top == 0)
        return "";
    stack[top] = '\0';
    return stack;
}

int main() {
    char s[] = "leet**cod*e";
    char * res = removeStars(s);
    printf("%s\n", res);

    return 0;
}
