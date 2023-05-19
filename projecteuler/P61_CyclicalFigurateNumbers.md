# Problem 61: Cyclical figurate numbers

> https://projecteuler.net/problem=61

Triangle, square, pentagonal, hexagonal, heptagonal, and octagonal numbers are all figurate (polygonal) numbers and are generated by the following formulae:

Triangle        P<sub>3,n</sub>=n(n+1)/2         1, 3, 6, 10, 15, ...
Square          P<sub>4,n</sub>=n<sup>2</sup>    1, 4, 9, 16, 25, ...
Pentagonal      P<sub>5,n</sub>=n(3n−1)/2        1, 5, 12, 22, 35, ...
Hexagonal       P<sub>6,n</sub>=n(2n−1)          1, 6, 15, 28, 45, ...
Heptagonal      P<sub>7,n</sub>=n(5n−3)/2        1, 7, 18, 34, 55, ...
Octagonal       P<sub>8,n</sub>=n(3n−2)          1, 8, 21, 40, 65, ...

The ordered set of three 4-digit numbers: 8128, 2882, 8281, has three interesting properties.

The set is cyclic, in that the last two digits of each number is the first two digits of the next number (including the last number with the first).
Each polygonal type: triangle (P3,127=8128), square (P4,91=8281), and pentagonal (P5,44=2882), is represented by a different number in the set.
This is the only set of 4-digit numbers with this property.
Find the sum of the only ordered set of six cyclic 4-digit numbers for which each polygonal type: triangle, square, pentagonal, hexagonal, heptagonal, and octagonal, is represented by a different number in the set.

## 分析

8128,2882,8281 分别是三角形数，五边形数和五边形数，并且前一个数的后两位数字，是后一个数的前两位（最后一个数的后两位，是第一个数的前两位），形成了一个循环，即 abcd, cdef, efab 这样的格式。

找到 6 个 4 位的数，他们满足上述的循环格式（即前一个数的后两位数字，是后一个数的前两位，末尾的数的后两位是第一个数的前两位），并且，他们分别是三角形数，四边形数，五边形数，六边形数，七边形数，八边形数。

满足条件的 6 个数只有一组，求这个 6 个数的和。

## 方法 遍历判断

首先，找到所有4位的三角形数、四边形数，五边形数，六边形数，七边形数，八边形数，存放到 triangle, square, pentagonal, hexagonal, heptagonal, octagonal 中。

然后，将所有的数保存到 set 中完成去重，并且排序，用于后续的遍历。

假设最终的6个数为 **x1,x2,x3,x4,x5,x6**，x1 从 set 中遍历，然后找出所有 set 中所有前两位数字等于 x1 后两位数字的数，作为 x2 的备选集合， 然后再遍历 x2 的备选集合，找到set中所有前两位数字等于 x2 后两位数字的数，作为 x3 的备选集合，依次类推。可以找到一组 x1,x2,x3,x4,x5,x6，满足前一个的后两位是后一个的前两位。 再判断 x6 的后两位是否是 x1 的前两位，如果是，则 x1~x6 满足循环的要求。

题目要求最终的6个数，必须包含三角形数，四边形数，五边形数，六边形数，七边形数，八边形数。但因为一个数可能是多种类型的，那么就需要判断各种情况下，能否满足每种类型的数都存在。 采用 containsAllKinds(nums, kinds) 递归实现。

