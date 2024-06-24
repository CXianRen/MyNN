# Image to cols
[REF](https://www.mo4tech.com/high-performance-convolution-computing-img2col-principle-explained.html)

Can we convert convolution into matrix dot operation? ! **Image to cols**.

![img2cols](./imgs/img2cols.jpeg)

Now, we can use dot operation to calculate cnn convolution!. 

From this figure, given a matrix [N,C,H,W] and filter [K,K] we can get the resolution of converted matrix:


Colum size:
```math 
  W' = C * K * K
```

Row size:
```math
  H' = N * (\frac{(W - K + P)}{S}+1) *（\frac{(H - K + P)}{S}+1）
```

In this context:
+ N is the number of samples.
+ C is the number of channels.
+ H is the height of the input matrix.
+ W is the width of the input matrix.
+ K is the size of the filter.
+ P is the padding applied to the input matrix.
+ S is the stride of the filter.