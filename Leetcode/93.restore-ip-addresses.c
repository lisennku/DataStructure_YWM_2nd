//
// Created by lisen on 24-10-15.
//
// https://leetcode.cn/problems/restore-ip-addresses/description/?envType=problem-list-v2&envId=backtracking

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define IP_SEG 4

void backtrack(
    int * state,
    int state_size,
    int start,                   // 每次递归时循环字符串的起始位置
    char * s,
    char **ans,
    int * ans_len
) {
    int s_len = strlen(s);
    if(state_size == IP_SEG ) {  // 如果状态数组的长度和IP段数相同
        if(start == s_len) {     // 如果start等于字符串长度 说明此时状态数组里的内容合法
            ans[*ans_len] = (char *) malloc(sizeof(char) * (s_len + 4)) ;  // IP地址数组的长度应是字符串长度加上3个点号再加上\0
            int position = 0;
            for(int i = 0; i < state_size; i++) {
                // printf("%d", state[i]);
                int number = state[i];
                if (number >= 100) {
                    ans[*ans_len][position++] = number / 100 + '0';
                }
                if (number >= 10) {
                    ans[*ans_len][position++] = number % 100 / 10 + '0';
                }
                ans[*ans_len][position++] = number % 10 + '0';

                if(i != state_size-1) {
                    // printf(" ");
                    ans[*ans_len][position++] = '.';
                }

                ans[*ans_len][position] = '\0';
            }
            (*ans_len)++;
        }
        else {                   // 如果状态数组的长度和IP段数相同但是仍未遍历完数组 表示此时内容不合法 需要回溯
            return ;
        }
    }

    if(start == s_len)           // 如果提前遍历结束字符串 需要回溯
        return ;

    if(s[start] == '0') {        // 对于字符0 由于IP地址不允许带有前导0 说明0一定是单独的IP段
        state[state_size] = 0;
        backtrack(state, state_size+1, start+1, s, ans, ans_len);
    }
    // 使用整型数字记录记录从开头到结束遍历的值
    int value = 0;
    for(int i = start; i < s_len; i++) {
        value = value * 10 + (s[i] - '0');
        if(value > 0 && value <= 255) {
            state[state_size] = value;
            state_size ++;
            backtrack(state, state_size, i+1, s, ans, ans_len);
            state_size --;
        }
        else
            return ;
    }
}

char** restoreIpAddresses(char* s, int* returnSize) {
    char ** ans = (char **) malloc(sizeof(char *) * 1000);
    int ans_len = 0;
    int state[IP_SEG];
    int state_size = 0;

    backtrack(state, state_size, 0, s, ans, &ans_len);
    *returnSize = ans_len;
    return ans;
}

int main() {
    char s[] = "101023";
    int len;
    char ** res = restoreIpAddresses(s, &len);
    for(int i = 0; i < len; i++)
        printf("%s\n", res[i]);
}