#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"

/*
 * to test softmax operation
 */

std::string test_name = "Test softmax operation";

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  int rows = 2;
  int cols = 3;

  float a[6] = {1, 2, 3, 4, 5, 6};
  float *result = new float[6];

  float ground_truth[6] = {
      0.09003057,
      0.24472847,
      0.66524096,
      0.09003057,
      0.24472847,
      0.66524096};

  Potato::softmax<float *, float>(a, result, rows, cols);

  // check the result
  for (int i = 0; i < rows * cols; i++)
  {
    if (result[i] != ground_truth[i])
    {
      test_result(test_name, false);
      return 1;
    }
  }
  test_result(test_name, true);
}