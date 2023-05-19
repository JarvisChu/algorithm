// https://leetcode.com/problems/letter-combinations-of-a-phone-number
// 题目：每个数字代表了一组字母，输入一串数字。从每个数字后面代表的字母中依次选择一个，组成一个字符串。输出所有可能的字符串
// 思路：
//     全排列问题，可以用递归解决

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Accepted 4 ms Beats 36.29%
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> ret;
        perm(ret, digits, "", 0);
        return ret;
    }

    void perm(vector<string>& ret, const string& digits, const string& prefix, int idx){
        //cout << "digits:" << digits << ", prefix:" << prefix << ", idx:" << idx << endl;
        if(idx >= digits.size()) return;

        string key = m_keys[digits[idx] - '0'];
        if(idx == digits.size() - 1){
            for(int i = 0; i < key.size(); i++){
                string s = prefix;
                s.push_back(key[i]);
                ret.push_back(s);
            }
            return;
        }

        for(int i = 0; i < key.size(); i++){
            string s = prefix;
            s.push_back(key[i]);
            perm(ret, digits, s, idx+1);
        }
    }
private:
    //保留所有的数字对应的字母表，keyboard[2] = "abc"
    string m_keys[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
};


int main()
{
    Solution s;
    vector<string> v1 = s.letterCombinations("23");

    for(auto str : v1) {
        cout << str << endl;
    }

    return 0;
}