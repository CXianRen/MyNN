#include <iostream>

#include <vector>

#include <iomanip>
#include <chrono>

std::vector<float> dot(std::vector<float> &m1, std::vector<float> &m2, int m1_rows, int m1_cols, int m2_cols)
{
  // Returns the product of two matrices: m1 (N,M) x m2 (M,K).
  // m1: left matrix, size (m1_ros * m1_cols)
  // m2: right matrix, size (m1_cols * m2_cols)
  // return: m1_rows * m2_cols

  std::vector<float> output(m1_rows * m2_cols);
  //@Todo: will this step spend a lot of time?
  //@Todo: will the elements be initialized as zero?

  // very basic method.
  for (int m1_row = 0; m1_row < m1_rows; m1_row++)
  {
    for (int m2_col = 0; m2_col < m2_cols; m2_col++)
    {
      for (int k = 0; k < m1_cols; k++)
      {
        // output[m1_row][m2_col] += m1[m1_row][k] * m2[j][m2_col]
        output[m1_row * m2_cols + m2_col] += m1[m1_row * m1_cols + k] * m2[k * m2_cols + m2_col];
      }
    }
  }
  return output;
}

void print_m(std::vector<float> m, int rows, int cols)
{
  std::cout << "matrix: " << rows << "," << cols << std::endl;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      std::cout << std::setw(10) << std::fixed << std::setprecision(6) << m[i * cols + j] << " ";
    }
    std::cout << std::endl;
  }
}

bool test(std::vector<float> &m1, std::vector<float> &m2)
{

  // check the result
  print_m(m1, 1, m1.size());
  print_m(m2, 1, m2.size());

  if (m1.size() != m2.size())
  {
    std::cout << "m1 size:" << m1.size() << " but m2 size:" << m2.size() << std::endl;
    return false;
  }

  for (size_t i = 0; i < m1.size(); i++)
  {
    if (m1[i] != m2[i])
    {
      std::cout << "m1[" << i << "](" << m1[i] << ") != m2[" << i << "](" << m2[i] << ")" << std::endl;
      return false;
    }
  }
  return true;
}

void testCorrectness()
{
  {
    std::vector<float> m1 = {1, 2, 3};
    std::vector<float> m2 = {1,
                             2,
                             3};
    std::vector<float> m1m2 = {14};

    auto output = dot(m1, m2, 1, 3, 1);
    test(m1m2, output);
  }
  {
    std::vector<float> m1 = {1, 2,
                             3, 4};

    std::vector<float> m2 = {1, 2,
                             3, 4};

    std::vector<float> m1m2 = {7, 10,
                               15, 22};

    auto output = dot(m1, m2, 2, 2, 2);
    test(m1m2, output);
  }
  {
    std::vector<float> m1 = {1, 2, 3,
                             4, 5, 6};

    std::vector<float> m2 = {1, 2,
                             3, 4,
                             5, 6};

    std::vector<float> m1m2 = {22, 28,
                               49, 64};

    auto output = dot(m1, m2, 2, 3, 2);
    test(m1m2, output);
  }
}


void test_speed(){
  //@todo vector 大小会有限制吗？
  {
    std::vector<float> m1(4*480*360);
    std::vector<float> m2(4*480*360*512);

    auto start = std::chrono::high_resolution_clock::now();
    auto output = dot(m1, m2, 4, 480*360, 512);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Function took " << duration.count() << " microseconds" << std::endl;
  }
};

int main(int argc, char **argv)
{
  testCorrectness();

  
  test_speed();

  return 0;
}