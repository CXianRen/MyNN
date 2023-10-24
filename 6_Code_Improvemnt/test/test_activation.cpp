
#include "deep_core.hpp"
#include "help.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <algorithm>

void test_softmax()
{
  {
    std::vector<float> m = {1, 2, 3};
    float exp_sum = std::exp(1.f) + std::exp(2.f) + std::exp(3.f);
    std::vector<float> r = {std::exp(1.f) / exp_sum, std::exp(2.f) / exp_sum, std::exp(3.f) / exp_sum};

    std::cout << "start softmax" << std::endl;
    auto y = softmax(m, 1, 3);
    std::cout << " y: " << std::endl;
    print_m(y, 1, 3);
    std::cout << " r: " << std::endl;
    print_m(r, 1, 3);
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

void test_relu()
{
  {
    std::vector<float> m1 = {0.f, -0.1f, 1.0f};
    std::vector<float> r = {0.f, 0.f, 1.0f};
    auto y = relu(m1);
    test(y, r);
  }
}

void test_reluPrime()
{
  {
    std::vector<float> m1 = {0.f, -0.1f, 2.0f};
    std::vector<float> r = {0.f, 0.f, 1.0f};
    auto y = reluPrime(m1);
    test(y, r);
  }
}

int main(int argc, char **argv)
{
  std::cout << "test softmax" << std::endl;
  test_softmax();
  std::cout << "test relu" << std::endl;
  test_relu();
  std::cout << "test reluPrime" << std::endl;
  test_reluPrime();
  return 0;
}