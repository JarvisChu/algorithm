// 删除排序数组中的重复项

//给定一个排序数组，你需要在原地删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。
//不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。

// 题目：https://leetcode.com/problems/remove-duplicates-from-sorted-array/
// 分析：zhujiangtao.com

#include <stdio.h>

int removeDuplicates(int* nums, int numsSize){
    if(numsSize == 0) return 0;

    int p = 0; // p 指向当前数组中最后一个不同的数字，初始指向数组第0位

    for(int i = 0; i < numsSize; i++){
        // 发现新的数字，放到p中
        if( nums[i] != nums[p]) {
            p ++;
            nums[p] = nums[i];
        }
    }

    return p + 1;
}

int main()
{
    int arr[10] = {1,2,2,4,4,4,5,6,7,7};
    int cnt = removeDuplicates(arr, 10);
    
    printf("cnt:%d\n", cnt);
    for(int i = 0; i<cnt; i++) {
        printf("%d", arr[i]);
    }

    return 0;
}

