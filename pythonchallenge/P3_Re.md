# Re

解谜P2之后，转到P3，（其url如下）

http://www.pythonchallenge.com/pc/def/equality.html

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p3_1.png)

先观察图中下方的文字，有这么一句：

> To see the solutions to the previous level, replace pc with pcc, i.e. go to: http://www.pythonchallenge.com/pcc/def/equality.html

这就告诉了我们如何查看已经做过的题目的解答（做过Preject Euler童鞋都不陌生，这与PE中的论坛类似）。看了一下Solutions，这里面确实有很多不错的值得借鉴的解法。

回到题目，图中是一排蜡烛，下面是一行文字

> One small letter, surrounded by EXACTLY three big bodyguards on each of its sides.

直译过来就是一个小写字母，它两边确切的各有3个大的保镖。稍想一下就可猜出“大的保镖”应该是大写字母，也就是说一个小写字母两边各有3个大写字母。

那么在哪里找这样的小写字母？提示本身这段文本中字母太少，而且也没有满足条件的字母。那么要找的字符串在哪里？根据前文中提到的规则3，打开网页的源代码

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p3_2.png)

果然藏有问题。于是P3的问题就变成了：从这一堆给出的字符中，查找出满足条件的小写字母，条件就是它的左边和右边各有三个大写字母，而且有且只能有三个，不能出现四个（由加粗的EXACTLY推知）。

## 思路
首先要把网页源代码中的一堆字符读取到程序中，这里借鉴上一题的做法，通过文件读写实现，保存在字符串src中。

然后遍历src，判断当前字符是不是小写字母，如果是小写字母，再判断它符不符合条件（调用guarded()方法），符合则输出该字母。

guarded(s,n)方法用来判断字符串s中，字符s[n]满不满足其左右恰好有且只有3个大写字母。判断方法如下：对于一个位置处在中间字符（也就是左边、右边各自至少有四个字符），则要求左右两边的三个字符都是大写（借助isBig()方法），而且两边的第四个字符都不是大写（not isBig()）；对于最左边的可能字符，它左边只有三个字符，所有要求满足左右两边三个字符都是大写，右边第四个不是大写；同理有最右边的可能字符。

## 代码

### 方案1，遍历

```python
# -*- coding: utf-8 -*-

#从串中找一个字母，左边右边刚好有三个比它大的字母

#step1 读取所有字符到src
src=""
# read the whole file to a string
with open('source.txt', 'r') as file:
    src = file.read().replace('\n', '')

#step2 从串中找一个字母它左右刚好有三个比它大的字母
#判断是否是大写
def isBig(ch):
    if ord(ch)<=ord('Z') and ord(ch)>=ord('A'):
        return True
    else:
        return False

#判断n的左右三个是不是大写，而且只能是三个
def guarded(s,n):
    #中间的字符，左右至少有四个字符的
    if n>3 and n<(len(s)-3):
        if isBig(s[n-3]) and isBig(s[n-2]) and isBig(s[n-1]) and \
           isBig(s[n+1]) and isBig(s[n+2]) and isBig(s[n+3]) and \
           (not isBig(s[n-4])) and (not isBig(s[n+4])):
            return True;
    #最左边一个可能的值
    elif n==3:
        if isBig(s[n-3]) and isBig(s[n-2]) and isBig(s[n-1]) and \
           isBig(s[n+1]) and isBig(s[n+2]) and isBig(s[n+3]) and \
           (not isBig(s[n+4])):
            return True;
    #最右边一个可能的值
    elif n==(len(s)-3):
        if isBig(s[n-3]) and isBig(s[n-2]) and isBig(s[n-1]) and \
           isBig(s[n+1]) and isBig(s[n+2]) and isBig(s[n+3]) and \
           (not isBig(s[n-4])):
            return True;
    #不可能的点n=0、1 len-1、len-2
    else:
        return False

    return False

#搜索
for n in range(3,len(src)-3):
    #找到一个小写字母
    if ord(src[n])<=ord('z') and ord(src[n])>=ord('a'):
        #print "find little "+src[n];
        #判断是否符合条件
        if guarded(src,n):
            print(src[n],end="")
```            

输出：linkedlist

----------------------------------------------

### 方案2，使用正则表达式（2013-12-30 更新）

```python
# -*- coding: utf-8 -*-
#使用正则表达式re实现P3
#从串中找一个字母，左边右边刚好有三个比它大的字母

# read the whole file to a string
src=""
with open('source.txt', 'r') as file:
    src = file.read().replace('\n', '')

import re
pattern = re.compile(r'[^A-Z][A-Z][A-Z][A-Z][a-z][A-Z][A-Z][A-Z][^A-Z]')
rst = pattern.findall(src)
#rst = re.findall(r'[^A-Z][A-Z][A-Z][A-Z][a-z][A-Z][A-Z][A-Z][^A-Z]',src)
print(rst)

for item in rst:
    print(item[4],end="") #linkedlist
```

step1 读入字符串，step2 直接通过正则表达式(regular expression)实现匹配。模式pattern中[a-z]表示匹配一个小写字母，[A-Z]表示匹配一个大写字母，[^A-Z]表示匹配一个不是大写字母的。（相比前一段代码，使用re是不是很简洁！）

----------------------------------------------

## 解谜
根据经验（规则1）将url中的equality替换成linkedlist，如下

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p3_3.png)

显示linkedlist.php，再将url中的linkedlist.html 替换成linkedlist.php，成功解谜P3，并打开了下一题

http://www.pythonchallenge.com/pc/def/linkedlist.php

## Python知识点
- 正则表达式（Regular-Expression）