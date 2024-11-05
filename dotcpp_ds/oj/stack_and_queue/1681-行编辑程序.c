//
// Created by lisen on 24-11-5.
//
// https://www.dotcpp.com/oj/problem1681.html

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 201

void handle_line(char * line) {
    char stack[MAXSIZE];
    int top = 0;
    for(int i = 0; i < strlen(line); i++) {
        if (line[i] == '@')
            top = 0;
        else if(line[i] == '#') {
            if(top != 0)
                top -- ;
        }
        else {
            stack[top++] = line[i];
        }
    }
    for(int i = 0; i < top; i++)
        printf("%c", stack[i]);
    // putchar('\n');
}

int main() {
    char line[MAXSIZE];
    while(fgets(line, MAXSIZE-1, stdin) != NULL) {
        handle_line(line);
    }
}
