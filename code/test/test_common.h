#ifndef __POTATO_TEST_COMMON_H__
#define __POTATO_TEST_COMMON_H__

#include <iostream>

void test_print(const std::string &info)
{
  std::cout << "[TEST]:" << info << std::endl;
}

#endif // __POTATO_TEST_COMMON_H__