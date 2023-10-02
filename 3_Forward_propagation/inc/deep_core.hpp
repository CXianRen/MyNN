#ifndef __DEEP_CORE_HPP__
#define __DEEP_CORE_HPP__
#include <vector>
std::vector<float> dot(std::vector<float> &m1, std::vector<float> &m2, int m1_rows, int m1_cols, int m2_cols);
std::vector<float> softmax(std::vector<float> &m1, int rows, int cols);
std::vector<float> relu(std::vector<float> &m1);
#endif
