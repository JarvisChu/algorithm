# Problem 8: Largest product in a series

> https://projecteuler.net/problem=8

The four adjacent digits in the 1000-digit number that have the greatest product are 9 × 9 × 8 × 9 = 5832.

73167176531330624919225119674426574742355349194934
96983520312774506326239578318016984801869478851843
85861560789112949495459501737958331952853208805511
12540698747158523863050715693290963295227443043557
66896648950445244523161731856403098711121722383113
62229893423380308135336276614282806444486645238749
30358907296290491560440772390713810515859307960866
70172427121883998797908792274921901699720888093776
65727333001053367881220235421809751254540594752243
52584907711670556013604839586446706324415722155397
53697817977846174064955149290862569321978468622482
83972241375657056057490261407972968652414535100474
82166370484403199890008895243450658541227588666881
16427171479924442928230863465674813919123162824586
17866458359124566529476545682848912883142607690042
24219022671055626321111109370544217506941658960408
07198403850962455444362981230987879927244284909188
84580156166097919133875499200524063689912560717606
05886116467109405077541002256983155200055935729725
71636269561882670428252483600823257530420752963450

Find the thirteen adjacent digits in the 1000-digit number that have the greatest product. What is the value of this product?

## 分析

找出1000个数字中，连续的13个数字，乘积最大，求该乘积

## 方法1 遍历

比如连续的13个数为：a1,a2,a3 ... a11,a12,a13
product(a1,a13) = a1 * a2 * a3 ... *a11 * a12 * a13

向后寻找时，我们不用每次都将13个数字相乘，比如查找一个连续的13个数
product(a2,a14) = a2 * a3 * a4 ... *a12 * a13 * a14

一旦发现数字为0，则可以快速的向后跳跃 13个数字，因为 0 乘以任何数的乘积都是0

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const char * digits = 

"73167176531330624919225119674426574742355349194934\
96983520312774506326239578318016984801869478851843\
85861560789112949495459501737958331952853208805511\
12540698747158523863050715693290963295227443043557\
66896648950445244523161731856403098711121722383113\
62229893423380308135336276614282806444486645238749\
30358907296290491560440772390713810515859307960866\
70172427121883998797908792274921901699720888093776\
65727333001053367881220235421809751254540594752243\
52584907711670556013604839586446706324415722155397\
53697817977846174064955149290862569321978468622482\
83972241375657056057490261407972968652414535100474\
82166370484403199890008895243450658541227588666881\
16427171479924442928230863465674813919123162824586\
17866458359124566529476545682848912883142607690042\
24219022671055626321111109370544217506941658960408\
07198403850962455444362981230987879927244284909188\
84580156166097919133875499200524063689912560717606\
05886116467109405077541002256983155200055935729725\
71636269561882670428252483600823257530420752963450";

int main()
{
    int     maxStartIdx = 0;
    int64_t maxProduct  = 0;

    for(int i=0; i < 1000-13; i++){
        int64_t product = 1;

        for(int j=i+12; j>=i; j --){ // 从后往前累乘，这样一旦发现 0，可以快速的跳到 0 的下一位。略过了 0 之前可能出现的0，跳的最远。
            if( digits[j] == '0') {
                i = j; // 快速往后移动。 本来应该是：i = j + 1, 但 for循环中已有 i++
                break;
            }
            product *= (int64_t)(digits[j]-'0');
        }

        if(product > maxProduct){
            maxProduct = product;
            maxStartIdx = i;
        }
    }

    printf("max product is: %lld\n", maxProduct);
    for(int i = maxStartIdx; i<maxStartIdx+13; i++){
        printf("%c ", digits[i]);
    }

    return 0;
}
```

### Golang

```go
package main

import "fmt"

var digits = 
"73167176531330624919225119674426574742355349194934" + 
"96983520312774506326239578318016984801869478851843" + 
"85861560789112949495459501737958331952853208805511" + 
"12540698747158523863050715693290963295227443043557" + 
"66896648950445244523161731856403098711121722383113" + 
"62229893423380308135336276614282806444486645238749" + 
"30358907296290491560440772390713810515859307960866" + 
"70172427121883998797908792274921901699720888093776" +
"65727333001053367881220235421809751254540594752243" + 
"52584907711670556013604839586446706324415722155397" + 
"53697817977846174064955149290862569321978468622482" + 
"83972241375657056057490261407972968652414535100474" + 
"82166370484403199890008895243450658541227588666881" + 
"16427171479924442928230863465674813919123162824586" + 
"17866458359124566529476545682848912883142607690042" + 
"24219022671055626321111109370544217506941658960408" + 
"07198403850962455444362981230987879927244284909188" + 
"84580156166097919133875499200524063689912560717606" + 
"05886116467109405077541002256983155200055935729725" + 
"71636269561882670428252483600823257530420752963450"

