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

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            int c = board[i][j] - '1';
            int idx = (i/3) * 3 + j/3;
            if(board[i][j] == '.')
                continue;
            if(row[i][c] != 0 || col[j][c] != 0 || sub[idx][c] != 0)
                return false;
            row[i][c]++;
            col[j][c]++;
            sub[idx][c]++;
        }
    }
    return true;
}