#include <vector>
#include <cmath>
#include <algorithm>

std::vector<float> softmax(std::vector<float> &m1, int rows, int cols)
{
  std::vector<float> output(m1.size());
  float max_x = 0;
  float exp_sum = 0;
  for (size_t i = 0; i < m1.size(); i += cols)
  {
    // how to avoid row*cols?: just calcualte in loop
    max_x = *std::max_element(m1.begin() + i, m1.begin() + i + cols);
    exp_sum = 0;
    for (int col = 0; col < cols; col++)
    {
      // to avoid exp overflow
      output[i + col] = std::exp(m1[i + col] - max_x);
      exp_sum += output[i + col];
    }
    for (int col = 0; col < cols; col++)
    {
      output[i + col] /= exp_sum;
    }
  }
  return output;
}

std::vector<float> relu(std::vector<float> &m1)
{
  //
  std::vector<float> output(m1.size());
  for (size_t i = 0; i < m1.size(); i++)
  {
    output[i] = m1[i] < 0.f ? 0.f : m1[i];
  }
  return output;
}
