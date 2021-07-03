# Problem 21: Amicable numbers

> https://projecteuler.net/problem=21

Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.

## 分析

亲和数。一个数a的所有因子的和（不含a）等于另一个数b，刚好b的所有因子和（不包括b）也等于a，则a和b是一对亲和数。统计10000以下所有亲和数的和。

## 方法1 直接遍历计算每个数的因子和

解题思路还是比较简答的。使用 sumOfDivisors(n) 函数返回n的所有因子和(不包括n)，然后从1~10000开始统计。

```cpp
#include <stdio.h>

/*求n的所有因子（不包括n）的和*/
int sumOfDivisors(int n)
{
    int sum = 1; // 1肯定是n的因子
    for (int i = 2; i * i <= n; i++) {
        if (n%i == 0){
            int a = n/i; //a和i都是n的因子
            if(i>a) break;
            else if(i==a) sum += i;
            else sum += (a + i);
        }
    }
    return sum;
}

/*求n以下所有亲和数的和*/
int sumOfAmicableBelowN(int n)
{
    int sum=0;
    for (int i = 1; i < n; i++){
        int a = sumOfDivisors(i);
        if(i == sumOfDivisors(a)){ //i和a是一对亲和数
            // a == i 时，不算亲和数
            //printf("i:%d a:%d\n", i, a);
            if( i < a ){ //保证一对亲和数只统计一次
                sum += i;
                if( a < n) sum += a;
            }
        }
    }
    return sum;
}

int main(int argc, char* argv[])
{
    printf("%d\n", sumOfAmicableBelowN(10000));
    return 0;
}

```

### Golang

```go
package main

import "fmt"

/*求n的所有因子（不包括n）的和*/
func sumOfDivisors(n int) int {

	sum := 1 // 1肯定是n的因子
	for i := 2; i*i <= n; i++ {
		if n%i == 0 {
			a := n / i //a和i都是n的因子
			if i > a {
				break
			} else if i == a {
				sum += i
			} else {
				sum += a + i
			}
		}
	}
	return sum
}

/*求n以下所有亲和数的和*/
func sumOfAmicableBelowN(n int) int {

	sum := 0
	for i := 1; i < n; i++ {
		a := sumOfDivisors(i)
		if i == sumOfDivisors(a) { //i和a是一对亲和数
			// a == i 时，不算亲和数
			if i < a { //保证一对亲和数只统计一次
				sum += i
				if a < n {
					sum += a
				}
			}
		}
	}
	return sum
}

func main() {
	fmt.Println(sumOfAmicableBelowN(10000))
}
```

### Python

```python
# 求n的所有因子（不包括n）的和
def sumOfDivisors(n) :

    sum = 1 # 1肯定是n的因子
    for i in range(2, n):
        if i * i > n :
            break
        if n%i == 0 :
            a = n / i #a和i都是n的因子
            if i > a :
                break
            elif i == a :
                sum += i
            else:
                sum += a + i
    return int(sum)

# 求n以下所有亲和数的和
def sumOfAmicableBelowN(n) :
    sum = 0
    for i in range(1, n):
        a = sumOfDivisors(i)
        if i == sumOfDivisors(a) : #i和a是一对亲和数
            # a == i 时，不算亲和数
            if i < a : #保证一对亲和数只统计一次
                sum += i
                if a < n :
                    sum += a
    return sum


print(sumOfAmicableBelowN(10000))
```

## 方法2 使用 lookup table，提高效率

基于方法1，为了提高效率，我们使用lookup table，用一个数组cache[] 记录下每个n的所有因子和，这样计算时，如果该数的所有因子和已经计算过了，就直接从cache数组中提取即可。

### CPP

