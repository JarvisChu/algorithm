# Problem 42: Coded triangle numbers

> https://projecteuler.net/problem=42

The n<sup>th</sup> term of the sequence of triangle numbers is given by, t<sub>n</sub> = ½n(n+1); so the first ten triangle numbers are:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t<sub>10</sub>. If the word value is a triangle number then we shall call the word a triangle word.

Using [words.txt](https://projecteuler.net/project/resources/p042_words.txt) (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, how many are triangle words?

## 分析

当一个单词的所有字母对应的数字(A->1 B->2…)之和（称为单词的 value）是一个三角数，则称该单词为三角单词。 所谓三角数，即 n(n+1)/2 的数。
统计 words.txt 中所有的三角单词的个数

思路比较简单，直接统计所有单词的value，判断是否是三角数。

## 方法1 遍历统计

假设最长的单词的长度为 maxWordsLen，则单词的 value ≤ 26*maxWordsLen。所以可以直接先找出所有 ≤ 26*maxWordsLen 的三角数，保存到set中。再统计单词的value，判断是否在set中。


### CPP

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>


// 获取 word 的 value
int getValue(std::string word)
{
    int sum = 0;
    for(int i = 0; i < word.size(); i++){
        sum += word[i] - 'A' + 1;
    }

    return sum;
}

int main()
{
    int maxWordsLen = 0; // 保存最长的单词的长度

    // read all names from file
    std::vector<std::string> names;
    std::ifstream f("words.txt");
    char name[64] = {0};
    while( f.getline(name, 64, ',' )){
        std::string str(name);
        str = str.substr(1,str.length()-2); //去掉name外的""
        names.push_back(str);
        if(str.size() > maxWordsLen){
            maxWordsLen = str.size();
        }
    }

    // 保存三角数
    std::set<int> triangles;
    for(int i = 1; ; i++){
        int v = i*(i+1) / 2;
        if( v > 26 * maxWordsLen) break;
        triangles.insert(v);
    }

    // 统计
    int cnt = 0;
    for(int i = 0; i < names.size(); i++){
        int v = getValue(names[i]);

        std::set<int>::iterator it = triangles.find(v); //查找集合
        if (it != triangles.end()){ //找到
            cnt ++;
        }
    }

    std::cout<<cnt<<std::endl;
    return 0;
}
```

### Golang

```go
package main

import (
	"fmt"
	"io/ioutil"
	"strings"
)

func getWords(file string) []string {
	bytes, _ := ioutil.ReadFile(file)
	content := string(bytes)
	content = strings.ReplaceAll(content, "\"", "") // 去除所有 引号
	return strings.Split(content, ",")
}

func getValue(word string) int {
	value := 0
	for _, c := range word {
		value += int(c) - 64 // A->65 位置为1
	}
	return value
}

func main() {
	words := getWords("words.txt")

	// 保存最长的单词的长度
	maxWordsLen := 0
	for _, w := range words {
		if len(w) > maxWordsLen {
			maxWordsLen = len(w)
		}
	}

	// 保存三角数
	triangles := make(map[int]struct{}, 0)
	for i := 1; ; i++ {
		v := i * (i + 1) / 2
		if v > 26*maxWordsLen {
			break
		}
		triangles[v] = struct{}{}
	}

	// 统计
	cnt := 0
	for _, w := range words {
		v := getValue(w)
		if _, ok := triangles[v]; ok {
			cnt++
		}
	}

	fmt.Println(cnt)
}

```

### Python

```python

# 读取所有单词
with open('words.txt','r') as f:
    #remove the "" , and then split by ',' into a words list
    words = f.read().replace(r'"', '').replace(r'"', '').split(',')

# 保存最长的单词的长度
maxWordsLen = 0
for w in words :
    if len(w) > maxWordsLen :
        maxWordsLen = len(w)

# 保存三角数
triangles = []
i = 1
while True:
    v = int(i * (i + 1) / 2)
    if v > 26 * maxWordsLen :
        break
    triangles.append(v)
    i = i + 1

# 统计
print( sum([1 for w in words if sum([ ord(ch) - 64 for ch in w ]) in triangles ]) )
```

# 答案

162