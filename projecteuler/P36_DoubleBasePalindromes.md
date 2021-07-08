# Problem 36: Double-base palindromes

https://projecteuler.net/problem=36

The decimal number, 585 = 1001001001<sub>2</sub> (binary), is palindromic in both bases.

Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not include leading zeros.)

## 分析

一个数，二进制和十进制都是回文数。求1000,000以内所有这样的数的和。

问题的核心点有两个：(1) 十进制转二进制；(2) 判断数字是否是回文

### 核心点1： 十进制转二进制

**(1) 手动编码实现**

可以参考[C++数制转换](http://zhujiangtao.com/cpp-conversion-of-number-systems/)这篇博客，其中实现了各种进制之间的转换，当然包括了十进制转化为二进制。其核心思想是不断的 %x 后再 /= x来转换为x进制，代码如下：

```cpp
// 十进制 n 转换为 x 进制
std::string decimalToX(int n, int x)
{
    // 对 n 循环 mod x ，结果存放在 chs 中
    std::string chs;
    while(n > 0){
        char ch =  n % x + '0'; // + '0' 转换为字符
        
        // 如果 x 大于10进制，则将大于 9 的字符，转换成字母
        if ( ch > '9') {
            ch += ('A' - '9' - 1);
        }

        chs = std::string(&ch) + chs; // ch 放到 chs 的开头.  &ch 为了将 char 转换为 string
        n /= x;
    }

   return chs;
}
```

因为itoa 不是标准库的一部分，可以手动实现一份itoa

```cpp
// myItoa 
// itoa is not part of standard library
char*  myItoa(int value, char* str, int base)
{
    char* p = str;
    int len = 0;
    while(value > 0){
        char ch =  value % base + '0';
        if ( ch > '9') {
            ch += ('A' - '9' - 1);
        }
        *p++ = ch;
        value /= base;
        len ++;
    }

    for(int i = 0; i <= len/2; i++){
        char tmp = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = tmp;
    }

    str[len] = '\0';

    return str;
}
```

**(2) 使用库函数**

c/c++

```cpp

// 使用 snprintf 的方式
char buf[32] = {0};
snprintf(buf,32, "%o", 1234); // 转换为8进制
snprintf(buf,32, "%x", 1234); // 转换为16进制，小写 4d2
snprintf(buf,32, "%X", 1234); // 转换为16进制，大写 4D2

// 使用itoa

```

golang

```go

// 使用 fmt.Sprintf 
s := fmt.Sprintf("%b", 1234) // 转换为2进制
s := fmt.Sprintf("%o", 1234) // 转换为8进制
s := fmt.Sprintf("%x", 1234) // 转换为16进制，小写 4d2
s := fmt.Sprintf("%X", 1234) // 转换为16进制，大写 4D2

// 使用strconv.ParseXXX 
func ParseInt(s string, base int, bitSize int) (i int64, err error)

```

python

```python
# 使用 int() 将其它进制转换为 10进制
n = int('101010',2)  # 2进制转
n = int('1234',8)    # 8进制转10进制
n = int('0x12AB',16) # 16进制转10进制
n = int('12AB',16)   # 16进制转10进制

# 使用 bin()/hex()
b = bin(585) # 10进制转2进制，0b1001001001
o = oct(585) # 10进制转8进制，0o1111
h = hex(585) # 10进制转16进制，0x249
```

### 核心点2：判断数字是否是回文

- 方法1：拆解数字的过程中，再重组合

```cpp
// 判断 n 是否是回文数
bool isPalindromes(int n)
{
    int cpy = n;
    int r = 0; // reverse

    // 从低位到高位，拆解出 n 的每一位数字
    while(cpy > 0) {
        int v = cpy % 10; // 当前的最低位，比如 n = 1234，则 v = 4,3,2,1
        r = r * 10 + v;   // 重组
        cpy /= 10;
    }

    return n == r;
}
```

- 方法2：数字转换为字符串，比较字符串即可

```cpp
// 判断 n 是否是回文数
// e.g. n = "1234321"
bool isPalindromes(const char* n)
{
    int len = strlen(n);
    for(int i = 0; i <= len/2; i++){
        if(n[i] != n[len-1-i]) return false;
    }

    return true;
}
```

## 方法 遍历判断

解决了上面两个核心问题，问题的解决就很简单了

### CPP

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 判断 n 是否是回文数
bool isPalindromes(int n)
{
    int cpy = n;
    int r = 0; // reverse

    // 从低位到高位，拆解出 n 的每一位数字
    while(cpy > 0) {
        int v = cpy % 10; // 当前的最低位，比如 n = 1234，则 v = 4,3,2,1
        r = r * 10 + v;   // 重组
        cpy /= 10;
    }

    return n == r;
}

// myItoa 
// itoa is not part of standard library
char*  myItoa(int value, char* str, int base)
{
    char* p = str;
    int len = 0;
    while(value > 0){
        char ch =  value % base + '0';
        if ( ch > '9') {
            ch += ('A' - '9' - 1);
        }
        *p++ = ch;
        value /= base;
        len ++;
    }

    for(int i = 0; i <= len/2; i++){
        char tmp = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = tmp;
    }

    str[len] = '\0';

    return str;
}

// 判断 n 的二进制是否是回文数
bool isPalindromesBinary(int n)
{
    // n 转成 2 进制
    char bin[16] = {0};
    myItoa(n, bin, 2);

    int len = strlen(bin);
    for(int i = 0; i <= len/2; i++){
        if(bin[i] != bin[len-1-i]) return false;
    }

    return true;
}

int main()
{
    int sum = 0;
    for(int i = 1; i < 1000000; i++){
        if( isPalindromes(i) && isPalindromesBinary(i)){
            sum += i;
        }
    }
    printf("sum=%d\n", sum);
    return 0;
}
```


### Golang

```go
package main

import (
	"fmt"
)

// 判断 s 是否是回文数
func isPalindromes(s string) bool {
	size := len(s)
	for i := 0; i <= size/2; i++ {
		if s[i] != s[size-1-i] {
			return false
		}
	}
	return true
}

func main() {
	sum := 0
	for i := 1; i < 1000000; i++ {
		decimal := fmt.Sprintf("%d", i)
		bin := fmt.Sprintf("%b", i)

		if isPalindromes(decimal) && isPalindromes(bin) {
			fmt.Printf("%s, %s\n", decimal, bin)
			sum += i
		}
	}

	fmt.Println(sum)
}

```

### Python

通过 s[::-1] 来逆序
通过 str(i) == str(i)[::-1] 来判断是否是回文

注意 bin() 返回带有 0b 前缀，所以需要通过 bin(i)[2:] 去除

```python
sum = 0
for i in range(1,1000000):
    if str(i) == str(i)[::-1] and bin(i)[2:] == bin(i)[2:][::-1]:
        sum += i
print(sum)
```

或者写成一行

```python
print(sum( [i for i in range(1,1000000) if str(i) == str(i)[::-1] and bin(i)[2:] == bin(i)[2:][::-1] ] ))
```

## 答案
872187