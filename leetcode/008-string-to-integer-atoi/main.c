/*
https://leetcode.com/problems/string-to-integer-atoi/

8. String to Integer (atoi)

Implement atoi which converts a string to an integer.

The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. 
Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned.

Note:
Only the space character ' ' is considered as whitespace character.
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is returned.

Example 1:
    Input: "42"
    Output: 42

Example 2:
    Input: "   -42"
    Output: -42
Explanation: The first non-whitespace character is '-', which is the minus sign.
             Then take as many numerical digits as possible, which gets 42.

Example 3:
    Input: "4193 with words"
    Output: 4193
    Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.

Example 4:
    Input: "words and 987"
    Output: 0
    Explanation: The first non-whitespace character is 'w', which is not a numerical 
                digit or a +/- sign. Therefore no valid conversion could be performed.

Example 5:
    Input: "-91283472332"
    Output: -2147483648
    Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
                Thefore INT_MIN (−231) is returned.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 思路
// 1. 遍历字符，找到第一个非空格字符，如果不是数字、+、-，则结束，返回0
// 2. 从第一个非空格字符开始，再往后遍历，找数字，每找到一个数字，就更新下当前数值，
// 3. 如果当前数值 溢出，则直接返回，否则继续往后遍历

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

int char2int(char c) {
    return (int) (c-'0');
}

// 重新实现atoi
int myAtoi(char * str){
    int isNegtive = 0; // 是否是负数
    long num = 0;      // 当前找到的数值，使用long，防止溢出

    char * p = str;
    while(p != NULL && *p !='\0' && *p == ' ') p ++; // 跳过空格
    if(p == NULL || *p =='\0') return 0;             // 没找到数字，结束

    // 判断第一个非空格是否是 数字或+、-号
    if(*p == '+') {
        p ++;
    }else if(*p == '-') {
        p ++;
        isNegtive = 1;
    }else if(*p >= '0' && *p <= '9') {
        // digit 
    }else {
        // invalid char
        return 0;
    }

    //printf("p=%s  negtive=%d \n", p, isNegtive);

    while( *p != '\0' && isDigit(*p)) {
        //printf("*p=%c num=%ld  num2=%ld\n", *p, num, num * 10 + char2int(*p));
        num = num * 10 + char2int(*p++);
        // 判断是否溢出
        if(isNegtive) {
            long a = -num;
            if (a <= INT32_MIN) {
                //printf("num=%ld  min=%d \n", a, INT32_MIN);
                return INT32_MIN;
            }
        }
        else if (num >= INT32_MAX) return INT32_MAX;
    }

    //printf("num=%ld\n", num);

    return isNegtive ? -num:num;
}

int main()
{
    printf("%d\n", myAtoi("-2147483648")); // expect -2147483648
    printf("%d\n", myAtoi("-2147483647")); // expect -2147483647 
    
    printf("%d\n", myAtoi("42"));
    printf("%d\n", myAtoi("-42"));
    printf("%d\n", myAtoi("4193 with words"));
    printf("%d\n", myAtoi("words and 987"));
    printf("%d\n", myAtoi("-91283472332"));

    return 0;
}