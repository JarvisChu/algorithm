// https://leetcode.com/problems/4sum/
// 题目：给定一个数组，从中找出4个数，其和等于 target，输出所有的组合
// 思路：和 015-3sum 几乎一样

#include <iostream>
#include <string>

using namespace std;

#define TEST(a, b) (a == b) ? "pass" : "fail"

// Accepted 110 ms Beats 45.80%
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if(nums.size() < 4) return {};
        std::sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        for(int a = 0; a < nums.size() - 3; a++) {
            for(int b = a + 1; b < nums.size() - 2; b++){
                int front = b+1;
                int rear = nums.size() - 1;
                while(front < rear){
                    long sum = (long)nums[a] + (long)nums[b] + (long)nums[front] + (long)nums[rear];
                    if(sum < target) front ++;
                    else if(sum > target) rear--;
                    else{
                        vector<int> v = {nums[a], nums[b], nums[front], nums[rear]};
                        ret.push_back(v);

                        while(front < rear && nums[front] == v[2]) front++;
                        while(front < rear && nums[rear] == v[3]) rear--;
                    }
                }
                while( (b < nums.size() - 2) && nums[b] == nums[b+1]) b++;
            }
            while( (a < nums.size() - 3) && nums[a] == nums[a+1]) a++;
        }

        return ret;
    }
};

int main()
{
    //vector<int> nums = {1,0,-1,0,-2,2};
    //vector<int> nums = {0,0,0,0,0,0};
    //vector<int> nums = {0,0,0,0};
    //vector<int> nums = {-1,-1,-1,-1,-1,0, 3};
    //vector<int> nums = {-3,-1,0,2,4,5};
    vector<int> nums = {1000000000,1000000000,1000000000,1000000000};
    
    int target = 0;


    Solution s;
    auto ret = s.fourSum(nums, 0);

    for(auto v:ret) {
        for(auto i:v) {
            cout<< i <<",";
        }
        cout<<endl;
    }

    return 0;
}