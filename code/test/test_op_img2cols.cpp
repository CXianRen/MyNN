
#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"

/*
 * to test img2cols operation
 */

/**
 *  kerneal size matches the input size
 *  the kernel size is 2x2, stride is 1, padding is 0, the input is 3x3 image
 *
 */
int case_1()
{
  std::string test_name = "Test img2cols case 1";
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
  return 0;
}

/**
 *  kerneal size does not match the input size
 *  the kernel size is 2x2, stride is 2, padding is 0, the input is 3x3 image
 *  1, 2, 3
 *  4, 5, 6
 *  7, 8, 9
 *
 *  the output size is 1x4
 *  1, 2, 4, 5
 */

int case_2()
{
  std::string test_name = "Test img2cols case 2";
  int N = 1;
  int C = 1;
  int H = 3;
  int W = 3;
  int K = 2;
  int S = 2;

  float a[N * C * H * W] = {
      1, 2, 3,
      4, 5, 6,
      7, 8, 9};

  float ground_truth[4] = {
      1, 2, 4, 5};

  float *result = new float[5];
  result[4] = -0.12345;

  Potato::Op::img2cols<float *>(a, result, N, C, H, W, K, S, 0);

  // check the result
  for (int i = 0; i < 4; i++)
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
  if (fabs(result[4] - (-0.12345)) > 1e-6)
  {
    test_print("Memory overflow check failed, expected -0.12345 got " + std::to_string(result[4]));
    test_result(test_name, false);
    return 1;
  }
  test_result(test_name, true);
  return 0;
}

/**
 * case 3
 * padding is 1, input 3*3, K =2, S = 1
 */

int case_3()
{
  std::string test_name = "Test img2cols case 3";
  int N = 1;
  int C = 1;
  int H = 3;
  int W = 3;
  int K = 2;
  int S = 1;
  int P = 1;

  float a[N * C * H * W] = {
      1, 2, 3,
      4, 5, 6,
      7, 8, 9};
  /*
   *  0 0 0 0 0
   *  0 1 2 3 0
   *  0 4 5 6 0
   *  0 7 8 9 0
   *  0 0 0 0 0
   */

  float ground_truth[16 * 5] = {
      0, 0, 0, 1,
      0, 0, 1, 2,
      0, 0, 2, 3,
      0, 0, 3, 0,

      0, 1, 0, 4,
      1, 2, 4, 5,
      2, 3, 5, 6,
      3, 0, 6, 0,

      0, 4, 0, 7,
      4, 5, 7, 8,
      5, 6, 8, 9,
      6, 0, 9, 0,

      0, 7, 0, 0,
      7, 8, 0, 0,
      8, 9, 0, 0,
      9, 0, 0, 0};

  float *result = new float[16 * 5 + 1];
  result[16 * 5] = -0.12345;

  Potato::Op::img2cols<float *>(a, result, N, C, H, W, K, S, P);

  // check the result
  for (int i = 0; i < 16 * 5; i++)
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
  if (fabs(result[16 * 5] - (-0.12345)) > 1e-6)
  {
    test_print("Memory overflow check failed, expected -0.12345 got " + std::to_string(result[16 * 5]));
    test_result(test_name, false);
    return 1;
  }
  test_result(test_name, true);
  return 0;
}

/**
 * case 4
 * padding 1, input 3*3, K = 2, S = 2
 */
int case_4()
{
  std::string test_name = "Test img2cols case 4";
  int N = 1;
  int C = 1;
  int H = 3;
  int W = 3;
  int K = 2;
  int S = 2;
  int P = 1;

  float a[N * C * H * W] = {
      1, 2, 3,
      4, 5, 6,
      7, 8, 9};
  /*
   *  0 0 0 0 0
   *  0 1 2 3 0
   *  0 4 5 6 0
   *  0 7 8 9 0
   *  0 0 0 0 0
   */

  float ground_truth[16] = {
      0, 0, 0, 1,
      0, 0, 2, 3,

      0, 4, 0, 7,
      5, 6, 8, 9};

  float *result = new float[16 + 1];
  result[16] = -0.12345;

  Potato::Op::img2cols<float *>(a, result, N, C, H, W, K, S, P);

  // check the result
  for (int i = 0; i < 16; i++)
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
  if (fabs(result[16] - (-0.12345)) > 1e-6)
  {
    test_print("Memory overflow check failed, expected -0.12345 got " + std::to_string(result[16]));
    test_result(test_name, false);
    return 1;
  }
  test_result(test_name, true);
  return 0;
}

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);
  case_1();
  case_2();
  case_3();
  case_4();
}