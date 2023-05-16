#include <stdio.h>
#include <stdlib.h>

// 上个答案有问题（main.c）
// 1. 按照题目的意思，不能使用64位整型，所以不能使用long
// 2. 使用数组来存储数据的方案不够优化，完全可以一边分解 x，一边得到新的逆序值n
//    如 x = 123，分解过程为：
//       初始 n = 0
//       (1) x % 10 -> 3， n = n*10 + 3 -> n=3，  x /= 10 -> x=12
//       (2) x % 10 -> 2， n = n*10 + 2 -> n=32， x /= 10 -> x=1
//       (3) x % 10 -> 1， n = n*10 + 1 -> n=321，x /= 10 -> x=0
// 分解过程中，要注意不能超出 int 值的范围
// MySolution: https://leetcode.com/problems/reverse-integer/solutions/3531299/c-3ms-only-using-int/

// Accepted 3ms Beats 62.50%
int reverse(int x){
    int MAX_INT = 2147483647;   // 或者引入 <limits.h> 使用 INT32_MAX
    int MIN_INT = (-MAX_INT-1); // -2147483648，或者引入 <limits.h> 使用 INT32_MIN

    int positive = 1;
    if(x < 0) {
        if(x == MIN_INT) return 0;
        positive = 0; // negative
        x = -x;
    }

    int n = 0;
    while(x > 0) {
        int d = x % 10;
        x /= 10;

        // 新的n值为 n = 10*n + d;
        // 这里的核心为问题时，不能把新的 n 算出来再比较，因为新的 n 可能超过int范围，如果算出来保存在int中，值就已经不对了
        // 在计算 n 之前要判断新生成的 n 是否会超过 int 值的范围
        // 如果是正数，判断 10*n + d > MAX_INT            // 10*n + d 可能溢出
        //                  即 10*n > MAX_INT - d       // 10*n 可能溢出
        //                  即  n > (MAX_INT - d) / 10  // 无溢出
        // 如果是负数，判断 -(10*n + d) < MIN_INT         // -(10*n + d) 可能溢出
        //                  即  -10*n < MIN_INT + d     // -10*n 可能溢出
        //                  即  n > -(MIN_INT + d)/10   // -(MIN_INT + d) 可能溢出
        //                  即  n > -((MIN_INT + d)/10) // 无溢出

        if(positive) {
            if( n > (MAX_INT - d) / 10 ) return 0; // 新的n值会溢出，直接返回0
        }else{
            if( n > - ((MIN_INT + d) / 10) ) return 0; // 新的n值会溢出，直接返回0
        }
        n = 10*n + d;
    }

    return positive ? n : -n;
}

int main(){
    printf("%d\n", reverse(123));
    printf("%d\n", reverse(-123));
    printf("%d\n", reverse(120));
    printf("%d\n", reverse(2147483647)); // max int      
    printf("%d\n", reverse(-2147483648)); // min int
    return 0;
}
