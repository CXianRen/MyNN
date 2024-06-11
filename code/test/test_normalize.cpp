#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"

/*
 * to test normalize operation
 */

std::string test_name = "Test normalize operation";

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  float a[6] = {1, 2, 3, 4, 5, 6};

  float *result = new float[6];

  float ground_truth[6] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0};

  Potato::Op::normalize<float *, float>(a, result, 6);

  // check the result
  for (int i = 0; i < 6; i++)
  {
    if (result[i] != ground_truth[i])
    {
      std::stringstream ss;
      ss << "Test failed at index " << i << " expected " << ground_truth[i] << " but got " << result[i];
      test_print(ss.str());
      test_result(test_name, false);
      return 1;
    }
  }
  test_result(test_name, true);
}