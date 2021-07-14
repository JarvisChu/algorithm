# Problem 53: Combinatoric selections

> https://projecteuler.net/problem=53

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/project_euler_53_1.png)

## 分析

组合 C(n,r) 表示从 n 个数中选择 r 个数选择方案的总数。 当 1 ≤ n ≤ 1000时， 统计有多少个 C(n,r) 的值超过了 1 百万。

思路很简单直接，难点是如果采用非python的实现，计算阶乘时存在大数问题。所以需要对 C(n,r) 的计算做优化，避免大数问题。

C(n,r) = n! / r!(n-r)!，计算过程中，可以先做约分，再计算最终结果。假设 max = max(r,n-r). 可以先约去 max!。 min = min(r,n-r).

```
   n!        (约去max)     (max+1)(max+2)...(n-2)(n-1)n
-----------     =     ------------------------------------
 max!*min!                 1*2*3...*(min-2)*(min-1)*min
```

然后再对分子的每个乘数，依次和分母中的所有乘数做约分。因为C(n,r) 最终必然是整数，所以约分到最后，分母中所有乘数都可以被约分成1，直接计算分子的乘积即可。并且，计算分子乘积的过程中，为了避免大数问题，我们不需要计算最终的结果，只要计算判断 > 1000000 即可。

## 方法 通过约分，避免大数

### CPP

```cpp
#include <iostream>
#include <vector>

#define MAX_C 1000000

// 辗转相除法 求最大公约数
int gcd(int a, int b){
    int r=1;        // 余数,赋初值为1 
    while(r != 0){  // 如果a<b,亦无需颠倒ab，在计算中商0余除数本身，在下次运算中自可颠倒回来 
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// 判断 C(n,r) 是否大于 MAX_C
bool C(int n, int r)
{
    // 获取 r 和 n-r 中较大的数和较小的数，保存在 max,min 中
    int max = r, min = n-r; 
    if(r < n-r){
        max = n-r;
        min = r;
    }

    //C(n,r) = n! / (max! * min!)

    // 分别统计分子和分母的所有乘数

    std::vector<int> numerator; // 保存分子的所有乘数 (max+1)(max+2)...(n-2)(n-1)n
    for(int i = max + 1; i <= n; i++){
        numerator.push_back(i);
    }

    std::vector<int> denominator; // 保存分母的所有乘数 1*2*3...*(min-2)*(min-1)*min
    for(int i = 1; i <= min; i++){
        denominator.push_back(i);
    }

    // 对分子分母做约分
    
    // 从分子的最后一个乘数（因为最后一个乘数最大）开始，分别对分母的所有乘数做约分
    for(int i = numerator.size() - 1; i >= 0; i--){
        for(int j = denominator.size() -1; j >= 0; j--){
            if(numerator[i] == 1 ) break;    // 分子的乘数无需再化简了
            if(denominator[j] == 1) continue; // 分母的乘数无法再化简了，继续判断分母的下一个乘数

            // 找到 numerator[i] 和 denominator[j] 的最大公约数，然后做约分
            int g = gcd(numerator[i], denominator[j]);
            //printf("i=%d, j=%d, %d, %d, %d\n", i, j, numerator[i], denominator[j], g);
            numerator[i] /= g;
            denominator[j] /= g;
        }
    }

    // 因为C(n,r) 最终必然是整数，所以约分到最后，分母中所有乘数应该都是 1
    // 所有直接计算分子的乘积即可

    int mul = 1;
    for(int i = 0; i < numerator.size(); i++){
        mul *= numerator[i];

        if(mul > MAX_C) return true;
    }

    return false;
}

int main()
{
    int cnt = 0;
    for(int n = 1; n <= 100; n++){
        for(int r = 1; r <= n; r++){
            if (C(n,r)) {
                cnt ++;
            }
        }
    }

    printf("cnt=%d\n", cnt);
    return 0;
}
```

### Golang

```go
package main

import "fmt"

const MAX_C = 1000000

// 辗转相除法 求最大公约数
func gcd(a, b int) int {
	r := 1       // 余数,赋初值为1
	for r != 0 { // 如果a<b,亦无需颠倒ab，在计算中商0余除数本身，在下次运算中自可颠倒回来
		r = a % b
		a = b
		b = r
	}
	return a // 此时b的值已经在a中了，所以输出的a就是最大公约数
}

// 判断 C(n,r) 是否大于 MAX_C
func C(n, r int) bool {

	// 获取 r 和 n-r 中较大的数和较小的数，保存在 max,min 中
	max, min := r, n-r
	if r < n-r {
		max = n - r
		min = r
	}

	// C(n,r) = n! / (max! * min!)

	// 分别统计分子和分母的所有乘数

	var numerator []int // 保存分子的所有乘数 (max+1)(max+2)...(n-2)(n-1)n
	for i := max + 1; i <= n; i++ {
		numerator = append(numerator, i)
	}

	var denominator []int // 保存分母的所有乘数 1*2*3...*(min-2)*(min-1)*min
	for i := 1; i <= min; i++ {
		denominator = append(denominator, i)
	}

	// 对分子分母做约分

	// 从分子的最后一个乘数（因为最后一个乘数最大）开始，分别对分母的所有乘数做约分
	for i := len(numerator) - 1; i >= 0; i-- {
		for j := len(denominator) - 1; j >= 0; j-- {
			if numerator[i] == 1 { // 分子的乘数无需再化简了
				break
			}

			if denominator[j] == 1 { // 分母的乘数无法再化简了，继续判断分母的下一个乘数
				continue
			}

			// 找到 numerator[i] 和 denominator[j] 的最大公约数，然后做约分
			g := gcd(numerator[i], denominator[j])
			numerator[i] /= g
			denominator[j] /= g
		}
	}

	// 因为C(n,r) 最终必然是整数，所以约分到最后，分母中所有乘数应该都是 1
	// 所有直接计算分子的乘积即可

	mul := 1
	for i := 0; i < len(numerator); i++ {
		mul *= numerator[i]

		if mul > MAX_C {
			return true
		}
	}

	return false
}

func main() {

	cnt := 0
	for n := 1; n <= 100; n++ {
		for r := 1; r <= n; r++ {
			if C(n, r) {
				cnt++
			}
		}
	}

	fmt.Printf("cnt=%d\n", cnt)
}

```

### Python

可以复用上面的方法，也可以直接计算，因为python处理大数很方便。

```python
def factorial(n):
    mul = 1
    for i in range(1,n+1):
        mul *= i
    return mul

def C(n,r):
    return factorial(n) / (factorial(r) * factorial(n-r))

cnt = 0
for n in range(1,101):
    for r in range(1, n+1):
        if C(n,r) > 1000000:
            cnt += 1
print(cnt)
```

## 答案

4075




