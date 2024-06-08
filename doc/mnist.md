### 数据
MNIST（Modified National Institute of Standards and Technology）数据集是一个经典的手写数字识别数据集，包含了大量的手写数字图片。MNIST数据集中的图片具有以下规格：

1. 图片尺寸：每个图片都是28x28像素的灰度图像，也就是说，每个图片由28行和28列像素组成。

2. 像素值范围：每个像素的值在0到255之间，表示灰度级别，0表示黑色，255表示白色。

这个数据集通常用于机器学习和深度学习任务，如数字识别，分类，以及图像处理。每张图片都包含一个手写的数字（0到9之间的一个数字），任务通常是识别出图片中的数字是什么。因为MNIST数据集的规模相对较小，所以它常常被用来作为入门级的图像分类问题的基础数据集，用于验证和测试不同机器学习算法和神经网络模型的性能。

### data 下 train.txt 数据格式
+ 明文的
+ 每行第一个时lable 0-9, 后面是28*28的点的值，在0-255
+ 有4200行
+ 见data/check_data.ipynb 可以见到读出和显示的图 如下:

![0](imgs/num_0.png)
![1](imgs/num_1.png)

### 需要什么接口
```cpp
// 随机抽奖 batch 个图 
int mnist_random_get(std::vector<float> &input,
                      std::vector<float> &label, int batch);

```