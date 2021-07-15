# Problem 56: Powerful digit sum

> https://projecteuler.net/problem=56

A googol (10<sup>100</sup>) is a massive number: one followed by one-hundred zeros; 100<sup>100</sup> is almost unimaginably large: one followed by two-hundred zeros. Despite their size, the sum of the digits in each number is only 1.

Considering natural numbers of the form, a<sup>b</sup>, where a, b < 100, what is the maximum digital sum?

## 分析

a<sup>b</sup>, 其中 a, b < 100，求所有数字的和最大的数，它的所有数字和。

思路：仍然是大数问题

## 方法1 使用字符串解决大数问题 [适用于C++]

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 123 => [1,2,3]
// n >= 0
std::vector<char> int2vector(int n)
{
    std::vector<char> digits;
    if(n == 0){
        digits.push_back('0');
        return digits;
    }

    while(n > 0){
        digits.push_back( n % 10 + '0' );
        n /= 10;
    }

    std::reverse(digits.begin(), digits.end());

    return digits;
}

/***********************************************************
* a+b
* a >= 0
* b >= 0
* return a+b
************************************************************/
std::vector<char> add(const std::vector<char>& a, const std::vector<char>& b)
{
    // 存放和（逆序）
    std::vector<char> sum;

    // 从低位到高位，依次相加
    int i = 0, j = 0, acc = 0; // acc 进位
    for(i = a.size()-1, j = b.size()-1; i >= 0 && j >= 0; i--, j --){
        int v = (int) (a[i] - '0') + (int) (b[j] - '0') + acc;
        acc = v / 10;
        sum.push_back( (char) ( (v % 10) + '0' ) );
    }

    // a.size > b.size, b已经加完，a剩余
    for(; i >= 0; i--){
        int v = (int) (a[i] - '0') + acc;
        acc = v / 10;
        sum.push_back( (char) ( (v % 10) + '0' ) );
    }

    // a.size < b.size, a已经加完，b剩余
    for(; j >= 0; j--){
        int v = (int) (b[j] - '0') + acc;
        acc = v / 10;
        sum.push_back( (char) ( (v % 10) + '0' ) );
    }

    // 补上 acc
    if( acc > 0){
        sum.push_back( (char) ( acc + '0' ) );
    }

    // 对sum进行逆序
    std::reverse(sum.begin(), sum.end());
    return sum;
}

/***********************************************************
* a*b
* a >= 0
* b 是 0~9 之间的整数
* return a*b
************************************************************/
std::vector<char> mul(const std::vector<char>& a, int b)
{
    // 存放乘积
    std::vector<char> product;

    if(b == 0){
        product.push_back('0');
        return std::move(product);
    }

    // 将乘法转换为加法
    for(int i = 0; i < a.size(); i++){ // product = a
        product.push_back(a[i]);
    }

    for(int i = 0; i < b-1; i ++){  //  累加 b-1 次 a
        product = add(product, a);
    }

    return std::move(product);
}


/***********************************************************
* a*b
* a >= 0
* b >= 0
* return a*b
************************************************************/
std::vector<char> mul(const std::vector<char>& a, const std::vector<char>& b)
{
    // 存放乘积
    std::vector<char> product;
    std::vector<char> a1;
    for(int i = 0; i< a.size(); i ++) a1.push_back(a[i]);

    // 将乘法转换为加法
    for(int i = b.size() - 1; i >= 0; i--){
        std::vector<char> p = mul(a1, (int)(b[i] - '0') );
        product = add(product, p);
        a1.push_back('0'); // a1 *= 10，因为b的位数每高一位，a1 要乘以 10
    }

    return product;
}

int main()
{
    int max = 0;
    for(int a = 1; a <= 100; a++){

        std::vector<char> va = int2vector(a);
        std::vector<char> product = int2vector(a);

        for(int b = 1; b <= 100; b++){
            std::vector<char> tmp = mul(product, va);
            product.swap(tmp);

            int sum = 0;
            for(int i = 0; i < product.size(); i++){
                sum += product[i] - '0';
            }

            if(sum > max){
                max = sum;
            }
        }
    }
    
    printf("max:%d\n", max);
    return 0;
}
```

## 方法2 使用库函数解决大数问题 [适用于 Golang]

```go
package main

import (
	"fmt"
	"math/big"
)

func sumOfDigits(a, b int) int {

	bigA := big.NewInt(int64(a))
	mul := big.NewInt(int64(a))
	for i := 1; i < b; i++ {
		mul.Mul(mul, bigA)
	}

	sum := 0
	for _, s := range mul.String() {
		sum += int(s - 48)
	}

	return sum
}

func main() {

	max := 0
	for a := 1; a <= 100; a++ {
		for b := 1; b <= 100; b++ {
			sum := sumOfDigits(a, b)
			if sum > max {
				max = sum
			}
		}
	}

	fmt.Println(max)
}

```

## 方法3 无需考虑大数问题，直接计算 [适用于 Python]

```python
max = 0
for a in range(1,101):
    for b in range(1, 101):
        r = sum( [ int(n) for n in list(str(a**b))] )
        if r > max :
            print("find a larger: ", a,b,r)
            max = r
print(max)
```

写成一行

```python
print( max([ sum( [ int(n) for n in list(str(a**b))] ) for a in range(1,101) for b in range(1, 101) ]))
```

## 答案

972

99<sup>95</sup>