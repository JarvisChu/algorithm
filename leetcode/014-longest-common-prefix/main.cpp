/*
https://leetcode.com/problems/longest-common-prefix/

14. Longest Common Prefix

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

Example 1:
    Input: ["flower","flow","flight"]
    Output: "fl"

Example 2:
    Input: ["dog","racecar","car"]
    Output: ""
    Explanation: There is no common prefix among the input strings.

Note:
    All given inputs are in lowercase letters a-z.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 思路： 
// 很简单，拿第一个字符串的每一位和后面的字符做比较即可

// Accepted 16 ms
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size() == 0) return "";

        int i = 0;
        for(i = 0; i < strs[0].size(); i ++) {
            bool stop = false;
            for(auto s:strs){
                if (s.size() <= i) {
                    stop = true;
                    break;
                }

                if(s[i] != strs[0][i]) {
                    stop = true;
                    break;
                }
            }
            if(stop) break;
        }

        return strs[0].substr(0,i);
    }
};

int main()
{
    Solution s;
    vector<string> s1 = {"flower","flow","flight"};
    cout << s.longestCommonPrefix(s1) <<endl;

    vector<string> s2 = {"dog","racecar","car"};
    cout << s.longestCommonPrefix(s2) <<endl;

    vector<string> s3 = {"dog"};
    cout << s.longestCommonPrefix(s3) <<endl;

    vector<string> s4 = {};
    cout << s.longestCommonPrefix(s4) <<endl;
    return 0;
}
