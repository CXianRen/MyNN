
#include "deep_core.hpp"
#include "help.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <algorithm>

void test_loss_mse(){
  {
    std::vector<float> y = {1,0,0};
    std::vector<float> yp = {0,0,1};
    float l = (1+0+1)/3.0;
    float r =  Loss_MSE(y,yp);
    if (l != r){
      std::cout << "mse loss error" << std::endl;
      print_m(y,1,3);
      print_m(yp,1,3);
      std::cout<< "loss should be :"<< l << " but is:" << r << std::endl;
    }
  }
}


int main(int argc, char **argv)
{
  std::cout << "test loss mse" << std::endl;
  test_loss_mse();
  return 0;
}