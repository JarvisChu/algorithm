// https://leetcode.com/problems/valid-parentheses/
// 题目：给定一个字符串，只包含括号 {, }, [, ], (, )，判断括号是否合法
// 思路：
//   典型的栈问题，左括号入栈，右括号时查看与栈顶符号是否匹配。

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

#define TEST(a, b) ((a == b) ? "pass" : "fail")

// Accept 0ms Beats 100%
class Solution {
public:
    bool isValid(string s) {
        std::stack<char> chars;
        for(auto c : s){
            if(c == '{' || c == '[' || c == '(') {
                chars.push(c);
            }

            else if( c == '}') {
                if(chars.empty()) return false;
                auto top = chars.top();
                if(top != '{') return false;
                chars.pop();
            }

            else if( c == ']') {
                if(chars.empty()) return false;
                auto top = chars.top();
                if(top != '[') return false;
                chars.pop();
            }

            else if( c == ')') {
                if(chars.empty()) return false;
                auto top = chars.top();
                if(top != '(') return false;
                chars.pop();
            }
        }

        return chars.empty();
    };
};

int main()
{
    Solution s;
    cout << TEST(s.isValid("()"), true) << endl;
    cout << TEST(s.isValid("()[]{}"), true) << endl;
    cout << TEST(s.isValid("(]"), false) << endl;

    return 0;
}