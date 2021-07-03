# Problem 20: Factorial digit sum

> https://projecteuler.net/problem=20


n! means n × (n − 1) × ... × 3 × 2 × 1

For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100!

## 分析

计算100！各位数字的和。

100! 共有158位数字。本质还是大数问题，和 [Problem 16 Power digit sum](http://zhujiangtao.com/problem-16-power-digit-sum/) 相同。
所以可以直接复用 Problem 16 中的方法。

## 方法1 使用字符串实现乘法

详见 [Problem 16 Power digit sum](http://zhujiangtao.com/problem-16-power-digit-sum/) ，复用其中的add/mul等函数即可，此处不再赘述。

### CPP

```cpp
// 计算n!
std::vector<char> factorial(int n) 
{
    std::vector<char> v;
    v.push_back('1');

    for(int i = 2; i <= n; i++){
        v = mul(v, i);
    }

    return v;
}

// 计算每一位数字之和
int calSum(const std::vector<char>& v)
{
    int sum = 0;
    for(int i = 0; i < v.size(); i++){
        sum += int(v[i] - '0');
    }

    return sum;
}

int main(int argc, char* argv[])
{
    std::vector<char> v =  factorial(100);
    printf("sum:%d\n", calSum(v));
    return 0;
}
```

## 方法2 使用大数包，适用于golang

### Golang

```go
package main

import (
	"fmt"
	"math/big"
)

func factorial(n int) *big.Int{
	a := big.NewInt(1)
	for i := 2; i <= n; i++ {
		b := big.NewInt(int64(i))
		a.Mul(a, b)
	}
	return a
}

// 计算每一位数字之和
func calSum(n *big.Int) int {
	sum := 0
	for _, s := range n.String(){
		sum += int(s-'0')
	}
	return sum
}

func main() {
	f := factorial(100)
	fmt.Println(f)
	fmt.Println(calSum(f))
}
```

## 方法3 直接计算，适用于python

```python
from functools import reduce
print ( sum([int(i) for i in str(reduce(lambda x, y: x * y, range(1, 101)))]) )
```

首先使用 reduce(lambda x, y: x * y, range(1, 101)) 获得 100！，再用str()将结果转换为字符串，遍历字符串，将各位字符转换为int，并生成一个列表，最后使用sum函数计算各位的和。

## 答案
648

100!=93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000