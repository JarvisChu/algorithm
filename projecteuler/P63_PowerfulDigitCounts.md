# Problem 63: Powerful digit counts

> https://projecteuler.net/problem=63

The 5-digit number, 16807=7<sup>5</sup>, is also a fifth power. Similarly, the 9-digit number, 134217728=8<sup>9</sup>, is a ninth power.

How many n-digit positive integers exist which are also an nth power?

## 分析

16807 是 5 位数，也是 7 的 5 次方 
134217728 是 9 位数，也是 8 的 9 次方

求： 有多少个 n 位的正整数，它也是某个数的 n 次方。

思路：可以用穷举法解决，但是需要知道穷举的边界。

如果 x<sup>n</sup> 是一个 n 位数，则 **10<sup>n-1</sup>  ≤ x<sup>n</sup> < 10<sup>n</sup>**，x 必然小于10，所以 10<sup>n-1</sup> 的增速比 x<sup>n</sup> 快，所以在某个时刻，10<sup>n-1</sup> 大于 x<sup>n</sup> 后，后面就不可能找到满足上面不等式的解了。

所以，遍历 x = 1~9，然后穷举 x^n ，如果发现 x^n 是 n 位数，则cnt++；如果发现 x^n 小于 10^(n-1)，则结束，继续搜索下一个x。最终输出cnt.

## 方法

### Python

```python
cnt = 0
for x in range(1, 10) :
    n = 1
    while True:
        if 10**(n-1) > x**n: break
        if len(str(x**n)) == n: 
            #print(x,n, x**n)
            cnt += 1
        n += 1
print(cnt)
```

### Golang

使用大数包 math/big

```go
package main

import (
	"fmt"
	"math/big"
)

func main() {
	cnt := 0
	for x := int64(1); x < 10; x++ {
		for n := 1; ; n++ {
			bx := big.NewInt(x)
			pow := big.NewInt(x) // x^n
			for i := 1; i <= n-1; i++ {
				pow.Mul(pow, bx)
			}

			b10 := big.NewInt(10)
			pow10 := big.NewInt(1) // 10^(n-1)
			for i := 1; i <= n-1; i++ {
				pow10.Mul(pow10, b10)
			}

			if pow10.Cmp(pow) > 0 {
				break
			}

			if len(pow.String()) == n {
				fmt.Println(x, n, pow.String())
				cnt++
			}
		}
	}

	fmt.Println(cnt)
}

```


### CPP

使用我们自己封装的大数运算函数（add, mul），详见 [Problem 16 Power digit sum](http://zhujiangtao.com/problem-16-power-digit-sum/)

基于 add,mul 实现 pow() 函数，如此，就能和 python\golang 一样处理本题的大数问题了


```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

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

// x^n
std::vector<char> pow(int x, int n)
{
	if(n == 0){
		std::vector<char> v;
		v.push_back('1');
		return v;
	}

	std::vector<char> vx = int2vector(x);
	std::vector<char> product = int2vector(x);

	for(int i = 1; i <= n-1; i++){
		product = mul(product, vx);
	}
	
	return product;
}

// a>b: return 1
// a==b: return 0
// a<b: return -1
int compare(const std::vector<char>& a, const std::vector<char>& b)
{
	if(a.size() > b.size()) return 1;
	if(a.size() < b.size()) return -1;

	for(int i = a.size()-1; i >= 0; i--){
		if(a[i] > b[i]) return 1;
		if(a[i] < b[i]) return -1;
	}

	return 0;
}

std::string v2string(const std::vector<char>& v)
{
	std::string s;
	for(int i = 0; i<v.size(); i++){
		s.push_back(v[i]);
	}
	return s;
}

int main()
{
	int cnt = 0;
	for (int x = 1; x < 10; x++ ){

		for (int n = 1;;n++){
			std::vector<char> powx = pow(x, n);
			std::vector<char> pow10 = pow(10, n-1);
			if (compare(pow10, powx) > 0) {
				break;
			}

			if (powx.size() == n) {
				printf("%d, %d, %s\n", x,n, v2string(powx).c_str());
				cnt += 1;
			}
		}

	}

	printf("%d\n", cnt);
	return 0;

}
```

## 答案

49

这 49 个数为

```
1^1, 1
2^1, 2
3^1, 3
4^1, 4
4^2, 16
5^1, 5
5^2, 25
5^3, 125
6^1, 6
6^2, 36
6^3, 216
6^4, 1296
7^1, 7
7^2, 49
7^3, 343
7^4, 2401
7^5, 16807
7^6, 117649
8^1, 8
8^2, 64
8^3, 512
8^4, 4096
8^5, 32768
8^6, 262144
8^7, 2097152
8^8, 16777216
8^9, 134217728
8^10, 1073741824
9^1, 9
9^2, 81
9^3, 729
9^4, 6561
9^5, 59049
9^6, 531441
9^7, 4782969
9^8, 43046721
9^9, 387420489
9^10, 3486784401
9^11, 31381059609
9^12, 282429536481
9^13, 2541865828329
9^14, 22876792454961
9^15, 205891132094649
9^16, 1853020188851841
9^17, 16677181699666569
9^18, 150094635296999121
9^19, 1350851717672992089
9^20, 12157665459056928801
9^21, 109418989131512359209
```