```cpp
#include <stdio.h>
#include <stdlib.h>

/*求n的所有因子（不包括n）的和*/
int sumOfDivisors(int n)
{
    int sum = 1; // 1肯定是n的因子
    for (int i = 2; i * i <= n; i++) {
        if (n%i == 0){
            int a = n/i; //a和i都是n的因子
            if(i>a) break;
            else if(i==a) sum += i;
            else sum += (a + i);
        }
    }
    return sum;
}

/*求n以下所有亲和数的和*/
int sumOfAmicableBelowN(int n)
{
    int* cache = (int*)malloc(n * sizeof(int)); // 记录 0~n 的每个数的所有因子和，cache[i] 表示 i 的所有因子的和
    for(int i = 0; i < n; i++) cache[i] = 0;

    int sum=0;
    for (int i = 1; i < n; i++){
        if(cache[i] == 0){ // 还没计算，则计算
            cache[i] = sumOfDivisors(i);
        }
        int a = cache[i]; // a 是 i的所有因子和
        int b = 0;        // b 是 a的所有因子和

        if(a < n){
            if (cache[a] == 0) {
                cache[a] = sumOfDivisors(a);
            }
            b = cache[a];   
        }else{
            b = sumOfDivisors(a);
        }

        if(i == b){ // i和a是一对亲和数
            // a == i 时，不算亲和数
            //printf("i:%d a:%d\n", i, a);
            if( i < a ){ //保证一对亲和数只统计一次
                sum += i;
                if( a < n) sum += a;
            }
        }
    }

    free(cache);
    cache = NULL;
    return sum;
}

int main(int argc, char* argv[])
{
    printf("%d\n", sumOfAmicableBelowN(10000));
    return 0;
}
```

### Golang

```go
package main

import "fmt"

/*求n的所有因子（不包括n）的和*/
func sumOfDivisors(n int) int {

	sum := 1 // 1肯定是n的因子
	for i := 2; i*i <= n; i++ {
		if n%i == 0 {
			a := n / i //a和i都是n的因子
			if i > a {
				break
			} else if i == a {
				sum += i
			} else {
				sum += a + i
			}
		}
	}
	return sum
}

/*求n以下所有亲和数的和*/
func sumOfAmicableBelowN(n int) int {
	cache := make([]int, 0) // 记录 0~n 的每个数的所有因子和，cache[i] 表示 i 的所有因子的和
	for i := 0; i < n; i++ {
		cache = append(cache, 0)
	}

	sum := 0
	for i := 1; i < n; i++ {
		if cache[i] == 0 { // 还没计算，则计算
			cache[i] = sumOfDivisors(i)
		}
		a := cache[i] // a 是 i的所有因子和
		b := 0        // b 是 a的所有因子和

		if a < n {
			if cache[a] == 0 {
				cache[a] = sumOfDivisors(a)
			}
			b = cache[a]
		} else {
			b = sumOfDivisors(a)
		}

		if i == b { // i和a是一对亲和数
			// a == i 时，不算亲和数
			if i < a { //保证一对亲和数只统计一次
				sum += i
				if a < n {
					sum += a
				}
			}
		}
	}
	return sum
}

func main() {
	fmt.Println(sumOfAmicableBelowN(10000))
}
```

### Python

```python
# 求n的所有因子（不包括n）的和
def sumOfDivisors(n) :

    sum = 1 # 1肯定是n的因子
    for i in range(2, n):
        if i * i > n :
            break
        if n%i == 0 :
            a = n / i #a和i都是n的因子
            if i > a :
                break
            elif i == a :
                sum += i
            else:
                sum += a + i
    return int(sum)

# 求n以下所有亲和数的和
def sumOfAmicableBelowN(n) :
    cache = [] # 记录 0~n 的每个数的所有因子和，cache[i] 表示 i 的所有因子的和
    for i in range(0,n) :
        cache.append(0)

    sum = 0
    for i in range(1,n) :
        if cache[i] == 0 : # 还没计算，则计算
            cache[i] = sumOfDivisors(i)

        a = cache[i] # a 是 i的所有因子和
        b = 0        # b 是 a的所有因子和

        if a < n :
            if cache[a] == 0 :
                cache[a] = sumOfDivisors(a)

            b = cache[a]
        else :
            b = sumOfDivisors(a)

        if i == b : # i和a是一对亲和数
            #a == i 时，不算亲和数
            if i < a : # 保证一对亲和数只统计一次
                sum += i
                if a < n :
                    sum += a
    return sum


print(sumOfAmicableBelowN(10000))
```


## 答案
31626