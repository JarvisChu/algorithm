# Problem 60: Prime pair sets

> https://projecteuler.net/problem=60

The primes 3, 7, 109, and 673, are quite remarkable. By taking any two primes and concatenating them in any order the result will always be prime. For example, taking 7 and 109, both 7109 and 1097 are prime. The sum of these four primes, 792, represents the lowest sum for a set of four primes with this property.

Find the lowest sum for a set of five primes for which any two primes concatenate to produce another prime.

## 分析

找到 5 个质数，他们任意两个拼接在形成的数（如 3和7 拼接成37，73），也是质数。找到这样的 5 个质数，它们的和最小。

## 方法1 尝试 + 穷举

如果使用穷举的方法，我们并不知道穷举的界限在哪。所以，可以**先尝试穷举 10000 以内的所有质数**，看看能否找到符合条件的 5 个质数。 

```python
primes = [i for i in range(1,10000) if isPrime(i)]

curMin = 9999999999
answer = []
for a in range(0, len(primes)-5):
    print("a", a)
    stra = str(primes[a])
    for b in range(a+1, len(primes)-4):
        strb = str(primes[b])
        if not isPrime(int(stra+strb)) or not isPrime(int(strb+stra)) :
            continue
        for c in range(b+1, len(primes)-3):
            strc = str(primes[c])
            if not isPrime(int(stra+strc)) or not isPrime(int(strc+stra)) or \
               not isPrime(int(strb+strc)) or not isPrime(int(strc+strb)) :
                continue
            for d in range(c+1, len(primes)-2):
                strd = str(primes[d])
                if not isPrime(int(stra+strd)) or not isPrime(int(strd+stra)) or \
                   not isPrime(int(strb+strd)) or not isPrime(int(strd+strb)) or \
                   not isPrime(int(strc+strd)) or not isPrime(int(strd+strc)) :
                    continue
                for e in range(d+1, len(primes)-1):
                    stre = str(primes[e])
                    if not isPrime(int(stra+stre)) or not isPrime(int(stre+stra)) or \
                       not isPrime(int(strb+stre)) or not isPrime(int(stre+strb)) or \
                       not isPrime(int(strc+stre)) or not isPrime(int(stre+strc)) or \
                       not isPrime(int(strd+stre)) or not isPrime(int(stre+strd)) :
                        continue  
                    s = primes[a] +  primes[b] + primes[c] + primes[d] + primes[e]
                    print(stra, strb, strc, strd, stre, "sum:",s)
                    if s < curMin :
                        curMin = s
                        answer = [curMin, stra, strb, strc, strd, stre]
                    break

print(answer)
```

遍历发现，(13 5197 5701 6733 8389) 满足条件，它们的和是 26033。 但我们不能确定 26033 就是满足条件的最小的数。

因为 26033 的发现，我们便能得到遍历的界限，即我们最多只要遍历全 26033 以内的质数就可以了，因为超过了 26033 之后，即便找到了满足条件的 5 个质数，它们的和也必然比26033大，不是最小的了，不满足要求。

如果直接穷举 26033 的所有质数，运算速度还是太慢。所以需要做进一步的优化：**[优化点1] 每一步都判断当前几个数的和是否超过了 26033，如果超过了，则不用继续往后了**

### Python

```python
from math import sqrt
import time

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
    for i in range(5, int(sqrt(n)) + 1, 6):
        if n % i == 0 or n % (i+2) == 0: return False

    return True

primes = [i for i in range(1, 26034) if isPrime(i)]

curMin = 26034
answer = []
for a in range(0, len(primes)-5):
    if 5*primes[a] >= curMin: break # [优化点1] if a+a+a+a+a > curMin, then a+b+c+d+e > curMin, break
    stra = str(primes[a])
    for b in range(a+1, len(primes)-4):
        if primes[a] + 4*primes[b] >= curMin: break # [优化点1]
        strb = str(primes[b])
        if not isPrime(int(stra+strb)) or not isPrime(int(strb+stra)) : 
            continue
        for c in range(b+1, len(primes)-3):
            if primes[a] + primes[b] + 3*primes[c] >= curMin: break # [优化点1]
            strc = str(primes[c])
            if not isPrime(int(stra+strc)) or not isPrime(int(strc+stra)) or \
               not isPrime(int(strb+strc)) or not isPrime(int(strc+strb)) : 
               continue
            for d in range(c+1, len(primes)-2):
                if primes[a] + primes[b] + primes[c] + 2*primes[d] >= curMin: break # [优化点1]
                strd = str(primes[d])
                if not isPrime(int(stra+strd)) or not isPrime(int(strd+stra)) or \
                   not isPrime(int(strb+strd)) or not isPrime(int(strd+strb)) or \
                   not isPrime(int(strc+strd)) or not isPrime(int(strd+strc)) :
                    continue
                #print( primes[a],primes[b],primes[c],primes[d])
                for e in range(d+1, len(primes)-1):
                    if primes[a] + primes[b] + primes[c] + primes[d] + primes[e] >= curMin: break # [优化点1]
                    stre = str(primes[e])
                    if not isPrime(int(stra+stre)) or not isPrime(int(stre+stra)) or \
                       not isPrime(int(strb+stre)) or not isPrime(int(stre+strb)) or \
                       not isPrime(int(strc+stre)) or not isPrime(int(stre+strc)) or \
                       not isPrime(int(strd+stre)) or not isPrime(int(stre+strd)) :
                        continue  
                    s = primes[a] +  primes[b] + primes[c] + primes[d] + primes[e]
                    print(stra, strb, strc, strd, stre, "sum:", s)
                    if s < curMin :
                        curMin = s
                        answer = [curMin, stra, strb, strc, strd, stre]
                    break

print("answer:", answer)
```

