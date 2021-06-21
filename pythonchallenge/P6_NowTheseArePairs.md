# Now These Are Pairs

解谜P5后跳转至第六题P6

http://www.pythonchallenge.com/pc/def/channel.html

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p6_1.png)

just 一张图，注意到网页的标题为“Now there are pairs”, 看来是要用到pair数据结构，可是Python中并没有单独的这个类型的数据结构。继续，查看网页源代码，其中有如下一段话

> The following has nothing to do with the riddle itself. I just thought it would be the right point to offer you to donate to the Python Challenge project. Any amount will be greatly appreciated. -thesamet

与谜题无关，让捐助的，作者的工作确实很值得肯定，捐助也是很应该的。

源码第一行有提示

> ```<!-- <-- zip -->```


看来这是与压缩相关，下载下来原图片，修改后缀名为为zip，无法打开，看来不是这个意思。<-- 是什么意思？可能是问题的一个关键点吧。

先看看Python中的压缩相关知识，看有没有什么启发吧。

Python中有一个zip函数，将两个列表对应位置元素合成一个元组tuple，并返回所有tuple的列表。zip函数得到的正是一对对的pair，看来有戏。

```python
>>> x = [1, 2, 3]
>>> y = [4, 5, 6]
>>> zipped = zip(x, y)
>>> zipped
[(1, 4), (2, 5), (3, 6)]
>>> x2, y2 = zip(*zipped)
>>> x == list(x2) and y == list(y2)
True
```

但是到哪里去找两个列表呢，这个zip也不是压缩啊。问题在哪? 万般无奈，只能从url下手，将channel.html 换成zip.html，不错，页面提示一行文字

> Yes, find the zip

看来有戏，再将channel.html换成channel.zip。很好，是一个zip文件下载。

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p6_2.png)

解压，打开readme.txt，内容为

> welcome to my zipped list.
>
> hint1: start from 90052
>
> hint2: answer is inside the zip

在打开90052.txt，内容为

> Next nothing is 94191

看来和第四题P4差不多了。不过这次换成了文件而已。

## 思路

```python
#-*- coding: utf-8 -*-

nothing = "90052"
while True:
    filename = "channel/"+nothing+".txt"
    with open(filename, 'r') as infile:
       data = infile.read()
       print('filename:', filename, ", data:",data)
       nothing = data.rsplit()[-1]
#最后一个打开的文件为46145.txt,内容为“Collect the comments.”
```

comment，注释？ google一下 zip file comment，发现如下解释

> A comment is optional text information that is embedded in a Zip file. It can be viewed, created, edited, or deleted using the Comment window. Simply type in your text or use any common Windows cut, copy, or paste method. This feature is available for Zip files only (.zip or .zipx).【1】

Zip格式的文件有一个comment信息。

再google  “zipfile comment python” ，第一个结果就是Python文档 zipfile — Work with ZIP archives。这里面讲解了zipfile的用法。

首先下载channel.zip文件，放到当前目录下，使用zipfile模块中的ZipFile方法打开channel.zip（代码如下），返回一个ZipFile类对象zip，zip.infolist()返回一个list，包含zip压缩包中每个文件的ZipInfo对象，ZipInfo对象存储了文件相关信息（filename,date_time,compress_type,comment,file_size等等）。

遍历该list，由nothing构造出一个文件名，使用zip.getinfo()函数获取文件的ZipInfo，继而获取文件的comment，并追加到comments列表中；使用zip.read()读取文件中的内容，并分割得到下一个nothing的值。最后，使用join函数把comment连接成一个字符串并输出

```python
# -*- coding: utf-8 -*-
import zipfile

nothing = "90052"
comments = []

zip = zipfile.ZipFile('channel.zip','r')
try:
    for info in zip.infolist():
        filename = nothing+".txt"
        comments.append(zip.getinfo(filename).comment.decode('utf8')) #读取每个文件的comment
        print(filename, comments)
        nothing = ( zip.read(filename).rsplit()[-1] ).decode('utf8') #读取下一个nothing
except:
    print(comments)
    print("".join(comments)) #连接成一个字符串
```

输出结果为：

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p6_4.png)

hockey,曲棍球，冰球。

将url中的“channel.html” 替换成“hockey.html”，页面输出

> it's in the air. look at the letters.

让我们看单词，我们发现上面输出的”HOCKEY“ 分别由O、X、Y、G、E、N组成。所以单词是oxygen。再讲url中的hockey替换成oxygen。okay，问题解决。

## 解谜
将channel.html换成channel.zip，得到zip文件。依据zip文件comment，得到hockey.html，再将hockey.html替换成oxygen.html，成功解谜并打开下一题

http://www.pythonchallenge.com/pc/def/oxygen.html

## Python知识点

- zipfile模块用来处理zip压缩文件
- zipfile.ZipFile类用来读、写zip压缩文件
- ZipFile.get_info()获取压缩文件中一个文件的ZipInfo对象
- ZipInfo对象包含了文件的相关信息（filename,date_time,compress_type,file_size等）

### 压缩文件

创建了一个simple.zip压缩文件，并将四个txt文件添加到压缩包内。

```
# -*- coding: utf-8 -*-
import zipfile

#----------------------------------------------
# 压缩文件示例

txt = "This a simple text file"

#创建一个压缩文件
zf = zipfile.ZipFile('simple.zip','w', zipfile.ZIP_DEFLATED)

#创建4个txt文件,(1.txt,2.txt...),并添加到压缩文件
for i in range(1,5):
    filename = str(i)+".txt"
    with open(filename, 'w') as outfile:
        outfile.write(txt)
    #添加到压缩文件
    zf.write(filename,)

#关闭压缩文件
zf.close()
```

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p6_3.png)

### 解压文件

使用zipfile.ZipFile(name,’r’)打开一个zip压缩包；遍历infolist列表获取压缩包汇中的每个文件的信息；遍历namelist列表获取压缩包中每个文件名；使用read()函数读取压缩文件的内容。

```python
# -*- coding: utf-8 -*-
import zipfile
#----------------------------------------------
# 解压文件示例

#打开压缩包
zf = zipfile.ZipFile('simple.zip','r')

#读取压缩包中的文件信息
for info in zf.infolist():
    print(info.filename, info.date_time, info.file_size)
    #输出： 1.txt (2014, 1, 2, 13, 16, 26) 23

#解压文件
for name in zf.namelist(): #文件名列表
    #print name #1.txt,2.txt...
    with open(name, 'w') as outfile:
        outfile.write(zf.read(name).decode('utf8')) #read函数读取文件内容

#关闭压缩包
zf.close()
```