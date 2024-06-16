
#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"

/*
 * to test img2cols operation
 */

std::string test_name = "Test img2cols operation";

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  int N = 1;
  int C = 1;
  int H = 3;
  int W = 3;
  int K = 2;

  float a[N * C * H * W] = {
      1, 2, 3,
      4, 5, 6,
      7, 8, 9};

  float ground_truth[N * H * W * K * K] = {
      1, 2, 4, 5,
      2, 3, 5, 6,
      4, 5, 7, 8,
      5, 6, 8, 9};

  float *result = new float[N * H * W * K * K];

  Potato::Op::img2cols<float *>(a, result, N, C, H, W, K, 1, 0);

  // check the result
  for (int i = 0; i < N * H * W * K * K; i++)
  {
    if (result[i] != ground_truth[i])
    {
      std::stringstream ss;
      ss << "\tFailed at index " << i
         << " expected " << ground_truth[i] << " got " << result[i];
      test_print(ss.str());
      test_result(test_name, false);
      return 1;
    }
  }
  test_result(test_name, true);
}