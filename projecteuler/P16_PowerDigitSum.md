# Problem 16: Power digit sum

> https://projecteuler.net/problem=16

2<sup>15</sup> = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2<sup>1000</sup>?


## 分析
2的1000次方的各位数字和

2的1000次方很大，C\C++中long long都已经不够了，所以比较难解。如果用Python，一行代码就可以解决。

## 方法1 使用字符串实现乘法

与 Problem 20 基本相同。将21000转换为1000次乘法，乘法又转换为加法运算，a*b 转换为对a累加b次。a存放在字符串中，加法运算方法和摆算式的方式相同，从两个数的低位（即字符串的最高位）开始，不断往高位（即字符串的最低位）累加。使用一个变量记录运算过程的进位。


**（1）使用数组计算，需要手动分配和回收内存**

```cpp
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

/************************************************************************
* 计算a*b的积
* a 是一个很大的数，保存在一个字符串中
* b 是一个整型的数
************************************************************************/
char* mul(char* a,int b)
{
    // 初始化 product = a
    char* product = new char[strlen(a)+1]; //积，结尾 \0
    for(int i=0; i<=strlen(a); i++) product[i] = a[i];
    product[strlen(a)] = '\0';

    // 对 a 做 b-1 次累加
    for(int cnt=1; cnt<=b-1; cnt++){
        // product + = a

        int i = 0, j = 0, acc = 0; // acc 进位
        for(i = strlen(product) - 1, j = strlen(a)-1; i>=0 && j>=0; i--, j--){
            int v1 = (int)(product[i]-'0');
            int v2 = (int)(a[j]-'0');

            int sum = v1+v2+acc;
            acc = sum/10;
            product[i] = (char)( (sum%10) +'0' );
        }

        // 由于product总是>=a的，所以跳出循环时，肯定是 j==-1

        // 尝试继续累加product
        for (;i>=0;i--){
            int v = product[i]-'0';
            int sum = v+acc;
            product[i] = (sum%10)+'0';
            acc = sum/10;

            if(acc ==0 ) break; //没有进位了，停止
        }

        // 累加完product之后，跳出上面的循环时，如果还有进位，则需要补到最高位
        if(acc != 0) { //还有进位,此时i == -1
            char* tmp = new char[strlen(product)+2];// 多加一位空白 和 一位\0
            for(int k=0; k<=strlen(product); k++){
                tmp[k+1] = product[k];
            }
            tmp[0] = acc+'0'; //最高位

            delete[] product;
            product = tmp;
        }
    }

    return product;
}

/************************************************************************
* 计算2的n次方的字符串,返回各位数字之和
************************************************************************/
int digital_sum(int n)
{
    if (n==0) return 1;

    char* a = new char[2];
    a[0] = '2';
    a[1] = '\0';

    char* product = NULL;
    for (int i=1; i<n; i++){ // 2*2* ... *2
        product = mul(a,2);  // product 是在mul分配的空间
        delete[] a; //销毁空间
        a = product;
    }
    cout<<a<<endl;

    int sum = 0;
    for (int j=0;j<strlen(a);j++){
        sum += (int)(a[j]-'0');
    }

    cout<<sum<<endl;
    return sum;
}

int main(int argc, char* argv[])
{
    digital_sum(1000);
    return 0;
}
```


**（2）使用vector，不用考虑内存分配问题**

> 实现了任意长度数字的加法和乘法， add 和 mul 两个方法可以为以后解题复用

```cpp
#include <iostream>
#include <vector>
using namespace std;

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
    std::vector<char> sum1;
    for(int i = sum.size() - 1; i >= 0; i--){
        sum1.push_back(sum[i]);
    }

    return sum1;
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

int main(int argc, char* argv[])
{
    std::vector<char> a; // 987654
    a.push_back('9');
    a.push_back('8');
    a.push_back('7');
    a.push_back('6');
    a.push_back('5');
    a.push_back('4');

    std::vector<char> b; // 98765
    b.push_back('9');
    b.push_back('8');
    b.push_back('7');
    b.push_back('6');
    b.push_back('5');
    
    {
        // test add
        std::vector<char> sum = add(a, b);
        for(int i = 0; i < sum.size(); i++){
            printf("%c", sum[i]);
        }
        printf("\n");
    }

    {
        // test mul
        std::vector<char> product = mul(a, 9);
        for(int i = 0; i < product.size(); i++){
            printf("%c", product[i]);
        }
        printf("\n");
    }

    {
        // test mul
        std::vector<char> product = mul(a, b);
        for(int i = 0; i < product.size(); i++){
            printf("%c", product[i]);
        }
        printf("\n");
    }

    {
        // calc 2^1000
        // 计算2的n次方的字符串,返回各位数字之和
        std::vector<char> product; // product = 2
        product.push_back('2');
        for(int i = 0; i < 999; i++){
            product = mul(product, 2);
        }

        int sum = 0;
        for(int i = 0; i < product.size(); i++){
            printf("%c", product[i]);
            sum += (int) (product[i] - '0');
        }
        printf("\nsum: %d\n", sum);
    }

    return 0;
}
```

## 方法2 使用大数包，适用于golang

### Golang

```go
package main

import (
	"fmt"
	"math/big"
)

func main() {
	a := big.NewInt(2)
	for i := 0; i < 999; i++ {
		b := big.NewInt(2)
		a.Mul(a, b)
	}
	fmt.Println(a)

	s := a.String()
	sum := 0
	for _, c := range s {
		sum += int(c - '0')
	}
	fmt.Println(sum)
}

```

## 方法3 直接计算，适用于python

```python
print( sum([int(i) for i in list(str(2**1000))]) )
```

首先计算2的1000次方，即2**1000，然后将结果使用str()函数转换成字符串，再利用list()函数，将字符串转换成字符列表，就得到了各个位上的数字对应的字符，然后使用一个列表推导将字符转换成数字，形成一个数字的列表。最后使用sum统计统计这个数字列表的和。

## 答案
1366