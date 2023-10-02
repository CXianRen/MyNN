#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <iostream>

std::vector<float> softmax(std::vector<float> &m1, int rows, int cols)
{
  std::vector<float> output(rows * cols);
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

void print_m(std::vector<float> m, int rows, int cols)
{
  std::cout << "matrix: " << rows << "," << cols << std::endl;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      std::cout << std::setw(10) << std::fixed << std::setprecision(6) << m[i * cols + j] << " ";
    }
    std::cout << std::endl;
  }
}

bool test(std::vector<float> &m1, std::vector<float> &m2)
{

  // check the result
  print_m(m1, 1, m1.size());
  print_m(m2, 1, m2.size());

  if (m1.size() != m2.size())
  {
    std::cout << "m1 size:" << m1.size() << " but m2 size:" << m2.size() << std::endl;
    return false;
  }

  for (size_t i = 0; i < m1.size(); i++)
  {
    if (m1[i] != m2[i])
    {
      std::cout << "m1[" << i << "](" << m1[i] << ") != m2[" << i << "](" << m2[i] << ")" << std::endl;
      return false;
    }
  }
  return true;
}

void test_softmax()
{
  {
    std::vector<float> m = {1, 2, 3};
    float exp_sum = std::exp(1.f) + std::exp(2.f) + std::exp(3.f);
    std::vector<float> r = {std::exp(1.f) / exp_sum, std::exp(2.f) / exp_sum, std::exp(3.f) / exp_sum};

    std::cout << "start softmax" << std::endl;
    auto y = softmax(m, 1, 3);
    test(y, r);
  }

  {
    std::vector<float> m = {1, 2, 3, 3, 2, 1};
    float exp_sum = std::exp(1.f) + std::exp(2.f) + std::exp(3.f);
    std::vector<float> r = {std::exp(1.f) / exp_sum, std::exp(2.f) / exp_sum, std::exp(3.f) / exp_sum,
                            std::exp(3.f) / exp_sum, std::exp(2.f) / exp_sum, std::exp(1.f) / exp_sum};

    std::cout << "start softmax" << std::endl;
    auto y = softmax(m, 2, 3);
    test(y, r);
  }
}

int main(int argc, char **argv)
{
  std::cout << "test softmax" << std::endl;
  test_softmax();
  return 0;
}