#ifndef __POTATO_CORE_H__
#define __POTATO_CORE_H__

#include "error.h"

#include <cmath>
#include <algorithm>

#include <omp.h>

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
#pragma omp parallel for collapse(1)
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
   * tiled dot product of two matrices
   */
  template <typename T, typename T_e>
  void dot_tiled(const T &a, const T &b, T &result,
                 const int M, const int N, const int K,
                 const int tile_size = 64 / sizeof(T_e))
  {
#pragma omp parallel for collapse(3)
    for (int it = 0; it < M; it += tile_size)
      for (int kt = 0; kt < N; kt += tile_size)
        for (int jt = 0; jt < K; jt += tile_size)
          for (int i = it; i < std::min(it + tile_size, M); i++)
            for (int k = kt; k < std::min(kt + tile_size, N); k++)
              for (int j = jt; j < std::min(jt + tile_size, K); j++)
              {
                result[acc2d<T>(i, j, K)] +=
                    a[acc2d<T>(i, k, N)] * b[acc2d<T>(k, j, K)];
              }
  }

  /*
   * diff of two matrix
   * T: buffer type
   * T_e: element type
   * a : input matrix
   * b : input matrix
   * result: output matrix
   * size: size of the matrix
   */
  template <typename T>
  void diff(const T &a, const T &b, T &result, const int size)
  {
#pragma omp parallel for collapse(1)
    for (int i = 0; i < size; i++)
    {
      result[i] = a[i] - b[i];
    }
  }

  /**
   * add two matrix
   *
   */
  template <typename T>
  void add(const T &a, const T &b, T &result, const int size)
  {
#pragma omp parallel for collapse(1)
    for (int i = 0; i < size; i++)
    {
      result[i] = a[i] + b[i];
    }
  }

  /**
   * add a vector to a batch of vectors
   *
   */
  template <typename T>
  void add_vec_to_batch_vec(const T &a, const T &b, T &result, const int batch_size, const int size)
  {
    int cols = size / batch_size;
#pragma omp parallel for collapse(2)
    for (int i = 0; i < batch_size; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        result[acc2d<T>(i, j, cols)] = a[acc2d<T>(i, j, cols)] + b[j];
      }
    }
  }

  /**
   * add a batch of vectors to a vector
   */

  template <typename T>
  void add_batch_vec_to_vec(const T &a, const T &b, T &result, const int batch_size, const int size)
  {
    int cols = size / batch_size;

#pragma omp parallel for collapse(1)
    for (int j = 0; j < cols; j++)
    {
      using ElementType = typename std::remove_reference<decltype(result[0])>::type;
      ElementType sum = b[j];
      for (int i = 0; i < batch_size; i++)
      {
        sum += a[acc2d<T>(i, j, cols)];
      }
      result[j] = sum;
    }
  }

  /**
   * factor times a matrix
   *
   */
  template <typename T, typename T_e>
  void factor(const T &a, const T_e factor, T &result, const int size)
  {
#pragma omp parallel for collapse(1)
    for (int i = 0; i < size; i++)
    {
      result[i] = a[i] * factor;
    }
  }

  /**
   * a  times b
   * T: buffer type
   * a : input matrix
   * b : input matrix
   * result: output matrix
   */

  template <typename T>
  void times(const T &a, const T &b, T &result, const int size)
  {
#pragma omp parallel for collapse(1)
    for (int i = 0; i < size; i++)
    {
      result[i] = a[i] * b[i];
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
#pragma omp parallel for collapse(1)
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        result[acc2d<T>(j, i, rows)] = a[acc2d<T>(i, j, cols)];
      }
    }
  }

  /*
   * normalize a matrix, minus the max value
   * then divide by the difference of the max value and min value
   */
  template <typename T, typename T_e>
  void normalize(const T &a, T &result, const int size)
  {
    T_e max_x = a[0];
    T_e min_x = a[0];
    for (int i = 0; i < size; i++)
    {
      if (a[i] > max_x)
      {
        max_x = a[i];
      }
      if (a[i] < min_x)
      {
        min_x = a[i];
      }
    }
#pragma omp parallel for collapse(1)
    for (int i = 0; i < size; i++)
    {
      result[i] = (a[i] - min_x) / (max_x - min_x);
    }
  }

  // /**
  //  * img2col
  //  * convert a 3d tensor to a 2d tensor
  //  * see doc for more info
  //  */
  // template <typename T>
  // void img2col(const T &a, T &result,
  //              const int batch_size,
  //              const int channels, const int height, const int width,
  //              const int kernel_size, const int stride)
  // {
  //   // we handle padding before calling this function
  //   int out_height = (height - kernel_size) / stride + 1;
  //   int out_width = (width - kernel_size) / stride + 1;

  //   // each step
  //   for (int i = 0 ; i < out_height * out_width; i++){
  //     // each kernel channel
  //     for (int j = 0; j < kernel_size * kernel_size * channels; j++){
  //     }
  //   }
  // }

} // namespace Potato::Op

namespace Potato::Activ
{

  /**
   * Relu activation function
   */

  template <typename T>
  void relu(const T &a, T &result, const int size)
  {
#pragma omp parallel for collapse(1)
    for (int i = 0; i < size; i++)
    {
      result[i] = a[i] <= 0.0 ? 0.0 : a[i];
    }
  }

  /**
   * Relu prime activation function
   */
  template <typename T>
  void reluPrime(const T &a, T &result, const int size)
  {
#pragma omp parallel for collapse(1)
    for (int i = 0; i < size; i++)
    {
      result[i] = a[i] <= 0.0 ? 0.0 : 1.0;
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
    for (int i = 0; i < rows * cols; i += cols)
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