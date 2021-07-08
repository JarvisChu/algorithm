# Problem 38: Pandigital multiples

> https://projecteuler.net/problem=38


Take the number 192 and multiply it by each of 1, 2, and 3:

192 × 1 = 192
192 × 2 = 384
192 × 3 = 576

By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product of 192 and (1,2,3)

The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).

What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated product of an integer with (1,2, ... , n) where n > 1?

## 分析

由一个整数 x 与（1，2，…，n）依次的乘积连接而成的，只含有不重复的 1~9 九个数字的数，称为 9-digit pandigital。求可以写成 x 与(1,2,...,n) 乘积形式的最大的 9-digit pandigital。

假设 x 和 n 满足条件，len(x) 表示 x 的位数，题中要求 n >= 2，所以 len(x) + len(2x) <= 9，所以 len(x) <= 5. 即x最大是5位数，x < 100000

又因为：len(1x)+ len(2x) + ... + len(nx) = 9，所以 n <= 9，且 len(x) * n <= 9

由此，我们可知 x<100000, 2<= n <= 9，len(x) * n <= 9， 约束好范围之后，就可以遍历判断了



## 方法 遍历判断

### CPP

```cpp
#include <iostream>
#include <string>
#include <set>

// 判断 x * (1,...,n) 的乘积，是否是满足条件的pandigital
// 如果不满足，则返回 0
// 如果满足，则返回具体的pandigital
int isPandigital(int x, int n)
{
    // 最终乘积的位数不能超过 9。
    std::string sx = std::to_string(x);
    if( sx.size() * n > 9) return 0;

    // 计算 x,n 的乘积
    std::string product;
    for(int i = 1; i <= n; i++){
        product +=  std::to_string(x*i);
    }

    // 检查product 是否满足条件，即长度为9，包含1~9.
    if(product.size() != 9) return 0; 

    std::set<char> s; // 使用 set 去重
    for(int i = 0; i < 9; i++){
        if(product[i] == '0') return 0; // 不能包含 0
        s.insert(product[i]);
    }
    if(s.size() != 9) return 0;

    // string to int
    return atoi(product.c_str());
}

int main()
{
    int max = 0;
    for(int x = 1; x < 100000; x++ ){
        for(int n = 2; n <= 9; n++){
            int p = isPandigital(x,n);
            if(p > max) {
                max = p;
                std::cout<<"find a candidate: x="<<x<<",n="<<n<<",pandigital="<<p<<std::endl;
            }
        }
    }
    std::cout<<max<<std::endl;
    return 0;
}
```

### Golang

```go
package main

import (
	"fmt"
	"strconv"
)

// 判断 x * (1,...,n) 的乘积，是否是满足条件的pandigital
// 如果不满足，则返回 0
// 如果满足，则返回具体的pandigital
func isPandigital(x, n int) int {

	// 最终乘积的位数不能超过 9
	sx := fmt.Sprintf("%d", x)
	if len(sx)*n > 9 {
		return 0
	}

	// 计算 x,n 的乘积
	product := ""
	for i := 1; i <= n; i++ {
		product += fmt.Sprintf("%d", x*i)
	}

	// 检查product 是否满足条件，即长度为9，包含1~9.
	if len(product) != 9 {
		return 0
	}

	m := make(map[int32]struct{}) // 使用 map 去重
	for _, s := range product {
		if s == '0' { // 不能包含 0
			return 0
		}
		m[s] = struct{}{}
	}
	if len(m) != 9 {
		return 0
	}

	// string to int
	i64, _ := strconv.ParseInt(product, 10, 32)
	return int(i64)
}
func main() {

	max := 0
	for x := 1; x < 100000; x++ {
		for n := 2; n <= 9; n++ {
			p := isPandigital(x, n)
			if p > max {
				max = p
				fmt.Printf("find a candidate: x=%d,n=%d,pandigital=%d\n", x, n, p)
			}
		}
	}
	fmt.Println(max)
}
```

### Python

```python

# 判断 x * (1,...,n) 的乘积，是否是满足条件的pandigital
# 如果不满足，则返回 0
# 如果满足，则返回具体的pandigital
def isPandigital(x, n) :

	# 最终乘积的位数不能超过 9
	if len(str(x)) * n > 9 :
		return 0

	# 计算 x,n 的乘积
	product = ''
	for i in range(1,n+1) :
		product += str(x*i)

	# 检查product 是否满足条件，即长度为9，包含1~9.
	if len(product) != 9 :
		return 0

	if '0' in list(product): # 不能包含 0
		return 0

	s = set(list(product)) # 使用 set 去重
	if len(s) != 9 :
		return 0

	return int(product)


maxP = 0
for x in range(1,100000):
	for n in range(2,10):
		p = isPandigital(x, n)
		if p > maxP :
			maxP = p
			print(x, n, p)
print(maxP)

```

## 答案

932718654

所有满足条件的 9-digit pandigital 如下:

```
x=1,n=9,pandigital=123456789
x=9,n=5,pandigital=918273645
x=9267,n=2,pandigital=926718534
x=9273,n=2,pandigital=927318546
x=9327,n=2,pandigital=932718654
```