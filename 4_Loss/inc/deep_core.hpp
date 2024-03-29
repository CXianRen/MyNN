#ifndef __DEEP_CORE_HPP__
#define __DEEP_CORE_HPP__
#include <vector>
std::vector<float> dot(const std::vector<float> &m1, const std::vector<float> &m2, const int m1_rows, const int m1_cols, const int m2_cols);

/* Activation fucntion*/
std::vector<float> softmax(const std::vector<float> &m1, const int rows, const int cols);
std::vector<float> relu(const std::vector<float> &m1);

/* Loss function */
float Loss_MSE(const std::vector<float> y, const std::vector<float> yp);


/* network helper*/
void random_init_layer(std::vector<float> & layer);

#endif
