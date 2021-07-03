# Problem 19: Counting Sundays

> https://projecteuler.net/problem=19

You are given the following information, but you may prefer to do some research for yourself.

- 1 Jan 1900 was a Monday.
- Thirty days has September,
  April, June and November.
  All the rest have thirty-one,
  Saving February alone,
  Which has twenty-eight, rain or shine.
  And on leap years, twenty-nine.
- A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.

How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?


## 分析

统计从1901.1.1 到 2000.12.31 号，当月的第一天是星期天的次数。

题目给出这些提示的意思，应该是让我们自己算，而不是调用库函数去实现。当然，用库函数去实现确实是一个更简单快捷的方法。


## 方法1 从1901.1.1 往后遍历寻找

从1901.1.1 往后，每过一天，week++，如果week是星期天，且当天为1号，则cnt++

year,month,day 分别代表年月日，年从1900年开始走，（因为已知1900.1.1 是周一），月从1~12，日由getDaysOfTheMonth(year,month)函数获取。week 表示当天是星期几。如果当天是星期天，而且是当月1号，而且是1901年之后的（因为1900年的不用统计），则cnt++。每当week==8时，重置为1.（当然也可以取模实现）

getDaysOfTheMonth(year,month)函数返回year年month月的当月的天数。1，3，5，7，8，10，12月每月31天；4，6，9，11每月30天，闰年2月29天，非闰年28天。


### CPP
```cpp
#include <stdio.h>

// 判断 year 年是否是闰年
bool isLeapYear(int year)
{
    // 闰年, 能被4整除同时不能被100整除，或者能被400整除
    return  (year%4 == 0 && year%100 != 0) || year%400 == 0 ;  
}

// 返回 year 年 month 月的天数
int getDaysOfTheMonth(int year, int month) 
{
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
        return 31;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11){
        return 30;
    }

    if(month == 2){
        return isLeapYear(year) ? 29 : 28;
    }

    return 0;
}

int main(int argc, char* argv[])
{
    int cnt = 0;   // 记录月第一天是星期天的次数
    int week = 1;  // 1 表示星期1，...7 表示星期天 (初始化为1900.1.1 为星期1)

    // 从1900.1.1 往后遍历
    for (int year = 1900; year <= 2000; year++){
        for (int month = 1; month <= 12; month++){
            int days_one_month = getDaysOfTheMonth(year,month); //获取当月的天数
            for (int day = 1; day <= days_one_month; day++) {
                //printf("%d-%d-%d %d\n",year,month,day,week);
                if( week == 7 && day == 1 && year>=1901 ) { //星期天在当月的第1天(1901年以后)
                    //printf("%d-%d-%d\n",year,month,day);
                    cnt++;
                }
                week++; //每过一天，星期++
                if(week == 8) week = 1;
            }
        }
    }

    printf("%d\n",cnt);
    return 0;
}
```

### Golang

```go
package main

import "fmt"

// 判断 year 年是否是闰年
func isLeapYear(year int) bool {
	// 闰年, 能被4整除同时不能被100整除，或者能被400整除
	return (year%4 == 0 && year%100 != 0) || year%400 == 0
}

// 返回 year 年 month 月的天数
func getDaysOfTheMonth(year, month int) int {

	if month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12 {
		return 31
	}

	if month == 4 || month == 6 || month == 9 || month == 11 {
		return 30
	}

	if month == 2 {
		if isLeapYear(year) {
			return 29
		}
		return 28
	}

	return 0
}

func main() {

	cnt := 0  // 记录月第一天是星期天的次数
	week := 1 // 1 表示星期1，...7 表示星期天 (初始化为1900.1.1 为星期1)

	// 从1900.1.1 往后遍历
	for year := 1900; year <= 2000; year++ {
		for month := 1; month <= 12; month++ {
			daysOfTheMonth := getDaysOfTheMonth(year, month) //获取当月的天数
			for day := 1; day <= daysOfTheMonth; day++ {
				if week == 7 && day == 1 && year >= 1901 { //星期天在当月的第1天(1901年以后)
					//fmt.Printf("%d-%d-%d\n", year, month, day)
					cnt++
				}
				week++ //每过一天，星期++
				if week == 8 {
					week = 1
				}
			}
		}
	}

	fmt.Println(cnt)
}

```

### Python

```python

# 判断 year 年是否是闰年
def isLeapYear(year) :
	#闰年, 能被4整除同时不能被100整除，或者能被400整除
	return (year%4 == 0 and year%100 != 0) or year%400 == 0

# 返回 year 年 month 月的天数
def getDaysOfTheMonth(year, month) :

	if month == 1 or month == 3 or month == 5 or month == 7 or month == 8 or month == 10 or month == 12 :
		return 31

	if month == 4 or month == 6 or month == 9 or month == 11 :
		return 30

	if month == 2 :
		return 29 if isLeapYear(year) else 28
 
	return 0


cnt = 0  # 记录月第一天是星期天的次数
week = 1 # 1 表示星期1，...7 表示星期天 (初始化为1900.1.1 为星期1)

# 从1900.1.1 往后遍历
for year in range(1900,2001) :
	for month in range(1,13) :
		daysOfTheMonth = getDaysOfTheMonth(year, month) # 获取当月的天数
		for day in range(1, daysOfTheMonth+1):
			if week == 7 and day == 1 and year >= 1901 :  # 星期天在当月的第1天(1901年以后)
				cnt = cnt + 1
			week = week + 1 # 每过一天，星期++
			if week == 8 :
				week = 1

print(cnt)

```

