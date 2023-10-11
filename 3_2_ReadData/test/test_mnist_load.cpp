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
    int ret = mnist_init("../data/train.txt");
    if (ret != 0)
    {
      std::cout << "Init test fail: should return 0, but " << ret << std::endl;
    }
    auto imgs = mnist_get_imgs();
    if (imgs[0].size() != 784){
      std::cout << "img 0 size is not 784, but " << imgs[0].size()  << std::endl;
    }
    auto labels = mnist_get_labels();
    print_m(labels[0],1,10);
    if (labels[0][1] != 1.0){
      std::cout << "labels[0][1] is not 1, but " << labels[0][1]  << std::endl;
    } 
  }
}

int main(int argc, char **argv)
{
  test_init();
  return 0;
}