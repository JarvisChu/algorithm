# Problem 35: Circular primes

> https://projecteuler.net/problem=35

The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

How many circular primes are there below one million?

## 分析

一个数，它本身是质数，各位经过旋转后也是质数，求1,000,000以下满足这种条件的数的个数。

## 方法 

问题的核心是，如果对数进行右旋。对于一个数，一次右旋相当于将最低位的数字放到了最高位。

右旋一位的方法有两种：

- 1. [使用纯数字计算的方法] 通过不断 n /= 10 来获取n的位数 len ，通过 a = n % 10 获取最低位数字，然后再将最低位数字 a *= pow(10,len-1)，放到最高位。
- 2. [使用字符串的方法] 将 n 转换为字符串，使用字符串完成右移一位，再转换回数字

从 1~1000000 进行遍历，对每个数进行右移，判断是否满足条件。

**这里有两个提升算法效率的方法：**

(1) 如果 n 的所有位中包含 **偶数数字**，即 0,2,4,6,8 则 **必然不会满足条件**， 因为当这些数字被右移到最低位时，必然不是质数。[n > 2]
(2) 可以先将所有的质数保存到set中，这样只需要通过查表的方式来判断质数，这在 n 很大时会提高效率。 对于本题的规模(<= 1000000)，也可以不用该方法。


### CPP

使用纯数字计算的方法做右移

```cpp
#include <stdio.h>
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

// 判断 n 是否是循环质数
// 即 n 循环右移后的每一个数，是否都是质数
bool isCircularPrimes(int n)
{
    // 特殊处理 2
    if(n == 2) return true;

    if( ! isPrime(n) ) return false;

    // 获取 n 的长度
    int len = 0;
    int cpy = n;
    while(cpy > 0){
        int v = cpy % 10; // 最低位数字
        if (v % 2 == 0) return false; // 最低位数字为偶数时，必然不满足条件

        cpy /= 10;
        len ++;
    }

    // 对 n 做 len-1 次右移，判断每次右移的结果是否是质数
    for(int i = 0; i < len-1; i++){

        // 对 n 做一次右移
        int lowestBit = n % 10;  // (1) 获取 n 的个位上的数字
        n /= 10;                 // (2) 右移一位

        int highest = lowestBit; // (3) 将个位上的数字，补到最高位上; n += highest * pow(10,len-1)
        for(int k=len-1; k>0; k--){
            highest *= 10;
        }
        n += highest;

        // 判断 n 是否是质数
        if( !isPrime(n)) return false;
    }

    return true;
}

int main()
{
    int cnt = 0; 
    for(int i = 0; i < 1000000; i++){
        if(isCircularPrimes(i)) {
            printf("%d\n", i);
            cnt ++;
        }
    }

    printf("cnt:%d\n", cnt);
    return 0;
}
```

使用字符串的方法

```cpp
// 判断 n 是否是循环质数
// 即 n 循环右移后的每一个数，是否都是质数
bool isCircularPrimes(int n)
{
    // 特殊处理 2
    if(n == 2) return true;

    if( ! isPrime(n) ) return false;

    // 将 n 转换成 string
    char buf[32] = {0};
    snprintf(buf,32,"%d", n);
    int len = strlen(buf);

    // 如果 n 的所有位中包含 偶数数字，则必然不满足条件
    for(int i = 0; i < len; i++){
        if(buf[i] == '0' || buf[i] == '2' || buf[i] == '4' || buf[i] == '6' || buf[i] == '8') return false;
    }

    // 不断右移 len-1 次，判断每次右移的结果是否是质数
    for(int i = 0; i < len-1; i++){

        // 对 buf 右移一位
        char lowestBit = buf[len-1];
        for(int k = len-2; k >= 0; k--){
            buf[k+1] = buf[k];
        }
        buf[0] = lowestBit;

        // 将 buf 转换为 int
        int v = atoi(buf);
        if( ! isPrime(v) ) return false;
    }

    return true;
}
```

### Golang

使用 `buf = buf[len-1:len] + buf[0:len-1]` 进行右移操作，其它同 C++ 版本

