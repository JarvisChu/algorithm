// https://leetcode.com/problems/regular-expression-matching/
// 题目：实现简单的正则匹配，支持 . 和 * 两种符号。
//      . 表示任意一个字符
//      * 匹配前面一个字符 0 或 多次
// 思路：
//   https://blog.csdn.net/lishuo0204/article/details/115956510
//   https://blog.csdn.net/qq_17550379/article/details/84110005
//
//   普通字符和 . 比较好处理，唯一需要特殊处理的是 *
//   通过递归的方式，可以很好的解决 * 匹配0次或多次的情况

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define false 0
#define true 1
typedef int bool;

#define TEST(a, b) (a == b) ? "pass" : "fail"


bool isMatch(char * s, char * p){
    int lens = strlen(s);
    int lenp = strlen(p);

    // 匹配结束
    if(lenp == 0) {        // 模式串已经匹配完了
        return lens == 0;  // 如果被匹配的串也结束了，则说明匹配成功
    }
    
    // 模式串长度为1，p[0] 只可能是 . 或者 普通字符。题目会保证 * 不会出现在第一位，而且不会连续出现*， 因为这两种情况都是无效的。
    else if(lenp == 1) {
        if(p[0] == '.'){
            return lens == 1; // . 必须匹配一个字符
        }else {
            return lens == 1 && s[0] == p[0]; // 普通字符必须相等
        }
    }

    // 模式串长度大于1，p[0] 不可能是 *号，原因同上。 所以只要判断 p[1] 是否是 * 号即可
    else{
        if(p[1] == '*'){
            // 情况1 p[1] 匹配前一个字符 0 次
            if(isMatch(s, p+2)) return true; // ab;c*d => ab;d
    
            // 情况2 p[1] 匹配前一个字符 1或多次。（通过递归解决匹配多次）
            // s[0] 和 p[0] 匹配成功时，尝试匹配 s[1:] 和 p[0:]
            if(lens > 0 && (s[0] == p[0] || p[0] == '.') && isMatch(s+1, p)) return true; // ab a*

            return false;
        }else {
            if( lens > 0 && (s[0] == p[0] || p[0] == '.')){ // s[0] 和 p[0] 匹配成功
                 return isMatch(s+1, p+1); // ab ac; ab .c => b c; b c
            }

            return false; // ab cd
        }
    }
}

int main(){
    printf("%s\n", TEST(isMatch("aa", "a"), false));
    printf("%s\n", TEST(isMatch("aa", "a*"), true));
    printf("%s\n", TEST(isMatch("ab", ".*"), true));
    printf("%s\n", TEST(isMatch("aab", "c*a*b"), true));
    printf("%s\n", TEST(isMatch("aaaa", "ab*a*c*a"), true));
}