// https://leetcode.com/problems/letter-combinations-of-a-phone-number
// 题目：每个数字代表了一组字母，输入一串数字。从每个数字后面代表的字母中依次选择一个，组成一个字符串。输出所有可能的字符串
// 思路：
//     全排列问题，详见具体Solution的说明

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 递归解法
// 思路：比如数字为 "234", 即 [abc] [def] [efg]
//      perm("234") = [a+perm("34"), b+perm("34"), c+perm("34")]
// Accepted 4 ms Beats 36.29%
class Solution1 {
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
    //保留所有的数字对应的字母表，m_keys[2] = "abc"，即 keys['2' - '0'] = "abc"
    string m_keys[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
};

// 递推解法
// 参考：https://leetcode.com/problems/letter-combinations-of-a-phone-number/solutions/8090/iterative-c-solution-in-0ms/
// 思路：比如数字为 "234", 即 [abc] [def] [efg]
//    (1) 处理数字 "2"，把 "a", "b", "c" 放入数组 vec
//    (2) 处理数字 "3"，依次把 "d"，"e"， "f" 加到 vec 每个元素后面，生成数组 ["ad", "bd", "cd", "ae", "be", "ce", "af", "bf", "cf"]，用该数组替换 vec
//    (3) 同理，处理数字 "4"
// Accepted 0 ms Beats 100%
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};

        //保留所有的数字对应的字母表，keys[2] = "abc"，即 keys['2' - '0'] = "abc"
        string keys[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

        vector<string> ret;
        ret.push_back("");
        for(auto d : digits){
            // 将 d 对应的字母，都追加到 ret 中
            vector<string> tmp;
            for(auto c : keys[d-'0']){
                for(auto s : ret){
                    tmp.push_back(s+c);
                }
            }
            ret.swap(tmp);
        }

        return ret;
    }
};


int main()
{
    Solution s;
    vector<string> v1 = s.letterCombinations("234");

    for(auto str : v1) {
        cout << str << endl;
    }

    return 0;
}