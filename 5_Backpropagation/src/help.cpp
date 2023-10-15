#include "help.hpp"
#include <iomanip>
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

void print_m(const std::vector<float> m, const int rows, const int cols)
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

bool test(const std::vector<float> &m1, const std::vector<float> &m2)
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

// hard code
static std::vector<std::vector<float>> imgs;
static std::vector<std::vector<float>> labels;
static bool is_mnist_init = false;

const std::vector<std::vector<float>> &mnist_get_imgs() { return imgs; }
const std::vector<std::vector<float>> &mnist_get_labels() { return labels; }

int mnist_init(const std::string data_file)
{
  if (!is_mnist_init)
  {
    std::ifstream dfile(data_file);
    if (!dfile.is_open())
    {
      std::cout << "[MNIST] can not open data file" << std::endl;
      return -1;
    }
    std::string line;
    std::string token;

    while (std::getline(dfile, line))
    {
      std::stringstream ss(line);
      std::vector<std::string> tokens;
      while (std::getline(ss, token, '\t'))
      {
        tokens.push_back(token);
      }
      int label = strtof(tokens[0].c_str(), 0);
      std::vector<float> label_vec(10, 0);
      label_vec[label] = 1;
      labels.push_back(label_vec);

      std::vector<float> img(tokens.size() - 1, 0);
      for (size_t i = 0; i < img.size(); i++)
      {
        img[i] = strtof(tokens[i + 1].c_str(), 0);
      }
      imgs.push_back(img);
    }

    is_mnist_init = true;
    std::cout << "[MNIST] init, total :" << imgs.size() << " imgs" << std::endl;
  }
  return 0;
}

int mnist_random_get(std::vector<float> &input,
                     std::vector<float> &label, int batch)
{
  input.clear();
  label.clear();
  int idx = rand() % (imgs.size() - batch);
  for (int i = idx; i < idx + batch; i++)
  {
    input.insert(input.end(), imgs[i].begin(), imgs[i].end());
    label.insert(label.end(), labels[i].begin(), labels[i].end());
  }
  return 0;
}

void random_init_layer(std::vector<float> &layer)
{
  std::mt19937 mt(69);
  std::uniform_real_distribution<float> dist(0, 0.05);
  for (size_t i = 0; i < layer.size(); i++)
  {
    layer[i] = dist(mt);
  }
}