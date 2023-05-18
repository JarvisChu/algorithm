/*
  https://leetcode.com/problems/container-with-most-water/

  给定 n 个点，生成n条线，即 (Xi, Yi) => (Xi, 0)
  Xi = 0,1,2,3
  Yi = 从给定的数组中读取
  n条线围成一个容器，哪种容器能盛放最多的水
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// 思路：
// 盛水的容量为： v = (x2-x1) * min(y1,y2)
// 所以题目可理解为：在x和y给定的情况下，寻找v的最大值，
// 
// 思路1，穷举每种情况，分别以每条线为左边，再依次以其他线为右边，获取此时的v值，保留最大的v.
// 代码ok，但 Time Limit Exceeded
/*class Solution {
public:
    int maxArea(vector<int>& height) {
      int len = height.size();
      int maxVolume = 0;
      for(int i =0; i < len; i ++)
        for(int j = i+1; j < len; j++) {
          int volume = calcVolume(height, i, j);
          if(volume > maxVolume) maxVolume = volume;
        }

        return maxVolume;
    }

    int calcVolume(vector<int>& height, int x1,int x2) {
      return (x2-x1) * min(height[x1], height[x2]);
    }
};
*/


// 思路2
// 逼近法，左右两条线，不断往中间靠。
// 原理参考官网的说明，https://leetcode.com/problems/container-with-most-water/solution/
// 还可以参考：http://www.noteanddata.com/leetcode-11-Container-With-Most-Water-java-solution-note.html
// 理解：
// 记左侧的柱子为 l，右侧的柱子为 r，求 l 和 r 之间的最大面积
// 面积由宽和高决定，宽是 r-l, 高是 min(height[l], height[r])
// 从两边开始，往里面寻找最大面积
// 当前面积是  (r-l) * min(height[l], height[r]) ， 
// 为了寻找大的面积，要么增加宽度，要么增加高度。 r-l 已经是最宽的了，所以只能增加高度
// 增加高度的方法是：短的向内移动，长的保留。 为什么这样可行？ 原因在于：
//    如果不让短的向内移动，而是让长的向内移动， 宽度在减少，而高度始终是受限于短的，所以无论怎么找，都不会比当前面积更大了。

class Solution {
public:
    int maxArea(vector<int>& height) {
      int maxA = 0;
      int l = 0, r = height.size() - 1;
      while(l < r) {
        maxA = max(maxA, (r-l) * min(height[l], height[r]) );
        height[l] >= height[r] ? r--:l++; // 短的向内移动，长的保留
      }
      return maxA;
    }
};



int main()
{
    Solution s;
    vector<int> vec = {1,8,6,2,5,4,8,3,7};
    std::cout << s.maxArea(vec);
    return 0;
}