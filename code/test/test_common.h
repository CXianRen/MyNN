#ifndef __POTATO_TEST_COMMON_H__
#define __POTATO_TEST_COMMON_H__

#include <iostream>
#include <sstream>

void test_print(const std::string &info)
{
  std::cout << "[TEST]:" << info << std::endl;
}

void test_result(const std::string &test_name, bool result)
{
  // align the output, padding with spaces to 50 characters
  std::stringstream ss;
  ss << test_name << std::string(50 - test_name.size(), ' ');

  if (result)
  {
    ss << "\tPassed";
  }
  else
  {
    ss << "\tFailed";
  }
  test_print(ss.str());
}

template <typename T>
inline bool compare_float(T a, T b, T epsilon = 1e-6)
{
  return std::abs(a - b) < epsilon;
}


template <typename T>
void print_matrix(const T & a, int M, int N){
  for (int i = 0; i<M; i++){
    for (int j = 0; j<N; j++){
      // code for printing matrix element
      std::cout << a[i*N + j] << " ";
    }
    std::cout << std::endl;
  }
}

#endif // __POTATO_TEST_COMMON_H__