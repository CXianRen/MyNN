#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"
#include "inc/help.h"

/*
 * to test cnn 2 layer backward propagation
 * Input : 6*6
 * conv  : K = 3, P = 0, S = 1
 * Output: 4*4
 * conv  : K = 2, P = 0, S = 1
 * Output: 3*3
 */

std::string test_name = "Test cnn backward";

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

    float O1[16] = {
        474, 519, 564, 609,
        744, 789, 834, 879,
        1014, 1059, 1104, 1149,
        1284, 1329, 1374, 1419};

    float K2[4] = {
        1, 2, 3, 4};

    float O2[9] = {
        6900, 7350, 7800,
        9600, 10050, 10500,
        12300, 12750, 13200};

    float dLdO2[9] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9};

    float *dK2 = new float[4];

    float dK2_grount_truth[4] = {
        40635, 42660, 52785, 54810};

    float *img2col_O1 = new float[4 * 9];

    Potato::Op::img2cols<float *>(
        O1, img2col_O1,
        1, 1, 4, 4, 3, 1, 0);

    Potato::Op::dot<float *, float>(
        img2col_O1, dLdO2, dK2, 4, 9, 1);

    // print_matrix(dK2, 2, 2);

    // check the result
    for (int i = 0; i < 4; i++)
    {
        if (fabs(dK2[i] - dK2_grount_truth[i]) > 1e-6)
        {
            std::stringstream ss;
            ss << "dK2[" << i << "] = " << dK2[i] << " != " << dK2_grount_truth[i];
            test_result(test_name, false);
            test_print(ss.str());
            return 1;
        }
    }

    // flip the kernel
    float *K2_flipped = new float[4];
    Potato::Op::flipfilter<float *>(
        K2, K2_flipped, 2, 2);
    print_matrix(K2_flipped, 2, 2);

    // padding with K-1 
    float *img2col_dLdO2 = new float[(3 + 2 - 1) * (3 + 2 - 1) *4];
    Potato::Op::img2cols<float *>(
        dLdO2, img2col_dLdO2,
        1, 1, 3, 3, 2, 1, 1);
    
    // print_matrix(img2col_dLdO2, 4*4, 4);
    // full convolution
    float *dLdO1 = new float[16];
    Potato::Op::dot<float *, float>(
        img2col_dLdO2, K2_flipped, dLdO1, 4*4, 2*2, 1);

    float dLdO1_ground_truth[16] = {
       1, 4, 7, 6,
       7, 23, 33, 24,
       19, 53, 63, 42,
       21, 52, 59, 36};
    
    // check the result
    for (int i = 0; i < 16; i++)
    {
        if (fabs(dLdO1[i] - dLdO1_ground_truth[i]) > 1e-6)
        {
            std::stringstream ss;
            ss << "dLdO1[" << i << "] = " << dLdO1[i] << " != " << dLdO1_ground_truth[i];
            test_result(test_name, false);
            test_print(ss.str());
            return 1;
        }
    }
}