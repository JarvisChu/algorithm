/*

13. Roman to Integer

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

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.
Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999.

Example 1:
    Input: "III"
    Output: 3

Example 2:
    Input: "IV"
    Output: 4

Example 3:
    Input: "IX"
    Output: 9

Example 4:
    Input: "LVIII"
    Output: 58
    Explanation: L = 50, V= 5, III = 3.

Example 5:
    Input: "MCMXCIV"
    Output: 1994
    Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
*/

#include <iostream>
#include <string>

using namespace std;

// 思路
// 和 第12题完全相同，刚好相反。

// Accept 32 ms, faster than 25.91% of C++ 
class Solution {
public:
    int romanToInt(string s) {
        int roman_values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        string roman_chars[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

        int idx = 0;
        int ret = 0;

        //std::cout<< s << std::endl;   

        for(int i=0; i< 13; i++) {
            while( startWith(s, roman_chars[i]) ) {
                ret += roman_values[i];
                int len = s.size();
                s = s.substr(roman_chars[i].size(), len-roman_chars[i].size());
                //std::cout<< s << std::endl;     
            }
        }

        return ret;
    }

    // check if src is started with pattern
    bool startWith(string src, string pattern) {
        int len1 = src.size();
        int len2 = pattern.size();
        if(len1 < len2) return false;
        for(int i = 0 ; i < len2; i++) {
            if(src[i] != pattern[i]) return false;
        }
        return true;
    }
};

// 在线转换工具：https://www.calkoo.com/zh/alabo-luoma-shuzi-zhuanhuan-qi

int main()
{
    Solution s;
    std::cout<< s.romanToInt("XIII") << std::endl;
    std::cout<< s.romanToInt("IX") << std::endl;
    std::cout<< s.romanToInt("LVIII") << std::endl;
    std::cout<< s.romanToInt("MCMXCIV") << std::endl;
    return 0;
}