## 方法2 使用 基姆拉尔森计算公式

[基姆拉尔森计算公式（Kim larsen calculation formula）](https://baike.baidu.com/item/%E5%9F%BA%E5%A7%86%E6%8B%89%E5%B0%94%E6%A3%AE%E8%AE%A1%E7%AE%97%E5%85%AC%E5%BC%8F)

用于计算指定年月日是星期几，公式如下：

```cpp
W = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7
```

其中 
- d 表示日
- m 表示月
- y 表示年
- W 表示星期，0~6，分别代表星期一到星期日

> **注意**：要把一月和二月看成是上一年的十三月和十四月，例：如果是2004-1-10则换算成：2003-13-10来代入公式计算

### CPP

```cpp
#include <stdio.h>

// 获取指定年月日是星期几
// 基于 基姆拉尔森计算公式 Kim larsen calculation formula
// 0~6，分别代表星期一到星期日
int getWeek(int y, int m, int d)
{
    // 要把一月和二月看成是上一年的十三月和十四月，例：如果是2004-1-10则换算成：2003-13-10来代入公式计算
    if (m == 1 || m == 2) {
		m += 12;
		y--;
	}

    return (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7 ;
}

int main(int argc, char* argv[])
{
    int cnt = 0;   // 记录月第一天是星期天的次数
    // 从1900.1.1 往后遍历
    for (int year = 1901; year <= 2000; year++){
        for (int month = 1; month <= 12; month++){
            if( getWeek(year, month, 1) == 6 ){
                //printf("%d-%d-%d\n", year, month, 1);
                cnt ++;
            }
        }
    }

    printf("%d\n",cnt);
    return 0;
}

```

### Golang

```go
package main

import "fmt"

// 获取指定年月日是星期几
// 基于 基姆拉尔森计算公式 Kim larsen calculation formula
// 0~6，分别代表星期一到星期日
func getWeek(y, m, d int) int {
	// 要把一月和二月看成是上一年的十三月和十四月，例：如果是2004-1-10则换算成：2003-13-10来代入公式计算
	if m == 1 || m == 2 {
		m += 12
		y--
	}

	return (d + 2*m + 3*(m+1)/5 + y + y/4 - y/100 + y/400) % 7
}

func main() {

	cnt := 0 // 记录月第一天是星期天的次数

	// 从1900.1.1 往后遍历
	for year := 1901; year <= 2000; year++ {
		for month := 1; month <= 12; month++ {
			if getWeek(year, month, 1) == 6 {
				//fmt.Printf("%d-%d-%d\n", year, month, 1)
				cnt++
			}
		}
	}

	fmt.Println(cnt)
}

```

### Python

> 注意： 一定将对公式中的除法计算的值，强转为整数

```python
# 获取指定年月日是星期几
# 基于 基姆拉尔森计算公式 Kim larsen calculation formula
# 0~6，分别代表星期一到星期日
def getWeek(y, m, d) :
    # 要把一月和二月看成是上一年的十三月和十四月，例：如果是2004-1-10则换算成：2003-13-10来代入公式计算
    if m == 1 or m == 2 :
        m += 12
        y = y -1

    return (d + 2*m + int(3*(m+1)/5) + y + int(y/4) - int(y/100) + int(y/400)) % 7

cnt = 0  # 记录月第一天是星期天的次数
# 从1901.1.1 往后遍历
for year in range(1901,2001) :
    for month in range(1,13) :
        if getWeek(year, month, 1) == 6 :
            #print(year,month,1)
            cnt = cnt + 1

print(cnt)
```

## 方法3 基于 蔡勒公式（Zeller's congruence）

[蔡勒公式（Zeller's congruence）](https://en.wikipedia.org/wiki/Zeller%27s_congruence)

用于计算指定年月日是星期几，对于公历纪年，公式如下：

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/zellers_congruence.png)

> 一定要以英文版WikiPedia上的该公式为准，其它的公式可能有问题，谨防踩坑。

其中 

- h ：星期 (0 = Saturday, 1 = Sunday, 2 = Monday, ..., 6 = Friday)
- q ：日
- m ：月，(3 = March, 4 = April, 5 = May, ..., 14 = February)
- K ：年份后两位数字，(year mod 100)，如year=1987，则 K = 87
- J ：世纪-1，(year / 100)，如 year=1987，则 J = 19
- 对除数向下取整

注意：在蔡勒公式中，某年的1、2月要看作上一年的13、14月来计算，比如2003年1月1日要看作2002年的13月1日来计算），这点和 基姆拉尔森计算公式 的处理相同。

如果括号中出现负数，如 h = (-12) / 7 （2006年4月4日），则 h = h % 7 + 7

> [Zeller’s Congruence | Find the Day for a Date](https://www.geeksforgeeks.org/zellers-congruence-find-day-date/)


### CPP

```cpp
#include <stdio.h>

// 获取指定年月日是星期几
// 基于 蔡勒公式（Zeller's congruence）
// 0 = Saturday, 1 = Sunday, 2 = Monday, ..., 6 = Friday
int getWeek(int year, int month, int day)
{
    // 要把一月和二月看成是上一年的十三月和十四月，例：如果是2004-1-10则换算成：2003-13-10来代入公式计算
    if (month == 1 || month == 2) {
		month += 12;
		year--;
	}

    int q = day;
    int m = month;
    int k = year % 100;
    int j = year / 100;

    int h = (q + 13 * (m + 1) / 5 + k + k/4 + j/4 - 2*j) % 7;

    return h > 0 ? h: (h+7) % 7;
}

int main(int argc, char* argv[])
{
    int cnt = 0;   // 记录月第一天是星期天的次数
    // 从1900.1.1 往后遍历
    for (int year = 1901; year <= 2000; year++){
        for (int month = 1; month <= 12; month++){
            if( getWeek(year, month, 1) == 1 ){
                printf("%d-%d-%d\n", year, month, 1);
                cnt ++;
            }
        }
    }

    printf("%d\n",cnt);
    return 0;
}
```

### Golang

```go
package main

import "fmt"

// 获取指定年月日是星期几
// 基于 蔡勒公式（Zeller's congruence）
// 0 = Saturday, 1 = Sunday, 2 = Monday, ..., 6 = Friday
func getWeek(year, month, day int) int {

	// 要把一月和二月看成是上一年的十三月和十四月，例：如果是2004-1-10则换算成：2003-13-10来代入公式计算
	if month == 1 || month == 2 {
		month += 12
		year--
	}

	q := day
	m := month
	k := year % 100
	j := year / 100

	h := (q + 13*(m+1)/5 + k + k/4 + j/4 - 2*j) % 7

	if h > 0 {
		return h
	}

	return (h + 7) % 7
}

func main() {

	cnt := 0 // 记录月第一天是星期天的次数

	// 从1900.1.1 往后遍历
	for year := 1901; year <= 2000; year++ {
		for month := 1; month <= 12; month++ {
			if getWeek(year, month, 1) == 1 {
				fmt.Printf("%d-%d-%d\n", year, month, 1)
				cnt++
			}
		}
	}

	fmt.Println(cnt)
}

```

### Python

```python
# 获取指定年月日是星期几
# 基于 蔡勒公式（Zeller's congruence）
# 0 = Saturday, 1 = Sunday, 2 = Monday, ..., 6 = Friday
def getWeek(year, month, day) :
    #要把一月和二月看成是上一年的十三月和十四月，例：如果是2004-1-10则换算成：2003-13-10来代入公式计算
    if month == 1 or month == 2 :
        month += 12
        year = year - 1
    q = day
    m = month
    k = year % 100
    j = year / 100

    h = (q + int(13*(m+1)/5) + k + int(k/4) + int(j/4) - int(2*j)) % 7

    return h if h > 0 else (h + 7) % 7

cnt = 0  # 记录月第一天是星期天的次数
# 从1901.1.1 往后遍历
for year in range(1901,2001) :
    for month in range(1,13) :
        if getWeek(year, month, 1) == 1 :
            #print(year,month,1)
            cnt = cnt + 1

print(cnt)

```

## 方法4 基于系统库或三方库

Golang 使用 time包中的Date()
Python 使用 calendar模块


### Golang

```go
package main

import (
	"fmt"
	"time"
)

// 获取指定年月日是星期几
// 0~6: 星期日到星期六
func getWeek(year, month, day int) int {
	t := time.Date(year, time.Month(month) ,day,0,0,1,0,time.UTC)
	return int(t.Weekday())
}

func main() {

	cnt := 0 // 记录月第一天是星期天的次数

	// 从1900.1.1 往后遍历
	for year := 1901; year <= 2000; year++ {
		for month := 1; month <= 12; month++ {
			if getWeek(year, month, 1) == 0 {
				fmt.Printf("%d-%d-%d\n", year, month, 1)
				cnt++
			}
		}
	}

	fmt.Println(cnt)
}
```

### Python

```python
import calendar
count = 0
for y in range(1901,2001):
    for m in range(1,13):
        w = calendar.weekday(y,m,1)
        if w==6: #6 stards for sunday
            count += 1
            #print (y,'-',m,'-1')
print(count)

```

calendar.weekday(year,month,day)方法返回当天是星期几。或者写成一行

```python
import calendar
print( sum([1 for y in range(1901, 2001) for m in range(1,13) if calendar.weekday(y, m, 1) == 6] ))
```

当月1号为星期天时，列表中添加一个1，最后统计列表的和。

## 答案
171

## 知识点
- 星期的计算方式: 基姆拉尔森公式 和 蔡勒公式
- Golang time 包
- Python calendar 模块