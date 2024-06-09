
#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"

/*
 * to test factor operation
 */

std::string test_name = "Test factor operation";

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  float a[6] = {1, 2, 3, 4, 5, 6};
  float factor = 0.01;
  float *result = new float[6];

  float ground_truth[6] = {0.01, 0.02, 0.03, 0.04, 0.05, 0.06};

  Potato::Op::factor<float *, float>(a, factor, result, 6);

  // check the result
  for (int i = 0; i < 6; i++)
  {
    if (fabs(result[i]-ground_truth[i]) > 1e-6)
    {
      std::stringstream ss;
      ss << "\tFailed at index " << i
         << " expected " << ground_truth[i] << " got " << result[i];
      test_print(ss.str());
      test_result(test_name, false);
      return 1;
    }
  }
}