### Python
```python

# 三角形数 n(n+1)/2
triangle = [ int(n*(n+1)/2) for n in range(1, 200) if n*(n+1)/2 >= 1000 and n*(n+1)/2 <= 9999 ]
# 四边形数 n^2
square = [ n*n for n in range(1, 101) if n*n >= 1000 and n*n <= 9999 ]
# 五边形数 n(3n−1)/2
pentagonal = [ int(n*(3*n-1)/2) for n in range(1, 100) if n*(3*n-1)/2 >= 1000 and n*(3*n-1)/2 <= 9999 ]
# 六边形数 n(2n−1)
hexagonal = [ n*(2*n-1) for n in range(1, 100) if n*(2*n-1) >= 1000 and n*(2*n-1) <= 9999 ]
# 七边形数 n(5n−3)/2 
heptagonal = [ int(n*(5*n-3)/2) for n in range(1, 100) if n*(5*n-3)/2 >= 1000 and n*(5*n-3)/2 <= 9999 ]
# 八边形数 n(3n−2) 
octagonal = [ n*(3*n-2) for n in range(1, 100) if n*(3*n-2) >= 1000 and n*(3*n-2) <= 9999 ]

# 保存所有类型的数并去重
all = set()
for n in triangle: all.add(n)
for n in square: all.add(n)
for n in pentagonal: all.add(n)
for n in hexagonal: all.add(n)
for n in heptagonal: all.add(n)
for n in octagonal: all.add(n)

# 将所有的数从小到大排序，用于后面的遍历
all = sorted(all)

# 判断 nums 中的数，是否包含了 kinds 中的所有种类（不能一个数代表多个种类）
# 初始时：kinds = {3,4,5,6,7,8} 表示 三角形数，四边形数，.... 八边形数
def containsAllKinds(nums, kinds):
    if len(nums) == 0:
        return True if len(kinds) == 0 else False

    global triangle, square, pentagonal, hexagonal, heptagonal, octagonal
    
    if nums[0] in triangle: 
        # remove 3 from kinds
        kinds_cpy = kinds.copy()
        if 3 in kinds_cpy:
            kinds_cpy.remove(3)
            if containsAllKinds(nums[1:], kinds_cpy): return True

    if nums[0] in square: 
        # remove 4 from kinds
        kinds_cpy = kinds.copy()
        if 4 in kinds_cpy:
            kinds_cpy.remove(4)
            if containsAllKinds(nums[1:], kinds_cpy): return True
    
    if nums[0] in pentagonal: 
        # remove 5 from kinds
        kinds_cpy = kinds.copy()
        if 5 in kinds_cpy:
            kinds_cpy.remove(5)
            if containsAllKinds(nums[1:], kinds_cpy): return True
    
    if nums[0] in hexagonal: 
        # remove 6 from kinds
        kinds_cpy = kinds.copy()
        if 6 in kinds_cpy:
            kinds_cpy.remove(6)
            if containsAllKinds(nums[1:], kinds_cpy): return True
    
    if nums[0] in heptagonal: 
        # remove 7 from kinds
        kinds_cpy = kinds.copy()
        if 7 in kinds_cpy:
            kinds_cpy.remove(7)
            if containsAllKinds(nums[1:], kinds_cpy): return True
    
    if nums[0] in octagonal: 
        # remove 8 from kinds
        kinds_cpy = kinds.copy()
        if 8 in kinds_cpy:
            kinds_cpy.remove(8)
            if containsAllKinds(nums[1:], kinds_cpy): return True

    return False

# 假设 6个数依次为 : x1,x2,x3,x4,x5,x6
# 遍历寻找答案
for x1 in all:
    # 找到所有以 x1 后两位开头的数，即可能的 x2 集合
    possiblex2  = [ x2 for x2 in all if str(x2)[0:2] == str(x1)[-2:] ]

    for x2 in possiblex2: 
        # 找到所有以 x2 后两位开头的数，即可能的 x3 集合
        possiblex3  = [ x3 for x3 in all if str(x3)[0:2] == str(x2)[-2:] ]

        for x3 in possiblex3: 
            # 找到所有以 x3 后两位开头的数，即可能的 x4 集合
            possiblex4  = [ x4 for x4 in all if str(x4)[0:2] == str(x3)[-2:] ]

            for x4 in possiblex4: 
                # 找到所有以 x4 后两位开头的数，即可能的 x5 集合
                possiblex5  = [ x5 for x5 in all if str(x5)[0:2] == str(x4)[-2:] ]

                for x5 in possiblex5: 
                    # 找到所有以 x5 后两位开头的数，即可能的 x6 集合
                    possiblex6  = [ x6 for x6 in all if str(x6)[0:2] == str(x5)[-2:] ]

                    for x6 in possiblex6: 
                        # 判断 x6 的后两位，是否是x1 的前两位，如果是，则满足了循环的要求
                        if str(x1)[0:2] == str(x6)[-2:] :
                            nums = [x1,x2,x3,x4,x5,x6]

                            # 不能有重复数字
                            if len(set(nums)) < 6 : continue

                            # 判断 x1,x2,x3,x4,x5,x6 是否满足分别是三角形数... 八边形数都存在
                            if containsAllKinds(nums, set([3,4,5,6,7,8])):
                                print(x1,x2,x3,x4,x5,x6, "sum:", sum(nums))
```

