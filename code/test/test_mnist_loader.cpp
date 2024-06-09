#include "test/test_common.h"

#include "inc/common.h"

#include <iostream>
#include <iomanip>
#include <chrono>


#include "inc/dataloder.h"


/*
 * to test dataloader
 */

std::string test_name = "Test dataloader";

int test_init()
{
  {
    auto mydata = Potato::DataLoader::mnistDataLoader("/tmp/not_exit.txt");
    int ret = mydata.init();
    if (ret != -1)
    {
      test_result(test_name, false);
      test_print("\tInit test fail: should return -1, but " + ret);
      return 1;
    }
  }

  {
    auto mydata = Potato::DataLoader::mnistDataLoader("data/test_data.txt");
    int ret = mydata.init();
    if (ret != 0)
    {
      test_result(test_name, false);
      test_print("\tInit test fail: should return 0, but " + ret);
      return 1;
    }

    auto imgs = mydata.imgs_;
    if (imgs[0].size() != 784)
    {
      test_result(test_name, false);
      test_print("\timg 0 size is not 784, but " + imgs[0].size());
      return 1;
    }
    
    auto labels = mydata.labels_;
    if (labels[0][0] != 1.0)
    {
      test_result(test_name, false);
      std::stringstream ss;
      ss << "\tlabels[0][0] is not 1, but " << labels[0][0];
      test_print(ss.str());
      return 1;
    }
    for (int i = 0; i < 784; i++)
    {
      if (imgs[0][i] != i + 1)
      {
        test_result(test_name, false);
        test_print(
            "\timgs[0][" + std::to_string(i) +
            "] is not " + std::to_string(i + 1) +
            ", but " + std::to_string(imgs[0][i]));
        return 1;
      }
    }
  }
  return 0;
}

int test_get_batch()
{
  {
    auto mydata = Potato::DataLoader::mnistDataLoader("data/test_data.txt");
    int ret = mydata.init();
    if (ret != 0)
    {
      test_result(test_name, false);
      test_print("\tInit test fail: should return 0, but " + ret);
      return 1;
    }
    {
      std::vector<float> input;
      std::vector<float> label;

      mydata.random_get_trainning(input, label, 1);
      if (input.size() != 784 * 1)
      {
        test_result(test_name, false);
        test_print("\tinput size should be 784*1, but " + std::to_string(input.size()));
        return 1;
      }
      if (label.size() != 10 * 1)
      {
        test_result(test_name, false);
        test_print("\tlabel size should be 10*1, but " + std::to_string(label.size()));
        return 1;
      }
    }
    {
      std::vector<float> input;
      std::vector<float> label;

      mydata.random_get_trainning(input, label, 3);
      if (input.size() != 784 * 3)
      {
        test_result(test_name, false);
        test_print("\tinput size should be 784*3, but " + std::to_string(input.size()));
        return 1;
      }
      if (label.size() != 10 * 3)
      {
        test_result(test_name, false);
        test_print("\tlabel size should be 10*3, but " + std::to_string(label.size()));
        return 1;
      }
    }
  }
  return 0;
}

int main(int argc, char **argv)
{
  if (test_init() == 0 && test_get_batch() == 0)
  {
    test_result(test_name, true);
  }

  return 0;
}