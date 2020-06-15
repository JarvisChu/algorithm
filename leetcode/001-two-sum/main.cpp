#include <iostream>
#include <vector>
#include <map>

using namespace std;

// 思路
// 使用 map 保存数组每个元素的值和对应的索引
// 遍历数组，判断每个元素的互补元素（即 和等于target的值）是否在map中，
//     存在则找到返回
//     不存在则添加到map中，继续判断下个元素

// Accepted, 12 ms
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
         std::map<int,int> cache; // cache[elem] = index

        std::vector<int> ret;
        for(int i = 0; i < nums.size(); i ++ ){
            int completed = target - nums[i];
            auto it = cache.find(completed);
            if (it != cache.end()) {
                // find
                ret.push_back(it->second);   
                ret.push_back(i);
                return ret;
            }
            cache[nums[i]] = i;
        }

        return ret; 
    }
};

int main() {
    Solution s;

    vector<int> nums;
    nums.push_back(2);
    nums.push_back(7);
    nums.push_back(11);
    nums.push_back(15);

    s.twoSum(nums, 9);
    return 0;
}