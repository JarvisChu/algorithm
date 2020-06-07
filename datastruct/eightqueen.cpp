/*
 *  八皇后问题 
 *  8 * 8 的棋盘，8 个皇后，任意俩个皇后不能在同行、同列、同对角线，
 *  问：共有多少种摆放方案
 *  分析：
 *  (1) 典型的回溯法 问题
 *  (2) 8个皇后，共8行，则每一行必然有一个皇后
 *  (3) 第一个皇后 放第一行，有 8 种方法，遍历每种情况下所有可能性
 *  
 */

#include <stdio.h>
#include <stdlib.h>

#define N 8


// Place 准备摆放 第 index 个皇后， 即放到第 index 行
// column[0 ~ index) 存放了 index 之前所有皇后的位置
void Place(int index, int column[N], int *solutionCnt) {

    // 摆放完成了
    if(index == N){
        printf("Find: ");
        for(int i = 0; i < N; i ++) printf("%2d ", column[i]);
        printf("\n");
        *solutionCnt += 1;
        return;
    }

    // 摆放第 index 个皇后
    for(int i = 0; i < N; i ++ ){ // 有N个位置可以摆放
        // 判断 是否合法

        // 1. 是否有同列
        bool hasSameColumn = false;
        for(int j = 0; j < index; j++){
            if( column[j] == i ) hasSameColumn = true;
        }
        if (hasSameColumn) continue;  // 有同列，则跳过这种方案

        // 2. 判断是否有同对角线
        bool hasSameDiagonal = false;
        int r, c;

        // 判断左上斜角
        for(r = index-1, c = i -1; r >= 0 && c >= 0; r--, c--){
            if( column[r] == c ){
                hasSameDiagonal = true;
                break;
            }
        }
        if (hasSameDiagonal) continue;

        // 判断右上斜角
        for(r = index-1, c = i + 1; r >= 0 && c < N; r--, c++){
            if( column[r] == c ){
                hasSameDiagonal = true;
                break;
            }
        }
        if (hasSameDiagonal) continue;

        // 判断左下斜角
        for(r = index+1, c = i - 1; r < N  && c >= 0; r++, c--){
            if( column[r] == c ){
                hasSameDiagonal = true;
                break;
            }
        }
        if (hasSameDiagonal) continue;

         // 判断右下斜角
        for(r = index+1, c = i + 1; r < N  && c < N; r++, c++){
            if( column[r] == c ){
                hasSameDiagonal = true;
                break;
            }
        }
        if (hasSameDiagonal) continue;

        // 位置合法，摆放
        column[index] = i;

        // 继续摆放下一个皇后
        Place(index + 1, column, solutionCnt);

        // 尝试下一个位置前，先复原现场
        for(int k = index; k < N; k++) column[k] = -1;
    }
}

// 求解8皇后问题，返回方案
int EightQueen() 
{

    // 初始化棋盘，有皇后的方格值为1，无皇后的方格值为0，初始化全为 0
    int board[N][N];
    for(int i = 0; i < N; i++) for(int j=0; j<N; j++) board[i][j] = 0;

    // 每行一个皇后, column 依次记录每个皇后的所在列
    // 即 column[0] 表示： 第 0 个皇后，在第0行的第 column[0] 列
    int column[N];
    for(int i = 0; i < N; i++) column[i] = -1;

    int solutionCnt = 0;
    Place(0,column, &solutionCnt);

    printf("Total solution cnt: %d\n", solutionCnt);

    return 0;
}


int main()
{
    EightQueen();
    return 0;
}
