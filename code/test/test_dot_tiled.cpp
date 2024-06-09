#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"
#include "inc/help.h"

/*
 * to test dot_tiled operation
 */

std::string test_name = "Test dot_tiled operation";

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  int M = 512;
  int N = 128;
  int K = 256;

  // generate random matrices
  float *a = new float[M * N];
  float *b = new float[N * K];
  float *result = new float[M * K];
  float *result_tiled = new float[M * K];

  Potato::helper::random_init(a, M * N);
  Potato::helper::random_init(b, N * K);

  Potato::Op::dot<float *, float>(a, b, result, M, N, K);

  Potato::Op::dot_tiled<float *, float>(a, b, result_tiled, M, N, K);

  // check the result
  for (int i = 0; i < M * K; i++)
  {
    if (compare_float(result[i], result_tiled[i]) == false)
    {
      std::stringstream ss;
      ss << "Mismatch at index " << i << " result: " << result[i] << " result_tiled: " << result_tiled[i];
      test_print(ss.str());
      test_result(test_name, false);
      return 1;
    }
  }
  test_result(test_name, true);
}