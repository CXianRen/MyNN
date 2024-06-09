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

namespace Potato::Op
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

  /*
   * transpose a matrix
   * T: buffer type
   * T_e: element type
   * a : input matrix
   * rows: number of rows
   * cols: number of cols
   * result: output matrix
   *
   */
  template <typename T, typename T_e>
  void transpose(const T &a, const int rows, const int cols, T &result)
  {
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        result[acc2d<T>(j, i, rows)] = a[acc2d<T>(i, j, cols)];
      }
    }
  }

  /*
   * normalize a matrix to sum to 1
   */
  template <typename T, typename T_e>
  void normalize(const T &a, T &result, const int size)
  {
    T_e sum = 0;
    for (int i = 0; i < size; i++)
    {
      sum += a[i];
      // check sum is too large
      if (sum > 1e10)
      {
        throw std::runtime_error("Sum is too large");
      }
    }
    for (int i = 0; i < size; i++)
    {
      result[i] = a[i] / sum;
    }
  }

} // namespace Potato::Op

namespace Potato::Activ
{

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
      max_x = a[i];
      for (int col = 1; col < cols; col++)
      {
        if (a[i + col] > max_x)
        {
          max_x = a[i + col];
        }
      }

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

} // namespace Potato::Activ

namespace Potato::Loss
{

  /**
   * Mean Squared Error
   */
  template <typename T, typename T_e>
  T_e MSE(const T &a, const T &b, const int size)
  {
    T_e sum = 0;
    for (int i = 0; i < size; i++)
    {
      sum += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sum / size;
  }

} // namespace Potato::Loss

#endif // __POTATO_CORE_H__