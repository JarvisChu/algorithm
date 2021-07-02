# Problem 17: Number letter counts

> https://projecteuler.net/problem=17

If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?


**NOTE**: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.

## 分析

统计 1~1000 所有的英文单词的字符总数。(不算连字符和空格，但是要算 and)

## 方法1 找规律，遍历统计

数字的表示是有规律的

- 1~20：one two three … twenty
- 21~99：twenty-one twenty-two…nitety-nine ，其中又要考虑30，40，…90 几个特殊的
- 100~999：one hundred, one hundred and one,… nine hundred and nice，其中又要考虑100，200,…900 几个特殊的
- 1000：只有一个 one thousand

### CPP

```cpp
#include <iostream>
#include <map>
#include <string>

using namespace std;

map<int,string> words;

void init()
{
    words.insert(pair<int,string>(1,"one"));
    words.insert(pair<int,string>(2,"two"));
    words.insert(pair<int,string>(3,"three"));
    words.insert(pair<int,string>(4,"four"));
    words.insert(pair<int,string>(5,"five"));
    words.insert(pair<int,string>(6,"six"));
    words.insert(pair<int,string>(7,"seven"));
    words.insert(pair<int,string>(8,"eight"));
    words.insert(pair<int,string>(9,"nine"));
    words.insert(pair<int,string>(10,"ten"));
    words.insert(pair<int,string>(11,"eleven"));
    words.insert(pair<int,string>(12,"twelve"));
    words.insert(pair<int,string>(13,"thirteen"));
    words.insert(pair<int,string>(14,"fourteen"));
    words.insert(pair<int,string>(15,"fifteen"));
    words.insert(pair<int,string>(16,"sixteen"));
    words.insert(pair<int,string>(17,"seventeen"));
    words.insert(pair<int,string>(18,"eighteen"));
    words.insert(pair<int,string>(19,"nineteen"));
    words.insert(pair<int,string>(20,"twenty"));
    words.insert(pair<int,string>(30,"thirty"));
    words.insert(pair<int,string>(40,"forty"));
    words.insert(pair<int,string>(50,"fifty"));
    words.insert(pair<int,string>(60,"sixty"));
    words.insert(pair<int,string>(70,"seventy"));
    words.insert(pair<int,string>(80,"eighty"));
    words.insert(pair<int,string>(90,"ninety"));
}

// 获取 n 的字符数
int getLettleCount(int n)
{
    if( n <= 0 || n > 1000){
        printf("invalid n: %d\n", n)	
		return 0;
	}

    // 1~20：one two three … twenty
    if(n >= 1 && n <= 20){
        return words[n].size();
    }

    // 21~99：twenty-one twenty-two…nitety-nine ，其中又要考虑30，40，…90几个特殊的
    if(n >= 21 && n <= 99){
        // 考虑30/40 ... 90 几个特殊的
        if( n % 10 == 0){
            return words[n].size();
        }

        // 其余格式为 xx-xx
        int a = n % 10;      // 个位上的数字
        int b = (n/10) * 10; // 十位上的数字
        return words[a].size() + words[b].size();
    }

    // 100~999：one hundred, one hundred and one,… nine hundred and nice，其中又要考虑100，200,…900几个特殊的
    if(n >= 100 && n <= 999){
        int a = n / 100; // 百位上的数字

        // 考虑 100/200 ... 900 几个特殊的
        if( n % 100 == 0){
            return words[a].size() + string("hundred").size();
        }

        // 其余格式为 xx hundred and xx-xx
        return words[a].size() + string("hundred").size() + string("and").size() + getLettleCount(n % 100);
    }

    // 1000：只有一个one thousand
    if( n == 1000 ){
        return string("one").size() + string("thousand").size();
    }

    // 忽略
    return 0;
}

int main(int argc, char* argv[])
{
    init();

    int sum = 0;
    for(int i = 1; i <= 1000; i++){
        sum += getLettleCount(i);
    }

    printf("%d\n", sum);
    return 0;
}
```

### Golang

```go
package main

import (
	"fmt"
)

var words = make(map[int]string, 0)

func init() {
	words[1] = "one"
	words[2] = "two"
	words[3] = "three"
	words[4] = "four"
	words[5] = "five"
	words[6] = "six"
	words[7] = "seven"
	words[8] = "eight"
	words[9] = "nine"
	words[10] = "ten"
	words[11] = "eleven"
	words[12] = "twelve"
	words[13] = "thirteen"
	words[14] = "fourteen"
	words[15] = "fifteen"
	words[16] = "sixteen"
	words[17] = "seventeen"
	words[18] = "eighteen"
	words[19] = "nineteen"
	words[20] = "twenty"
	words[30] = "thirty"
	words[40] = "forty"
	words[50] = "fifty"
	words[60] = "sixty"
	words[70] = "seventy"
	words[80] = "eighty"
	words[90] = "ninety"
}

// 获取 n 的字符数
func getLettleCount(n int) int {
	if n <= 0 || n > 1000 {
		fmt.Printf("invalid n:%v\n", n)
		return 0
	}

	// 1~20：one two three … twenty
	if n >= 1 && n <= 20 {
		return len(words[n])
	}

	// 21~99：twenty-one twenty-two…nitety-nine ，其中又要考虑30，40，…90几个特殊的
	if n >= 21 && n <= 99 {
		// 考虑30/40 ... 90 几个特殊的
		if n%10 == 0 {
			return len(words[n])
		}

		// 其余格式为 xx-xx
		a := n % 10        // 个位上的数字
		b := (n / 10) * 10 // 十位上的数字
		return len(words[a]) + len(words[b])
	}

	// 100~999：one hundred, one hundred and one,… nine hundred and nice，其中又要考虑100，200,…900几个特殊的
	if n >= 100 && n <= 999 {
		a := n / 100 // 百位上的数字

		// 考虑 100/200 ... 900 几个特殊的
		if n%100 == 0 {
			return len(words[a]) + len(string("hundred"))
		}

		// 其余格式为 xx hundred and xx-xx
		return len(words[a]) + len(string("hundred")) + len(string("and")) + getLettleCount(n%100)
	}

	// 1000：只有一个one thousand
	if n == 1000 {
		return len(string("one")) + len(string("thousand"))
	}

	return 0
}

func main() {
	//init();

	sum := 0
	for i := 1; i <= 1000; i++ {
		sum += getLettleCount(i)
	}

	fmt.Println(sum)
}
```