在我的机器上，运行时间约为 80s，勉强可以接受。


### Golang

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
	for i := int64(5); i*i <= n; i++ {
		if n%i == 0 {
			return false
		}
	}

	return true
}

func isBothPrimes(a, b string) bool {
	ab, _ := strconv.ParseInt(a+b, 10, 64)
	if !isPrime(ab) {
		return false
	}

	ba, _ := strconv.ParseInt(b+a, 10, 64)
	if !isPrime(ba) {
		return false
	}
	return true
}

func main() {

	primes := []int{2}
	for i := 3; i <= 26033; i += 2 {
		if isPrime(int64(i)) {
			primes = append(primes, i)
		}
	}
	fmt.Println(len(primes))

	curMin := 26034
	for a := 5; a < len(primes)-4; a++ {
		if 5*primes[a] >= curMin { // [优化点1] if a+a+a+a+a > curMin, then a+b+c+d+e > curMin, break
			break
		}
		stra := fmt.Sprintf("%d", primes[a])

		for b := a + 1; b < len(primes)-3; b++ {
			if primes[a]+4*primes[b] >= curMin { // [优化点1]
				break
			}
			strb := fmt.Sprintf("%d", primes[b])
			if !isBothPrimes(stra, strb) {
				continue
			}

			for c := b + 1; c < len(primes)-2; c++ {
				if primes[a]+primes[b]+3*primes[c] >= curMin { // [优化点1]
					break
				}
				strc := fmt.Sprintf("%d", primes[c])
				if !isBothPrimes(stra, strc) || !isBothPrimes(strb, strc) {
					continue
				}

				for d := c + 1; d < len(primes)-1; d++ {
					if primes[a]+primes[b]+primes[c]+2*primes[d] >= curMin {
						break
					}

					strd := fmt.Sprintf("%d", primes[d])
					if !isBothPrimes(stra, strd) || !isBothPrimes(strb, strd) || !isBothPrimes(strc, strd) {
						continue
					}

					for e := d + 1; e < len(primes); e++ {
						if primes[a]+primes[b]+primes[c]+primes[d]+primes[e] >= curMin {
							break
						}
						stre := fmt.Sprintf("%d", primes[e])
						if !isBothPrimes(stra, stre) || !isBothPrimes(strb, stre) ||
							!isBothPrimes(strc, stre) || !isBothPrimes(strd, stre) {
							continue
						}

						sum := primes[a] + primes[b] + primes[c] + primes[d] + primes[e]
						fmt.Printf("%v, %v, %v, %v, %v, sum:%v", stra, strb, strc, strd, stre, sum)
						if sum < curMin {
							curMin = sum
						}
						break
					}
				}
			}
		}
	}
	fmt.Printf("answer:%v\n", curMin)
}
```
在我的机器上，运行时间约为 20s

### CPP

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
    for(int64_t i=5; i * i <= n; i+=6){
        if( n % i == 0 || n % (i+2) == 0 ) return false;
    }
    return true;
}


bool isBothPrimes(std::string a, std::string b)
{
    std::string strAB = a + b;
	long ab = atol(strAB.c_str());
	if (!isPrime((int64_t)ab)) {
		return false;
	}

	std::string strBA = b + a;
	long ba = atol(strBA.c_str());
	if (!isPrime((int64_t)ba)) {
		return false;
	}

	return true;
}

int main() 
{
	std::vector<int> primes;
    primes.push_back(2);
	for(int i = 3; i <= 26033; i += 2) {
		if(isPrime((int64_t)i)) {
			primes.push_back(i);
		}
	}
	printf("%ld\n", primes.size());

	int curMin = 26034;
	for( int a = 5; a < primes.size()-4; a++) {
		if( 5*primes[a] >= curMin) break; // [优化点1] if a+a+a+a+a > curMin, then a+b+c+d+e > curMin, break

		std::string stra = std::to_string(primes[a]);
		for(int b = a + 1; b < primes.size()-3; b++) {
			if( primes[a]+4*primes[b] >= curMin) break;  // [优化点1]

			std::string strb = std::to_string(primes[b]);
			if( !isBothPrimes(stra, strb)) continue;

			for(int c = b + 1; c < primes.size()-2; c++) {
				if(primes[a]+primes[b]+3*primes[c] >= curMin) break;  // [优化点1]

				std::string strc = std::to_string(primes[c]);
				if( !isBothPrimes(stra, strc) || !isBothPrimes(strb, strc)) continue;

				for(int d = c + 1; d < primes.size()-1; d++) {
					if( primes[a]+primes[b]+primes[c]+2*primes[d] >= curMin) break;

					std::string strd = std::to_string(primes[d]);
					if( !isBothPrimes(stra, strd) || !isBothPrimes(strb, strd) || 
                        !isBothPrimes(strc, strd)){
                        continue;
                    }

					for( int e = d + 1; e < primes.size(); e++) {
						if(primes[a]+primes[b]+primes[c]+primes[d]+primes[e] >= curMin) break;

						std::string stre = std::to_string(primes[e]);
						if (!isBothPrimes(stra, stre) || !isBothPrimes(strb, stre) ||
							!isBothPrimes(strc, stre) || !isBothPrimes(strd, stre)) {
							continue;
						}

						int sum = primes[a] + primes[b] + primes[c] + primes[d] + primes[e];
						printf("%d, %d, %d, %d, %d, sum:%d\n", primes[a], primes[b], primes[c], primes[d], primes[e], sum);
						if (sum < curMin) {
							curMin = sum;
						}
						break;
					}
				}
			}
		}
	}

	printf("answer:%d\n", curMin);
    return 0;
}
```

在我的机器上，运行时间约为 8s

## 答案

26033

符合条件的 5 个质数为：13, 5197, 5701, 6733, 8389






