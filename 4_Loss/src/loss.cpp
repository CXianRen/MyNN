#include <vector>
#include <cmath>
#include <algorithm>


float Loss_MSE(const std::vector<float> y, const std::vector<float> yp){
  float result = 0;
  for(size_t i = 0; i < y.size(); i++){
    result += std::pow(y[i]-yp[i],2); 
  }
  return result/y.size();
}