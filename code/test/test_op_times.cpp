
#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"

/*
 * to test times operation
 */

std::string test_name = "Test times operation";

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  float a[6] = {1, -2, 3, -4, 5, -6};
  float b[6] = {1, 2, 3, 4, 5, 6};
  float *result = new float[6];

  float ground_truth[6] = {1, -4, 9, -16, 25, -36};

  Potato::Op::times<float *>(a, b, result, 6);

  // check the result
  for (int i = 0; i < 6; i++)
  {
    if (result[i] != ground_truth[i])
    {
      std::stringstream ss;
      ss << "\tFailed at index " << i << " expected " << ground_truth[i] << " got " << result[i];
      test_result(test_name, false);
      return 1;
    }
  }
  test_result(test_name, true);
}