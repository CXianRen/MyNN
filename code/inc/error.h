#ifndef __POTATO_ERROR_H__
#define __POTATO_ERROR_H__

#include <iostream>
#include <sstream>
#include <stdexcept>

#define CHECK_SIZE(a, b)                         \
  if ((a) != (b))                                \
  {                                              \
    std::stringstream ss;                        \
    ss << "Size mismatch: "                      \
       << (a) << " != " << (b)                   \
       << " at " << __FILE__ << ":" << __LINE__; \
    throw std::runtime_error(ss.str());          \
  }

#endif // __POTATO_ERROR_H__