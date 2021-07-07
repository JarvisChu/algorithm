# Problem 32: Pandigital products

> https://projecteuler.net/problem=32

We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.

## 分析

Pandigital 是一个n位的数，它刚好由数字1~n组成。 39 x 186 = 7254，被乘数、乘数、积刚好由1~9组成，7254就是满足条件的一个积。求所有满足这种条件（即被乘数、乘数、积刚好由1~9组成）的积的和。

## 方法 缩小遍历范围后穷举遍历

如果 a * b = c 中 c 满足条件，假设a<b，则必然 a<b<c。因为a,b,c的位数总共等于9，所以a必然小于3位数（100*100=10000 共11位 > 9位）。所以a的范围最多为[1,98]。 a至少为1为，则b和c总共最多为8位，b<c，所以b最多为4位。所以b的范围为[a+1, 9876]。

有了a和b的范围，下面就是穷举遍历+判断了。为了确保数据的不重复，使用set来存储。


### CPP

```cpp
#include <iostream>
#include <vector>
#include <set>

// 判断 a,b,c 的所有数字是否满足条件，即a,b,c 的所有位刚好是1~9
bool isPandigitalProducts(int a, int b, int c)
{
    std::vector<int> digits;

    // 取出a的每一位数字
    while(a > 0){
        digits.push_back( a % 10 );
        if(a % 10 == 0) return false; // 如果存在数字0，必然不满足

        a /= 10;
    }

    // 取出b的每一位数字
    while(b > 0){
        digits.push_back( b % 10 );
        if(b % 10 == 0) return false; // 如果存在数字0，必然不满足

        b /= 10;
    }

    // 取出c的每一位数字
    while(c > 0){
        digits.push_back( c % 10 );
        if(c % 10 == 0) return false; // 如果存在数字0，必然不满足

        c /= 10;
    }

    // 如果满足，则digits的长度必然是9
    if(digits.size() != 9){
        return false;
    }

    // 如果满足条件，则digits中必然只有1~9，不会有重复数字
    // 使用set 去重
    std::set<int> digitsUnique;
    for(int i = 0; i < 9; i++){
        digitsUnique.insert(digits[i]);
    }

    return digitsUnique.size() == 9;
}

int main()
{

    // a * b = c
    std::set<int> answers; // 使用set去重
    for(int a = 1; a <= 98; a++){
        for(int b = a+1; b <= 9876; b++){
            if(isPandigitalProducts(a,b,a*b)){
                std::cout << a << " * " << b << " = " << a*b <<std::endl;
                answers.insert(a*b);
            }
        }
    }

    int sum = 0; 
    for(std::set<int>::iterator it = answers.begin(); it != answers.end(); it ++){
        sum += *it;
    }

    std::cout << sum << std::endl;
    return 0;
}
```

### Golang

使用 map 来做去重

```go
package main

import "fmt"

// 判断 a,b,c 的所有数字是否满足条件，即a,b,c 的所有位刚好是1~9
func isPandigitalProducts(a, b, c int) bool {
	digits := make([]int, 0)

	// 取 a 的每一位数字
	for a > 0 {
		digits = append(digits, a % 10)
		if a % 10 == 0 { // 如果存在数字0，必然不满足
			return false
		}
		a /= 10
	}

	// 取 b 的每一位数字
	for b > 0 {
		digits = append(digits, b % 10)
		if b % 10 == 0 { // 如果存在数字0，必然不满足
			return false
		}
		b /= 10
	}

	// 取 c 的每一位数字
	for c > 0 {
		digits = append(digits, c % 10)
		if c % 10 == 0 { // 如果存在数字0，必然不满足
			return false
		}
		c /= 10
	}

	// 如果满足，则digits的长度必然是9
	if len(digits) != 9 {
		return false
	}

	// 如果满足条件，则digits中必然只有1~9，不会有重复数字
	// 使用map 去重
	digitsUnique := make(map[int]struct{}, 0) // value 为 struct{} 不占内存
	for _, d := range digits{
		if _, ok := digitsUnique[d]; ok { // 出现重复
			return false
		}
		digitsUnique[d] = struct{}{}
	}

	return true
}

func main() {
	// a * b = c
	answers := make(map[int]struct{}, 0) // 使用map去重

	for a := 1; a <= 98; a++ {
		for b := a+1; b <= 9876; b++ {
			if isPandigitalProducts(a,b,a*b) {
				fmt.Printf("%v*%v=%v\n", a, b, a*b)
				answers[a*b] = struct{}{}
			}
		}
	}

	sum := 0
	for k := range answers{
		sum += k
	}
	fmt.Println(sum)
}

```

### Python

不用像 cpp/golang 一样取出数字的每一位，可以直接将数字转换为string即可

```python
def is_unique(s):
    ''' whether s has two same digits '''
    if '0' in s:
        return False
    return len(s) == len(set(s)) #using set to unique

answers = set()
for a in range(1, 99): #[1,99)
    if not is_unique(str(a)): #digits of a must be unique
        continue

    for b in range(a+1, 9877):
        if not is_unique(str(b)): #digits of b must be unique
            continue

        s = str(a)+str(b)+str(a*b)
        if len(s) == 9 and is_unique(s):
            print(a,b,a*b)
            answers.add(a*b)

print (sum(answers))
```

## 答案
45228
