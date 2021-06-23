# Problem 4: Largest palindrome product

> https://projecteuler.net/problem=4

A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 ×99.

Find the largest palindrome made from the product of two 3-digit numbers.

## 分析
两个3位数乘积能得到的最大回文数。

思路：首先要能判断一个数是否是回文数isPalindrome()，其次要能判断一个数能否是两个3位数的乘积isProduct()，最后从两个三位数的最大乘积999*999=9989001开始，到最小乘积100*100=10000递减，判断是否是回文数和乘积。重点是isPalindrome()函数如何判断回文数。C\C++中，可以通过对要判断的数n，获取每一位上的数字，计算逆序形成的数是否和原数n相等，相等则是回文数，不等则不是。Python中，就相当简单了，将数n转换为string类型，然后再逆置一下，判断与原string是否相等即可。

## 方法1 通过数字的拆分重组，判断是否是回文

如 n = 123，依次拆得 3，2，1，并且对 3，2，1进行重组，即 sum = 3 + 2 * 10 + 1 * 100
判断 n 是否等于 sum，相等则为回文数

### CPP

```cpp
#include <stdio.h>

bool isPalindrome(int n)
{
    int m=n, sum = 0;
    while (m) {
        sum = sum*10 + m%10; // m%10 the lowest digital
        m /= 10;
    }
    return (n == sum);
}

int main()
{
    int max = 0;
    for(int i = 999; i > 100; i--){
        for(int j=i-1; j >= 100; j--){
            if( i*j > max && isPalindrome(i*j)){
                max = i*j;
            }
        }
    }
    printf("%d\n", max);
    return 0;
}
```

讲解一下 isPalindrome() 函数，以isPalindrome(n=1234)为例，具体过程如下：

- 初始化时: m=n, sum=0；m用于拆分
- 取m的个位数，m%10 = 4，sum = sum*10 +m%10 = 0 *10  + 4 = 4，  m= m/10 = 123
- 取m的个位数，m%10 = 3，sum = sum*10 +m%10 = 4 *10  + 3 = 43， m= m/10 = 12 
- 取m的个位数，m%10 = 2，sum = sum*10 +m%10 = 43*10  + 2 = 432，m= m/10 = 1
- 取m的个位数，m%10 = 1，sum = sum*10 +m%10 = 432*10 + 1 = 432，m= m/10 = 0，结束

如此，n=1234,sum=4321.  判断两者是否相等，即可知道n是否是回文数

### Golang

```go
package main

import "fmt"

func isPalindrome(n int) bool {
	m, sum := n, 0
	for m > 0 {
		sum = sum*10 + m%10
		m /= 10
	}
	return (n == sum)
}

func main(){
    
	max := 0
	for i := 999; i > 100; i-- {
		for j := i -1; j >= 100; j-- {
			if( i*j > max && isPalindrome(i*j) ){
				max = i*j
			}
		}
	}

	fmt.Println(max)
}
```

### Python

```python
def isPalindrome(n):
    m, sum = n, 0
    while m > 0 :
        sum = sum*10 + m%10
        m = int(m/10)
    return (n == sum)

max = 0
for i in range(999, 100, -1):
    for j in range(i-1, 99, -1):
        if i*j > max and isPalindrome(i*j) :
            max = i*j
print(max)
```

## 方法2 将数字转换为字符串，再将字符串逆序，比较字符串

### CPP

相比方法1，仅仅改变了 isPalindrome 函数

```cpp
#include <stdio.h>
#include <string.h>

bool isPalindrome(int n)
{
    char strN[32] = {0};
    snprintf(strN,32,"%d", n);

    int len = strlen(strN);
    for(int i=0; i<len/2; i++){
        if(strN[i] != strN[len-1-i]) return false;
    }

    return true;
}

int main()
{
    int max = 0;
    for(int i = 999; i > 100; i--){
        for(int j=i-1; j >= 100; j--){
            if( i*j > max && isPalindrome(i*j)){
                max = i*j;
            }
        }
    }
    printf("%d\n", max);
    return 0;
}
```

### Golang

```go
package main

import "fmt"

func isPalindrome(n int) bool {
	strN := fmt.Sprintf("%d",n)
	
	sz := len(strN)
	for i := 0; i < sz/2; i ++ {
		if strN[i] != strN[sz-1-i] {
			return false
		}
	}
	return true
}

func main(){
    
	max := 0
	for i := 999; i > 100; i-- {
		for j := i -1; j >= 100; j-- {
			if( i*j > max && isPalindrome(i*j) ){
				max = i*j
			}
		}
	}

	fmt.Println(max)
}
```

### Python

```python
def isPalindrome(n):
    strN = str(n)
    strReversed = strN[::-1]
    return strN == strReversed

max = 0
for i in range(999, 100, -1):
    for j in range(i-1, 99, -1):
        if i*j > max and isPalindrome(i*j) :
            max = i*j
print(max)
```

isPalindrome函数中，利用str(n)将n转换为字符串strN，然后利用strN的步长为-1的切片，将strN反转，赋值给strReversed。判断strN与strReversed是否相等即可。

**利用列表推导方法和max函数将代码合成了一行**

```python
print( max([x*y for x in range(100,1000) for y in range(100,1000) if str(x*y) == str(x*y)[::-1]]) )
```

## 答案
906609

## 知识点
- 判断回文数
- 字符串反转
