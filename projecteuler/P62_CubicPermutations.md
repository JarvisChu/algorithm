# Problem 62: Cubic permutations

> https://projecteuler.net/problem=62

The cube, 41063625 (345<sup>3</sup>), can be permuted to produce two other cubes: 56623104 (384<sup>3</sup>) and 66430125 (405<sup>3</sup>). In fact, 41063625 is the smallest cube which has exactly three permutations of its digits which are also cube.

Find the smallest cube for which exactly five permutations of its digits are cube.

## 分析

41063625（345 的立方）可以排列（即数字重组）出 56623104 (384的立方) 和 66430125 (405的立方)

事实上，41063625 是最小的、可以排列出3个立方数的立方数。

找到最小的立方数，它通过数字重排列可以得到 5 个立方数。

## 方法 按位数遍历

一个数对应的排列的位数，肯定和它的位数相等，即8位数的排列，必然也是8位数
我们从1位数开始，先找到所有位数为 1 的立方数，判断其中是否有5个立方数包含的数字相同，如果有则输出，结束。如果没有，则继续判断2位数。依次类推，直到结束。

这里的关键在于：如何判断一组数中，有5个数包含的数字相同，并且获取这5个数。方法如下：

(1) 先将所有数，分解成数字，然后将数字从小到大排序重组，得到新的一组字符串。比如 41063625 转换成 '01234566'
(2) 再对新的一组字符串做排序，这样包含的数字相同的数就排到了一起
(3) 再遍历排序后的这组字符串，找到重复了5次字符串
(4) 如果找到了满足条件的字符串 S ，说明本组中存在5个数，包含的数字完全相同。那么再遍历依次这组数，和(1) 一样分解排序重组后得到的字符串，如果和 S 相等，则满足条件，保存。最后输出所有保存的数即可

### Python

```python
# 一个数对应的排列的位数，肯定和它的位数相等，即8位数的排列，必然也是8位数
# 那么我们就从1位数开始，找到所有位数相同的立方数，然后尝试从中找5个立方数的数字相同的数

lastLen = 0
cubes = [] # 存放所有位数相同的立方数
i = 1
while True :
    cube = i**3
    if len(str(cube)) > lastLen : # 位数增加
        lastLen = len(str(cube))   

        # 至此，cubes 中已经保存了所有位数为 lastLen 的立方数    
        # 再判断 cubes 中是否存在 5 个数，它们包含的数字相同

        # (1) 先将所有数，分解成数字，然后将数字从小到大重组，得到新的一组字符串。比如 41063625 转换成 '01234566'
        cubes_str = [ ''.join(sorted(list(str(n)))) for n in cubes]

        # (2) 再对这组字符串做排序，这样包含的数字相同的数就排到了一起
        cubes_str = sorted(cubes_str)

        # (3) 再遍历排序后的这组字符串，找到出现了5次字符串
        repeatedCnt = 0
        lastStr = 0
        for n in cubes_str :
            if n == lastStr :
                repeatedCnt += 1
                if repeatedCnt == 4 : # 重复了4次，加上自己，共出现5次
                    answer = [ c for c in cubes  if ''.join(sorted(list(str(c)))) == lastStr ]
                    print(answer)
                    exit(0)
            else:
                lastStr = n
                repeatedCnt = 0
        # 重置 cubes
        cubes = []
    cubes.append(cube)
    i += 1
```

### Golang

```go
package main

import (
	"fmt"
	"sort"
	"strings"
)

// 将n分解成数字，然后将数字从小到大重组，得到新的一组字符串。
// 如 n = 41063625，返回 '01234566'
func sortNumber(n int64) string {

	// 分解
	str := fmt.Sprintf("%v", n)
	var digits []string
	for _, c := range str {
		digits = append(digits, fmt.Sprintf("%v", c-48))
	}

	// 排序
	sort.Slice(digits, func(i, j int) bool {
		return digits[i] < digits[j]
	})

	// 重组
	return strings.Join(digits, "")
}

func main() {

	// 一个数对应的排列的位数，肯定和它的位数相等，即8位数的排列，必然也是8位数
	// 那么我们就从1位数开始，找到所有位数相同的立方数，然后尝试从中找5个立方数的数字相同的数

	lastLen := 0
	var cubes []int64 // 存放所有位数相同的立方数
	for i := int64(1); ; i++ {
		cube := i * i * i
		cubeStr := fmt.Sprintf("%v", cube)
		if len(cubeStr) > lastLen { // 位数增加
			lastLen = len(cubeStr)

			// 至此，cubes 中已经保存了所有位数为 lastLen 的立方数 
			// 再判断 cubes 中是否存在 5 个数，它们包含的数字相同

			// (1) 先将所有数，分解成数字，然后将数字从小到大重组，得到新的一组字符串。比如 41063625 转换成 '01234566'
			var cubesStr []string
			for _, c := range cubes {
				// e.g. c = 41063625 转换成 '01234566'，存放到 cubesStr 中
				cubesStr = append(cubesStr, sortNumber(c))
			}

			// (2) 再对这组字符串做排序，这样包含的数字相同的数就排到了一起
			sort.Slice(cubesStr, func(i, j int) bool {
				return cubesStr[i] < cubesStr[j]
			})

			// (3) 再遍历排序后的这组字符串，找到出现了5次字符串
			repeatedCnt, lastStr := 0, ""
			for _, s := range cubesStr {
				if s == lastStr {
					repeatedCnt++
					if repeatedCnt == 4 { // 重复了4次，加上自己，共出现5次
						var answer []int64
						for _, c := range cubes {
							if sortNumber(c) == lastStr {
								answer = append(answer, c)
							}
						}

						fmt.Println(answer)
						return
					}
				} else {
					repeatedCnt = 0
					lastStr = s
				}
			}

			// 重置 cubes
			cubes = []int64{}

		} else {
			// 位数没有增加，继续添加
			cubes = append(cubes, cube)
		}
	}
}
```

## 答案

127035954683

这5个数为：127035954683, 352045367981, 373559126408, 569310543872, 589323567104