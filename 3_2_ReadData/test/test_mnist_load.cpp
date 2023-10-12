#include "help.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>

void test_init()
{
  {
    int ret = mnist_init("/tmp/not_exit.txt");
    if (ret != -1)
    {
      std::cout << "Init test fail: should return -1, but " << ret << std::endl;
    }
  }

  {
    int ret = mnist_init("../data/test_data.txt");
    if (ret != 0)
    {
      std::cout << "Init test fail: should return 0, but " << ret << std::endl;
    }
    auto imgs = mnist_get_imgs();
    if (imgs[0].size() != 784)
    {
      std::cout << "img 0 size is not 784, but " << imgs[0].size() << std::endl;
    }
    auto labels = mnist_get_labels();
    print_m(labels[0], 1, 10);
    if (labels[0][0] != 1.0)
    {
      std::cout << "labels[0][1] is not 1, but " << labels[0][1] << std::endl;
    }
    for (int i = 0; i < 784; i++)
    {
      if (imgs[0][i] != i + 1)
      {
        std::cout << "test imgs[0][" << i << "] is not " << i + 1 << ", but " << imgs[0][i] << std::endl;
        break;
      }
    }
  }
}

void test_get_batch()
{
  {
    int ret = mnist_init("../data/test_data.txt");
    if (ret != 0)
    {
      std::cout << "Init test fail: should return 0, but " << ret << std::endl;
    }
    {
      std::vector<float> input;
      std::vector<float> label;

      mnist_random_get(input, label, 1);
      if (input.size() != 784 * 1)
      {
        std::cout << "test_get_batch test fail, input size should be 784*1, but "
                  << input.size() << std::endl;
      }
      if (label.size() != 10 * 1)
      {
        std::cout << "test_get_batch test fail, label size should be 10*1, but "
                  << label.size() << std::endl;
      }
    }
    {
      std::vector<float> input;
      std::vector<float> label;

      mnist_random_get(input, label, 3);
      if (input.size() != 784 * 3)
      {
        std::cout << "test_get_batch test fail, input size should be 784*3, but "
                  << input.size() << std::endl;
      }
      if (label.size() != 10 * 3)
      {
        std::cout << "test_get_batch test fail, label size should be 10*3, but "
                  << label.size() << std::endl;
      }
    }
  }
}

int main(int argc, char **argv)
{
  test_init();
  test_get_batch();
  return 0;
}