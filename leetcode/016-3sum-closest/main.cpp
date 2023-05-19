// https://leetcode.com/problems/3sum-closest/
// 题目：给定一个数组和一个目标数，要求从数组中找到3个元素，其和最接近目标数。输出这三个元素的和。
// 思路：同问题15

#include <iostream>
#include <string>
#include <climits>

using namespace std;

#define TEST(a, b) ((a == b) ? "pass" : "fail")

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        int min_dist = abs(target - nums[0] - nums[1] - nums[nums.size() - 1]);
        int three_sum = nums[0] + nums[1] + nums[nums.size() - 1];
        for(int i = 0; i < nums.size() - 2; i++){
            int front = i + 1;
            int rear = nums.size() - 1;
            while(front < rear){
                int sum = nums[i] + nums[front] + nums[rear];
                int dist = abs(target - sum);
                if(dist < min_dist) {
                    min_dist = dist;
                    three_sum = sum;
                    //printf("Found: (%d,%d,%d)[%d, %d, %d], sum=%d, dist=%d\n", i, front, rear, nums[i], nums[front], nums[rear], three_sum, dist );
                }

                if(sum == target){ // 找到相等，则不用再找了，这个必然是距离最近的
                    return sum;
                }else if( sum < target){
                    front++;
                }else{
                    rear--;
                }
            }

            // 避免i的重复
            while(i+1 < nums.size() && nums[i] == nums[i+1]) i ++;
        }

        return (int)three_sum;
    }

    int abs(int x){
        return x >= 0 ? x : -x;
    }
};

int main()
{
    Solution s;

    vector<int> nums = {-1,2,1,-4};
    int target = 1;
    int answer = 2;

//    vector<int> nums = {1,1,1,1};
//    int target = 0;
//    int answer = 3;

//    vector<int> nums = {13,252,-87,-431,-148,387,-290,572,-311,-721,222,673,538,919,483,-128,-518,7,-36,-840,233,-184,-541,522,-162,127,-935,-397,761,903,-217,543,906,-503,-826,-342,599,-726,960,-235,436,-91,-511,-793,-658,-143,-524,-609,-728,-734,273,-19,-10,630,-294,-453,149,-581,-405,984,154,-968,623,-631,384,-825,308,779,-7,617,221,394,151,-282,472,332,-5,-509,611,-116,113,672,-497,-182,307,-592,925,766,-62,237,-8,789,318,-314,-792,-632,-781,375,939,-304,-149,544,-742,663,484,802,616,501,-269,-458,-763,-950,-390,-816,683,-219,381,478,-129,602,-931,128,502,508,-565,-243,-695,-943,-987,-692,346,-13,-225,-740,-441,-112,658,855,-531,542,839,795,-664,404,-844,-164,-709,167,953,-941,-848,211,-75,792,-208,569,-647,-714,-76,-603,-852,-665,-897,-627,123,-177,-35,-519,-241,-711,-74,420,-2,-101,715,708,256,-307,466,-602,-636,990,857,70,590,-4,610,-151,196,-981,385,-689,-617,827,360,-959,-289,620,933,-522,597,-667,-882,524,181,-854,275,-600,453,-942,134};
//    int target = -2805;
//    int answer = -2805;

    cout << s.threeSumClosest(nums, target) << endl;
    cout << TEST(s.threeSumClosest(nums, target), answer) << endl;
    return 0;
}