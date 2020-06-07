/*
 * 汉诺塔问题，展示递归的用法     
 */

#include <stdio.h>
#include <stdlib.h>


void move(char from, char to){
    printf("move %c -> %c\n", from, to);
}

// 汉诺塔问题，n个盘子，借助 b，从 a 挪到 c
void hanoi(int n, char a, char b, char c)
{
    // 1 个盘子，直接挪到c
    if( n == 1) {
        move(a,c);
    }else{
        hanoi(n-1, a, c, b); // 现将 n-1 个盘子，先挪到b
        move(a,c);           // 剩下一个盘子，直接挪到c
        hanoi(n-1, b, a, c); // 再将 n-1 个盘子，从b挪到c
    }
    return;
}

int main()
{
    hanoi(4,'a', 'b', 'c');
    return 0;
}
