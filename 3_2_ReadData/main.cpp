#include <deep_core.hpp>
#include <help.hpp>
#include <iostream>

#define BATCH_SIZE 4
#define INPUT_NODE 784
#define L1_NODE 128
#define L2_NODE 64
#define OUTPUT_NODE 10

int main(int argc, char **argv)
{
  std::vector<float> input_node, label; // (BATCH_SIZE * INPUT_NODE); will be filled by mnist_get_random()
  std::vector<float> l1_node(INPUT_NODE * L1_NODE);
  std::vector<float> l2_node(L1_NODE * L2_NODE);
  std::vector<float> output_node(L2_NODE * OUTPUT_NODE);

  // init data set
  int ret = mnist_init("../data/train.txt");
  if (ret != 0)
  {
    std::cout << "Init test fail: should return 0, but " << ret << std::endl;
    return ret;
  }
  mnist_random_get(input_node, label, BATCH_SIZE);
  
  // forward propagation
  auto a1 = relu(dot(input_node, l1_node, BATCH_SIZE, INPUT_NODE, L1_NODE));
  auto a2 = relu(dot(a1, l2_node, BATCH_SIZE, L1_NODE, L2_NODE));
  auto yp = softmax(dot(a2, output_node, BATCH_SIZE, L2_NODE, OUTPUT_NODE), BATCH_SIZE, OUTPUT_NODE);
  print_m(yp, BATCH_SIZE, OUTPUT_NODE);

  return 0;
}