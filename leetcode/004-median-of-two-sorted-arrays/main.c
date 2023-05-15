/*
https://leetcode.com/problems/median-of-two-sorted-arrays/

4. Median of Two Sorted Arrays

There are two sorted arrays nums1 and nums2 of size m and n respectively.
Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

You may assume nums1 and nums2 cannot be both empty.

Example 1:
    nums1 = [1, 3]
    nums2 = [2]

    The median is 2.0

Example 2:
    nums1 = [1, 2]
    nums2 = [3, 4]

    The median is (2 + 3)/2 = 2.5
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// 思路
// 查找两个排序数组的中位数，难点在于算法的复杂度要求是 log(m+n)，所以必然会用到二分查找
// 思路详见：https://www.youtube.com/watch?time_continue=1220&v=LPFhl65R7ww&feature=emb_logo

// 两个数组 X，Y
//      x1，x2，x3，x4，x5
//      y1，y2，y3，y4，y5，y6，
//
// （1）找到一个分割点, 使得该分割点左右两边的数字个数相等或差1（条件1），并且左边所有数小于等于右边
//      x1，x2，| x3，x4，x5
//      y1，y2，y3，| y4，y5，y6，
//     即：x2 <= y4 && y3 <= x3    (条件2)
//     分割点两边的x分别为 maxLeftX，minRightX，即x2, x3
//          两边的x分别为 maxLeftY，minRightY，即y3, y4
//     
//  (2) 当数字个数为偶数时，中位数就是  avg( max(maxLeftX, maxLeftY), min(minRightX,minRightY)  )  
//      当数字个数为奇数时，中位数就是  max(maxLeftX, maxLeftY) 
//  (3) 初始时，X 的分割点（记作 partitionX） 就取 X 的中间点，
//      然后根据（条件1），由公式 partitionX + partitionY = (X.size + Y.size + 1）/ 2 来算出 Y 分割点位置 partitionY
//      然后再根据是否满足（条件2），来做调整
//      如果满足（条件2），则结束，根据步骤(2) 输出结果
//      如果不满足（条件2），
//            If   maxLeftX >= minRightY，说明分割点要 X 向左移动（直接移动到左半部分的中间点，相当于再次折半），Y 会随之向右移动（由公式自动算出）。
//            Else 说明分割点要 X 向右移动（直接移动到右半部分的中间点，相当于再次折半），Y 会随之向左移动（由公式自动算出）


#define MAX(X, Y)  ((X) > (Y) ? (X) : (Y))
#define MIN(X, Y)  ((X) < (Y) ? (X) : (Y))

// Accept, 12 ms
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    
    // 保证nums1 比nums2 数字个数少，因为我们总是从数字个数少的数组进行二分
    if (nums1Size > nums2Size){
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size); 
    }

    int low = 0;
    int high = nums1Size;

    // 对数字个数少的数组进行二分
    while(low <= high) {
        int partitionX = (low + high) / 2;                             // 数字个数少的数组，记做X，
                                                                       //  partitionX 表示分割点的位置，每次都是取二分的位置
        int partitionY = (nums1Size + nums2Size + 1) / 2 - partitionX; // 另一个数组，记做Y，
                                                                       //  partitionY 表示分割点的位置
                                                                       //  partitionX + partitionY = （nums1Size + nums2Size + 1）/ 2
                                                                       //  即 分割点左边的数字个数，要等于数字总数的一半(或+1)
        int maxLeftX = (partitionX == 0) ?  INT_MIN : nums1[partitionX - 1];      // 如果partitionX=0，说明X的分割点左边，没有数字了，即认为是一个极小数
        int minRightX = (partitionX == nums1Size) ?  INT_MAX : nums1[partitionX]; // 如果partitionX=num1Size，说明X的分割点右边，没有数字了，即认为是一个极大数

        int maxLeftY = (partitionY == 0) ?  INT_MIN : nums2[partitionY - 1];      // 如果partitionY=0，说明Y的分割点左边，没有数字了，即认为是一个极小数                                       
        int minRightY = (partitionY == nums2Size) ?  INT_MAX : nums2[partitionY]; // 如果partitionY=num2Size，说明Y的分割点右边，没有数字了，即认为是一个极大数
                                                                       

        // 判断是否符合条件1
        if (maxLeftX <= minRightY && maxLeftY <= minRightX) { // 符合条件，即找到了
            if ((nums1Size + nums2Size) % 2 == 0 ) {          // 数字总和为偶数
                return (double) (MAX(maxLeftX, maxLeftY) + MIN(minRightX, minRightY)) / 2 ;
            }else {                                           // 数字总和为奇数 
                return (double) MAX(maxLeftX, maxLeftY);
            }
        }else if ( maxLeftX > minRightY )  {
            high = partitionX - 1;   // 分割点要向左移动，让X更小，好让 maxLeftX <= minRightY
        }else {
            low = partitionX + 1;    // 分割点要向右移动，让X更大，好让 maxLeftY <= minRightX
        }
    }

    return 0.0;
}

int main() {

    int nums1[] = {1,3};
    int nums2[] = {2};
    int nums3[] = {1,2};
    int nums4[] = {3,4};

    printf("%lf\n", findMedianSortedArrays(nums1, 2, nums2, 1) );
    printf("%lf\n", findMedianSortedArrays(nums3, 2, nums4, 2) );

    return 0;
}
