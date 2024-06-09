#ifndef __POTATO_CORE_H__
#define __POTATO_CORE_H__

#include "error.h"

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
  void dot(T a, T b, T result, int M, int N, int K)
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
}

#endif // __POTATO_CORE_H__