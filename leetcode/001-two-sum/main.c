
/* 
https://leetcode.com/problems/two-sum/

1. Two Sum
Given an array of integers, return indices of the two numbers such that they add up to a specific target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:
    Given nums = [2, 7, 11, 15], target = 9,
    Because nums[0] + nums[1] = 2 + 7 = 9,
    return [0, 1].
*/


#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */


// Accepted, 180ms
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    for (int i = 0; i < numsSize; i ++){
        for (int j = i+1;j < numsSize; j++){
            if (nums[i] + nums[j] == target){

                int* arr = (int *) malloc(sizeof(int) * 2);
                arr[0] = i;
                arr[1] = j;
                return arr;
            }
        }
    }
    return NULL;
}

int main() {
    return 0;
}