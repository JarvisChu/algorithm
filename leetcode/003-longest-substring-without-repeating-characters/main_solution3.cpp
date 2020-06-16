/*

// 找到不包含重复字符的最长子串

Given a string, find the length of the longest substring without repeating characters.

Example 1:
    Input: "abcabcbb"
    Output: 3 
    Explanation: The answer is "abc", with the length of 3. 

Example 2:
    Input: "bbbbb"
    Output: 1
    Explanation: The answer is "b", with the length of 1.

Example 3:
    Input: "pwwkew"
    Output: 3
    Explanation: The answer is "wke", with the length of 3. 
                Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

*/

/* 思路

使用滑动窗口 [i, j] 的思路，让滑动窗口不断外后延伸，[i, j+1]
    如果新加入的字符 str[j+1]，不和窗口中任意元素重复，则继续往后延伸，窗口变成[i, j+1]
    如果新加入的字符重复，则借鉴KMP的匹配表思路，假如和 str[k]重复，则将窗口调整为 [k+1,j+1]
    如此，j++, 直到遍历完成。记录滑动窗口宽度的最大值  
*/

#include <iostream>
#include <string>
#include <unordered_map> // hash map

using namespace std;

// 最高效
// 使用hash_map，直接存储索引，更加高效
// 仿照官方的Java解法
// Accepted, 24 ms
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int max_len = 0;
        std::unordered_map<char, int> hash_map; // 存储当前字符的位置（+1）

        // try to extend the range [i, j]
        for(int j = 0, i = 0; j < n; j ++) {
            auto it = hash_map.find(s[j]);
            if (it != hash_map.end()) {
                i = max(it->second, i); // 如果重复，不用清除[i, 重复的位置] 之间的缓存
                                        // 只需要判断重复的位置是否在滑动窗口中
                                        // 如果重复的位置，在滑动窗口前面，即 <i，那就不用移动i
                                        // 如果重复的位置，在滑动窗口中，即 > i， 则更新i即可
            }

            max_len = max(max_len, j - i + 1);
            hash_map[s[j]] = j + 1;
        }

        return max_len;
    }

    int max(int a, int b) {
        return a>=b ? a:b;
    }

};

int main() 
{
    Solution s;

    std::cout<<s.lengthOfLongestSubstring("abcabcbb")<<std::endl;
    std::cout<<s.lengthOfLongestSubstring("bbbbb")<<std::endl;
    std::cout<<s.lengthOfLongestSubstring("pwwkew")<<std::endl;
    return 0;
}