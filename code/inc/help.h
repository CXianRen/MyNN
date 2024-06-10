#ifndef __POTATO_HELP_H__
#define __POTATO_HELP_H__

#include <random>

namespace Potato::helper
{

  /*
   * random initialer
   */
  template <typename T>
  void random_init(T &a, const int size)
  {
    std::mt19937 mt(69);
    std::uniform_real_distribution<float> dist(0, 0.05);
    for (int i = 0; i < size; i++)
    {
      a[i] = dist(mt);
    }
  }

} // namespace Potato::helper

#endif // __POTATO_HELP_H__