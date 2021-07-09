# Problem 41: Pandigital prime

> https://projecteuler.net/problem=41

We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.

What is the largest n-digit pandigital prime that exists?


## 分析

如果一个 n 位的数，它只包含 1~n n个数字，那么它被称为 pandigital，如 2143 是一个 4 位的pandigital. 找到最大的pandigital，并且它是质数。

n 最大为9，所以最大的 pandigital 是 987654321。只需要从 987654321 往下遍历，判断每个数是否是 pandigital 并且 是质数，找到则返回。

问题的核心有两个：(1) 判断质数，之前已经实现过很多次了，可以直接复用；(2) 判断一个数是否是 pandigital，其实之前也实现过。

## 方法1 遍历求解

只需要从 987654321 往下遍历，判断每个数是否是 pandigital 并且 是质数，找到则返回。
这种方法实际速度特别慢，故只提供 C/C++ 的版本实现，golang/python 不适用。


```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isPrime(int n)
{
    if(n <= 1 ) return false;
    if(n == 2 || n == 3) return true;
    if(n % 2 == 0) return false;

    // 关于质数分布的规律：大于等于5的质数一定和6的倍数相邻
    // 即大于等于5的质数一定是 6x-1 和 6x+1，6x+2 ~ 6x+4 一定不是质数
    // 即大于等于5的质数一定满足 n%6==1 or n%6==5
    // https://blog.csdn.net/songyunli1111/article/details/78690447
    if(n % 6 != 1 && n % 6 != 5 ) return false;

    // 从 [5, sqrt(n)] 遍历寻找是否是其因数
    for(int i=5; i * i <= n; i++){
        if( n % i == 0 ) return false;
    }
    return true;
}

bool isPanDigital(int n)
{
    // 拆分n的每一位数字
    int digits[32] = {0}; // 保存 n 的每一位数字
    int unique[32] = {0}; // 保存 n 的每一位数字，去重
    int lenD= 0;  // 保存 digits 的长度
    int lenU = 0; // 保存 unique 的长度

    while(n > 0){
        int v = n % 10;
        if(v == 0) return false; // 不能包含数字 0
        digits[lenD ++] = v;
        n /= 10;

        // 去重保存
        for(int i = 0; i < 32; i++){
            if(unique[i] == v) break; // 已存在，不用重复存储
            if(unique[i] == 0) { // 找到空位置，存放
                unique[i] = v;
                lenU ++;
                break;
            }
        }
    }

    return lenD == lenU;
}

int main()
{
    for(int i = 987654321; i > 0; i = i-2 ){
        if(isPrime(i) && isPanDigital(i)){
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}
```


## 方法2 全排列

实际上一个pandigital 就是 n 个数字的全排列。所以，我们只要依次获取 n 个数字的全排列，然后判断是否是质数即可。

### CPP

使用 std::prev_permutation 来获取全排列中的上一个排列，再将排列转换为 int ，判断是否是质数。
速度很快。

```cpp
#include <iostream>
#include <algorithm>

bool isPrime(int n)
{
    if(n <= 1 ) return false;
    if(n == 2 || n == 3) return true;
    if(n % 2 == 0) return false;

    // 关于质数分布的规律：大于等于5的质数一定和6的倍数相邻
    // 即大于等于5的质数一定是 6x-1 和 6x+1，6x+2 ~ 6x+4 一定不是质数
    // 即大于等于5的质数一定满足 n%6==1 or n%6==5
    // https://blog.csdn.net/songyunli1111/article/details/78690447
    if(n % 6 != 1 && n % 6 != 5 ) return false;

    // 从 [5, sqrt(n)] 遍历寻找是否是其因数
    for(int i=5; i * i <= n; i++){
        if( n % i == 0 ) return false;
    }
    return true;
}

int main()
{
    char digits[] = {'9','8','7','6','5','4','3','2','1'};

    for(int n = 9; n >= 1; n--){

        // 获取 n 全排列的最大数
        char digitsN[10] = {0}; // {'9','8','7','6','5','4','3','2','1'}，{'8','7','6','5','4','3','2','1'}... {'1'}
        for(int i = 0; i < n; i++){
            digitsN[i] = digits[i+9-n];
        }

        // 依次取全排列的上一个序列，判断是否满足条件
        do{
            int v = atoi(digitsN);
            if(isPrime(v)){
                printf("%d\n", v);
                return 0;
            }
        }while(std::prev_permutation(digitsN, digitsN + n));
    }
    return 0;
}
```

