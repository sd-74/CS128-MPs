#include "path_image.hpp"

const Color kGreen(31, 253, 13);
const Color kRed(252, 25, 63);

void ComputeNextRow(const std::vector<std::vector<int>>& data_vec,
                    size_t& curr_row,
                    size_t& col,
                    size_t height,
                    std::vector<std::vector<Color>>& img,
                    Path& this_path) {
  size_t next_row = 0;
  int mid = std::abs(data_vec.at(curr_row).at(col) -
                     data_vec.at(curr_row).at(col + 1));
  if (col == 0) {
    img.at(curr_row).at(col) = kRed;
  }
  if (curr_row == 0) {
    int top = std::abs(data_vec.at(curr_row).at(col) -
                       data_vec.at(curr_row + 1).at(col + 1));
    next_row = (mid <= top) ? curr_row : curr_row + 1;
  } else if (curr_row == height - 1) {
    int bottom = std::abs(data_vec.at(curr_row).at(col) -
                          data_vec.at(curr_row - 1).at(col + 1));
    next_row = (bottom < mid) ? curr_row - 1 : curr_row;
  } else {
    int top = std::abs(data_vec.at(curr_row).at(col) -
                       data_vec.at(curr_row - 1).at(col + 1));
    int bottom = std::abs(data_vec.at(curr_row).at(col) -
                          data_vec.at(curr_row + 1).at(col + 1));
    if (mid <= bottom && mid <= top)
      next_row = curr_row;
    else if (bottom <= top && bottom < mid)
      next_row = curr_row + 1;
    else
      next_row = curr_row - 1;
  }
  img.at(next_row).at(col + 1) = kRed;
  this_path.SetLoc(col + 1, next_row);
  this_path.IncEleChange(std::abs(data_vec.at(curr_row).at(col) -
                                  data_vec.at(next_row).at(col + 1)));
  curr_row = next_row;
}

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  std::vector<std::vector<Color>> img = GrayscaleImage(image).GetImage();
  std::vector<std::vector<int>> data_vec = ElevationDataset(dataset).GetData();
  width_ = image.Width();
  height_ = image.Height();
  size_t best_path_row = 0;
  unsigned int min_elevation_change = std::numeric_limits<unsigned int>::max();
  for (size_t row = 0; row < height_; row++) {
    size_t curr_row = row;
    Path this_path = Path(width_, row);
    for (size_t col = 0; col < width_ - 1; col++) {
      ComputeNextRow(data_vec, curr_row, col, height_, img, this_path);
    }
    if (this_path.EleChange() < min_elevation_change) {
      min_elevation_change = this_path.EleChange();
      best_path_row = row;
    }
    paths_.push_back(this_path);
  }
  Path best_path = paths_.at(best_path_row);
  for (size_t col = 0; col < width_; col++) {
    img[best_path.GetPath().at(col)][col] = kGreen;
  }
  path_image_ = img;
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream out_file(name);
  out_file << "P3\n"
           << width_ << " " << height_ << "\n"
           << kMaxColorValue << "\n";
  for (size_t row = 0; row < height_; row++) {
    for (size_t col = 0; col < width_; col++) {
      out_file << path_image_.at(row).at(col).Red() << " "
               << path_image_.at(row).at(col).Green() << " "
               << path_image_.at(row).at(col).Blue() << " ";
    }
    out_file << "\n";
  }
}
