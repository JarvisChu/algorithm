# Problem 33: Digit cancelling fractions

> https://projecteuler.net/problem=33

The fraction <sup>49</sup>/<sub>98</sub> is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that<sup>49</sup>/<sub>98</sub> = <sup>4</sup>/<sub>8</sub>, which is correct, is obtained by cancelling the 9s.

We shall consider fractions like, <sup>30</sup>/<sub>50</sub> = <sup>3</sup>/<sub>5</sub>, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.

If the product of these four fractions is given in its lowest common terms, find the value of the denominator.


## 分析
<sup>49</sup>/<sub>98</sub> = <sup>4</sup>/<sub>8</sub>  通过删除9，所得结果也是正确的。找到分子分母都是2位数（分子小于分母），且满足这种条件的（即<sup>ab</sup>/<sub>bc</sub> = <sup>a</sup>/c  ）数，这样的分数共有4个。求这个四个分数的乘积最后约分简化后的分母。


## 方法 遍历穷举

问题的规模并不大，a/b，其中ab都是两位数。可以直接穷举来获得满足条件的分数。 然后将四个分数相乘，再约分简化，输出分母即为最终的答案。

### CPP

```cpp
#include <iostream>
#include <vector>

// 判断两个分数是否相等
// return a1/a2 == b1/b2
bool isFractionEqual(int a1, int a2, int b1, int b2)
{
    // a1/a2 == b1/b2 => a1*b2 = b1*a2
    return a1 * b2 == b1 * a2;
}

int main()
{
    int numeratorOfProduct = 1;   // 所有满足条件分数乘积的分子
    int denominatorOfProduct = 1; // 所有满足条件分数乘积的分母

    // 找到满足条件的分数
    for(int numerator = 11; numerator < 99; numerator++){ // 分子
        for(int denominator = numerator+1; denominator <= 99; denominator++){ // 分母
            // numerator/denominator 满足 ab/bc
            if(numerator % 10 != denominator/10 ) continue; // 分子的个位 必须等于 分母的十位

            // numerator/denominator = ab/bc
            // (numerator/10)/(denominator%10) = a/c
            // check if ab/bc == a/c
            if( isFractionEqual( numerator,denominator, numerator/10, denominator%10 )){
                std::cout << numerator << "/" << denominator << " = " << numerator/10 << "/" << denominator%10 <<std::endl;
                numeratorOfProduct *= numerator/10;
                denominatorOfProduct *= denominator%10;
            }
        }
    }

    // 满足条件的所有分数的乘积是 numeratorOfProduct/denominatorOfProduct
    std::cout<<"product of all fraction is: " << numeratorOfProduct << "/" << denominatorOfProduct << std::endl;

    // 分子分母进行约分简化
    for(int i = numeratorOfProduct; i >= 1; i --){
        if(numeratorOfProduct % i == 0 && denominatorOfProduct % i == 0){
            numeratorOfProduct /= i;
            denominatorOfProduct /= i;
            std::cout<<"after simplified: " << numeratorOfProduct << "/" << denominatorOfProduct << std::endl;
            break;
        }
    }

    // 输出最后的结果
    std::cout << "answer is: " << denominatorOfProduct <<std::endl;

    return 0;
}
```

输出如下：

```
16/64 = 1/4
19/95 = 1/5
26/65 = 2/5
49/98 = 4/8
product of all fraction is: 8/800
after simplified: 1/100
answer is: 100
```

### Golang

```go
package main

import "fmt"

// 判断两个分数是否相等
// return a1/a2 == b1/b2
func isFractionEqual(a1, a2, b1, b2 int) bool {
	// a1/a2 == b1/b2 => a1*b2 = b1*a2
	return a1*b2 == b1*a2
}

func main() {

	numeratorOfProduct := 1   // 乘积的分子
	denominatorOfProduct := 1 // 乘积的分母

	// 找到满足条件的分数
	for numerator := 11; numerator < 99; numerator++ { // 分子
		for denominator := numerator + 1; denominator <= 99; denominator++ { // 分母
			// numerator/denominator 满足 ab/bc
			if numerator%10 != denominator/10 { // 分子的个位 必须等于 分母的十位
				continue
			}

			// numerator/denominator = ab/bc
			// (numerator/10)/(denominator%10) = a/c
			// check if ab/bc == a/c
			if isFractionEqual(numerator, denominator, numerator/10, denominator%10) {
				fmt.Printf("%d/%d = %d/%d\n", numerator, denominator, numerator/10, denominator%10)
				numeratorOfProduct *= numerator / 10
				denominatorOfProduct *= denominator % 10
			}
		}
	}

	// 满足条件的所有分数的乘积是 numeratorOfProduct/denominatorOfProduct
	fmt.Printf("product of all fraction is: %d/%d\n", numeratorOfProduct, denominatorOfProduct)

	// 分子分母进行约分简化
	for i := numeratorOfProduct; i >= 1; i-- {
		if numeratorOfProduct%i == 0 && denominatorOfProduct%i == 0 {
			numeratorOfProduct /= i
			denominatorOfProduct /= i
			fmt.Printf("after simplified: %d/%d\n", numeratorOfProduct, denominatorOfProduct)
			break
		}
	}

	// 输出最后的结果
	fmt.Printf("answer is: %d \n", denominatorOfProduct)

}

```

### Python

```python

# 判断两个分数是否相等
# return a1/a2 == b1/b2
def isFractionEqual(a1, a2, b1, b2) :
	# a1/a2 == b1/b2 => a1*b2 = b1*a2
	return a1*b2 == b1*a2

numeratorOfProduct = 1   # 乘积的分子
denominatorOfProduct = 1 # 乘积的分母

# 找到满足条件的分数
for numerator in range(11,99) : # 分子
	for denominator in range(numerator + 1, 100) : # 分母
		# numerator/denominator 满足 ab/bc
		if numerator%10 != int(denominator/10) : # 分子的个位 必须等于 分母的十位
				continue

		# numerator/denominator = ab/bc
		# (numerator/10)/(denominator%10) = a/c
		# check if ab/bc == a/c
		if isFractionEqual(numerator, denominator, int(numerator/10), denominator%10):
			print(numerator,"/",denominator, "=", int(numerator/10),"/",denominator%10)
			numeratorOfProduct *= int(numerator / 10)
			denominatorOfProduct *= denominator % 10

# 满足条件的所有分数的乘积是 numeratorOfProduct/denominatorOfProduct
print("product of all fraction is:", numeratorOfProduct,"/",denominatorOfProduct)

# 分子分母进行约分简化
for i in range(numeratorOfProduct, 0, -1) :
	if numeratorOfProduct%i == 0 and denominatorOfProduct%i == 0 :
		numeratorOfProduct /= i
		denominatorOfProduct /= i
		print("after simplified:", int(numeratorOfProduct),"/",int(denominatorOfProduct))
		break

# 输出最后的结果
print("answer is:", int(denominatorOfProduct))

```

## 答案
100


