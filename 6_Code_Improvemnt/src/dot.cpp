#include "../inc/deep_core.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>

#define CHECK_SIZE(a, b)                                                  \
  do                                                                      \
  {                                                                       \
    if (a.size() != b.size())                                             \
    {                                                                     \
      std::stringstream ss;                                               \
      ss << "vector " << __func__ << " error, a.size() != b.size(), a = " \
         << a.size() << " b = " << b.size() << "\n";                      \
      throw std::runtime_error(ss.str());                                 \
    }                                                                     \
  } while (0)


std::vector<float> dot(const std::vector<float> &m1, const std::vector<float> &m2, const int m1_rows, const int m1_cols, const int m2_cols)
{
  if (int(m1.size()) != m1_rows * m1_cols || int(m2.size()) != m1_cols * m2_cols)
  {
    throw std::runtime_error("invalid input to dot");
  }
  
  // Returns the product of two matrices: m1 (N,M) x m2 (M,K).
  // m1: left matrix, size (m1_ros * m1_cols)
  // m2: right matrix, size (m1_cols * m2_cols)
  // return: m1_rows * m2_cols

  std::vector<float> output(m1_rows * m2_cols, 0);
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

std::vector<float> transform(const std::vector<float> &m1, int rows, int cols)
{
  std::vector<float> rec(cols * rows);
  int r = 0;
  int c = 0;
  for (size_t i = 0; i < rec.size(); i++)
  {
    r = i / rows;
    c = i % rows;
    rec[i] = m1[c * cols + r];
  }
  return rec;
}

std::vector<float> operator+(const std::vector<float> &a, const std::vector<float> &b)
{
  CHECK_SIZE(a, b);
  std::vector<float> c(a.size());
  for (size_t i = 0; i < a.size(); i++)
  {
    c[i] = a[i] + b[i];
  }
  return c;
}

std::vector<float> operator-(const std::vector<float> &a, const std::vector<float> &b)
{
  CHECK_SIZE(a, b);
  std::vector<float> c(a.size());
  for (size_t i = 0; i < a.size(); i++)
  {
    c[i] = a[i] - b[i];
  }
  return c;
}

std::vector<float> operator*(const std::vector<float> &a, const float scalar)
{
  {
    std::vector<float> c(a.size());
    for (size_t i = 0; i < a.size(); i++)
    {
      c[i] = a[i] * scalar;
    }
    return c;
  }
}

std::vector<float> operator*(const float scalar, const std::vector<float> &a) { return a * scalar; }

std::vector<float> operator*(const std::vector<float> &a, const std::vector<float> &b)
{
  CHECK_SIZE(a, b);
  std::vector<float> c(a.size());
  for (size_t i = 0; i < a.size(); i++)
  {
    c[i] = a[i] * b[i];
  }
  return c;
}
std::vector<float> operator/(const std::vector<float> &a, const float scalar)
{
  {
    std::vector<float> c(a.size());
    for (size_t i = 0; i < a.size(); i++)
    {
      c[i] = a[i] / scalar;
    }
    return c;
  }
}
