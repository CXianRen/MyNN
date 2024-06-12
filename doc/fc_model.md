# A simple full connected model

![img](./imgs/fc_model.drawio.png)

+ consist of input layer, hidden 1, hidden 2, output layer.

+ Input consists 784 nodes ( unrolled from a 28*28 pixel image), hidden layer 1 contains 128 nodes, hidden layer 2 contains 64 node. And output layer is with 10 nodes represneting values from 0 to 9.

+ when input layer only contains 1 image, it means the batch size is 1. The computing steps showed in figure above, 128 nodes, and 784 weights for each node, because each nodes is conneted to 784 input nodes. Thus the first layer, there will be 784*128 paramters. 

+ when input layer contains more than one image, for exampe 2, now, the batch size is 2. The forward propagtion compution like the images at the bottom of figure above. We can see that batch size won't effect the number of weights.

Now, let's assume the batch size is N. We have:
```math

(N,784) * (784,128) * (128,64) * (64*10) = (N*10)

```
Thus, the output will be a  N * 10 matrix. 
