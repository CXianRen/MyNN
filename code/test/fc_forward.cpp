
#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"

/*
 * to test forward operation
 */

std::string test_name = "Test forward operation";

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  const int BatchSize = 256;
  const int InputNode = 784;
  const int L1Node = 128;
  const int L2Node = 64;
  const int OutputNode = 10;

  float input_node[BatchSize * InputNode];
  float y_lable[BatchSize * OutputNode];

  float l1_node[InputNode * L1Node];
  float l2_node[L1Node * L2Node];

  float output_node[L2Node * OutputNode];

  // fc forward propagation
  static float *a1 = new float[BatchSize * L1Node];
  Potato::dot<float *, float>(
      input_node, l1_node, a1, BatchSize, InputNode, L1Node);
  Potato::relu<float *>(a1, a1, BatchSize * L1Node);

  static float *a2 = new float[BatchSize * L2Node];
  Potato::dot<float *, float>(
      a1, l2_node, a2, BatchSize, L1Node, L2Node);
  Potato::relu<float *>(a2, a2, BatchSize * L2Node);

  static float *yp = new float[BatchSize * OutputNode];
  Potato::dot<float *, float>(
      a2, output_node, yp, BatchSize, L2Node, OutputNode);

  Potato::softmax<float *, float>(yp, yp, BatchSize, OutputNode);

  test_result(test_name, true);
}