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

#endif // __POTATO_TEST_COMMON_H__