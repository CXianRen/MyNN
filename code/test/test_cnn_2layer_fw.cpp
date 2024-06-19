
#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"
#include "inc/help.h"

/*
 * to test cnn 2 layer forward propagation
 * Input : 6*6
 * conv  : K = 3, P = 0, S = 1
 * Output: 4*4
 * conv  : K = 2, P = 0, S = 1
 * Output: 3*3
 */

std::string test_name = "Test cnn forward";

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  float input[36] = {
      1, 2, 3, 4, 5, 6,
      7, 8, 9, 10, 11, 12,
      13, 14, 15, 16, 17, 18,
      19, 20, 21, 22, 23, 24,
      25, 26, 27, 28, 29, 30,
      31, 32, 33, 34, 35, 36};

  float K1[9] = {
      1, 2, 3,
      4, 5, 6,
      7, 8, 9};

  float *O1 = new float[16];
  float O1_ground_truth[16] = {
      474, 519, 564, 609,
      744, 789, 834, 879,
      1014, 1059, 1104, 1149,
      1284, 1329, 1374, 1419};
    
  // layer 1
  {
    // calculate the size of img2col
    int cols = (6 - 3) / 1 + 1;
    int rows = (6 - 3) / 1 + 1;
    int size = cols * rows * 3 * 3;

    float *img2col_input = new float[size];
    Potato::Op::img2cols<float *>(
        input, img2col_input,
        1, 1, 6, 6, 3, 1, 0);

    // print_matrix(img2col_input,cols*rows, 9);

    Potato::Op::dot<float *, float>(
        img2col_input, K1, O1, cols * rows, 3 * 3, 1);

    // check O1 result
    for (int i = 0; i < 16; i++)
    {
      if (fabs(O1[i] - O1_ground_truth[i]) > 1e-6)
      {
        std::stringstream ss;
        ss << "\tFailed at index " << i
           << " expected :"
           << O1_ground_truth[i] << " got: " << O1[i];
        test_print(ss.str());
        test_result(test_name + " O1 result", false);
        return 1;
      }
    }
  }
  {
  // layer 2 
    float K2[4] = {
      1,2,3,4
    };

    float * O2 =  new float[9];
    float O2_ground_truth[9] = {
      6900, 7350, 7800,
      9600, 10050, 10500,
      12300, 12750, 13200
    };

    int cols = (4-2)/1 +1;
    int rows = (4-2)/1 +1;
    int size = cols * rows * 3 * 3;

    float * img2col_O1 = new float[size];

    Potato::Op::img2cols<float *>(
        O1, img2col_O1,
        1, 1, 4, 4, 2, 1, 0);
    
    Potato::Op::dot<float *, float>(
        img2col_O1, K2, O2, cols * rows, 2 * 2, 1);
    
    // check O2 result
    for (int i = 0; i < 9; i++)
    {
      if (fabs(O2[i] - O2_ground_truth[i]) > 1e-6)
      {
        std::stringstream ss;
        ss << "\tFailed at index " << i
           << " expected :"
           << O2_ground_truth[i] << " got: " << O2[i];
        test_print(ss.str());
        test_result(test_name + " O2 result", false);
        return 1;
      }
    }
  }
  test_result(test_name, true);
}