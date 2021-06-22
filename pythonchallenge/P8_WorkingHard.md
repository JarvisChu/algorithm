# Work Hard

解谜P7之后，转至第八题P8，其URL为

http://www.pythonchallenge.com/pc/def/integrity.html

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p8_1.png)

一张蜜蜂采蜜的图片，下面提示“Where is the missing link?”。蜜蜂区域可以点击，点击弹出身份验证窗口

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p8_2.png)

需要用户名和密码，服务器提示“inflate”(膨胀，充气)。再看网页源码，蜜蜂的点击区域使用HTML的map标签实现的，当然这与题目应该无关，但其中有两行重要提示：

>un: 'BZh91AY&SYA\xaf\x82\r\x00\x00\x01\x01\x80\x02\xc0\x02\x00 \x00!\x9ah3M\x07<]\xc9\x14\xe1BA\x06\xbe\x084'
>
>pw: 'BZh91AY&SY\x94$|\x0e\x00\x00\x00\x81\x00\x03$ \x00!\x9ah3M\x13<]\xc9\x14\xe1BBP\x91\xf08'

un应该是username，pw应该是password，这里的用户名密码应该就是前面身份验证窗口的用户名密码。

看到这两串字符，我首先想到的是url的编码。看了一下HTML URL Encode Reference觉得也不对。

这个编码应该是和身份验证相关的编码吧。

google “web  authentic encryption”，全部结果都是SSL，应该就是它了。

再 google “python ssl”，第一个结果就是Python关于ssl的官方文档。这里面提到了base64编码，会不会是这个？

将上面两串字符分别复制到 http://www.base64decode.org/ 通过base64编码进行decode，发现解码后仍是混乱无意义的字符。也许这样做法是不对的。

inflate究竟是什么意思？直到我知道了inflate对应的deflate是一个压缩算法。它是无损压缩。试着使用Python中的zlib去解码字符串（import zlib;print zlib.decompress(un);），发现提示错误“incorrect header check”。查了一下，原因是zip编码的字符串开头是PK(即文件头是PK）（wikipedia：zip 文件头）。

那么BZ是什么文件头？bzip2。尝试用bzip2去解决。发现可行。

## 代码

```python
#-*- coding: utf-8 -*-
import bz2

un = b'BZh91AY&SYA\xaf\x82\r\x00\x00\x01\x01\x80\x02\xc0\x02\x00 \x00!\x9ah3M\x07<]\xc9\x14\xe1BA\x06\xbe\x084'
pw = b'BZh91AY&SY\x94$|\x0e\x00\x00\x00\x81\x00\x03$ \x00!\x9ah3M\x13<]\xc9\x14\xe1BBP\x91\xf08'

username = bz2.BZ2Decompressor().decompress(un)
password = bz2.BZ2Decompressor().decompress(pw)

print (username) #huge
print (password) #file

```

## 解谜
用bzip2解压网页源码中的un和pw字符串，分别得到huge和file。用huge作用户名，file作密码，登陆身份验证窗口，成功解谜P8，并打开了第9题。

http://www.pythonchallenge.com/pc/return/good.html

## Python知识点
- deflate压缩算法，也就是zip压缩算法
- bzip2压缩和解压缩