```go
package main

import (
	"fmt"
	"strconv"
)

func isPrime(n int) bool {
	if n <= 1 {
		return false
	}

	if n == 2 || n == 3 {
		return true
	}

	if n%2 == 0 {
		return false
	}

	// 关于质数分布的规律：大于等于5的质数一定和6的倍数相邻
	// 即大于等于5的质数一定是 6x-1 和 6x+1，6x+2 ~ 6x+4 一定不是质数
	// 即大于等于5的质数一定满足 n%6==1 or n%6==5
	// https://blog.csdn.net/songyunli1111/article/details/78690447
	if n%6 != 1 && n%6 != 5 {
		return false
	}

	// 从 [5, sqrt(n)] 遍历寻找是否是其因数
	for i := 5; i*i <= n; i++ {
		if n%i == 0 {
			return false
		}
	}

	return true
}

// 判断 n 是否是循环质数
// 即 n 循环右移后的每一个数，是否都是质数
func isCircularPrimes(n int) bool {
	// 特殊处理 2
	if n == 2 {
		return true
	}

	if !isPrime(n) {
		return false
	}

	// 获取 n 的长度
	len, cpy := 0, n
	for cpy > 0 {
		v := cpy % 10 // 最低位数字
		if v%2 == 0 { // 最低位数字为偶数时，必然不满足条件
			return false
		}

		cpy /= 10
		len++
	}

	// 对 n 做 len-1 次右移，判断每次右移的结果是否是质数
	for i := 0; i < len-1; i++ {

		// 对 n 做一次右移
		lowestBit := n % 10 // (1) 获取 n 的个位上的数字
		n /= 10             // (2) 右移一位

		highest := lowestBit // (3) 将个位上的数字，补到最高位上; n += highest * pow(10,len-1)
		for k := len - 1; k > 0; k-- {
			highest *= 10
		}
		n += highest

		// 判断 n 是否是质数
		if !isPrime(n) {
			return false
		}
	}

	return true
}

// 判断 n 是否是循环质数
// 即 n 循环右移后的每一个数，是否都是质数
func isCircularPrimes1(n int) bool {

	// 特殊处理 2
	if n == 2 {
		return true
	}

	if !isPrime(n) {
		return false
	}

	// 将 n 转换成 string
	buf := fmt.Sprintf("%d", n)
	len := len(buf)

	// 如果 n 的所有位中包含 偶数数字，则必然不满足条件
	for i := 0; i < len; i++ {
		if buf[i] == '0' || buf[i] == '2' || buf[i] == '4' || buf[i] == '6' || buf[i] == '8' {
			return false
		}
	}

	// 不断右移 len-1 次，判断每次右移的结果是否是质数
	for i := 0; i < len-1; i++ {

		// 对 buf 右移一位
		buf = buf[len-1:len] + buf[0:len-1]

		// 将 buf 转换为 int
		i64, _ := strconv.ParseInt(buf, 10, 32)

		if !isPrime(int(i64)) {
			return false
		}
	}

	return true
}

func main() {

	cnt := 0
	for i := 0; i < 1000000; i++ {
		if isCircularPrimes(i) {
			fmt.Println(i)
			cnt++
		}
	}

	fmt.Printf("cnt:%d\n", cnt)
}
```

### Python

使用 `buf = buf[-1:] + buf[0:-1]` 进行右移操作，其它同 C++ 版本

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

# 判断 n 是否是循环质数
# 即 n 循环右移后的每一个数，是否都是质数
def isCircularPrimes(n) :

    # 特殊处理 2
    if n == 2 :
        return True

    if not isPrime(n) :
        return False

    # 如果 n 的所有位中包含 偶数数字，则必然不满足条件
    for c in list(str(n)) :
        if c == '0' or c == '2' or c == '4' or c == '6' or c == '8' :
            return False


	# 不断右移 len-1 次，判断每次右移的结果是否是质数
    buf = str(n)
    for i in range(1, len(buf)):
        # 对 buf 右移一位
        buf = buf[-1:] + buf[0:-1]

        if not isPrime(int(buf)) :
            return False

    return True

cnt = 0
for i in range(0,1000000) :
    if isCircularPrimes(i) :
        print(i)
        cnt = cnt + 1

print("cnt:", cnt)
```

## 答案

55

这个55个数字是：2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, 97, 113, 131, 197, 199, 311, 337, 373, 719, 733, 919, 971, 991, 1193, 1931, 3119, 3779, 7793, 7937, 9311, 9377, 11939, 19391, 19937, 37199, 39119, 71993, 91193, 93719, 93911, 99371, 193939, 199933, 319993, 331999, 391939, 393919, 919393, 933199, 939193, 939391, 993319, 999331

## 知识点

- Python 切片实现右旋一位： s = s[-1:] + s[:-1]
- C\C++ 通过将个位移动到高位实现右旋一位