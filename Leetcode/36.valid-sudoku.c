//
// Created by lisen on 24-10-9.
//
// 参考该解题https://leetcode.cn/problems/valid-sudoku/solutions/1002240/suan-fa-xiao-ai-san-ge-jian-dan-ti-ding-fmori

// 创建三个哈希表 分别表示行/列/九宫格
//      哈希表格式为9*9
#include <stdbool.h>


bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    int row[9][9] = {0};
    int col[9][9] = {0};
    int sub[9][9] = {0};

}