### Python

```python
words = {
    1:"one",
    2:"two",
    3:"three",
    4:"four",
    5:"five",
    6:"six",
    7:"seven",
    8:"eight",
    9:"nine",
    10:"ten",
    11:"eleven",
    12:"twelve",
    13:"thirteen",
    14:"fourteen",
    15:"fifteen",
    16:"sixteen",
    17:"seventeen",
    18:"eighteen",
    19:"nineteen",
    20:"twenty",
    30:"thirty",
    40:"forty",
    50:"fifty",
    60:"sixty",
    70:"seventy",
    80:"eighty",
    90:"ninety"
}

data ={1000:11} # data[1000] = "one thousand"

#calc the len
for digit,word in words.items():
    data[digit] = len(word)

total = 0

#one --> twenty
for i in range(1,21):
    total += data[i]

# twenty-one -->ninety-nine
for i in range(21,100):
    if (i%10 == 0): #20,30,40...
        total += data[i]
    else:
        bit = list(str(i)) # split
        shiwei = int(bit[0])*10 #
        gewei = int(bit[1])
        data[i] = data[shiwei] + data[gewei] #add to dict
        total += data[i]

# one hundred and one --> nine hundred and ninety-nine
for i in range(100,1000):
    if (i%100 == 0): #100,200,300...
        bit = i/100
        data[i] = data[bit] + len("hundred") #add to dict
        total += data[i]
    else: #110,111,120,130
        bit = list(str(i)) #split
        baiwei = int(bit[0])*100 #
        data[i] = data[baiwei] + len("and")+ data[i%100];
        total += data[i]

# one thousand
total += data[1000]
print (data)
print (total)
```

## 扩展，获取 1~1000 所有数字的英文拼写

改造一下 **getLettleCount** 即可

```cpp
#include <iostream>
#include <map>
#include <string>

using namespace std;


map<int,string> words;

void init()
{
    words.insert(pair<int,string>(1,"one"));
    words.insert(pair<int,string>(2,"two"));
    words.insert(pair<int,string>(3,"three"));
    words.insert(pair<int,string>(4,"four"));
    words.insert(pair<int,string>(5,"five"));
    words.insert(pair<int,string>(6,"six"));
    words.insert(pair<int,string>(7,"seven"));
    words.insert(pair<int,string>(8,"eight"));
    words.insert(pair<int,string>(9,"nine"));
    words.insert(pair<int,string>(10,"ten"));
    words.insert(pair<int,string>(11,"eleven"));
    words.insert(pair<int,string>(12,"twelve"));
    words.insert(pair<int,string>(13,"thirteen"));
    words.insert(pair<int,string>(14,"fourteen"));
    words.insert(pair<int,string>(15,"fifteen"));
    words.insert(pair<int,string>(16,"sixteen"));
    words.insert(pair<int,string>(17,"seventeen"));
    words.insert(pair<int,string>(18,"eighteen"));
    words.insert(pair<int,string>(19,"nineteen"));
    words.insert(pair<int,string>(20,"twenty"));
    words.insert(pair<int,string>(30,"thirty"));
    words.insert(pair<int,string>(40,"forty"));
    words.insert(pair<int,string>(50,"fifty"));
    words.insert(pair<int,string>(60,"sixty"));
    words.insert(pair<int,string>(70,"seventy"));
    words.insert(pair<int,string>(80,"eighty"));
    words.insert(pair<int,string>(90,"ninety"));
}

// 获取 n 的拼写字符串
string getNumberString(int n)
{
    // 1~20：one two three … twenty
    if(n >= 1 && n <= 20){
        return words[n];
    }

    // 21~99：twenty-one twenty-two…nitety-nine ，其中又要考虑30，40，…90几个特殊的
    if(n >= 21 && n <= 99){
        // 考虑30/40 ... 90 几个特殊的
        if( n % 10 == 0){
            return words[n];
        }

        // 其余格式为 xx-xx
        int a = n % 10;      //个位上的数字
        int b = (n/10) * 10; //十位上的数字
        return words[a] + "-" + words[b];
    }

    // 100~999：one hundred, one hundred and one,… nine hundred and nice，其中又要考虑100，200,…900几个特殊的
    if(n >= 100 && n <= 999){
        int a = n / 100; // 百位上的数字

        // 考虑 100/200 ... 900 几个特殊的
        if( n % 100 == 0){
            return words[a] + " " + string("hundred");
        }

        // 其余格式为 xx hundred and xx-xx
        return words[a] + string(" hundred and ") + getNumberString(n % 100);
    }

    // 1000：只有一个one thousand
    if( n == 1000 ){
        return string("one thousand");
    }

    return "";
}

int main(int argc, char* argv[])
{
    init();

    for(int i = 1; i <= 1000; i++){
        cout << getNumberString(i) << endl;
    }
    return 0;
}
```

## 答案
21124