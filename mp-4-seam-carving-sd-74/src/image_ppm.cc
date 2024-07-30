#include "image_ppm.hpp"

// implement the rest of ImagePPM's functions here
std::ostream& operator<<(std::ostream& os, const ImagePPM& image) {
  os << "P3\n";
  os << image.GetWidth() << " " << image.GetHeight() << "\n";
  os << image.GetMaxColorValue() << "\n";
  for (int row = 0; row < image.GetHeight(); row++) {
    for (int col = 0; col < image.GetWidth(); col++) {
      Pixel current_pixel = image.GetPixel(row, col);
      os << current_pixel.GetRed() << "\n";
      os << current_pixel.GetGreen() << "\n";
      os << current_pixel.GetBlue() << "\n";
    }
  }
  return os;
}

void ImagePPM::CarveV(const int* removing) {
  auto** carved = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    carved[row] = new Pixel[width_ - 1];
  }
  for (int row = 0; row < height_; row++) {
    int count = 0;
    for (int col = 0; col < width_; col++) {
      if (col != removing[row]) {
        carved[row][count] = pixels_[row][col];
        count++;
      }
    }
  }
  int h = height_;
  int w = width_ - 1;
  Clear();
  height_ = h;
  width_ = w;
  pixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    pixels_[row] = new Pixel[width_];
    for (int col = 0; col < width_; col++) {
      pixels_[row][col] = carved[row][col];
    }
  }
  for (int row = 0; row < height_; row++) {
    delete[] carved[row];
  }
  delete[] carved;
}

void ImagePPM::CarveH(const int* removing) {
  auto** carved = new Pixel*[height_ - 1];
  for (int row = 0; row < height_ - 1; row++) {
    carved[row] = new Pixel[width_];
  }
  for (int col = 0; col < width_; col++) {
    int count = 0;
    for (int row = 0; row < height_; row++) {
      if (row != removing[col]) {
        carved[count][col] = pixels_[row][col];
        count++;
      }
    }
  }
  int h = height_ - 1;
  int w = width_;
  Clear();
  height_ = h;
  width_ = w;
  pixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    pixels_[row] = new Pixel[width_];
    for (int col = 0; col < width_; col++) {
      pixels_[row][col] = carved[row][col];
    }
  }
  for (int row = 0; row < height_; row++) {
    delete[] carved[row];
  }
  delete[] carved;
}

// given functions below, DO NOT MODIFY

ImagePPM::ImagePPM(const std::string& path) {
  std::ifstream input_file(path);
  input_file >> *this;
  input_file.close();
}

ImagePPM::ImagePPM(const ImagePPM& source) { *this = source; }

ImagePPM& ImagePPM::operator=(const ImagePPM& source) {
  if (this == &source) {
    return *this;
  }

  Clear();

  height_ = source.height_;
  width_ = source.width_;
  max_color_value_ = source.max_color_value_;

  pixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    pixels_[row] = new Pixel[width_];

    for (int col = 0; col < width_; col++) {
      pixels_[row][col] = source.pixels_[row][col];
    }
  }

  return *this;
}

ImagePPM::~ImagePPM() { Clear(); }

void ImagePPM::Clear() {
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }

  delete[] pixels_;

  height_ = 0;
  width_ = 0;
  pixels_ = nullptr;
}

std::istream& operator>>(std::istream& is, ImagePPM& image) {
  image.Clear();
  std::string line;
  // ignore magic number line
  getline(is, line);
  // check to see if there's a comment line
  getline(is, line);
  if (line[0] == '#') {
    getline(is, line);
  }
  // parse width and height
  int space = line.find_first_of(' ');
  image.width_ = std::stoi(line.substr(0, space));
  image.height_ = std::stoi(line.substr(space + 1));
  // get max color value
  getline(is, line);
  image.max_color_value_ = std::stoi(line);
  // init and fill in Pixels array
  image.pixels_ = new Pixel*[image.height_];
  for (int i = 0; i < image.height_; i++) {
    image.pixels_[i] = new Pixel[image.width_];
  }
  for (int row = 0; row < image.height_; row++) {
    for (int col = 0; col < image.width_; col++) {
      getline(is, line);
      int red = std::stoi(line);
      getline(is, line);
      int green = std::stoi(line);
      getline(is, line);
      int blue = std::stoi(line);

      Pixel p(red, green, blue);
      image.pixels_[row][col] = p;
    }
  }
  return is;
}