### Golang

```golang
package main

import (
	"fmt"
	"sort"
)

var triangle []int
var square []int
var pentagonal []int
var hexagonal []int
var heptagonal []int
var octagonal []int

func containsElement(slice []int, element int) bool {
	for _, e := range slice {
		if e == element {
			return true
		}
	}
	return false
}

func removeElementFromSlice(slice []int, element int) []int {
	var cpy []int
	for _, e := range slice {
		if e != element {
			cpy = append(cpy, e)
		}
	}
	return cpy
}

// 判断 nums 中的数，是否包含了 kinds 中的所有种类（不能一个数代表多个种类）
// 初始时：kinds = {3,4,5,6,7,8} 表示 三角形数，四边形数，.... 八边形数
func containsAllKinds(nums, kinds []int) bool {

	// 数字没了
	if len(nums) == 0 {
		if len(kinds) == 0 { // 类型也没了，说明覆盖全了
			return true
		}
		return false
	}

	if containsElement(triangle, nums[0]) {
		// remove 3 from kinds
		kindsCopy := removeElementFromSlice(kinds, 3)
		if containsAllKinds(nums[1:], kindsCopy) {
			return true
		}
	}

	if containsElement(square, nums[0]) {
		// remove 4 from kinds
		kindsCopy := removeElementFromSlice(kinds, 4)
		if containsAllKinds(nums[1:], kindsCopy) {
			return true
		}
	}

	if containsElement(pentagonal, nums[0]) {
		// remove 5 from kinds
		kindsCopy := removeElementFromSlice(kinds, 5)
		if containsAllKinds(nums[1:], kindsCopy) {
			return true
		}
	}

	if containsElement(hexagonal, nums[0]) {
		// remove 6 from kinds
		kindsCopy := removeElementFromSlice(kinds, 6)
		if containsAllKinds(nums[1:], kindsCopy) {
			return true
		}
	}

	if containsElement(heptagonal, nums[0]) {
		// remove 7 from kinds
		kindsCopy := removeElementFromSlice(kinds, 7)
		if containsAllKinds(nums[1:], kindsCopy) {
			return true
		}
	}

	if containsElement(octagonal, nums[0]) {
		// remove 8 from kinds
		kindsCopy := removeElementFromSlice(kinds, 8)
		if containsAllKinds(nums[1:], kindsCopy) {
			return true
		}
	}

	return false
}

func getNumbers(expression func(n int) int) []int {
	var numbers []int
	for n := 1; ; n++ {
		v := expression(n)
		if v >= 1000 && v <= 9999 {
			numbers = append(numbers, v)
		}
		if v >= 10000 {
			break
		}
	}
	return numbers
}

func main() {

	// 找到所有所有4位的三角形数、四边形数，五边形数，六边形数，七边形数，八边形数，
	// 存放到 triangle, square, pentagonal, hexagonal, heptagonal, octagonal 中

	// 三角形数 n(n+1)/2
	triangle = getNumbers(func(n int) int {
		return n * (n + 1) / 2
	})

	// 四边形数 n^2
	square = getNumbers(func(n int) int {
		return n * n
	})

	// 五边形数 n(3n−1)/2
	pentagonal = getNumbers(func(n int) int {
		return n * (3*n - 1) / 2
	})

	// 六边形数 n(2n−1)
	hexagonal = getNumbers(func(n int) int {
		return n * (2*n - 1)
	})

	// 七边形数 n(5n−3)/2
	heptagonal = getNumbers(func(n int) int {
		return n * (5*n - 3) / 2
	})

	// 八边形数 n(3n−2)
	octagonal = getNumbers(func(n int) int {
		return n * (3*n - 2)
	})

	// 保存所有类型的数并去重
	mapNumbers := make(map[int]struct{}, 0) // 使用map去重
	for _, n := range triangle {
		mapNumbers[n] = struct{}{}
	}
	for _, n := range square {
		mapNumbers[n] = struct{}{}
	}
	for _, n := range pentagonal {
		mapNumbers[n] = struct{}{}
	}
	for _, n := range hexagonal {
		mapNumbers[n] = struct{}{}
	}
	for _, n := range heptagonal {
		mapNumbers[n] = struct{}{}
	}
	for _, n := range octagonal {
		mapNumbers[n] = struct{}{}
	}

	var all []int
	for k := range mapNumbers {
		all = append(all, k)
	}

	// 将所有的数从小到大排序，用于后面的遍历
	sort.Slice(all, func(i, j int) bool {
		return all[i] < all[j]
	})

	// 假设 6个数依次为 : x1,x2,x3,x4,x5,x6
	// 遍历寻找答案
	for _, x1 := range all {
		// 找到所有以 x1 后两位开头的数即可能的 x2 集合
		last2bitOfx1 := (fmt.Sprintf("%v", x1))[2:4]

		var possiblex2 []int
		for _, x2 := range all {
			first2bitOfx2 := (fmt.Sprintf("%v", x2))[0:2]
			if last2bitOfx1 == first2bitOfx2 {
				possiblex2 = append(possiblex2, x2)
			}
		}

		for _, x2 := range possiblex2 {
			// 找到所有以 x2 后两位开头的数，即可能的 x3 集合
			last2bitOfx2 := (fmt.Sprintf("%v", x2))[2:4]

			var possiblex3 []int
			for _, x3 := range all {
				first2bitOfx3 := (fmt.Sprintf("%v", x3))[0:2]
				if last2bitOfx2 == first2bitOfx3 {
					possiblex3 = append(possiblex3, x3)
				}
			}

			for _, x3 := range possiblex3 {
				// 找到所有以 x3 后两位开头的数，即可能的 x4 集合
				last2bitOfx3 := (fmt.Sprintf("%v", x3))[2:4]

				var possiblex4 []int
				for _, x4 := range all {
					first2bitOfx4 := (fmt.Sprintf("%v", x4))[0:2]
					if last2bitOfx3 == first2bitOfx4 {
						possiblex4 = append(possiblex4, x4)
					}
				}

				for _, x4 := range possiblex4 {
					// 找到所有以 x4 后两位开头的数，即可能的 x5 集合
					last2bitOfx4 := (fmt.Sprintf("%v", x4))[2:4]

					var possiblex5 []int
					for _, x5 := range all {
						first2bitOfx5 := (fmt.Sprintf("%v", x5))[0:2]
						if last2bitOfx4 == first2bitOfx5 {
							possiblex5 = append(possiblex5, x5)
						}
					}

					for _, x5 := range possiblex5 {
						// 找到所有以 x5 后两位开头的数，即可能的 x6 集合
						last2bitOfx5 := (fmt.Sprintf("%v", x5))[2:4]

						var possiblex6 []int
						for _, x6 := range all {
							first2bitOfx6 := (fmt.Sprintf("%v", x6))[0:2]
							if last2bitOfx5 == first2bitOfx6 {
								possiblex6 = append(possiblex6, x6)
							}
						}

						for _, x6 := range possiblex6 {
							// 判断 x6 的后两位，是否是x1 的前两位，如果是，则满足了循环的要求
							first2bitOfx1 := (fmt.Sprintf("%v", x1))[0:2]
							last2bitOfx6 := (fmt.Sprintf("%v", x6))[2:4]
							if first2bitOfx1 != last2bitOfx6 {
								continue
							}

							nums := []int{x1, x2, x3, x4, x5, x6}

							// 不能有重复数字
							mapNums := make(map[int]struct{}, 0)
							for _, n := range nums {
								mapNums[n] = struct{}{}
							}

							if len(mapNums) != len(nums) {
								continue
							}

							// 判断 x1,x2,x3,x4,x5,x6 是否满足分别是三角形数... 八边形数都存在
							if containsAllKinds(nums, []int{3, 4, 5, 6, 7, 8}) {
								fmt.Println(x1, x2, x3, x4, x5, x6, "sum:", x1+x2+x3+x4+x5+x6)
							}
						}
					}
				}
			}
		}
	}

}

```

## 答案

28684

6个数为：1281 8128 2882 8256 5625 2512