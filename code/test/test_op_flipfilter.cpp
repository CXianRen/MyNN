#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"
#include "inc/help.h"

/**
 * to test flip filter
 *
 */

std::string test_name = "Test flip filter";

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  float K1[9] = {
      1, 2, 3,
      4, 5, 6,
      7, 8, 9};

  float K1_flip[9] = {
      9, 8, 7,
      6, 5, 4,
      3, 2, 1};

  float *K1_flipped = new float[9];
  Potato::Op::flipfilter<float *>(
      K1, K1_flipped, 3, 3);

  for (int i = 0; i < 9; i++)
  {
    if (!compare_float(K1_flipped[i], K1_flip[i]))
    {
      test_result(test_name, false);
      return 1;
    }
  }
  test_result(test_name, true);
}
