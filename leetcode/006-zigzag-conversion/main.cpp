/*

6. ZigZag Conversion
Medium

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
Example 1:
    Input: s = "PAYPALISHIRING", numRows = 3
    Output: "PAHNAPLSIIGYIR"

Example 2:
    Input: s = "PAYPALISHIRING", numRows = 4
    Output: "PINALSIGYAHRPI"
    Explanation:
            P     I    N
            A   L S  I G
            Y A   H R
            P     I

*/


#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 思路
// 遍历字符串，将每个字符，分配到不同的行即可

// Accepted, 32ms, faster than 44.69%
class Solution {
public:
    string convert(string s, int numRows) {

        // vecRowStr 保存每一行的字符串
        std::vector<string> vecRowStr;
        for(int i = 0; i < numRows; i ++ ){
            vecRowStr.push_back("");
        }

        // 遍历字符串
        int len = s.size();
        int row = 0;
        int increase = 1; // 行数增加还是减少
        for(int i = 0; i < len; i++) {
            vecRowStr[row].push_back(s[i]);  // 将 s[i] 附加到第row行字符串的末尾
            
            if(increase){
                if (row < (numRows -1) ) {
                    row ++; // 继续递增
                }else {
                    row --;
                    if(row < 0) row = 0;
                    increase = 0; // 逆向，递减
                }
            }else {
                if(row > 0 ){
                    row --;
                }else {
                    row ++;
                    if (row > (numRows -1)) row = numRows -1;
                    increase = 1; // 逆向，递增
                }
            }
        }

        // 将每行的字符串，拼接成一个完整的字符串
        string ret;
        for(int i = 0; i < numRows; i ++) {
            ret += vecRowStr[i];
        }

        return ret;
    }
};

int main()
{
    Solution s;
    std::cout << s.convert("AB", 1) << std::endl;
    std::cout << s.convert("PAYPALISHIRING", 3) << std::endl;
    std::cout << s.convert("PAYPALISHIRING", 4) << std::endl;

    return 0;
}