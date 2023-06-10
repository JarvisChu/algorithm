/*
 * https://leetcode.com/problems/next-permutation/
 * 题目：全排列的下一个排列，其实就是实现 std::next_permutation。
 *      要求 in-place，并且只能使用常量级别的额外内存
 *      注意：[3,2,1] 的下一个排列是 [1,2,3]，即最大排列的下一个排列是最小
 * 思路：
 *
 */
#include <iostream>
#include <string_view>
using namespace std;

#define TEST(a, b) ((a == b) ? "pass" : "fail")

class Solution0 {
public:
    void nextPermutation(vector<int>& nums) {
        std::next_permutation(nums.begin(), nums.end());
    }
};

// Accepted 0ms Beats 100%
// 思路1：从后往前找到，找到第一个i，满足 nums[i] > nums[i-1]
//   (1) 如果找不到，则说明当前的排列已经是最大的了。 下一个排列是最小。 调整到最小排序，结束
//   (2) 如果找到满足条件的 i，则将：
//       此时， nums[i:] 是降序排列的
//       (2.1) 从 nums[i:] 中找到值最小并且大于 nums[i-1] 的那个元素（比如是 nums[k]），然后 swap(nums[k], nums[i-1])
//       (2.2) 交换后 nums[i:] 也是降序排列，所以直接做个逆序即可
//    如 nums = [1,2,7,4,1]，发现 7 > 2，因为4是大于2的最小的值，所以交换 4 和 2，得到 nums=[1,4,7,2,1]，
//    因为原先[7,4,1]本来就是降序的，2 又是替换了4的位置，新的[7,2,1] 也必然是降序的。所以直接逆序，最终得到 nums=[1,4,1,2,7]
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if(nums.size() <= 1) return;

        int tmp = 0; // 只用了 1 个单位的额外内存
        for(int i = nums.size()-1; i > 0; i--){
            if(nums[i] > nums[i-1]){ // (2)
                // (2.1)
                int k = nums.size()-1;
                for(; k >= i; k--){
                    if(nums[k] > nums[i-1]) break;
                }

                // swap(nums[k], nums[i-1])
                tmp = nums[k];
                nums[k] = nums[i-1];
                nums[i-1] = tmp;

                // [code1] 将 nums[i:] 做个逆序，首尾交换即可
                int front = i, rear = nums.size()-1;
                while(front < rear){
                    // swap(front, rear)
                    tmp = nums[front];
                    nums[front] = nums[rear];
                    nums[rear] = tmp;
                    front++;
                    rear--;
                }

                return;
            }
        }

        // [code2] 运行至此，说明没找到满足条件的i，即 (1)，将nums整体做个逆序即可
        int front = 0, rear = nums.size()-1;
        while(front < rear){
            // swap(front, rear)
            tmp = nums[front];
            nums[front] = nums[rear];
            nums[rear] = tmp;
            front++;
            rear--;
        }
        return;
    }
};

// Accepted 4ms Beats 68.30%
// 思路2：优化下思路1 的代码
class Solution2 {
public:
    void nextPermutation(vector<int>& nums) {
        if(nums.size() <= 1) return;

        int tmp = 0; // 只用了 1 个单位的额外内存
        for(int i = nums.size()-1; i > 0; i--){
            if(nums[i] > nums[i-1]){ // (2)
                int k = nums.size()-1;
                for(; k >= i; k--){
                    if(nums[k] > nums[i-1]) break;
                }

                swap(nums, k, i-1);
                reverse(nums, i, nums.size()-1);
                return;
            }
        }

        // 运行至此，说明没找到满足条件的i，即 (1)，将nums整体做个逆序即可
        reverse(nums, 0, nums.size()-1);
        return;
    }

    // reverse nums[begin, end]
    void reverse(vector<int>& nums, int begin, int end){
        int front = begin, rear = end;
        while(front < rear){
            swap(nums, front, rear);
            front++;
            rear--;
        }
    }

    // swap(nums[a], nums[b])
    void swap(vector<int>& nums, int a, int b){
        int tmp = nums[a];
        nums[a] = nums[b];
        nums[b] = tmp;
    }
};


void PrintVector(const vector<int>& vec)
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
    auto start = chrono::steady_clock::now();

    Solution2 s;

    // case 1
    vector<int> nums = {1,2,3};
    s.nextPermutation(nums);
    PrintVector(nums); // expect [1,3,2]
    cout<<"Expect [1,3,2]" << endl;

    // case 2
    vector<int> nums2 = {3,2,1};
    s.nextPermutation(nums2);
    PrintVector(nums2); // expect [1,2,3]
    cout<<"Expect [1,2,3]" << endl;

    // case 3
    vector<int> nums3 = {1,1,5};
    s.nextPermutation(nums3);
    PrintVector(nums3); // expect [1,5,1]
    cout<<"Expect [1,5,1]" << endl;

    // case 4
    vector<int> nums4 = {1,3,2};
    s.nextPermutation(nums4);
    PrintVector(nums4); // expect [2,1,3]
    cout<<"Expect [2,1,3]" << endl;

    // case 5
    vector<int> nums5 = {2,3,1};
    s.nextPermutation(nums5);
    PrintVector(nums5); // expect [3,1,2]
    cout<<"Expect [3,1,2]" << endl;

    auto end = chrono::steady_clock::now();
    cout<< "cost:" << chrono::duration_cast<chrono::milliseconds>(end-start).count() <<endl;
    return 0;
}