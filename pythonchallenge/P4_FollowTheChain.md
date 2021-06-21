# Follow The Chain

解谜P3后，转至第四题P4,其url为

http://www.pythonchallenge.com/pc/def/linkedlist.php

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p4_1.png)

只有一张图片，没有文字提示。鼠标移动到图片上，发现可点击，点击图片。

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p4_2.png)


观察，url中有一个“nothing=12345”，页面内容提示“next nothing=44827”，那么把url中的12345替换成44827，又打开了一个新页面，页面又提示了新的nothing中，看来nothing值上大有文章，但具体怎么做文章，目前的提示不够，再看网页源代码。

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p4_3.png)

>urllib may help. DON'T TRY ALL NOTHINGS, since it will never end. 400 times is more than enough.

至此，本题的意思已经出来了。

使用urllib模块，请求url地址 http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=12345，从该页面获取下一个nothing的值，为44827,即请求下一个url地址为http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=44827，从该页面再获取下一个nothing的值，如此往复，400次。

## 思路
使用变量count记录请求的次数，变量nothing记录每次的nothing，初始时count=1，nothing=“12345”。对于一个nothing，以nothing构造出一个url，使用urllib函数打开这个url，使用fd.read()函数读出页面的内容，然后从页面的内容中获取下一个nothing的值，然后count++，继续以新的nothing构造新的url，重复上述过程，直到count达到400。

观察前面几个页面的内容，统一为”and the next nothing is XXXXX”，先尝试以空格分隔字符串，取分割结果数组的第五部分( 即str.split(“ ”)[5] )，发现nothing=3时，页面内容为 `Your hands are getting tired and the next nothing is 94485`, 所以取第五部分不行；随后我通过“nothing is ”来分隔，取str.split[“nothing is ”].[1]，到了nothing=16044时，发现页面内容为`Yes. Divide by two and keep going.`。最后，就尝试去页面的最后一个单词（rsplit()[-1]），一切顺利

观察前400次的结果，发现 nothing=peak.html 循环出现。所以这个peak.html应该就是答案。peak.html替换P4题目首页url中的linkedlist.php，成功。


## 代码
```python
# -*- coding: utf-8 -*-

#1   ,  http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=12345 ,  and the next nothing is 44827
#2   ,  http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=44827 ,  and the next nothing is 45439
#3   ,  http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=45439 ,  <font color=red>Your hands are getting tired </font>and the next nothing is 94485
#86  ,  http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=16044 ,  Yes. Divide by two and keep going.
#234 ,  http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=66831 ,  peak.html
#235 ,  http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=peak.html ,  and the next nothing is 55274
#382 ,  http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=66831 ,  peak.html
#383 ,  http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=peak.html ,  and the next nothing is 55274

from urllib.request import urlopen
count, nothing = 1, "12345"
while count<= 400:
    url = "http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing="+nothing
    html = urlopen(url).read().decode('utf8')
    print(count, ", ", url, ", " , html)

    nothing = html.rsplit()[-1]
    count = count + 1
```    
## 解谜
使用peak.html替换P4题目首页url中的linkedlist.php，成功解谜P4，并打开了下一题。

http://www.pythonchallenge.com/pc/def/peak.html

## Python知识点
在解决的本题的过程中，发现一个不错的Python入门网站，[Python For Beginners](http://www.pythonforbeginners.com).
- urllib 模块的使用
- 字符串的分割，string.split</li>
- 字符串分割后取分割的最后一个部分。两种方法（假设分隔符为空格）：(1) str.rsplit()[-1]；(2)str.rsplit(‘ ’,1)[1]