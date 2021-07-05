# Problem 23: Non-abundant sums

> https://projecteuler.net/problem=23

A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.

## 分析

- 完美数（perfect number）：   一个数 n 的所有因子（不包括自身）的和 等于 n，则 n 称为完美数
- 欠缺数（deficient number）：一个数 n 的所有因子（不包括自身）的和 小于 n，则 n 称为欠缺数
- 富余数（abundant number）：一个数 n 的所有因子（不包括自身）的和 大于 n，则 n 称为富余数

12是最小的富余数，1 + 2 + 3 + 4 + 6 = 16，能写成两个富余数之和的最小的数是24。由数学分析可知，所有大于28123的数可以写成两个富余数的和。但是这个上限不能通过分析的方法进一步减小了，即便目前已知的不能写成两个富余数之和的最大的数比这个上限小。

求所有不能被写成两个富余数之和的正整数的和。

## 方法 遍历存储所有的富足数，然后再遍历判断每个数能否写成两个富足数的和

该题和上上一题Problem 21 有相同之处，都需要求一个数的所有因子之和（不包括自身）。可以先记录1~28123范围所有的富足数。然后从1~28123遍历，依次判断是否能写成两个富足数的和。

- 首先将所有1~28123范围所有的富足数放置到一个容器 abundants 中，
- 然后 i 从 1 遍历到 28123，对于每一个 i，用 i 减去abundants中的每一个富足数，判断差是不是富足数，如果差是富足数，则 i 可以写成两个富足数之和，不符合条件，不能被累加。

### CPP

使用 std::set<int> 存放所有的富足数


```cpp
#include <iostream>
#include <stdint.h>
#include <set>

using namespace std;

/*容器，存放1~28123所有的富足数*/
std::set<int> abundants;

// 判断n是否是富足数
bool isAbundant(int n)
{
    int sum = 1; //1肯定是n的因子
    for (int i=2; i * i <= n; i++){
        if (n%i == 0){
            int a = n/i; //a和i都是n的因子
            if(i>a) break;
            else if (i==a) sum += i;
            else sum += (a + i);
        }
    }

    return (sum>n) ? true:false;
}

// 找到1~28123范围内所有的富足数
void getAbundantsBelowN(int n)
{
    for(int i=1; i<=n; i++) {
        if(isAbundant(i)) {
            abundants.insert(i);
        }
    }
}

// 求解问题：所有不能被写成两个富余数之和的正整数的和*/
int64_t calcSum(int n)
{
    int64_t sum=0;
    for(int i=1; i<=n; i++) {
       
        //if ( i%2000 ==0) cout<<"i="<<i<<endl;

        // 从abundants数组依次取元素 *it，判断 i - *it 是否是富足数
        bool flag = false; // 标识是否可被写成两个富足数之和
        for(std::set<int>::iterator it= abundants.begin(); it != abundants.end(); it++){
            std::set<int>::iterator itFind = abundants.find(i-*it);
            if(itFind != abundants.end()){
                flag = true; //i是两个富足数之和
                break;
            }
        }

        // 如果i不是两个富足数之和，则累加
        if(flag==false) {
            sum += i;
        }
    }

    return sum;
}
int main()
{
    getAbundantsBelowN(28123);
    cout << calcSum(28123) << endl;
    return 0;
}
```

### Golang

```go
package main

import (
	"fmt"
)

// 判断n是否是富足数
func isAbundant(n int) bool {
	sum := 1 // 1肯定是n的因子
	for i := 2; i*i <= n; i++ {
		if n%i == 0 {
			a := n / i //a和i都是n的因子
			if i > a {
				break
			} else if i == a {
				sum += i
			} else {
				sum += a + i
			}
		}
	}

	if sum > n {
		return true
	}

	return false
}

// 找到1~28123范围内所有的富足数
func getAbundantsBelowN(n int) map[int]bool {
	abundants := make(map[int]bool, 0)
	for i := 1; i < n; i++ {
		if isAbundant(i) {
			abundants[i] = true
		}
	}
	return abundants
}

// 求解问题：所有不能被写成两个富余数之和的正整数的和*/
func calcSum(n int) int {

	abundants := getAbundantsBelowN(n)

	sum := 0
	for i := 1; i <= n; i++ {

		// 从abundants数组依次取元素 a，判断 i - a 是否是富足数
		flag := false // 标识是否可被写成两个富足数之和
		for k := range abundants {
			if _, ok := abundants[i-k]; ok {
				flag = true //i是两个富足数之和
				break
			}
		}

		// 如果i不是两个富足数之和，则累加
		if !flag {
			sum += i
		}
	}
	return sum
}

func main() {
	fmt.Println(calcSum(28123))
}

```

### Python

```python
from math import sqrt

def isAbundant(n): #... same to the code above
    # factor_sum = sum([i for i in range(1, n) if n % i == 0]); return factor_sum > n #low efficiency but simple
    sum = 1 # high efficiency but complicated
    for i in range(2, int(sqrt(n)) + 1):
        if n % i == 0:
            a = n / i
            if i > a: break
            elif i == a: sum += i
            else: sum += i + a
    return sum > n

allAbundants = set(i for i in range(1, 28123) if isAbundant(i))
print( sum(i for i in range(1,28124) if not any(i-a in allAbundants for a in allAbundants)))
```

使用set存储所有的富足数，for i in range(1,28124) 遍历 1~28123，对每一个 i，for a in allAbundants 如果 a 属于富足数，i-a in allAbundants， 如果 i-a 属于富足数，使用 any 函数判断结果，只要找到一个 a 和 i-a 都属于富足数，则 any() 会返回True，说明 i 是两个富足数的和，not any() 则表示 i 不是两个富足数的和。

> any(iterable) 函数用于判断给定的可迭代参数 iterable 是否全部为 False，则返回 False，如果有一个为 True，则返回 True。
> 元素除了是 0、空、FALSE 外都算 TRUE。
> 等价于：

```python
def any(iterable):
    for element in iterable:
        if element:
            return True
    return False
```

## 答案
4179871

## 知识点
- Python set 集合
- Python any(iterable)函数，可迭代对象iterable 有一个为True，则返回True，否则返回False