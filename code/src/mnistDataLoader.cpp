#include "inc/dataloader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

int Potato::DataLoader::mnistDataLoader::init()
{
  if (!is_init_)
  {
    std::ifstream dfile(data_file_path_);
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
      labels_.push_back(label_vec);

      std::vector<float> img(tokens.size() - 1, 0);
      for (size_t i = 0; i < img.size(); i++)
      {
        img[i] = strtof(tokens[i + 1].c_str(), 0);
      }
      imgs_.push_back(img);
    }

    is_init_ = true;
    std::cout << "[MNIST] init, total :" << imgs_.size() << " imgs" << std::endl;
  }
  return 0;
}

int Potato::DataLoader::mnistDataLoader::
    random_get_trainning(std::vector<float> &input,
                         std::vector<float> &label, int batch)
{
  if (size_t(batch) > imgs_.size())
    return -1;

  input.clear();
  label.clear();

  int idx = rand() % (imgs_.size() - batch);
  for (int i = idx; i < idx + batch; i++)
  {
    input.insert(input.end(), imgs_[i].begin(), imgs_[i].end());
    label.insert(label.end(), labels_[i].begin(), labels_[i].end());
  }
  return 0;
}

int Potato::DataLoader::mnistDataLoader::
    random_get_testing(std::vector<float> &input,
                       std::vector<float> &label, int batch)
{
  // TODO
  return 0;
}
