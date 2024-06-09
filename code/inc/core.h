#ifndef __POTATO_CORE_H__
#define __POTATO_CORE_H__

#include "error.h"
#include <cmath>
#include <algorithm>

template <typename T>
inline int acc2d(int i, int j, int cols)
{
  return i * cols + j;
}

/*
 *  this file is the core of the potato engine
 *  it includes all the necessary headers for the engine to work
 */

namespace Potato
{

  /*
   * Returns the dot product of two matrices
   * R = M*N . N * K = M*K
   * T: buffer type
   * T_e: element type
   */
  template <typename T, typename T_e>
  void dot(const T &a, const T &b, T &result,
           const int M, const int N, const int K)
  {
    for (int i = 0; i < M; i++)
    {
      for (int j = 0; j < K; j++)
      {
        T_e sum = 0;
        for (int k = 0; k < N; k++)
        {
          sum += a[acc2d<T>(i, k, N)] * b[acc2d<T>(k, j, K)];
        }
        result[acc2d<T>(i, j, K)] = sum;
      }
    }
  }

  /** activation **/

  /**
   * Relu activation function
   */

  template <typename T>
  void relu(const T &a, T &result, const int size)
  {
    for (int i = 0; i < size; i++)
    {
      result[i] = a[i] <= 0.0 ? 0.0 : a[i];
    }
  }

  /**
   * Softmax activation function
   */
  template <typename T, typename T_e>
  void softmax(const T &a, T &result, const int rows, const int cols)
  {
    T_e max_x = 0;
    T_e exp_sum = 0;
    for (size_t i = 0; i < rows * cols; i += cols)
    {
      // how to avoid row*cols?: just calcualte in loop
      max_x = *std::max_element(a.begin() + i, a.begin() + i + cols);
      exp_sum = 0;
      for (int col = 0; col < cols; col++)
      {
        // to avoid exp overflow
        result[i + col] = std::exp(a[i + col] - max_x);
        exp_sum += result[i + col];
      }
      for (int col = 0; col < cols; col++)
      {
        result[i + col] /= exp_sum;
      }
    }
  }

} // namespace Potato
#endif // __POTATO_CORE_H__