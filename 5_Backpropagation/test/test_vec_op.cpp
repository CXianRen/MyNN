
#include <cassert>
#include <iostream>

#include "help.hpp"
#include "deep_core.hpp"

void test_vec_plus_vec()
{
  std::cout << "test:" << __func__ << std::endl;
  std::vector<float> vec1(3, 1);
  std::vector<float> vec2(3, 2);
  {
    auto c = vec1 + vec2;
    // print_m(c,1,3);
    for (size_t i = 0; i < c.size(); i++)
    {
      assert(c[i] == 3 ? true : (std::cerr << "test fail"
                                           << "c[" << i << "] =" << c[i] << " != 3" << std::endl,
                                 false));
    }
  }
}

void test_vec_minus_vec()
{
  std::cout << "test:" << __func__ << std::endl;
  std::vector<float> vec1(3, 1);
  std::vector<float> vec2(3, 2);
  {
    auto c = vec1 - vec2;
    // print_m(c,1,3);
    for (size_t i = 0; i < c.size(); i++)
    {
      assert(c[i] == -1 ? true : (std::cerr << "test fail"
                                            << "c[" << i << "] =" << c[i] << " != -1" << std::endl,
                                  false));
    }
  }
}

void test_vec_mult_scalar()
{
  std::cout << "test:" << __func__ << std::endl;
  std::vector<float> vec1(3, 1);
  // std::vector<float> vec2(3, 2);
  float s = 2;
  {
    auto c = vec1 * s;
    // print_m(c,1,3);
    for (size_t i = 0; i < c.size(); i++)
    {
      assert(c[i] == 2 ? true : (std::cerr << "test fail"
                                           << "c[" << i << "] =" << c[i] << " != 2" << std::endl,
                                 false));
    }
  }

  {
    auto c = s * vec1;
    // print_m(c,1,3);
    for (size_t i = 0; i < c.size(); i++)
    {
      assert(c[i] == 2 ? true : (std::cerr << "test fail"
                                           << "c[" << i << "] =" << c[i] << " != 2" << std::endl,
                                 false));
    }
  }
}

void test_vec_divived_scalar()
{
  std::cout << "test:" << __func__ << std::endl;
  std::vector<float> vec1(3, 1);
  // std::vector<float> vec2(3, 2);
  float s = 2;
  {
    auto c = vec1 / s;
    // print_m(c,1,3);
    for (size_t i = 0; i < c.size(); i++)
    {
      assert(c[i] == 0.5 ? true : (std::cerr << "test fail"
                                             << "c[" << i << "] =" << c[i] << " != 0.5" << std::endl,
                                   false));
    }
  }
}

void test_vec_transform()
{
  std::cout << "test:" << __func__ << std::endl;
  {
    std::vector<float> vec1 = {
        1, 2,
        3, 4};
    auto r = transform(vec1, 2, 2);
    std::vector<float> vec_r = {
        1, 3,
        2, 4};

    for (size_t i = 0; i < vec1.size(); i++)
    {
      assert(r[i] == vec_r[i]);
    }
  }
  {
    std::vector<float> vec1 = {
        1, 2, 3,
        4, 5, 6};
    auto r = transform(vec1, 2, 3);
    std::vector<float> vec_r = {
        1, 4,
        2, 5,
        3, 6};

    for (size_t i = 0; i < vec1.size(); i++)
    {
      if (r[i] != vec_r[i])
      {
        print_m(vec1, 2, 3);
        print_m(r, 3, 2);
        assert(false);
      }
    }
  }
  {
    std::vector<float> vec1 = {
        1, 2,
        3, 4,
        5, 6};
    auto r = transform(vec1, 3, 2);
    std::vector<float> vec_r = {
        1, 3, 5,
        2, 4, 6};
    for (size_t i = 0; i < vec1.size(); i++)
    {
      assert(r[i] == vec_r[i]);
    }
  }
}

int main(int argc, char **argv)
{
  test_vec_plus_vec();
  test_vec_minus_vec();
  test_vec_mult_scalar();
  test_vec_divived_scalar();
  test_vec_transform();
  return 0;
}