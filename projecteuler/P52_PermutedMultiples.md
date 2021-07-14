# Problem 52: Permuted multiples

> https://projecteuler.net/problem=52

It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.

Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.

## 分析

找到最小的整数 x，满足 x, 2x, 3x, 4x, 5x, 6x 包含相同的数字

题目相对比较简单，可做简单的遍历即可。 但是为了提高遍历的效率，我们不用遍历每一个数。

## 方法 遍历求解

从 x = 11 往上遍历，对于每一个 x，做如下处理：

- (1) 判断 x 和 6x 的位数是否相同；如果不相同跳转到 (2)，如果相同跳转到 (3)
- (2) 不相等时，在 x 位数不变的情况下，随着 x 的增大，两者更不可能相等, 所以，此时需要给 x 增加位数。 如 x = 17，6x = 102，此时 18~99 都可以直接跳过了，直接跳到下一个位数的起始点 x = 100。 增加位数后，再跳转会(1)
- (3) 依次获取 x, 2x, 3x, 4x, 5x, 6x 的所有排序好的数字列表，判断是否都相等，如果全都相等，则找到了答案，输出，结束。 如果不全相等，x++ 继续 步骤 (1)。

###

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int getLen(int n)
{
    int len = 0;
    while(n > 0){
        len++;
        n /= 10;
    }

    return len;
}

std::vector<int> getDigitsSorted(int n)
{
    std::vector<int> digits;
    while(n > 0){
        digits.push_back(n % 10);
        n /= 10;
    }
    std::sort(digits.begin(), digits.end());

    return digits;
}

bool hasSameDigits(const std::vector<int>& v1, const std::vector<int>& v2)
{
    if(v1.size() != v2.size()) return false;

    for(int i = 0; i < v1.size(); i++){
        if( v1[i] != v2[i]) return false;
    }

    return true;
}

int main()
{
    int x = 11;
    while(true){
        // 判断 x 和 6x 的位数是否相等
        int lenX = getLen(x);
        int len6X = getLen(6*x);

        // 如果不相等，在 x 位数不变的情况下，随着 x 的增大，两者更不可能相等
        // 所以，此时需要给 x 增加位数
        // 如， x = 17，6x = 102，此时 18~99 都可以直接跳过了，直接跳到下一个位数的起始点 x = 100，再继续处理
        if(len6X > lenX){
            x = (int) pow(10, lenX) ;
            continue;
        }

        // 如果相等，继续判断 x, 2x, 3x, 4x, 5x, 6x 是否包含相同的数字

        // 获取 x 的所有数字
        std::vector<int> digitsX = getDigitsSorted(x);

        bool bHasSameDigits = true;
        for(int i = 2; i <= 6; i++){
            // 获取 i*x 的所有数字
            std::vector<int> digitsIX= getDigitsSorted(i*x);
            if( ! hasSameDigits(digitsX, digitsIX)){
                bHasSameDigits = false;
                break;
            }
        }

        // 找到了一个满足条件的解
        if(bHasSameDigits){
            printf("find answer: %d, %d, %d, %d, %d, %d\n", x, 2*x,3*x, 4*x, 5*x, 6*x);
            return 0;
        }

        // 继续查找下一个数
        x++;
    }

    return 0;
}
```

### Golang

```go
package main

import (
	"fmt"
	"math"
	"sort"
)

func getDigitsSorted(n int) []int {
	var digits []int
	for n > 0 {
		digits = append(digits, n%10)
		n /= 10
	}

	sort.Slice(digits, func(i, j int) bool {
		return digits[i] < digits[j]
	})

	return digits
}

func hasSameDigits(v1, v2 []int) bool {

	if len(v1) != len(v2) {
		return false
	}

	for i := 0; i < len(v1); i++ {
		if v1[i] != v2[i] {
			return false
		}
	}

	return true
}

func main() {
	x := 11
	for {
		// 判断 x 和 6x 的位数是否相等
		lenX := len(fmt.Sprintf("%d", x))
		len6X := len(fmt.Sprintf("%d", 6*x))

		// 如果不相等，在 x 位数不变的情况下，随着 x 的增大，两者更不可能相等
		// 所以，此时需要给 x 增加位数
		// 如， x = 17，6x = 102，此时 18~99 都可以直接跳过了，直接跳到下一个位数的起始点 x = 100，再继续处理
		if len6X > lenX {
			x = int(math.Pow(10, float64(lenX)))
			continue
		}

		// 如果相等，继续判断 x, 2x, 3x, 4x, 5x, 6x 是否包含相同的数字

		// 获取 x 的所有数字
		digitsX := getDigitsSorted(x)

		bHasSameDigits := true
		for i := 2; i <= 6; i++ {
			// 获取 i*x 的所有数字
			digitsIX := getDigitsSorted(i * x)

			if !hasSameDigits(digitsX, digitsIX) {
				bHasSameDigits = false
				break
			}
		}

		// 找到了一个满足条件的解
		if bHasSameDigits {
			fmt.Printf("find answer: %d, %d, %d, %d, %d, %d\n", x, 2*x, 3*x, 4*x, 5*x, 6*x)
			return
		}

		// 继续查找下一个数
		x++
	}
}

```

### Python

```python
x = int(11)

while True:
    # 判断 x 和 6x 的位数是否相等
    lenX = len(str(x))
    len6X = len(str(6*x))

    # 如果不相等，在 x 位数不变的情况下，随着 x 的增大，两者更不可能相等
    # 所以，此时需要给 x 增加位数
    # 如， x = 17，6x = 102，此时 18~99 都可以直接跳过了，直接跳到下一个位数的起始点 x = 100，再继续处理
    if len6X > lenX :
        x = 10**lenX
        continue
    
    # 如果相等，继续判断 x, 2x, 3x, 4x, 5x, 6x 是否包含相同的数字
    # 获取 x 的所有数字
    digitsX = list(str(x))
    digitsX.sort()

    bHasSameDigits = True
    for i in range(1,7):
        # 获取 i*x 的所有数字
        digitsIX = list(str(i*x))
        digitsIX.sort()
        
        if digitsX != digitsIX :
            bHasSameDigits = False
            break

    # 找到了一个满足条件的解
    if bHasSameDigits :
        print("find answer: ", x, 2*x, 3*x, 4*x, 5*x, 6*x)
        exit(0)
    
    # 继续查找下一个数
    x = x + 1
```

## 答案

142857

find answer: 142857, 285714, 428571, 571428, 714285, 857142