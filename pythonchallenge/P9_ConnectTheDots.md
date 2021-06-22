# Connect The Dots

PythonChallenge系列第九题P9（http://www.pythonchallenge.com/pc/return/good.html，如需登陆：用户名huge,密码file）

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p9_1.png)

页面标题为connect the dots，和图像展示意义一样，就是告诉我们将点连接起来。问题是，点在哪里？

打开网页源码，里面有一个first和一个second，然后提示first+second，意思就是两者的组合能够得到坐标点，+号是什么意思，因为first和second的数字位数并不相等，不能简单的由（first,second）组成一个(x,y)坐标。

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p9_2.png)

那么是不是连接起来？可以尝试。将second连接到first后面，得到一个数字的列表，每两个数字组成一个(x,y)坐标，然后在图像上面将这些坐标点连接起来。

## 代码

```python
#-*- coding: utf-8 -*-

import base64
from urllib.request import Request, urlopen

def downloadContent():
    '''获取网页源代码 需要用户名 密码认证
    从源码中获取 first 和 second,并返回'''

    try:
        url = 'http://www.pythonchallenge.com/pc/return/good.html'
        auth = b'%s:%s' % (b'huge', b'file')
        base64string = base64.encodebytes(auth).decode('utf8').replace('\n', '')
        req = Request(url)
        req.add_header("Authorization", "Basic %s" % base64string)
        src = urlopen(req).read()

        #获取 first 和 second
        import re
        first = re.search(b'first:\n([\d,]+\n)+', src).group().replace(b'first:\n',b'').replace(b'\n',b'')
        second = re.search(b'second:\n([\d,]+\n)+', src).group().replace(b'second:\n',b'').replace(b'\n',b'')
        return (first, second)

    except IOError as e:
        print('downloadContent Error! ', e)
        return ([],[])

if __name__ == '__main__':
    (first,second) = downloadContent()

    list1 = first.split(b',')
    list2 = second.split(b',')

    dot1 = [int(i) for i in list1]#转换成int型
    dot2 = [int(i) for i in list2]#转换成int型

    from PIL import Image,ImageDraw
    img = Image.new('RGB',(500,500),'white')
    imgDraw = ImageDraw.Draw(img)

    imgDraw.polygon(dot1,outline=255)
    imgDraw.polygon(dot2,outline=255)

    img.show()
```

使用downloadContent函数从网页上读取出first和second的值，并且以一个tuple的形式返回。因为网页需要登陆验证，所以这个函数使用了base64编码和urllib.request.Request的add_header方法。为了从网页中截取出first和second，使用正则表达式re的search方法[re的使用详见Python正则表达式Regex]。利用str.split将first和second分割成列表，然后再转化成int类型的列表dot1、dot2。

使用PIL中的Image模块，new一个空白的RGB图像，然后使用ImageDraw模块的polygon函数，分别传入dot1，dot2，将列表中的int数字，每两个形成一个坐标，绘制出多边形。最后使用show函数显示图像。

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p9_3.png)

## 解谜
图像是一个牛的轮廓。将url中的good替换cow，网页提示

> hmm. it's a male.

那么再试将good替换成bull。OK,成功解谜并打开下一题。

http://www.pythonchallenge.com/pc/return/bull.html

## Python知识点

### 1. urllib 实现网页认证

利用base64编码一个认证字符串，使用urllib2中的Request请求的add_header方法，将认证信息添加到Request请求中。

```python
try:
    url = 'http://www.pythonchallenge.com/pc/return/good.html'
    base64string = base64.encodebytes(b'%s:%s' % (b'huge', b'file')).decode('utf8').replace('\n', '')
    req = Request(url)
    req.add_header("Authorization", "Basic %s" % base64string)
    src = urlopen(req).read()

except IOError as e:
    print('downloadContent Error! ', e)
```        

### 2. PIL库中Image和ImageDraw的使用

- Image模块的使用：The Image Module

- ImageDraw模块的使用：The ImageDraw Module