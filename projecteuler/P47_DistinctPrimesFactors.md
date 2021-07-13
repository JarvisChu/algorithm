# Problem 47: Distinct primes factors

> https://projecteuler.net/problem=47

The first two consecutive numbers to have two distinct prime factors are:

14 = 2 × 7
15 = 3 × 5

The first three consecutive numbers to have three distinct prime factors are:

644 = 2² × 7 × 23
645 = 3 × 5 × 43
646 = 2 × 17 × 19.

Find the first four consecutive integers to have four distinct prime factors each. What is the first of these numbers?

## 分析

找到最靠前的四个连续的整数，它们有4个不同的质因数，并且可以写成这四个质因数的乘积（质因数可以重复使用，但必须4个都用到）。

思路：从最小的满足条件的整数 n = 2 * 3 * 5 * 7 开始往上遍历，判断每个n是否满足条件，如果找到连续的四个数满足，输出答案即可。

## 方法1 遍历

开始时：使用 beginNumber 记录满足条件的4个连续数的第一个，使用 findCnt 记录当前连续满足条件数的个数
然后：从最小的满足条件的整数 n = 2 * 3 * 5 * 7 开始往上遍历。对于每个 n，做如下处理：
- (1) 获取其所有质因数，并通过 set 进行去重。如果去重后的质因数个数不等于 4，则 n++；否则进入下一步
- (2) 判断 n 能否写成其所有质因数的乘积（每个质因数可以重复使用），如果可以，则满足条件 findCnt++; 如果是第一个数，则记录到beginNumber，如果是第4个数，则说明找到了满足题意的答案。输出 beginNumber 即可。


重点在于 (2) 中怎么判断 n 能否写成其所有质因数的乘积（每个质因数可以重复使用）。 方法是： 使用 n 依次去整除 n 的所有质因数，如果当前质因数可以整除，则继续尝试整除它，如果当前不能整除，则继续尝试下一个质因数。使用 set 记录每次可以整除的质因数并去重。 当所有质因数都遍历完，或者 n 已经被整除到0了，则结束。 结束后，判断set中记录的质因数个数是否等于 4，等于4在满足条件，不等于则不满足条件。


### CPP

```cpp
#include <iostream>
#include <set>
#include <cmath>
#include <cstdint>

bool isPrime(int64_t n)
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
    for(int64_t i=5; i * i <= n; i++){
        if( n % i == 0 ) return false;
    }
    return true;
}

int main()
{

    int beginNumber = 0; // 最终的答案，即连续4个满足条件的数中的第一个
    int findCnt = 0;     // 记录当前找到几个连续的满足条件的数

    for(int n = 210; ; n++){ //  n = 210 = 2*3*5*7

        // 找到 n 的所有的质因数并去重
        std::set<int> primeFactors;
        for(int i = 2; i*i <= n; i++){
            if(  n % i == 0 ) {
                if(isPrime(i)) primeFactors.insert(i);
                if(isPrime(n/i)) primeFactors.insert(n/i); 
            }
            if(primeFactors.size() > 4) break;
        }

        // n 的质因数不等于4个，不满足
        if(primeFactors.size() != 4){
            findCnt = 0;
            continue;
        }

        // 判断 n 能否写成 4 个质因数的乘积（每个质因数可以重复使用）
        std::set<int> f;
        int cpy = n;
        for(std::set<int>::iterator it = primeFactors.begin(); it != primeFactors.end(); ){
           if(cpy % *it == 0){
               f.insert(*it);
               cpy /= *it;
               if( cpy == 0) break;
           }else{
               it++;
           }
        }

        // 不能写成4个质因数的乘积
        if(f.size() != 4){
            findCnt = 0;
            continue;
        }

        // 可以写成4个质因数的乘积，累加 findCnt，如果已找到4个，则满足条件，结束。
        findCnt ++;
        if(findCnt == 1) beginNumber = n;
        if(findCnt == 4) {
            printf("beginNumber: %d\n", beginNumber);
            return 0;
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

	if n%6 != 1 && n%6 != 5 {
		return false
	}

	for i := 5; i*i <= n; i++ {
		if n%i == 0 {
			return false
		}
	}

	return true
}

func main() {
	beginNumber := 0 // 最终的答案，即连续4个满足条件的数中的第一个
	findCnt := 0     // 记录当前找到几个连续的满足条件的数

	for n := 210; ; n++ { // n = 210 = 2*3*5*7
		// 找到 n 的所有质因数并去重
		primeFactors := make(map[int]struct{}, 0) // 使用map去重
		for i := 1; i*i <= n; i++ {
			if n%i == 0 {
				if isPrime(i) {
					primeFactors[i] = struct{}{}
				}
				if isPrime(n / i) {
					primeFactors[n/i] = struct{}{}
				}

				if len(primeFactors) > 4 {
					break
				}
			}
		}

		// n 的质因数不等于4个，不满足
		if len(primeFactors) != 4 {
			findCnt = 0
			continue
		}

		// 判断 n 能否写成 4 个质因数的乘积（每个质因数可以重复使用）
		f := make(map[int]struct{}, 0)
		cpy := n
		for k := range primeFactors {

			for cpy % k == 0 {
				f[k] = struct{}{}
				cpy /= k
				if cpy == 0 {
					break
				}
			}

			if cpy == 0 {
				break
			}
		}

		// 不能写成4个质因数的乘积
		if len(f) != 4 {
			findCnt = 0
			continue
		}

		// 可以写成4个质因数的乘积，累加 findCnt，如果已找到4个，则满足条件，结束。
		findCnt++
		if findCnt == 1 {
			beginNumber = n
		}
		if findCnt == 4 {
			fmt.Printf("beginNumber: %d\n", beginNumber)
			return
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

beginNumber = 0 # 最终的答案，即连续4个满足条件的数中的第一个
findCnt = 0     # 记录当前找到几个连续的满足条件的数

n = 210 # 210 = 2*3*5*7
while True:
    # 找到 n 的所有质因数并去重
    primeFactors = set()
    for i in range(1, int(math.sqrt(n))+1):
        if n % i == 0 :
            if isPrime(i) :
                primeFactors.add(i)
            if isPrime(n / i):
                primeFactors.add(n / i)
            if len(primeFactors) > 4:
                break

    # n 的质因数不等于4个，不满足
    if len(primeFactors) != 4 :
        findCnt = 0
        n = n + 1
        continue
    
    #print(n, primeFactors)
    # 判断 n 能否写成 4 个质因数的乘积（每个质因数可以重复使用）
    f = set()
    cpy = n
    for k in primeFactors :
        while cpy % k == 0 :
            f.add(k)
            cpy = int(cpy/k)
            if cpy == 0 :
                break

        if cpy == 0 :
            break

    # 不能写成4个质因数的乘积
    if len(f) != 4 :
        findCnt = 0
        n = n + 1
        continue

    # 可以写成4个质因数的乘积，累加 findCnt，如果已找到4个，则满足条件，结束。
    findCnt = findCnt + 1
    if findCnt == 1 :
        beginNumber = n
    if findCnt == 4 :
        print("beginNumber: ", beginNumber)
        exit(0)
    n = n + 1
```

## 答案

134043

具体的质因数如下

```
134043 set([3, 491, 13, 7])
134044 set([47, 2, 31, 23])
134045 set([17, 83, 19, 5])
134046 set([11, 2, 3, 677])
```