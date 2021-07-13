# Problem 49: Prime permutations

> https://projecteuler.net/problem=49

The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the 4-digit numbers are permutations of one another.

There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, but there is one other 4-digit increasing sequence.

What 12-digit number do you form by concatenating the three terms in this sequence?

## 分析

质数的排列。找到三个4位的质数，它们是等差数列，并且它们互为排列。

思路：先找到所有的4位质数，存放到primes中，判断两个数是否含有相同的数字，如果包含，则根据等差数列的特性，计算第三项，判断第三项是否是质数，是否包含相同的数字。


## 方法 

### CPP

```cpp
#include <stdio.h>

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

// 判断 a b 是否包含相同的数字
// a, b 均是4位数字
bool hasSameDigits(int a, int b)
{
    int doa[4] = {0}; // digits of a
    int dob[4] = {0}; // digits of b

    // 获取a的4位数字
    int i = 0;
    while(a > 0){
        doa[i++] = a % 10;
        a /= 10;
    }

    // 获取b的4位数字
    i = 0;
    while(b > 0){
        dob[i++] = b % 10;
        b /= 10;
    }

    // 判断 a 的4位数字是否都在 b 中，判断 b 的4位数字是否都在 a 中
    // 如果互相包含，则表明两者相等
    for( i = 0; i < 4; i++){
        bool aExistsInB = false; // doa[i] 是否包含在 dob 中
        bool bExistsInA = false; // dob[i] 是否包含在 doa 中
        for(int j = 0; j < 4; j++){

            if(doa[i] == dob[j]){
                aExistsInB = true;
            }

            if(dob[i] == doa[j]){
                bExistsInA = true;
            }
        }

        if(!aExistsInB || !bExistsInA ) return false;
    }

    // doa dob 互相包含，说明两者完全相同
    return true; 
}

int main()
{
    // 获取所有的四位质数
    int primes[1100] = {0}; // 存放所有的四位质数，总共有 1061 个
    int primesCnt = 0;
    for(int i = 1001; i < 9999; i+=2 ){
        if(isPrime(i)){
            primes[primesCnt++] = i;
        }
    }

    // 遍历寻找
    for(int i = 0; i < primesCnt-2; i++){
        for(int j = i + 1; j < primesCnt-1; j++ ){
            if( hasSameDigits(primes[i], primes[j])){
                int diff = primes[j] - primes[i];
                int next = primes[j] + diff;

                if( next < 9999 && isPrime(next) && hasSameDigits(primes[j], next )){
                    printf("%d, %d, %d \n", primes[i], primes[j], next);
                }
            }
        }
    }

    return 0;
}
```

### Golang

```go
package main

import "fmt"

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

// 判断 a b 是否包含相同的数字
// a, b 均是4位数字
func hasSameDigits(a, b int) bool {

	var doa []int // digits of a
	var dob []int // digits of b

	// 获取a的4位数字
	for a > 0 {
		doa = append(doa, a%10)
		a /= 10
	}

	// 获取b的4位数字
	for b > 0 {
		dob = append(dob, b%10)
		b /= 10
	}

	// 判断 a 的4位数字是否都在 b 中，判断 b 的4位数字是否都在 a 中
	// 如果互相包含，则表明两者相等
	for i := 0; i < 4; i++ {
		aExistsInB := false // doa[i] 是否包含在 dob 中
		bExistsInA := false // dob[i] 是否包含在 doa 中
		for j := 0; j < 4; j++ {

			if doa[i] == dob[j] {
				aExistsInB = true
			}

			if dob[i] == doa[j] {
				bExistsInA = true
			}
		}

		if !aExistsInB || !bExistsInA {
			return false
		}
	}

	// doa dob 互相包含，说明两者完全相同
	return true
}

func main() {

	// 获取所有的四位质数
	var primes []int // 存放所有的四位质数
	for i := 1001; i < 9999; i += 2 {
		if isPrime(i) {
			primes = append(primes, i)
		}
	}

	// 遍历寻找
	for i := 0; i < len(primes)-2; i++ {
		for j := i + 1; j < len(primes)-1; j++ {
			if hasSameDigits(primes[i], primes[j]) {
				diff := primes[j] - primes[i]
				next := primes[j] + diff

				if next < 9999 && isPrime(next) && hasSameDigits(primes[j], next) {
					fmt.Println(primes[i], primes[j], next)
				}
			}
		}
	}
}

```

### Python

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

# 判断 a b 是否包含相同的数字
# a, b 均是4位数字
def hasSameDigits(a, b) :
    doa = list(str(a)) # digits of a
    dob = list(str(b)) # digits of b

    # 判断 a 的4位数字是否都在 b 中
    for d in doa :
        if d not in dob:
            return False
    # 判断 b 的4位数字是否都在 a 中
    for d in dob :
        if d not in doa:
            return False

    # 如果互相包含，则表明两者相等
    return True

# 获取所有的四位质数
primes = [i for i in range(1001, 10000, 2) if isPrime(i)]

# 遍历寻找
for i in range(0, len(primes) - 1) :
    for j in range(i+1, len(primes)) :
        if hasSameDigits(primes[i], primes[j]) :
            diff = primes[j] - primes[i]
            next = primes[j] + diff
            if next < 9999 and isPrime(next) and hasSameDigits(primes[j], next) :
                print(primes[i], primes[j], next)
```

## 答案

296962999629

三个数为：2969, 6299, 9629