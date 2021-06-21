# OCR

解谜P1之后即可来到P2，（其url如下）

http://www.pythonchallenge.com/pc/def/ocr.html

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p2_1.png)

观察谜面，图中是一本打开的书，书中字符不可辨认。下方文字提示：字符识别，或许在书中，或许在页面源代码（page source）中。书中不可能，那么就看网页源代码。

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p2_2.png)

果然在源代码中，问题是“find rare characters in the mess below”，在一大段字符中找出现次数少的字符。下面着手分析解决这个问题

## 思路
首先遇到的问题就是字符太多了（一千多行），如果直接复制到代码中，赋值给字符串变量，即便代码很庞大不是问题，但要在每一行之后加一个“\”就是工作量惊人。所以直接通过复制赋值给字符串变量不可取，那么就通过文件。将网页源码中要处理的一千多行的字符复制进souce.txt文本文件。使用file.readline函数从文件中读取一行，截去行末的换行符’\n’，追加到字符串src中。这样文本就连接成了一个一行的字符串src。

然后要保存每个字符出现的次数，最好的方法就是使用Python中的字典（dict），dict可以保存键值对（key-value），将key就是字符，value就是该字符出现的次数。代码中使用字典变量rst保存结果。

遍历字符串src，如果当前的字符在rst中存在（借助rst.has_key()函数），则将其value+1，若果不存在则加入字典rst，并将其value设置为1。

最后输出字典rst，观察出现次数少的字符。

但是，输出结果中，虽然发现了出现次数少的几个字母（各出现了一次）：a e i l q t u y，但是其输出顺序却不是按照在源字符串src中的顺序，而是字母表的顺序。如何按照插入顺序显示出来？想到了一个简单的解决方法，再遍历以便src，如果一个字符的出现次数为1，则将其输出。最后得到的结果是equality。

## 代码

```python
# -*- coding: utf-8 -*-
src=""

# read the whole file to a string
with open('source.txt', 'r') as file:
    src = file.read().replace('\n', '')

#store key=character value=appearance count of character
#字典，用来存储一个字符 和 其出现的次数
rst={}

#遍历字符串，如果该字符已经出现过，则字典中对应的value++,否则插入字典且value=1
for c in src:
    if c in rst:
        rst[c] = rst[c]+1 #count ++
    else:
        rst[c] = 1

#输出结果
for key,value in rst.items():
    print(key,value)

print("--------------")
#上面输出的结果并不是按照插入的顺序 比如rst['e']=1 插入时在 rst['a']=1后，但是输出显示时，a却在e前
#如何按照插入的顺序来输出？
#一种简单的方法是，从新再找一遍，因为已经知道了a e i l q u t y几个字母value都是1
for c in src:
    if c in rst and rst[c] == 1:
        print(c,end =" ")
```

输出结果: e q u l i t y

## 解谜
通过Python编程，我们得到了出现最少的字符组成了equality。结合前面的经验（规则1），将url中的ocr换成equality。成功解谜P2，并打开了下一题。

http://www.pythonchallenge.com/pc/def/equality.html

> 规则3：注意查看网页的源代码，其中也许藏有问题

## Python知识点

- 读取文件到字符串，并且去除换行符
- Python字典的使用：使用 in 判断key是否存在，for key, value in dict.items() 遍历字典