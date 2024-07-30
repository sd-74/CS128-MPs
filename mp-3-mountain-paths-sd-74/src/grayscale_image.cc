#include "grayscale_image.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();
  image_ = std::vector<std::vector<Color>>(height_, std::vector<Color>(width_));
  for (size_t row = 0; row < height_; row++) {
    for (size_t col = 0; col < width_; col++) {
      if (dataset.MaxEle() != dataset.MinEle()) {
        auto top =
            static_cast<double>(dataset.DatumAt(row, col) - dataset.MinEle()) *
            kMaxColorValue;
        auto bottom = static_cast<double>(dataset.MaxEle() - dataset.MinEle());

        int shade_of_gray = static_cast<int>(std::round(top / bottom));
        image_[row][col] = Color(shade_of_gray, shade_of_gray, shade_of_gray);
        /*std::cout << "top: " << top << std::endl;
        std::cout << "bottom: " << bottom << std::endl;
        std::cout << "data at: " << dataset.DatumAt(row, col) << std::endl;
        std::cout << "max: " << dataset.MaxEle() << std::endl;
        std::cout << "min: " << dataset.MinEle() << std::endl;
        std::cout << "value: " << shade_of_gray << std::endl;
        std::cout << std::endl;*/
      }
    }
  }
}
GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height) {
  ElevationDataset dataset = ElevationDataset(filename, width, height);
  GrayscaleImage temp = GrayscaleImage(dataset);
  width_ = width;
  height_ = height;
  image_ = temp.GetImage();
}
void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream out_file(name);
  out_file << "P3\n"
           << width_ << " " << height_ << "\n"
           << kMaxColorValue << "\n";
  for (size_t row = 0; row < height_; row++) {
    for (size_t col = 0; col < width_; col++) {
      out_file << image_.at(row).at(col).Red() << " "
               << image_.at(row).at(col).Green() << " "
               << image_.at(row).at(col).Blue() << " ";
    }
    out_file << "\n";
  }
}
