#include "test/test_common.h"

#include "inc/common.h"
#include "inc/core.h"
#include "inc/help.h"

/*
 * to test radom init operation
 */

std::string test_name = "Test radom init operation";

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);

  int rows = 2;
  int cols = 3;

  float *result = new float[6];

  Potato::helper::random_init<float *>(result, rows * cols);

  // check the result
  for (int i = 0; i < rows * cols; i++)
  {
    if (result[i] < -1 || result[i] > 1)
    {
      test_result(test_name, false);
      return 1;
    }
  }
  test_result(test_name, true);
  return 0;
}