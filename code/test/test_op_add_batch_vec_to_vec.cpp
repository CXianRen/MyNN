#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"

/*
 * to test add_batch_vec_to_vec operation
 */

std::string test_name = "Test add_batch_vec_to_vec operation";

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  int batch = 3;
  float a[6] = {1, 2, 3, 4, 5, 6};
  float b[2] = {1, 2};
  float *result = new float[2];
  float ground_truth[2] = {10, 14};

  Potato::Op::add_batch_vec_to_vec<float *>(a, b, result, batch, 2);

  // check the result
  for (int i = 0; i < 2; i++)
  {
    if (fabs(result[i] - ground_truth[i]) > 1e-6)
    {
      std::stringstream ss;
      ss << "\tFailed at index " << i
         << " expected :" 
         << ground_truth[i] << " got: " << result[i]
         << " diff: " << fabs(result[i] - ground_truth[i]);
      test_print(ss.str());
      test_result(test_name, false);
      return 1;
    }
  }
  test_result(test_name, true);
}