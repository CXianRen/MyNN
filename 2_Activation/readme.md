### 全连接层的基本结构-2
#### 激活函数
+ example 1, 最简单的例子  
![img](../1_Dot//doc/example_1.png)

+ 没有激活函数会怎么样子?
  只能学习线性分类， 使用激活函数能让模型变成非线性的。

+ 激活函数有哪些?
  + sigmoid, tanh, ReLu, Leaky ReLU, ELU, Maxout,

https://zhuanlan.zhihu.com/p/32824193


+ ReLU为什么能让模型具有线性?
```math
ReLU = max(0,x); \\

ReLU' = \begin{cases}
  0 & \text{if } x \leq 0 \\
  1 & \text{if } x > 0
\end{cases}
```
https://zhuanlan.zhihu.com/p/405068757#%E4%B8%80%E3%80%81%E5%9B%BE%E5%83%8F%E5%88%86%E6%9E%90

是 stack 和 add 操作让ReLU 网络具有非线性的。


#### 增加激活函数后的网络结构

![img](./doc/example_2.png)


#### 输出层的激活函数

+ 输出层的激活函数有哪些？
https://www.zhihu.com/question/462549835

+ 常见函数: sigmod, softmax.
+ sigmod: 大家独立的不想关的,
+ softmax： 分布式相关的, 比如 0-9 的数字概率.

```math 
sigmod = \frac{1}{1+e^{-x}} \\

softmax(x_j) = \frac{e^{x_j}}{\sum^K_{k=1} e^{x_k}}

```

**由于指数的存在, 会让偏大的结果数据更大.**


+ 在代码中是现实, 为了避免浮点溢出, 通常先减去最大x
```math
softmax(x_j) = \frac{e^{x_j-x_{max}}}{\sum^K_{k=1} e^{x_k-x_{max}}}
```


