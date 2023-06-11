/*
 * https://leetcode.com/problems/longest-valid-parentheses/
 * 题目：给定一个字符串，只包含左括号( 和 右括号)，找到包含最长的有效括号的子串，返回其长度
 *      如 s = "(()", 最长有效子串为(), 所以返回2。
 *         s = ")()())", 最长有效子串为"()()", 所以返回 4
 * 思路：见具体Solution
 */
#include <iostream>
using namespace std;

#define TEST(a, b) ((a == b) ? "pass" : "fail")

// Accept 924 ms Beats 5.1%
// 思路：遍历字符串，初始 v = 0, 遇到左括号 +1，遇到右括号 -1.
//      如果 v = 0 说明是合法的括号；如果v < 0 则结束；如果 v > 0 则继续遍历
class Solution {
public:
    int longestValidParentheses(string s) {

        int curMaxLen = 0;
        for(int i = 0; i < s.size(); i++){  // 依次寻找 s[i:] 中的最长合法子串
            int v = 0;
            for(int j = i; j < s.size(); j++){
                s[j] == '(' ? v++ : v--;
                if(v < 0) break; // 非法
                if(v == 0) { // 找到一个合法串，判断此时的长度
                    int len = j-i+1;
                    if(len > curMaxLen){
                        curMaxLen = len;
                        //cout << "Found one: " << "len=" << len << ", str=" << s.substr(i, len) << endl;
                    }
                }
            }
        }

        return curMaxLen;
    }
};



int main()
{
    auto start = chrono::steady_clock::now();

    Solution s;
    cout << TEST(s.longestValidParentheses("(()"), 2) << endl;
    cout << TEST(s.longestValidParentheses(")()())"), 4) << endl;
    cout << TEST(s.longestValidParentheses(""), 0) << endl;

    auto end = chrono::steady_clock::now();
    cout<< "cost:" << chrono::duration_cast<chrono::milliseconds>(end-start).count() <<endl;
    return 0;
}