func main(){
	maxStartIdx, maxProduct := 0, int64(0)

	for i:=0; i < 1000-13; i++ {
		product := int64(1)
		for j:=i+12; j>=i; j-- { // 从后往前累乘，这样一旦发现 0，可以快速的跳到 0 的下一位。略过了 0 之前可能出现的0，跳的最远。
			if digits[j] == '0' {
				i = j // 本来应该是：i = j + 1, 但 for循环中已有 i++
				break
			}
			product *= int64(digits[j]-'0')
		}

		if(product > maxProduct){
			maxProduct = product
			maxStartIdx = i
		}
	}

	fmt.Printf("max product is: %v\n", maxProduct);
	for i := maxStartIdx; i<maxStartIdx+13; i++ {
		fmt.Printf("%c ", digits[i]);
	}
}
```

## Python

```python
#coding=utf-8
#author: JarvisChu
#date:2014-3-18

from urllib.request import urlopen

def download_string():
    '''从网页上将1000个数字下载下来保存到一个字符串中'''
    url = 'http://projecteuler.net/problem=8'
    content = urlopen(url).read().decode('utf8')

    #从源码中，找出1000个数字字符
    start = content.find('73167176531330624919225119674426574742355349194934<br />')
    end = content.find('450<br />') + 8
    nums = content[start:end+1] #包含了每行结尾的HTML换行符 <br />，还有\n字符
    #print(nums)
    nums = nums.replace('<br />','') #去掉结尾的 HTML换行符 <br />
    nums = nums.replace('\n','') #去掉结尾的 \n
    #print(nums)
    return nums

def find_max(s):
    '''s是1000个数字的字符串，函数返回最大乘积'''

    maxStartIdx, maxProduct = 0, 0

    for i=0; i < 1000-13; i = i+1 :
        product = 1
        for j:=i+12; j>=i; j = j-1 : # 从后往前累乘，这样一旦发现 0，可以快速的跳到 0 的下一位。略过了 0 之前可能出现的0，跳的最远。
            if digits[j] == '0' :
                i = j # 本来应该是：i = j + 1, 但 for循环中 i++
                break
            product *= int(digits[j])
		}

		if product > maxProduct :
            maxProduct = product
			maxStartIdx = i
		}
	}

	print("max product is: ", maxProduct)
	for i = maxStartIdx; i<maxStartIdx+13; i = i+1 {
		print(digits[i], ' ')
	}
    return maxProduct

s = download_string()
print(find_max(s))
```


使用列表综合和reduce()函数，可以得到更简洁的方法


```python

def download_string():
    '''从网页上将1000个数字下载下来保存到一个字符串中'''
    
    from urllib.request import urlopen
    url = 'http://projecteuler.net/problem=8'
    content = urlopen(url).read().decode('utf8')

    #从源码中，找出1000个数字字符
    start = content.find('73167176531330624919225119674426574742355349194934<br />')
    end = content.find('450<br />') + 8
    nums = content[start:end+1] #包含了每行结尾的HTML换行符 <br />，还有\n字符
    #print(nums)
    nums = nums.replace('<br />','') #去掉结尾的 HTML换行符 <br />
    nums = nums.replace('\n','') #去掉结尾的 \n
    #print(nums)
    return nums


s = download_string()
nums = [int(c) for c in s]
#print(nums)

# using lambda
from functools import reduce
print( max([reduce(lambda x,y: x*y, nums[i:i+13]) for i in range (len(nums) - 13 ) ]) )

# using mul
from operator import mul
print( max([reduce(mul, nums[i:i+13]) for i in range (len(nums) - 13 ) ]) )
```

先将字符串转换为int数组，再使用 reduce 统计连续13个数字的和，再使用 max 从所有连续的13个数字的和中找到最大的值

> reduce() 函数原型为： reduce(function, sequence, initial=_initial_missing)， 对序列sequence，每两个作为参数，执行function函数。如reduce(lambda x, y: x+y, [1, 2, 3, 4, 5]) 就等同于((((1+2)+3)+4)+5) 。

lambda表达式就是创建了一个简单的函数，如lambda x, y: x+y，就相当于 def foo(x,y): return x+y 。

本题中只使用了简单的累乘，所以，可以使用operator模块的mul 替换lambda表达式。

## 答案
23514624000

## 知识点
- Python urllib模块使用
- Python reduce()函数
- Python Lambda