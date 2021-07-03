# Problem 22: Names scores

> https://projecteuler.net/problem=22

Using [names.txt](https://projecteuler.net/project/resources/p022_names.txt) (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file?

## 分析

一个文件存放了超过5000个乱序的英文名字，需要按照字母表顺序排序，每个名字的有一个值 worth，该 worth 等于单词中每个字符在字母表中的位置之和，每个名字有一个得分SCORE，SCORE = worth * rank, rank是名字排序后的位置。要求给出文件中所有名字的得分之和。


## 方法1 排序 + 统计

将所有名称读取到数组中，然后对数组按字符表顺序进行排序，再依次遍历累加每个名字的得分，获得总分。

> 字母 c 的位置值等于 **c - 64**，因为‘A’的ASCII码是65，’A’的位置值是1

### CPP

- 使用 ifstream.getline 从 name.txt 中将所有名字按照逗号分割，读取到内存。
- 使用 std::vector 存储所有的名字
- 使用 std::sort 对所有的名字进行排序

```cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>

// 从文件中读取所有的名字到vector容器中，并且返回该容器
std::vector<std::string> read_names(std::string filename)
{
    std::vector<std::string> names; //存放所有的名字

    //以逗号为分隔符，读取文件
    char name[15];
    std::ifstream f(filename);
    while(f.getline(name,15,',')){
        std::string str(name);
        str = str.substr(1,str.length()-2); //去掉name外的""
        names.push_back(str);
    }
    f.close();

    return names;
}

// 按字母表顺序比较
bool cmp(std::string a, std::string b)
{
    return a < b;
}

// 获得name的值worth，即所有字母的位置的和
// e.g. name = COLIN, worth =  3 + 15 + 12 + 9 + 14 = 53
int worthOf(std::string name)
{
    int w = 0;
    for (int i=0;i<name.length();i++){
        w += name.at(i) - 64; // A->65 位置为1
    }
    return w;
}

// 获取name的score
int64_t scoreOf(std::string name, int64_t rank)
{
    return worthOf(name) * rank;
}

// 计算所有名字的得分之和
int64_t calcTotalScore(std::vector<std::string> names)
{
    //按字母表顺序排列
    sort(names.begin(), names.end()/*,cmp*/); //默认的排序也是按字母表顺序的

    //计算总分
    int64_t totalScore = 0;
    for (int i=0;i < names.size();++i){
        totalScore += scoreOf(names[i], i+1);
    }

    return totalScore;
}

int main(int argc, char* argv[])
{
    std::vector<std::string> names = read_names("names.txt");
    std::cout<<calcTotalScore(names)<<std::endl;
    return 0;
}
```

### Golang

使用ioutil.ReadFile读取文件，使用strings处理名称，并存放到slice中，使用sort方法排序

```go
package main

import (
	"fmt"
	"io/ioutil"
	"sort"
	"strings"
)

// 从文件中读取所有的名称，并返回
func readNames(fileName string) []string {
	bytes, _ := ioutil.ReadFile(fileName)
	content := string(bytes)
	content = strings.ReplaceAll(content, "\"", "") // 去除所有的引号
	names := strings.Split(content, ",")
	return names
}

// 计算name的值worth，即所有字母的位置的和
// e.g. name = COLIN, worth =  3 + 15 + 12 + 9 + 14 = 53
func worthOf(name string) int {
	w := 0
	for _, c := range name {
		w += int(c) - 64 // A->65 位置为1
	}
	return w
}

// 计算name的score
func scoreOf(name string, rank int64) int64 {
	return int64(worthOf(name)) * rank
}

// 计算所有名字的得分之和
func calcTotalScore(names []string) int64 {
	//按字母表顺序排列
	sort.Slice(names, func(i, j int) bool {
		return names[i] < names[j]
	})

	//计算总分
	totalScore := int64(0)
	for i := 0; i < len(names); i++ {
		totalScore += scoreOf(names[i], int64(i+1))
	}

	return totalScore
}

func main() {
	names := readNames("names.txt")
	fmt.Println(calcTotalScore(names))
}
```

### Python

使用字符串功能获取名字列表，使用列表的sort()函数排序，使用列表推导、sum()、ord()、enumerate()统计分数

```python
with open('names.txt','r') as f:
    #remove the "" , and then split by ',' into a name list
    names = f.read().replace(r'"', '').replace(r'"', '').split(',')

names.sort() #sort alphabetic
print ( sum([sum([ord(ch) - 64 for ch in name]) * (i+1) for i,name in enumerate(names)]) )
```

读取names.txt所有内容到一个字符串，将字符串中的 “ 和 ” 删除，然后按照‘,’ 分隔成一个列表names。

然后使用列表自带的sort()函数进行默认的排序，默认的排序就是按字母表的顺序。

再使用enumerate()函数遍历names，i 和 name 分别为遍历过程中的索引和表中元素。对每一个name，遍历name中每一个字母，使用ord(ch)获取字母ch对应的ASCII码值，ord(ch) - 64就是 ch 的位置值。

## 答案
871198282

## 知识点
- STL algorithm sort()
- Golang sort
- Python list.sort()
- Python ord() 获取字符对应的ASCII码值
- Python enumerate