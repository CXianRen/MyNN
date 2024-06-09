
#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"
#include "inc/help.h"

#include <chrono>

std::string test_name = "Test dot operation performance";

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  int M = 512;
  int N = 256;
  int K = 256;

  // generate random matrices
  float *a = new float[M * N];
  float *b = new float[N * K];
  float *result = new float[M * K];

  Potato::helper::random_init(a, M * N);
  Potato::helper::random_init(b, N * K);

  // do dot product 100 times and measure the time
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 100; i++)
  {
    Potato::Op::dot<float *, float>(a, b, result, M, N, K);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;

  std::stringstream ss;
  ss << "\t dot     : " << elapsed_seconds.count() << "s\n";

  // do dot_tiled product 100 times and measure the time
  start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 100; i++)
  {
    Potato::Op::dot_tiled<float *, float>(a, b, result, M, N, K);
  }
  end = std::chrono::high_resolution_clock::now();
  elapsed_seconds = end - start;

  ss << "\t dot tiled: " << elapsed_seconds.count() << "s\n";
  test_result(test_name, true);
  test_print(ss.str());
}