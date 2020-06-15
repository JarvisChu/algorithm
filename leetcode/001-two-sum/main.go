package main

import "fmt"

// Accepted, 36ms
func twoSum(nums []int, target int) []int {
	size := len(nums)
    for i := 0; i < size; i++ {
		for j := i + 1; j < size; j++ {
			if nums[i] + nums[j] == target {
				return []int{i,j}
			}
		}
	} 
	return []int{}
}

func main() {
	fmt.Printf("%v", twoSum([]int{2,7,11,15}, 9))
}