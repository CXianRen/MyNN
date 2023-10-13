#ifndef __DEEP_CORE_HPP__
#define __DEEP_CORE_HPP__
#include <vector>
/* vector operation */
std::vector<float> dot(const std::vector<float> &m1, const std::vector<float> &m2, const int m1_rows, const int m1_cols, const int m2_cols);
std::vector<float> transform(const std::vector<float> & m1, int rows, int cols);


std::vector<float> operator+(const std::vector<float> &a, const std::vector<float> &b);
std::vector<float> operator-(const std::vector<float> &a, const std::vector<float> &b);
std::vector<float> operator*(const std::vector<float> &a, const float scalar);
std::vector<float> operator*(const float scalar, const std::vector<float> &a);
std::vector<float> operator/(const std::vector<float> &a, const float scalar);

/* Activation fucntion*/
std::vector<float> softmax(const std::vector<float> &m1, const int rows, const int cols);
std::vector<float> relu(const std::vector<float> &m1);

/* Loss function */
float Loss_MSE(const std::vector<float> y, const std::vector<float> yp);

/* network helper*/
void random_init_layer(std::vector<float> &layer);

#endif