### Golang

golang 中没有 prev_permutation 和 next_permutation，需要手动实现。


```go
package main

import (
	"fmt"
	"strconv"
)

func isPrime(n int64) bool {
	if n <= 1 {
		return false
	}

	if n == 2 || n == 3 {
		return true
	}

	if n % 2 == 0 {
		return false
	}

	// 关于质数分布的规律：大于等于5的质数一定和6的倍数相邻
	// 即大于等于5的质数一定是 6x-1 和 6x+1，6x+2 ~ 6x+4 一定不是质数
	// 即大于等于5的质数一定满足 n%6==1 or n%6==5
	// https://blog.csdn.net/songyunli1111/article/details/78690447
	if n % 6 != 1 && n % 6 != 5 {
		return false
	}

	// 从 [5, sqrt(n)] 遍历寻找是否是其因数
	for i:=int64(5); i * i <= n; i++ {
		if n % i == 0 {
			return false
		}
	}

	return true
}

// 获取perm的上一个序列
// std::prev_permutation
func prevPermutation(perm []int32) bool {
	// 长度不超过1，直接返回
	if len(perm) <= 1 {
		return false
	}

	// 从后往前，找到第一个 perm[i] > perm[i+1]
	// e.g perm=1238[64]57, perm[i]=6
	i := -1
	for i = len(perm)-2; i >=0; i-- {
		if perm[i] > perm[i+1] {
			break
		}
	}

	// 找不到，说明整个 perm 是递增的，已是最小，没有prev
	if i == -1 {
		return false
	}

	// 从后往前 [末尾, i+1]，找到第一个比 perm[i] 小的数，然后交换
	// e.g. perm=1238[6]4[5]7, 交换 6 和 5
	for k := len(perm)-1; k >= i+1; k-- {
		if perm[k] < perm[i] {
			// 交换 perm[k] 和 perm[i]
			perm[k], perm[i] = perm[i], perm[k] // golang 支持这样交换
			break
		}
	}

	// i+1 到末尾目前是升序的，改为降序
	// e.g perm=12385[467] => perm=12385[764]
	for k := i+1; k < len(perm); k ++ {
		last :=  len(perm) + i - k
		if k >= last {
			break
		}

		// 交换 perm[k] 和 perm[last]
		perm[k], perm[last] = perm[last], perm[k] // golang 支持这样交换
	}

	return true
}

// 获取perm的下一个序列
// std::next_permutation
// 未使用
func nextPermutation(perm []int32) bool {
	// 长度不超过1，直接返回
	if len(perm) <= 1 {
		return false
	}

	// 从后往前，找到第一个 perm[i] < perm[i+1]
	// e.g perm=1238[57]64, perm[i]=5
	i := -1
	for i = len(perm)-2; i >=0; i-- {
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
	for k := len(perm)-1; k >= i+1; k-- {
		if perm[k] > perm[i] {
			// 交换 perm[k] 和 perm[i]
			perm[k], perm[i] = perm[i], perm[k] // golang 支持这样交换
			break;
		}
	}

	// i+1 到末尾目前是降序的，改为升序
	// e.g perm=12386[754] => perm=12386[457]
	for k := i+1; k < len(perm); k ++ {
		last :=  len(perm) + i - k
		if k >= last {
			break
		}

		// 交换 perm[k] 和 perm[last]
		perm[k], perm[last] = perm[last], perm[k] // golang 支持这样交换
	}

	return true
}

func main() {

	digits := []int32{'9','8','7','6','5','4','3','2','1'}

	for n := 9; n >= 1; n-- {

		// 获取 n 全排列的最大数
		var digitsN []int32 // {'9','8','7','6','5','4','3','2','1'}，{'8','7','6','5','4','3','2','1'}... {'1'}
		for i := 0; i < n; i++{
			digitsN = append(digitsN, digits[9-n+i])
		}

		// 依次取全排列的上一个序列，判断是否满足条件
		for {
			s := string(digitsN)
			v, _ := strconv.ParseInt(s, 10, 32)

			if isPrime(v) {
				fmt.Println(v)
				return
			}

			if !prevPermutation(digitsN) {
				break
			}
		}
	}
}

```

