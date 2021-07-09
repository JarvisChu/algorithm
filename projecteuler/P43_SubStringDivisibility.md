# Problem 43: Sub-string divisibility

> https://projecteuler.net/problem=43

The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.

Let d<sub>1</sub> be the 1<sup>st</sup> digit, d<sub>2</sub> be the 2<sup>nd</sup> digit, and so on. In this way, we note the following:

- d<sub>2</sub>d<sub>3</sub>d<sub>4</sub>=406 is divisible by 2
- d<sub>3</sub>d<sub>4</sub>d<sub>5</sub>=063 is divisible by 3
- d<sub>4</sub>d<sub>5</sub>d<sub>6</sub>=635 is divisible by 5
- d<sub>5</sub>d<sub>6</sub>d<sub>7</sub>=357 is divisible by 7
- d<sub>6</sub>d<sub>7</sub>d<sub>8</sub>=572 is divisible by 11
- d<sub>7</sub>d<sub>8</sub>d<sub>9</sub>=728 is divisible by 13
- d<sub>8</sub>d<sub>9</sub>d<sub>10</sub>=289 is divisible by 17


Find the sum of all 0 to 9 pandigital numbers with this property.

## 分析

1406357289 是 0~9 的一个pandigital, 因为它包含了0~9的所有数字。它还有个属性，就是 234位数字能被2整除，234位数字能被3整除，... 8910位数字能被 17 整除。求所有满足这个属性的 0~9 的 pandigital 的和。

