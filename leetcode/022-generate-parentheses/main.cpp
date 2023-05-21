/*
 * https://leetcode.com/problems/generate-parentheses/
 * 题目：给定一个n，生成 n 对 () 能组成的所有合法字符串
 *      比如 n = 2, 两对()能组成的所有合法串为： ()()，(())
 * 思路：详见后文
 */

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

// Accepted, 8ms
// 思路1 做个全排列，然后去重
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        if(n <= 0) return {};
        if(n == 1) return {"()"};

        vector<char> chars; //{'(', '(', '(', ')', ')', ')'};
        for(int i = 0; i < n; i++) chars.push_back('(');
        for(int i = 0; i < n; i++) chars.push_back(')');

        set<string> perms = {string(chars.begin(), chars.end())};
        while(std::next_permutation(chars.begin(), chars.end())){
            string s(chars.begin(), chars.end());
            if(isValid(s)){
                perms.insert(s);
            }
        }
        vector<string> ret;
        ret.assign(perms.begin(), perms.end());
        return ret;
    }

    // 检查字符串 s 中的括号使用是否合法
    bool isValid(std::string s) {
        int v = 0;
        for(auto c:s){
            if(c == '(') v++;
            else v--;
            if(v < 0) return false;
        }
        return v == 0;
    }
};

// Accepted 4 ms Beats 64.29%
// 思路2
// 参考：https://leetcode.com/problems/generate-parentheses/solutions/10100/easy-to-understand-java-backtracking-solution/
// n 对括号组成的字符串中，必然有 n 个左括号，n 个右括号
// 相当于 2n 个位置，随机放 n 个左括号和 n 个右括号，
// (1) 每个位置都有两种选择，要么放左括号，要么放右括号。选定一个位置后，就可以递归下一个位置
// (2) 有两个剪枝策略：
//     (2.1) 左括号/右括号 各只有 n 个，放完n个后就不能放了
//     (2.2) 右括号的个数不能多余左括号，即 "())" 这种情况是不合法的
class Solution2 {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> vec;
        perm(vec, "", 0, 0, n); // 初始时，字符串为空，左右括号都没有用
        return vec;
    }

    // vec 用来存放最终的结果
    // prefix 是当前已经排好了的字符串
    // leftUsedCnt 是当前已经用掉的左括号个数
    // rightUsedCnt 是当前已经用掉的右括号个数
    // maxCnt 是总共可以使用的个数，左右括号是相等的
    void perm(vector<string>& vec, std::string prefix, int leftUsedCnt, int rightUsedCnt, int maxCnt){
        if(prefix.size() == 2 * maxCnt) {
            vec.push_back(prefix);
            return;
        }

        // 左括号够放，放左括号 剪枝条件(2.1)
        if(leftUsedCnt < maxCnt){
            perm(vec, prefix + '(', leftUsedCnt+1, rightUsedCnt, maxCnt);
        }

        // 右括号能放，右括号的个数不能多余左括号，否则就是无效的。 剪枝条件(2.2)
        if(rightUsedCnt < leftUsedCnt){
            perm(vec, prefix + ')', leftUsedCnt, rightUsedCnt+1, maxCnt);
        }
    }
};

void PrintVector(const vector<string>& vec)
{
    cout << "[";
    for(int i = 0; i < vec.size(); i++){
        cout << vec[i];
        if(i < vec.size() - 1) cout << ", ";
    }
    cout <<"]"<<endl;
}

int main()
{
    Solution s;
    auto v0 = s.generateParenthesis(0);
    PrintVector(v0);

    auto v1 = s.generateParenthesis(1);
    PrintVector(v1);

    auto v2 = s.generateParenthesis(2);
    PrintVector(v2);

    auto v3 = s.generateParenthesis(3);
    PrintVector(v3);

    // 正确答案
    // ["(((())))","((()()))","((())())","((()))()","(()(()))","(()()())","(()())()","(())(())","(())()()","()((()))","()(()())","()(())()","()()(())","()()()()"]
    auto v4 = s.generateParenthesis(4);
    PrintVector(v4);
    
    return 0;
}