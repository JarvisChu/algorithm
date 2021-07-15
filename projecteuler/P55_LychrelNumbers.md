# Problem 55: Lychrel numbers

> https://projecteuler.net/problem=55

If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.

Not all numbers produce palindromes so quickly. For example,

349 + 943 = 1292,
1292 + 2921 = 4213
4213 + 3124 = 7337

That is, 349 took three iterations to arrive at a palindrome.

Although no one has proved it yet, it is thought that some numbers, like 196, never produce a palindrome. A number that never forms a palindrome through the reverse and add process is called a Lychrel number. Due to the theoretical nature of these numbers, and for the purpose of this problem, we shall assume that a number is Lychrel until proven otherwise. In addition you are given that for every number below ten-thousand, it will either (i) become a palindrome in less than fifty iterations, or, (ii) no one, with all the computing power that exists, has managed so far to map it to a palindrome. In fact, 10677 is the first number to be shown to require over fifty iterations before producing a palindrome: 4668731596684224866951378664 (53 iterations, 28-digits).

Surprisingly, there are palindromic numbers that are themselves Lychrel numbers; the first example is 4994.

How many Lychrel numbers are there below ten-thousand?

NOTE: Wording was modified slightly on 24 April 2007 to emphasise the theoretical nature of Lychrel numbers.

## 分析

47 逆序得到 74， 47 + 74 = 121 是一个回文数。 349 需要迭代 3 次：349 + 943 = 1292, 1292 + 2921 = 4213，4213 + 3124 = 7337 才能得到一个回文数。
尽管没被证明，但有些数，比如 196，无论迭代多少次(次数 >= 1)，都不会生成一个回文数，这样的数被称为 **Lychrel number**。
注意：4994 虽然本身是回文数，但是它仍然是**Lychrel number**，因为它经过1~N次迭代，都是无法得到回文数的。

对于本题，如果一个数迭代50次之后，还没有得到回文数，则认为它是 **Lychrel number**，统计 10000 一下的所有**Lychrel number**的个数。

思路：存在大数问题

## 方法1 使用字符串解决大数问题 [适用于C++]

使用 vector 存储数字的每一位

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

bool isEqual(const std::vector<char>& v1, const std::vector<char>& v2)
{
    for(int i = 0; i < v1.size(); i++){
        if(v1[i] != v2[i]){
            return false;
        }
    }
    return true;
}

bool isLychrelNumber(int n) 
{
    std::vector<char> number = int2vector(n);
    std::vector<char> reversed;
    std::reverse_copy(number.begin(), number.end(), std::back_inserter(reversed));


	// 最多迭代50次
	for (int iterator = 1; iterator <= 50; iterator++ ) {
        std::vector<char> sum = add(number, reversed);
        std::vector<char> sumReversed;
        std::reverse_copy(sum.begin(), sum.end(), std::back_inserter(sumReversed));

        if( isEqual(sum, sumReversed)) { // 回文
            return false;
        }

        number.swap(sum);
        reversed.swap(sumReversed);
	}

	return true;
}

int main()
{
    int cnt = 0;
    for (int i = 1; i < 10000; i++) {
		if (isLychrelNumber(i)) {
			//printf("%d\n", i);
            cnt++;
		}
	}
    
    printf("cnt:%d\n", cnt);
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

// 1234 -> 4321
func Reverse(n *big.Int) *big.Int {
	r := big.NewInt(0)
	strN := n.String()
	for i := len(strN) - 1; i >= 0; i-- {
		r.Mul(r, big.NewInt(10))                // r *= 10
		r.Add(r, big.NewInt(int64(strN[i]-48))) // 字符转数字：s-48
	}
	return r
}

func isLychrelNumber(n int) bool {

	number := big.NewInt(int64(n))
	reversed := Reverse(number)

	// 最多迭代50次
	for iterator := 1; iterator <= 50; iterator++ {
		sum := big.NewInt(0).Add(number, reversed)
		sumReversed := Reverse(sum)
		if sum.String() == sumReversed.String() {
			return false
		}

		number, reversed = sum, sumReversed
	}

	return true
}
func main() {

	var lychrelNumbers []int
	for i := 1; i < 10000; i++ {
		if isLychrelNumber(i) {
			lychrelNumbers = append(lychrelNumbers, i)
		}
	}

	fmt.Println(len(lychrelNumbers))
}
```

## 方法3 无需考虑大数问题，直接计算 [适用于 Python]

```python
def isLychrelNumber(n):
    for iterator in range(1,51): # 最多50次迭代
        reversed = int( str(n)[::-1] )
        sum = n + reversed
        if str(sum) == str(sum)[::-1] : # 判断是否回文
            return False
        n = sum

    return True

lychrelNumbers = []
for i in range(1, 10000):
    if isLychrelNumber(i):
        lychrelNumbers.append(i)

print(len(lychrelNumbers))
#print(lychrelNumbers)
```

## 答案

249



