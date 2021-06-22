# Smarty

解谜P6之后，转至第七题P7，其url为

http://www.pythonchallenge.com/pc/def/oxygen.html

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p7_1.png)

打开之后，只有一张图片，图片的特点就是中间有一条灰度部分。再查看网页源码，没有发现什么线索。还是从图片着手吧，结合之前的做题经验，每道题都关联着Python的一个重要部分，如P3为字符串匹配，P4为urllib模块使用，P5为数据序列化，P6为zip压缩。那么这一题，应该就是图像处理。

Python中图像处理最重要的一个库就是PIL（Python Image Library），Python3 中不再维护，改为 Pillow。看了看这个库学了点基本的知识，最重要的一个函数就是Image.crop()，它可以用来截取一部分的图像。使用之前，必须先安装Pillow，[参考教程](https://pillow.readthedocs.io/en/stable/installation.html)

首先要从图片中截取出灰度部分，然后将灰度值转换为对应的ASCII码字符，观察字符能不能给出什么线索或答案

## 思路
首先要下载oxygen.png 图片到本地，通过urllib模块实现

然后从PIL中导入Image类，使用Image.open()打开图像

然后使用Image.load()函数加载像素到pixel

遍历pixel，找到R=B=G的像素点（即灰度点），将第一个灰度点存储在start中，最后一个存储在end中，所有的灰度值存储在data中

将data中的数值转换为ASCII码对应的字符（chr函数，[P1](http://zhujiangtao.com/?p=303)中有介绍过），并存储到alpha中。使用join()函数将aphal连接成一个字符串，并输出。发现输出结果中出了第一个s出现连续出现5次外，其他的都是连续出现7次。下一步需要把连续重复的字符去除。

定义rst用来存放alpha中除去了重复值之后的结果。初始设置count=0，pre=“*”，遍历alpha，如果当前字符i和前一个字符pre相同，则count+1，如果+1后count==5且i==‘s’，说明一个s已经统计完了，下一个出现的字符时不算重复的字符；如果+1后，count==7且i !=’s’，则下一个出现的字符也不算重复字符。不重复的字符都追加到rst中

使用join函数，将rst连接成一个字符串并输出

最后使用Image.crop()将左上角start点到右下角end点之间的矩形区域（即灰度部分）截取并显示（循环中range(40,height)的40就是通过观察图像，尝试出来的）

## 代码

```python
#-*- coding: utf-8 -*-
import os

#判断图像是否存在，不存在则下载
if os.path.isfile('oxygen.png'):
    pass
    #print 'existed'
else: #download the image
    from urllib.request import urlopen
    response = urlopen('http://www.pythonchallenge.com/pc/def/oxygen.png')
    with open('oxygen.png', 'wb') as f:
        f.write(response.read())

#图像处理
from PIL import Image

try:
    #打开图片
    image = Image.open('oxygen.png')
    print(image.format,image.size,image.mode) #PNG (629, 95) RGBA
    width, height = image.size
    
    #加载像素
    pixel = image.load()
    
    #找到图像中的灰度部分
    start = []  #灰度部分的左上角的点坐标
    end = []    #灰度部分的右下角的点坐标
    first = True
    data = []

    #找到r=g=b的像素（即灰度像素）的开始start和结束end点
    for y in range(40,height):#40 is the result of trying
        for x in range(0,width):#RGBA
            if pixel[x,y][0]==pixel[x,y][1] and \
                            pixel[x,y][0]==pixel[x,y][2] and \
                            pixel[x,y][1]==pixel[x,y][2]:
                if(first):
                    start = [x,y]
                    first = False
                else:
                    end = [x,y]
                #print chr(pixel[x,y][0]),
                data.append(pixel[x,y][0])
                #data.append(pixel[x,y][0])
        #print ''
    print (start, end)
    #print ''.join(data)

    #将data中的数据由ASCII码值转换为字符，保存到alpha中
    alpha = []
    for i in data:
        alpha.append(chr(i))
    #print "".join(alpha)

    #去除alpha中的重复值，如果是s则重复数为5，其他的重复数为7
    rst = []
    count = 0
    pre = '*' #可以是任意一个与alpha中不同的字符
    for i in alpha:
        if(i==pre):
            count += 1
            if count==5:
                if i=='s':
                    count = 0
                    pre = '*'
                    continue
            elif count ==7:
                #rst.append(i)
                count = 0
                pre = "*"
                continue
            else:
                pass
        else:
            rst.append(i)
            count = 0
        pre = i

    #print rst
    #print ''.join(alpha)
    print (''.join(rst))

    #将rst中提示的结果转换为ASCII码对应字符(最后结果)
    ans = [105, 110, 116, 101, 103, 114, 105, 116, 121]
    for i in ans:
        print ( chr(i), end="")
    print ('')

    #截取出灰度部分并显示
    box = (start[0], start[1], end[0], end[1])
    #print box
    region = image.crop(box)#截取
    region.show()#显示
except:
    print('cannot open the image')
```    

> 输出结果：smart guy, you made it. the next level is [105, 110, 116, 101, 103, 114, 105, 116, 121]…

截取的图片为

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p7_2.png)

这里的 [105, 110, 116, 101, 103, 114, 105, 116, 121] 又是什么？

尝试转化成ASCII码字符输出（代码见上述代码中的“最后结果”部分），输出integrity。


## 解谜
通过将图像中灰度部分的灰度值去除连续重复后再转换为ASCII码对应字符，得到一串数字，再将该串数字转换成对应的ASCII码字符，得到integrity，将url中的oxygen替换为integrity，成功解谜P7，并打开P8

http://www.pythonchallenge.com/pc/def/integrity.html

## Python 知识点
- PIL，Python Image Library，Python3中为Pillow
- image = Image.open()打开图像
- pixel = image.load() 加载图像中的像素到pixel
- width,height = image.size 图像的大小
- pixel[x,y] 图像像素，其中通道为pixel[x,y][0]…