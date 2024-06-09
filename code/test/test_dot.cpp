
#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"

/*
 * to test dot operation
 */

std::string test_name = "Test dot operation";

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  int M = 2;
  int N = 3;
  int K = 2;

  float a[6] = {1, 2, 3, 4, 5, 6};
  float b[6] = {1, 2, 3, 4, 5, 6};
  float* result = new float[M * K];

  float ground_truth[4] = {22, 28, 49, 64};

  Potato::dot<float *, float>(a, b, result, M, N, K);

  // check the result
  for (int i = 0; i < M * K; i++)
  {
    if (result[i] != ground_truth[i])
    {
      test_result(test_name, false);
      return 1;
    }
  }
  test_result(test_name, true);
}