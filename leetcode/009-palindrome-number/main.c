/*
https://leetcode.com/problems/palindrome-number/

9. Palindrome Number

Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

Example 1:
    Input: 121
    Output: true

Example 2:
    Input: -121
    Output: false
    Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

Example 3:
    Input: 10
    Output: false
    Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
Follow up:

Coud you solve it without converting the integer to a string?
*/


// 题目：判断是否是回文数，且实现时不能将整型转化为字符串
// 思路： 
// 1. 负数肯定不是回文，0 肯定是回文
// 2. 处理正数即可，取出每一位，组合成新的数字，然后判断二者是否相等。

#include <stdio.h>
#include <stdlib.h>

#define false 0
#define true 1
typedef int bool;


// 判断是否是回文数，Accepted, 16ms
bool isPalindrome(int x){
    if (x < 0) return false;
    
    long reverse = 0; 
    int n = x;
    while(n > 0) {
        int digit = n % 10;
        reverse = reverse * 10 + digit;
        n /= 10;
    }

    return x == reverse;
}


int main()
{
    printf("%d \n", isPalindrome(121) );
    printf("%d \n", isPalindrome(-121) );
    printf("%d \n", isPalindrome(10) );
    printf("%d \n", isPalindrome(123454321) );
    return 0;
}
