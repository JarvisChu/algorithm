/*
https://leetcode.com/problems/longest-palindromic-substring/

5. Longest Palindromic Substring
最长回文子串

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:
    Input: "babad"
    Output: "bab"
    Note: "aba" is also a valid answer.
Example 2:
    Input: "cbbd"
    Output: "bb"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
思路： 
    两种类型的回文子串： (1) 奇数型 abcba 和 (2) 偶数型 abba

    从第二个字符开始遍历字符串，对每个字符串做如下处理：
    
    (1) 判断是否是偶数型回文：
        如果当前字符 和 前个字符相同，则是，此时继续向两边扩展，直至两边不等。更新最长回文
    (2) 判断是否是奇数型回文：
        如果当前字符的左右两个字符相同，则是，此时继续向两边扩展，直至两边不等。更新最长回文
    (3) 从（1）和（2）中选择最长回文，返回   
*/

// 最长回文子串
// Accept, 16ms，faster than 75.68%
// 代码可重构
char * longestPalindrome(char * s){
    if (s == NULL) return NULL;

    int maxLen = 1;     // 查找到的最长回文子串长度，默认为1
    int maxStart = 0;   // 查找到的最长回文子串的起点，默认为0， 这两个参数用于定位 回文子串
    int len = strlen(s);

    // 从第二个字符开始遍历字符串b
    for(int i = 1; i < len; i ++) {

        int left = i - 1;
        int right = i + 1;

        // 判断是否是偶数型
        if (s[i] == s[i-1]) { // 偶数型

            left = i-2;
            right = i+1;
            
            // 向两边扩展
            while(left >= 0 && right <= len-1){
                if(s[left] != s[right]) break;
                left --; right ++; 
            }

            // 此时s[left] 和 s[right] 不等的，恢复到上一个相等的位置
            left ++; right --;
            
            int curLen = right - left + 1;
            if (curLen > maxLen) {
                maxLen = curLen;
                maxStart = left;
            }
        }

        // 再判断是否是奇数型  [必须两个都判断，从奇数型和偶数型中找出最长的]
        left = i - 1; right = i + 1;
        if (right < len && s[left] == s[right] ) // 奇数型
        {
            // 向两边扩展
            while(left >= 0 && right <= len-1){
                if(s[left] != s[right]) break;
                left --; right ++; 
            }

            // 此时s[left] 和 s[right] 不等的，恢复到上一个相等的位置
            left ++; right --;
            
            int curLen = right - left + 1;
            if (curLen > maxLen) {
                maxLen = curLen;
                maxStart = left;
            }
        }
        
    }

    // 从原始串中复制出子串
    char * ret = (char*) malloc(sizeof(char) * maxLen + 1);
    for(int i = 0; i < maxLen; i ++ ){
        ret[i] = s[i+maxStart];
    }
    ret[maxLen] = '\0';
    return ret;
}

int main()
{
    printf("%s \n", longestPalindrome("babad"));
    printf("%s \n", longestPalindrome("abcbd"));
    printf("%s \n", longestPalindrome("bb"));
    printf("%s \n", longestPalindrome("bbbbb"));
    printf("%s \n", longestPalindrome("abbbcbb"));
    printf("%s \n", longestPalindrome("aaaa"));
    printf("%s \n", longestPalindrome("ccc"));

    return 0;
}