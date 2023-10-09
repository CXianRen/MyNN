#include "help.hpp"
#include <iomanip>
#include <chrono>
#include <iostream>
#include <random>

void print_m(const std::vector<float> m, const int rows, const int cols)
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

bool test(const std::vector<float> &m1, const std::vector<float> &m2)
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


void random_init_layer(std::vector<float> & layer){
  std::mt19937 mt(69);
  std::uniform_real_distribution<float> dist(0,1);
  for(size_t i = 0 ; i <layer.size(); i++){
    layer[i] = dist(mt);
  }
}