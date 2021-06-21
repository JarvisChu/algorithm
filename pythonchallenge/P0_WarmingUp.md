# Warming Up

[PythonChallenge](http://www.pythonchallenge.com/) 是一个编程解谜网站，依据题目给出的谜面，解谜问题并解决问题，继而打开下一题。通常每道题的谜面会是一张图片和一段文字提示，据此推断出要解决的问题是什么，并用Python编程解决问题，问题的答案就是打开下一个问题的线索。

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge.png)


## P0 热身题
点击“Click here to get challenged”开启解谜之旅

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p0_1.png)


谜面是一张图，图中是数字2和38，并组成了2^38，下面文字提示我们改变url地址。

url地址为："http://www.pythonchallenge.com/pc/def/0.html

## 思路

观察url，最后为0.html，提示我们改变url，明显是将0替换成另一个数字，谜面给出的数字就是2的38次方。利用python编程求解2的38次方，将结果替换url中的0.

## 代码

```python
i = 1
num = 1
while i <= 38:
    num = num * 2
    i = i+1
print(num)
```

或者一条语句

```python
print(pow(2,38))
```

## 谜底

2^38 = 274877906944，将url中0.html换成274877906944.html，成功解谜P0热身题，并跳转到第1题P1.

> 规则1：通过改变url进入下一题

## Python 知识点

- python通过缩进表示语句块关系，不用{}
- python语句末位可以加或不加分号
- pow()函数用于求幂