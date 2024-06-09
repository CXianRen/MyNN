#ifndef __POTATO_HELP_H__
#define __POTATO_HELP_H__

namespace Potato::helper
{

  /*
   * random initialer
   * [-1,1]
   */
  template <typename T>
  void random_init(T &a, const int size)
  {
    for (int i = 0; i < size; i++)
    {
      a[i] = (rand() % 2000 - 1000) / 1000.0;
    }
  }

} // namespace Potato::helper

#endif // __POTATO_HELP_H__