
#include "deep_core.hpp"
#include "help.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>

void testCorrectness()
{
  {
    std::vector<float> m1 = {1, 2, 3};
    std::vector<float> m2 = {1,
                             2,
                             3};
    std::vector<float> m1m2 = {14};

    auto output = dot(m1, m2, 1, 3, 1);
    test(m1m2, output);
  }
  {
    std::vector<float> m1 = {1, 2,
                             3, 4};

    std::vector<float> m2 = {1, 2,
                             3, 4};

    std::vector<float> m1m2 = {7, 10,
                               15, 22};

    auto output = dot(m1, m2, 2, 2, 2);
    test(m1m2, output);
  }
  {
    std::vector<float> m1 = {1, 2, 3,
                             4, 5, 6};

    std::vector<float> m2 = {1, 2,
                             3, 4,
                             5, 6};

    std::vector<float> m1m2 = {22, 28,
                               49, 64};

    auto output = dot(m1, m2, 2, 3, 2);
    test(m1m2, output);
  }
}


void test_speed(){
  //@todo vector 大小会有限制吗？
  { 
    std::cout << "data size:(4,480*360) * (480*360, 512)" << std::endl;
    std::vector<float> m1(4*480*360);
    std::vector<float> m2(4*480*360*512);

    auto start = std::chrono::high_resolution_clock::now();
    auto output = dot(m1, m2, 4, 480*360, 512);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Function took " << duration.count() << " microseconds" << std::endl;
  }

  { 
    std::cout << "data size:(4,240*180) * (240*180, 256)" << std::endl;
    std::vector<float> m1(4*240*180);
    std::vector<float> m2(4*240*180*256);

    auto start = std::chrono::high_resolution_clock::now();
    auto output = dot(m1, m2, 4, 240*180, 256);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Function took " << duration.count() << " microseconds" << std::endl;
  }

  { 
    std::cout << "data size:(4,120*90) * (120*90, 128)" << std::endl;
    std::vector<float> m1(4*120*90);
    std::vector<float> m2(4*120*90*128);

    auto start = std::chrono::high_resolution_clock::now();
    auto output = dot(m1, m2, 4, 120*90, 128);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Function took " << duration.count() << " microseconds" << std::endl;
  }

  { 
    std::cout << "data size:(128,28*28) * (28*28, 128)" << std::endl;
    std::vector<float> m1(128*28*28);
    std::vector<float> m2(128*28*28*128);

    auto start = std::chrono::high_resolution_clock::now();
    auto output = dot(m1, m2, 4, 28*28, 128);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Function took " << duration.count() << " microseconds" << std::endl;
  }

  { 
    std::cout << "data size:(1,10*10) * (10*10, 1)" << std::endl;
    std::vector<float> m1(1*10*10);
    std::vector<float> m2(1*10*10*1);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i =0; i<100000; i++)
      auto output = dot(m1, m2, 1, 10*10, 1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Function took " << duration.count()/100000.0 << " microseconds" << std::endl;
  }


};

int main(int argc, char **argv)
{
  testCorrectness();
  
  test_speed();

  return 0;
}