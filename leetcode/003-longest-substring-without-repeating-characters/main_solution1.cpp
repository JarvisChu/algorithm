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

使用滑动窗口 [i, j] 的思路，让滑动窗口不断往后延伸，[i, j+1]
    如果新加入的字符 str[j+1]，不和窗口中任意元素重复，则继续往后延伸，窗口变成[i, j+1]
    如果新加入的字符重复，则借鉴KMP的匹配表思路，假如和 str[k]重复，则将窗口调整为 [k+1,j+1]
    如此，j++, 直到遍历完成。记录滑动窗口宽度的最大值  
*/

#include <iostream>
#include <string>
#include <unordered_set> // hash set

using namespace std;

// Accepted, 164ms
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() == 0) return 0;

        int sw_start = 0; // slid window [sw_start, sw_end], len = sw_end - sw_start + 1
        int sw_end = 0;   // 滑动窗口中的元素是不重复的
        int sw_max_len = 1;
        std::unordered_set<char> hash_set;
        hash_set.insert(s[0]);

        for(int i = 1; i < s.size(); i++) {
            // 判断 i 是否在[sw_start, sw_end] 的滑动窗口中
            auto it = hash_set.find(s[i]);
            
            if (it == hash_set.end()) {
                // 不在滑动窗口中，则窗口继续往后扩展
                hash_set.insert(s[i]);
                sw_end = i;
                int sw_len = sw_end - sw_start + 1;
                if (sw_len > sw_max_len) sw_max_len = sw_len;
            }else {
                // 在滑动窗口中，则需要重新设置 sw_start

                // 找到重复元素的位置
                int pre = findPre(s, i);

                // 将 [sw_start, pre] 之间的值，从hash_set中移除
                for(int k = sw_start; k < pre; k++) {
                    hash_set.erase(s[k]);
                }

                // 更新滑动窗口
                sw_start = pre + 1;
                sw_end = i;
                int sw_len = sw_end - sw_start + 1;
                if (sw_len > sw_max_len) sw_max_len = sw_len;
            }
        }

        return sw_max_len;
    }

    // 从s中找到 s[idx] 上次出现的位置
    int findPre(string s, int idx)
    {
        for(int i = idx-1; i>= 0; i-- ) {
            if (s[i] == s[idx]) {
                return i;
            }
        }
        return 0;
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