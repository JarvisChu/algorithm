/*
12. Integer to Roman

Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

For example, two is written as II in Roman numeral, just two one's added together. 
Twelve is written as, XII, which is simply X + II. 
The number twenty seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. 
However, the numeral for four is not IIII. Instead, the number four is written as IV. 
Because the one is before the five we subtract it making four. 
The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.

Given an integer, convert it to a roman numeral. Input is guaranteed to be within the range from 1 to 3999.

Example 1:
    Input: 3
    Output: "III"

Example 2:
    Input: 4
    Output: "IV"

Example 3:
    Input: 9
    Output: "IX"

Example 4:
    Input: 58
    Output: "LVIII"
    Explanation: L = 50, V = 5, III = 3.

Example 5:
    Input: 1994
    Output: "MCMXCIV"
    Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
*/

#include <iostream>
#include <string>

using namespace std;

// 思路
// 生成一个数字和罗马字符的对应表，然后使用待转换的数字，依次遍历字符表即可

// Accpeted, 8 ms, faster than 88.82% of C++ 
class Solution {
public:
    string intToRoman(int num) {
        // Input is guaranteed to be within the range from 1 to 3999.
        if(num < 1 || num > 3999) return ""; 

        int roman_values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        string roman_chars[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

        string ret;
        for(int i =0; i < 13; i ++){
            while(num >= roman_values[i]) {
                ret += roman_chars[i];
                num -= roman_values[i];
            }
        }

        return ret;
    }
};

int main()
{
    Solution s;
    //std::cout<< s.intToRoman(3888) << std::endl;
    int num = 0;
    while( cin>>num) {
        std::cout<< s.intToRoman(num) << std::endl;
    }
    return 0;
}