
#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"

/*
 * to test loss MSE operation
 */

std::string test_name = "Test loss MSE operation";

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  float a[6] = {1, 2, 3, 4, 5, 6};
  float b[6] = {1, 2, 3, 4, 5, 6};

  float result = 0;

  float ground_truth = 0;

  result = Potato::Loss::MSE<float *, float>(a, b, 6);

  // check the result
  if (result != ground_truth)
  {
    test_result(test_name, false);
    return 1;
  }
  test_result(test_name, true);
}