参考：[下一个排列算法详解：思路+推导+步骤，看不懂算我输！](https://leetcode-cn.com/problems/next-permutation/solution/xia-yi-ge-pai-lie-suan-fa-xiang-jie-si-lu-tui-dao-/)

### Python

python 中没有 prev_permutation，需要手动实现。

```python
import math

def isPrime(n): 
    if n <= 1 : return False
    if n == 2 or n == 3 : return True
    if n % 2 == 0 : return False

    # 关于质数分布的规律：大于等于5的质数一定和6的倍数相邻
    # 即大于等于5的质数一定是 6x-1 和 6x+1，6x+2 ~ 6x+4 一定不是质数
    # 即大于等于5的质数一定满足 n%6==1 or n%6==5
    # https://blog.csdn.net/songyunli1111/article/details/78690447
    if n % 6 != 1 and n % 6 != 5 : return False

    # 从 [5, sqrt(n)] 遍历寻找是否是其因数
    for i in range(5, int(math.sqrt(n)) + 1):
        if n % i == 0 : return False

    return True

# 获取perm的上一个序列
# std::prev_permutation
def prevPermutation(perm) :
	# 长度不超过1，直接返回
	if len(perm) <= 1 :
		return False

	# 从后往前，找到第一个 perm[i] > perm[i+1]
	# e.g perm=1238[64]57, perm[i]=6
	i = len(perm) - 2
	while i >= 0 :
		if perm[i] > perm[i+1] :
			break
		i = i - 1

	# 找不到，说明整个 perm 是递增的，已是最小，没有prev
	if i == -1 :
		return False

	# 从后往前 [末尾, i+1]，找到第一个比 perm[i] 小的数，然后交换
	# e.g. perm=1238[6]4[5]7, 交换 6 和 5
	for k in range( len(perm)-1, i, -1) :
		if perm[k] < perm[i] :
			# 交换 perm[k] 和 perm[i]
			perm[k], perm[i] = perm[i], perm[k] # python 支持这样交换

	# i+1 到末尾目前是升序的，改为降序
	# e.g perm=12385[467] => perm=12385[764]
	for k in range(i+1, len(perm)) :
		last =  len(perm) + i - k
		if k >= last :
			break

		# 交换 perm[k] 和 perm[last]
		perm[k], perm[last] = perm[last], perm[k] # python 支持这样交换

	return True

digits = ['9','8','7','6','5','4','3','2','1']

for n in range(9, 0, -1):

	# 获取 n 全排列的最大数
	digitsN = [] # {'9','8','7','6','5','4','3','2','1'}，{'8','7','6','5','4','3','2','1'}... {'1'}
	for i in range(0,n) :
		digitsN.append(digits[9-n+i])

	# 依次取全排列的上一个序列，判断是否满足条件
	while True :
		v = int(''.join(digitsN))
		if isPrime(v) :
			print(v)
			exit(0)

		if not prevPermutation(digitsN) :
			break
```

## 答案

7652413

## 知识点

- [全排列](https://leetcode-cn.com/problems/next-permutation/solution/xia-yi-ge-pai-lie-suan-fa-xiang-jie-si-lu-tui-dao-/)