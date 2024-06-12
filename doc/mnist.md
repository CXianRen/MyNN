### Dataset
MNIST is a classic handwritten digit recongnition dataset, containing a number of images of handwritten digits.  


1. Image resolution: each image is a 28x28 pixel grayscale image

2. Pixel value range from 0 to 255, indicating the gray level, where 0 represents black, 255 represents white.


### Data format in train.txt
+ the first value of each row is the label, ranging from 0 to 9, followed by 28*28 pixel values
+ there are 42000 samples
+ use data/check_data.ipynb to see detail:

| 0                    | 1                    | 2                    | 3                    |
| -------------------- | -------------------- | -------------------- | -------------------- |
| ![0](imgs/num_0.png) | ![1](imgs/num_1.png) | ![1](imgs/num_2.png) | ![1](imgs/num_3.png) |

