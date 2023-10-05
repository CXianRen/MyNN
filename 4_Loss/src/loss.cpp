#include <vector>
#include <cmath>
#include <algorithm>


float Loss_MSE(std::vector<float> y, std::vector<float> yp){
  float result = 0;
  for(size_t i = 0; i < y.size(); i++){
    result += std::pow(y[i]-yp[i],2); 
  }
  return result/y.size();
}