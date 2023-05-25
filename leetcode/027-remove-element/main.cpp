/*
 * https://leetcode.com/problems/remove-element/
 * 题目：给定一个数组 nums，和一个数值 val。 将nums中所有值等于 val 的元素移除。
 *      将剩下的元素，比如剩余 K 个，则放到 nums 的前K个位置中（顺序无要求），返回 K
 * 思路：
 *    其实就是 std::remove 函数
 */
#include <iostream>
using namespace std;

// Accepted 0 ms  Beats 100%
// 思路1： 直接使用 std::remove
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        auto it = std::remove(nums.begin(), nums.end(), val);
        return it - nums.begin();
    }
};

// Accepted 8 ms Beats 18.75%
// 思路2: 和上一题 026-remove-duplicates-from-sorted-array 基本相同
//     k 记录当前位置前面有几个和 val 相等的数，则当前位置的数 nums[i] 放到 nums[i-k] 位置
//     比如：nums = [3,2,2,3], val = 3
//          初始时 k = 0，遍历nums
//          i = 0，nums[i] = 3，所以 nums[i] 要放到 nums[i-k]，即 nums[0] 位置。因为 nums[i] == 3, 所以 k++;
//          i = 1，nums[i] = 2，所以 num[i] 要放到 nums[1-1]，即nums[0] 位置。 因为 nums[i] != 3, k 不变
//          同理 i = 2/3
class Solution2 {
public:
    int removeElement(vector<int>& nums, int val) {
        int k = 0;
        for(int i = 0; i < nums.size(); i ++) {
            nums[i-k] = nums[i];
            if(nums[i] == val) k++;
        }
        return nums.size() - k;
    }
};

void PrintVector(const vector<int>& vec, int k)
{
    cout << "[";
    for(int i = 0; i < k; i++){
        cout << vec[i];
        if(i < k - 1) cout << ", ";
    }
    cout <<"]"<<endl;
}

int main()
{
    Solution2 s;

    vector<int> nums = {0,1,2,2,3,0,4,2};
    int val = 2;

    int k = s.removeElement(nums, val);

    cout << "K: " << k << endl;
    PrintVector(nums, k);
}