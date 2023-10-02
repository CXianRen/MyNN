#include "../inc/deep_core.hpp"
#include <vector>

std::vector<float> dot(std::vector<float> &m1, std::vector<float> &m2, int m1_rows, int m1_cols, int m2_cols)
{
  // Returns the product of two matrices: m1 (N,M) x m2 (M,K).
  // m1: left matrix, size (m1_ros * m1_cols)
  // m2: right matrix, size (m1_cols * m2_cols)
  // return: m1_rows * m2_cols

  std::vector<float> output(m1_rows * m2_cols);
  //@Todo: will this step spend a lot of time?
  //@Todo: will the elements be initialized as zero?

  // very basic method.
  for (int m1_row = 0; m1_row < m1_rows; m1_row++)
  {
    for (int m2_col = 0; m2_col < m2_cols; m2_col++)
    {
      for (int k = 0; k < m1_cols; k++)
      {
        // output[m1_row][m2_col] += m1[m1_row][k] * m2[j][m2_col]
        output[m1_row * m2_cols + m2_col] += m1[m1_row * m1_cols + k] * m2[k * m2_cols + m2_col];
      }
    }
  }
  return output;
}
