#include <help.hpp>
#include <deep_core.hpp>
#include <iostream>

#define BATCH_SIZE 256
#define INPUT_NODE 784
#define L1_NODE 128
#define L2_NODE 64
#define OUTPUT_NODE 10
#define LEARNING_RATE (0.01 / BATCH_SIZE)

int main(int argc, char **argv)
{
  // init data set
  int ret = mnist_init("../data/train.txt");
  if (ret != 0)
  {
    std::cout << "Init test fail: should return 0, but " << ret << std::endl;
    return ret;
  }

  std::vector<float> input_node, y_lable; // (BATCH_SIZE * INPUT_NODE); will be filled by mnist_get_random()

  std::vector<float> l1_node(INPUT_NODE * L1_NODE);
  random_init_layer(l1_node);
  std::vector<float> l2_node(L1_NODE * L2_NODE);
  random_init_layer(l2_node);
  std::vector<float> output_node(L2_NODE * OUTPUT_NODE);
  random_init_layer(output_node);

  for (int echo = 0; echo < 10000; echo++)
  {
    mnist_random_get(input_node, y_lable, BATCH_SIZE);
    // forward propagation
    // BATCH_SIZE,INPUT_NODE * INPUT_NODE,L1_NODE = BATCH_SIZE,L1_NODE
    input_node = input_node / 255.0;
    auto a1 = relu(dot(input_node, l1_node, BATCH_SIZE, INPUT_NODE, L1_NODE));
    // BATCH_SIZE,L1_NODE * L1_NODE,L2_NODE = BATCH_SIZE,L2_NODE
    auto a2 = relu(dot(a1, l2_node, BATCH_SIZE, L1_NODE, L2_NODE));
    // BATCH_SIZE,L2_NODE * L2_NODE,OUTPUT_NODE = BATCH_SIZE,OUTPUT_NODE
    auto yp = softmax(dot(a2, output_node, BATCH_SIZE, L2_NODE, OUTPUT_NODE), BATCH_SIZE, OUTPUT_NODE);

    // back propagation
    // BATCH_SIZE,output_node
    auto Loss_m = yp - y_lable;
    // L2_NODE, BATCH_SIZE * BATCH_SIZE,output_node
    auto dW3 = dot(transform(a2, BATCH_SIZE, L2_NODE), Loss_m, L2_NODE, BATCH_SIZE, OUTPUT_NODE);

    // dz2 = dz3 * W3.T x Relu'(a2)
    auto dz2 = dot(Loss_m, transform(output_node, L2_NODE, OUTPUT_NODE), BATCH_SIZE, OUTPUT_NODE, L2_NODE) * reluPrime(a2);
    /// dW2 = a1.T * dz2
    auto dW2 = dot(transform(a1, BATCH_SIZE, L1_NODE), dz2, L1_NODE, BATCH_SIZE, L2_NODE);

    // dz1 = dz2 * W2.T x Relu'(a1)
    auto dz1 = dot(dz2, transform(l2_node, L1_NODE, L2_NODE), BATCH_SIZE, L2_NODE, L1_NODE) * reluPrime(a1);
    // dW1 = input.T * dz1
    auto dW1 = dot(transform(input_node, BATCH_SIZE, INPUT_NODE), dz1, INPUT_NODE, BATCH_SIZE, L1_NODE);

    // update W1 W2 W3
    output_node = output_node - LEARNING_RATE * dW3;
    l2_node = l2_node - LEARNING_RATE * dW2;
    l1_node = l1_node - LEARNING_RATE * dW1;

    if (echo % 100 == 0)
    {
      auto loss = Loss_MSE(yp, y_lable) * 10;
      std::cout << "Loss is:" << loss << std::endl;
    }
  }
  return 0;
}