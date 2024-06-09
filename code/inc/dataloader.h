#ifndef __POTATO_DATA_SET__
#define __POTATO_DATA_SET__

#include <vector>
#include <string>

namespace Potato::DataLoader
{
  class abstractDataLoader
  {
  public:
    abstractDataLoader() = default;

    virtual const std::string
    get_data_file_path() { return data_file_path_; }

    virtual int init() = 0;

  protected:
    std::string data_file_path_;
  };

  class mnistDataLoader : abstractDataLoader
  {
  public:
    mnistDataLoader(const std::string data_file)
    {
      data_file_path_ = data_file;
    };

    int random_get_trainning(std::vector<float> &input,
                             std::vector<float> &label, int batch);
    int random_get_testing(std::vector<float> &input,
                           std::vector<float> &label, int batch);

    int init() override;

    int get_data_size() { return imgs_.size(); };

  public:
    bool is_init_ = false;
    std::vector<std::vector<float>> imgs_;
    std::vector<std::vector<float>> labels_;
    int mnist_init();
  };

} // namespace Potato::DataLoader
#endif // __POTATO_DATA_SET__