本题的核心仍是全排列问题，和 [Problem 41 PandigitalPrime](http://zhujiangtao.com/problem-41-pandigital-prime/) 类似，可复用其中的算法。

## 方法 全排列

得到 0~9 的全排列，依次判断是否满足上面的条件，满足则加到sum


### CPP

使用std::next_permutation 获取全排列的下一个序列，使用 atol 将排列转为整数

```cpp
#include <iostream>
#include <algorithm>
#include <cstdint>

int main()
{
    int64_t sum = 0;
    char digits[] = {'1','0','2','3','4','5','6','7','8','9', 0}; // '0' 不能放在开头, 最后的 0 用于转字符串

    do{
        // 判断 digits 是否满足属性
        int d234 = (digits[1] - '0') * 100 + (digits[2] - '0') * 10 + (digits[3] - '0');
        if(d234 % 2 != 0) continue;

        int d345 = (digits[2] - '0') * 100 + (digits[3] - '0') * 10 + (digits[4] - '0');
        if(d345 % 3 != 0) continue;

        int d456 = (digits[3] - '0') * 100 + (digits[4] - '0') * 10 + (digits[5] - '0');
        if(d456 % 5 != 0) continue;

        int d567 = (digits[4] - '0') * 100 + (digits[5] - '0') * 10 + (digits[6] - '0');
        if(d567 % 7 != 0) continue;

        int d678 = (digits[5] - '0') * 100 + (digits[6] - '0') * 10 + (digits[7] - '0');
        if(d678 % 11 != 0) continue;

        int d789 = (digits[6] - '0') * 100 + (digits[7] - '0') * 10 + (digits[8] - '0');
        if(d789 % 13 != 0) continue;

        int d8910 = (digits[7] - '0') * 100 + (digits[8] - '0') * 10 + (digits[9] - '0');
        if(d8910 % 17 != 0) continue;

        // digits to string
        int64_t d = atol(digits);
        sum += d;

    }while(std::next_permutation(digits, digits+10));

    std::cout << sum << std::endl;
    return 0;
}
```

### Golang

复用  [Problem 41 PandigitalPrime](http://zhujiangtao.com/problem-41-pandigital-prime/) 中实现的 nextPermutation 获取全排列的下一个序列，使用 atol 将排列转为整数

```golang
package main

import (
	"fmt"
	"strconv"
)

// 获取perm的下一个序列
// std::next_permutation
func nextPermutation(perm []int32) bool {
	// 长度不超过1，直接返回
	if len(perm) <= 1 {
		return false
	}

	// 从后往前，找到第一个 perm[i] < perm[i+1]
	// e.g perm=1238[57]64, perm[i]=5
	i := -1
	for i = len(perm) - 2; i >= 0; i-- {
		if perm[i] < perm[i+1] {
			break
		}
	}

	// 找不到，说明整个 perm 是递减的，已是最大，没有next
	if i == -1 {
		return false
	}

	// 从后往前 [末尾, i+1]，找到第一个比 perm[i] 大的数，然后交换
	// e.g. perm=1238[5]7[6]4, 交换 5 和 6
	for k := len(perm) - 1; k >= i+1; k-- {
		if perm[k] > perm[i] {
			// 交换 perm[k] 和 perm[i]
			perm[k], perm[i] = perm[i], perm[k] // golang 支持这样交换
			break
		}
	}

	// i+1 到末尾目前是降序的，改为升序
	// e.g perm=12386[754] => perm=12386[457]
	for k := i + 1; k < len(perm); k++ {
		last := len(perm) + i - k
		if k >= last {
			break
		}

		// 交换 perm[k] 和 perm[last]
		perm[k], perm[last] = perm[last], perm[k] // golang 支持这样交换
	}

	return true
}

func main() {
	sum := int64(0)
	digits := []int32{'1', '0', '2', '3', '4', '5', '6', '7', '8', '9'} // '0' 不能放在开头

	// do while
	for ok := true; ok; ok = nextPermutation(digits) {
		// 判断 digits 是否满足属性
		d234 := (digits[1]-'0')*100 + (digits[2]-'0')*10 + (digits[3] - '0')
		if d234%2 != 0 {
			continue
		}

		d345 := (digits[2]-'0')*100 + (digits[3]-'0')*10 + (digits[4] - '0')
		if d345%3 != 0 {
			continue
		}

		d456 := (digits[3]-'0')*100 + (digits[4]-'0')*10 + (digits[5] - '0')
		if d456%5 != 0 {
			continue
		}

		d567 := (digits[4]-'0')*100 + (digits[5]-'0')*10 + (digits[6] - '0')
		if d567%7 != 0 {
			continue
		}

		d678 := (digits[5]-'0')*100 + (digits[6]-'0')*10 + (digits[7] - '0')
		if d678%11 != 0 {
			continue
		}

		d789 := (digits[6]-'0')*100 + (digits[7]-'0')*10 + (digits[8] - '0')
		if d789%13 != 0 {
			continue
		}

		d8910 := (digits[7]-'0')*100 + (digits[8]-'0')*10 + (digits[9] - '0')
		if d8910%17 != 0 {
			continue
		}

		// digits to string
		s := string(digits)
		i64, _ := strconv.ParseInt(s, 10, 64)
		sum += i64
		//fmt.Printf("%v\n", i64)
	}

	fmt.Println(sum)
}

```

### Python

实现 next_permutaion 算法

```python

# 获取perm的下一个序列
# std::next_permutation
def nextPermutation(perm) :
	# 长度不超过1，直接返回
	if len(perm) <= 1 :
		return False

	# 从后往前，找到第一个 perm[i] < perm[i+1]
	# e.g perm=1238[57]64, perm[i]=5
	i = len(perm) - 2
	while i >= 0 : 
		if perm[i] < perm[i+1] :
			break
		i = i - 1

	# 找不到，说明整个 perm 是递减的，已是最大，没有next
	if i == -1 :
		return False

	# 从后往前 [末尾, i+1]，找到第一个比 perm[i] 大的数，然后交换
	# e.g. perm=1238[5]7[6]4, 交换 5 和 6
	for k in range(len(perm) - 1, i, -1) :
		if perm[k] > perm[i] :
			# 交换 perm[k] 和 perm[i]
			perm[k], perm[i] = perm[i], perm[k] # python 支持这样交换
			break

	# i+1 到末尾目前是降序的，改为升序
	# e.g perm=12386[754] => perm=12386[457]
	for k in range(i + 1, len(perm)) :
		last = len(perm) + i - k
		if k >= last :
			break

		# 交换 perm[k] 和 perm[last]
		perm[k], perm[last] = perm[last], perm[k] # python 支持这样交换

	return True

sum = 0
digits = ['1', '0', '2', '3', '4', '5', '6', '7', '8', '9'] # '0' 不能放在开头

# do while
first = True
while True:
	if first :
		first = False
	else:
		if not nextPermutation(digits):
			break
	#print(digits)
	# 判断 digits 是否满足属性
	d234 = int(''.join(digits[1:4]))
	#print("d234", d234)
	if d234 % 2 != 0 :
		continue

	d345 = int(''.join(digits[2:5]))
	if d345%3 != 0 :
		continue

	d456 = int(''.join(digits[3:6]))
	if d456%5 != 0 :
		continue

	d567 = int(''.join(digits[4:7]))
	if d567%7 != 0 :
		continue

	d678 = int(''.join(digits[5:8]))
	if d678%11 != 0 :
		continue

	d789 = int(''.join(digits[6:9]))
	if d789%13 != 0 :
		continue

	d8910 = int(''.join(digits[7:10]))
	if d8910%17 != 0 :
		continue

	# digits to string
	s = ''.join(digits)
	n = int(s)
	sum += n
	print(n)

print(sum)
```

## 答案

16695334890

符合条件的数共6个，分别为: 1430952867,1406357289,1460357289,4130952867,4106357289,4160357289