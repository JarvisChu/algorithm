# Odd Even

PythonChallenge系列第十一题P11（http://www.pythonchallenge.com/pc/return/5808.html，如需登陆：用户名huge,密码file）

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p11_1.png)

页面标题为odd even，再看图片，朦朦胧胧，像是有叠影。所以本题应该就是对这个图片的奇、偶像素做不同处理，从图片中分割出另一个藏着答案的图片。好了，问题就是这么处理这个奇偶了。经尝试，奇偶是指像素(x,y)，x+y区分偶数或奇数。

## 代码

```python
#-*- coding: utf-8 -*-
import os

#判断图像是否存在，不存在则下载
if os.path.isfile('cave.png'):
    pass
    #print 'existed'
else: #download the image
    import base64
    from urllib.request import Request,urlopen
    req = Request('http://www.pythonchallenge.com/pc/return/cave.jpg')
    auth = base64.encodebytes(b'%s:%s' % (b'huge',b'file')).decode('utf8').replace('\n','')
    req.add_header('Authorization','Basic %s' % auth)
    data = urlopen(req).read()
    with open('cave.png', 'wb') as f:
        f.write(data)

#图像处理
from PIL import Image #需要先下载安装PIL

try:
    #--打开图像
    image = Image.open('cave.png')
    print(image.format,image.size,image.mode) #PNG (629, 95) RGBA
    width, height = image.size
    imgOdd = Image.new('RGB',(width,height),0)
    imgEven = Image.new('RGB',(width,height),0)

    #--加载像素
    pixel = image.load()

    for y in range(0,height):
        for x in range(0,width):
            #print x,y,pixel[x,y]
            if (x+y)%2==0:
                imgEven.putpixel((x,y),pixel[x,y])
                #imgOdd.putpixel((x,y), (255,255,255))
            else:
                imgOdd.putpixel((x,y),pixel[x,y])
                #imgEven.putpixel((x,y), (255,255,255))
    
    imgEven.show()
    imgOdd.show()
    #image.show()
except IOError as e:
    print('Error', e)
```    

这段代码从网上下载要处理的图片(其中存在认证过程)，然后利用Image模块进行处理，将坐标(x,y) x+y为偶数的像素，复制到imgEven中。

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p11_2.png)

## 解谜
图像右上角是一个单词evil。将url中的5808替换evil。OK,成功解谜并打开下一题。

http://www.pythonchallenge.com/pc/return/evil.html