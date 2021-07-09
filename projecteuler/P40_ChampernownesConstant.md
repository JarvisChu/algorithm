# Problem 40: Champernowne's constant

> https://projecteuler.net/problem=40


An irrational decimal fraction is created by concatenating the positive integers:

0.12345678910**1**112131415161718192021...

It can be seen that the 12<sup>th</sup> digit of the fractional part is 1.

If d<sub>n</sub> represents the n<sup>th</sup> digit of the fractional part, find the value of the following expression.

d<sub>1</sub> x d<sub>10</sub>  x d<sub>100</sub>  x d<sub>1000</sub>  x d<sub>10000</sub>  x d<sub>100000</sub>  x d<sub>1000000</sub> 

## 分析

一个分数的小数部分由1,2,3,... 连续递增的正整数连接而成。求该分数的 第1位数字 * 第10位数字 * ... * 第1000000数字 的乘积

有几种解法：

- 方法1 直接从1往后遍历，把当前数的每一位拆分出来存放到 vector 中。然后直接从vector中取第1,10...100000 位数字相乘 [适合 c/c++/golang]
- 方法2 直接从1往后遍历，先计算当前数字 i 的位数并累加，只有出现了第 10/100/...1000000 位时，才拆分当前的数，来获取第 n 位的数字，用于累乘。[适合 c/c++/golang]
- 方法3 直接将每个数转换为string，使用字符连接。计算最终字符串的第 1/10/100/...1000000 位的乘积 [适合 c++/golang/python]

## 方法1 遍历拆分每一个数 [适合 c/c++/golang]

### CPP

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> digits; // 保存所有的数字
    digits.push_back(0);     // 从0开始，就不用考虑下标问题了

    // 从1开始遍历，将所有数的每一位保存在digits中
    for(int i = 1; i < 1000000; i++){

        //将i的各位数字保存到digits容器中
		int len=0;
		int cpy=i;
		int tmp[6];
		while (cpy > 0){
			tmp[len++] = cpy % 10;
			cpy /= 10;
		}

        for (int k = len-1; k >= 0; k--){
			digits.push_back(tmp[k]);
		}
    }

    std::cout<<digits[1]*digits[10]*digits[100]*digits[1000]*digits[10000]*digits[100000]<<std::endl;
	return 0;
}
```

### Golang

```go
package main

import (
	"fmt"
)

func main() {

	var digits []int           // 保存所有的数字
	digits = append(digits, 0) // 从0开始，就不用考虑下标问题了

	// 从1开始遍历，将所有数的每一位保存在digits中
	for i := 1; i < 1000000; i++ {

		//将i的各位数字保存到digits容器中
		cpy := i
		var tmp []int
		for cpy > 0 {
			tmp = append(tmp, cpy%10)
			cpy /= 10
		}

		for k := len(tmp) - 1; k >= 0; k-- {
			digits = append(digits, tmp[k])
		}
	}

	fmt.Println(digits[1] * digits[10] * digits[100] * digits[1000] * digits[10000] * digits[100000])
}

```

## 方法2 遍历并累加当前数字的长度 [适合 c/c++/golang]

遍历过程中，先获取当前数的位数，并累加。 只有出现了第 10/100/...1000000 位时，才拆分当前的数，来获取第 n 位的数字，用于累乘。

### CPP

```cpp
#include <stdio.h>

int main()
{
    int product = 1; // 最终的乘积
    int n = 1;       // dn
    int bits = 1;    // 当前数字的位数
    int mod1 = 10;   // 用于计算当前数字的位数
    int mod2 = 10;   // 用于计算 n 是否是10，1000，10000...
    for(int i = 2; ; i++){

        // 获取i的位数
        if(i % mod1 == 0){ // 10,100,1000 时，位数+1
            bits ++;
            mod1 *= 10;
        }

        // 统计i的每一位数字
        for(int k = 0; k < bits; k++){
            n ++;

            if (n % mod2 == 0) { // n = 10,100,1000,10000...
                mod2 *= 10;

                // 获取 i 的第 k 位
                char buf[32] = {0};
                snprintf(buf,32,"%d",i);
                int dn = buf[k] - '0'; 

                product *= dn; // product 乘以 i 的第k位
            }
        }  

        if(n > 1000000) break;
    }

    printf("%d\n", product);
    return 0;
}
```

### Golang

```go
package main

import (
	"fmt"
)

func main() {

	product := 1 // 最终的乘积
	n := 1       // dn
	bits := 1    // 当前数字的位数
	mod1 := 10   // 用于计算当前数字的位数
	mod2 := 10   // 用于计算 n 是否是10，1000，10000...
	for i := 2; ; i++ {

		// 获取i的位数
		if i%mod1 == 0 { // 10,100,1000 时，位数+1
			bits++
			mod1 *= 10
		}

		// 统计i的每一位数字
		for k := 0; k < bits; k++ {
			n++

			if n%mod2 == 0 { // n = 10,100,1000,10000...
				mod2 *= 10

				// 获取 i 的第 k 位
				s := fmt.Sprintf("%d", i)
				dn := s[k] - '0'

				product *= int(dn) // product 乘以 i 的第k位
			}
		}

		if n > 1000000 {
			break
		}
	}

	fmt.Println(product)
}
```

## 方法3 直接将每个数转换为string，使用字符连接 [适合 c++/golang/python]

### CPP

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string digits;
    for(int i = 0; i < 1000000; i++){
        digits += std::to_string(i);
        if(digits.size() > 1000000) break;
    }
    std::cout << (digits[1]-'0') * (digits[10]-'0') * (digits[100]-'0') * (digits[1000]-'0') * (digits[10000]-'0') * (digits[100000]-'0') * (digits[1000000]-'0')  << std::endl;
	return 0;
}
```

### Golang

```go
package main

import "fmt"

func main() {

	digits := ""
	for i := 0; i < 1000000; i++ {
		digits += fmt.Sprintf("%d", i)
		if len(digits) > 1000000 {
			break
		}
	}

	fmt.Println((digits[1] - '0') * (digits[10] - '0') * (digits[100] - '0') * (digits[1000] - '0') * (digits[10000] - '0') * (digits[100000] - '0') * (digits[1000000] - '0'))
}

```

### Python

```python

digits = ''
for i in range(0, 1000000):
	digits += str(i)
	if len(digits) > 1000000 :
		break

#print(digits)
print( int(digits[1]) * int(digits[10]) * int(digits[100]) * int(digits[1000]) * int(digits[10000]) * int(digits[100000]) * int(digits[1000000]) )
```

## 答案

210
