#include "elevation_dataset.hpp"

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height) {
  if (width < 0 || height < 0) {
    throw std::invalid_argument("invalid height and width");
  }
  width_ = width;
  height_ = height;
  data_ = std::vector<std::vector<int>>(height_, std::vector<int>(width_, 0));
  std::ifstream file(filename);
  int max = std::numeric_limits<int>::min();
  int min = std::numeric_limits<int>::max();
  size_t row = 0;
  size_t col = 0;
  int value = 0;
  // size_t col_count = 0;
  while (file >> value) {
    if (row > height_) {
      throw std::runtime_error("data dimensions wrong");
    }
    data_[row][col++] = value;
    // std::cout << value << " " << std::endl;
    max = std::max(max, value);
    min = std::min(min, value);
    if (col == width_) {
      col = 0;
      ++row;
    }
    // col_count++;
  }
  /*if (row != height_ || col_count != width_ * height_ || col != 0)
    throw std::runtime_error("data dimensions wrong");*/
  min_ele_ = min;
  max_ele_ = max;
}

size_t ElevationDataset::Width() const { return width_; }
size_t ElevationDataset::Height() const { return height_; }
int ElevationDataset::MaxEle() const { return max_ele_; }
int ElevationDataset::MinEle() const { return min_ele_; }
int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_.at(row).at(col);
}
const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}
