#include "help.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>

#define private public
#include "deep_dataset.hpp"
#undef private

void test_init()
{
  {
    auto mydata = MYNN::mnistDataLoader("/tmp/not_exit.txt");
    int ret = mydata.init();
    if (ret != -1)
    {
      std::cout << "Init test fail: should return -1, but " << ret << std::endl;
    }
  }

  {
    auto mydata = MYNN::mnistDataLoader("../data/test_data.txt");
    int ret = mydata.init();
    if (ret != 0)
    {
      std::cout << "Init test fail: should return 0, but " << ret << std::endl;
    }

    auto imgs = mydata.imgs_;
    if (imgs[0].size() != 784)
    {
      std::cout << "img 0 size is not 784, but " << imgs[0].size() << std::endl;
    }
    auto labels = mydata.labels_;
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
    auto mydata = MYNN::mnistDataLoader("../data/test_data.txt");
    int ret = mydata.init();
    if (ret != 0)
    {
      std::cout << "Init test fail: should return 0, but " << ret << std::endl;
    }
    {
      std::vector<float> input;
      std::vector<float> label;

      mydata.random_get_trainning(input, label, 1);
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

      mydata.random_get_trainning(input, label, 3);
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