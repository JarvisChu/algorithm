/*
https://leetcode.com/problems/reverse-integer/


7. Reverse Integer

Given a 32-bit signed integer, reverse digits of an integer.

Example 1:
    Input: 123
    Output: 321
Example 2:
    Input: -123
    Output: -321
Example 3:
    Input: 120
    Output: 21
Note:
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−2^31,  2^31 − 1]. 
For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 思路
// 1. 使用long 来做中间过程的处理，防止溢出
// 2. 除去原数字末尾的所有0后，再重新组合
int reverse(int x){
    int digits[20] = {0};             // 存放每一位数字，x = 123, digits=[3,2,1]; x = 120,  digits=[0,2,1]
    int len = 0;                      // 存放位数
    int isNegtive = (x < 0) ? 1:0;    // 是否是负数

    long num = x;                     // 使用long存储，防止溢出
    if (num < 0) num = -num;          // 注意，这里一定不能直接用 -x，因为可能溢出
 
    while(num > 0 ) {
        int digit = num % 10;
        digits[len++] = digit;
        num /= 10;
    }

    // 去除digits开头的0， 如 x = 1200，digits=[0,0,2,1]
    int firstNonZero = 0;
    for(firstNonZero = 0; firstNonZero < len; firstNonZero++) {
        if ( digits[firstNonZero] != 0) break;
    }

    long ret = 0; // 存放逆序后的数值，
                  // 如 x = 123, digits=[3,2,1]， ret = (1+10*0) + (2+10*1) + (3+10*2)
    for(int i = firstNonZero; i < len; i++) {
        //printf("i=%d digits[i]=%d, ret = %ld\n", i, digits[i], ret);
        ret = ret * 10 + digits[i];
    }

    if (isNegtive)  ret = -ret;

    // 判断溢出
    if( ret > INT32_MAX || ret < INT32_MIN) return 0;

    return (int)ret;
}


int main() {

    printf("%d\n", reverse(123));
    printf("%d\n", reverse(-123));
    printf("%d\n", reverse(120));
    printf("%d\n", reverse(INT32_MAX)); // #define INT32_MAX        2147483647
    printf("%d\n", reverse(INT32_MIN)); // max int


    return 0;
}