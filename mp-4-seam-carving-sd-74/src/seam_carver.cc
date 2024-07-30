#include "seam_carver.hpp"

// implement the rest of SeamCarver's functions here
void SeamCarver::InitializeArrHorizontal(int** arr) const {  // helper
  for (int row = 0; row < height_; row++) {
    arr[row][width_ - 1] = GetEnergy(row, width_ - 1);
  }
  for (int col = width_ - 2; col >= 0; col--) {
    for (int row = 0; row < height_; row++) {
      if (row == 0) {  // if you are at first row
        int compare_one = arr[row][col + 1];
        int compare_two = arr[row + 1][col + 1];
        arr[row][col] =
            GetEnergy(row, col) + std::min(compare_one, compare_two);
      } else if (row == height_ - 1) {  // if your are at last row
        int compare_one = arr[row - 1][col + 1];
        int compare_two = arr[row][col + 1];
        arr[row][col] =
            GetEnergy(row, col) + std::min(compare_one, compare_two);
      } else {
        int compare_one = arr[row - 1][col + 1];
        int compare_two = arr[row][col + 1];
        int compare_three = arr[row + 1][col + 1];
        arr[row][col] =
            GetEnergy(row, col) +
            std::min(compare_one, std::min(compare_two, compare_three));
      }
    }
  }
}

void SeamCarver::InitializeArrVertical(int** arr) const {  // helper
  for (int col = 0; col < width_; col++) {
    arr[height_ - 1][col] = GetEnergy(height_ - 1, col);
  }
  for (int row = height_ - 2; row >= 0; row--) {
    for (int col = 0; col < width_; col++) {
      if (col == 0) {  // if you are at first row
        int compare_one = arr[row + 1][col];
        int compare_two = arr[row + 1][col + 1];
        arr[row][col] =
            GetEnergy(row, col) + std::min(compare_one, compare_two);
      } else if (col == width_ - 1) {  // if your are at last row
        int compare_one = arr[row + 1][col - 1];
        int compare_two = arr[row + 1][col];
        arr[row][col] =
            GetEnergy(row, col) + std::min(compare_one, compare_two);
      } else {
        int compare_one = arr[row + 1][col - 1];
        int compare_two = arr[row + 1][col];
        int compare_three = arr[row + 1][col + 1];
        arr[row][col] =
            GetEnergy(row, col) +
            std::min(compare_one, std::min(compare_two, compare_three));
      }
    }
  }
}

int* SeamCarver::FindMinHorizontalPath(int** arr) const {
  int* path = new int[width_];
  int min = arr[0][0];
  int min_row = 0;
  for (int row = 0; row < height_; row++) {
    if (arr[row][0] < min) {
      min = arr[row][0];
      min_row = row;
    }
  }
  path[0] = min_row;
  for (int col = 0; col < width_ - 1; col++) {
    int row = (path[col] == 0) ? 0 : path[col];
    if (path[col] == 0) {
      int compare_one = arr[row][col + 1];
      int compare_two = arr[row + 1][col + 1];
      if (compare_one <= compare_two)
        path[col + 1] = row;
      else
        path[col + 1] = row + 1;
    } else if (path[col] == height_ - 1) {
      int compare_one = arr[row - 1][col + 1];
      int compare_two = arr[row][col + 1];
      if (compare_two <= compare_one)
        path[col + 1] = row;
      else
        path[col + 1] = row - 1;
    } else {
      int compare_one = arr[row - 1][col + 1];
      int compare_two = arr[row][col + 1];
      int compare_three = arr[row + 1][col + 1];
      if (compare_two <= compare_one && compare_two <= compare_three)
        path[col + 1] = row;
      else if (compare_one < compare_two && compare_one <= compare_three)
        path[col + 1] = row - 1;
      else
        path[col + 1] = row + 1;
    }
  }
  return path;
}

int* SeamCarver::FindMinVerticalPath(int** arr) const {
  int* path = new int[height_];
  int min = arr[0][0];
  int min_col = 0;
  for (int col = 0; col < width_; col++) {
    if (arr[0][col] < min) {
      min = arr[0][col];
      min_col = col;
    }
  }
  path[0] = min_col;
  for (int row = 0; row < height_ - 1; row++) {
    int col = (path[row] == 0) ? 0 : path[row];
    if (path[row] == 0) {
      int compare_one = arr[row + 1][col];
      int compare_two = arr[row + 1][col + 1];
      if (compare_one <= compare_two)
        path[row + 1] = col;
      else
        path[row + 1] = col + 1;
    } else if (path[row] == width_ - 1) {
      int compare_one = arr[row + 1][col - 1];
      int compare_two = arr[row + 1][col];
      if (compare_two <= compare_one)
        path[row + 1] = col;
      else
        path[row + 1] = col - 1;
    } else {
      int compare_one = arr[row + 1][col - 1];
      int compare_two = arr[row + 1][col];
      int compare_three = arr[row + 1][col + 1];
      if (compare_two <= compare_one && compare_two <= compare_three)
        path[row + 1] = col;
      else if (compare_one < compare_two && compare_one <= compare_three)
        path[row + 1] = col - 1;
      else
        path[row + 1] = col + 1;
    }
  }
  return path;
}

int SeamCarver::GetEnergy(int row, int col) const {
  Pixel left = Pixel();
  Pixel right = Pixel();
  Pixel top = Pixel();
  Pixel bottom = Pixel();
  if (col == 0) {  // left edge case
    left = image_.GetPixel(row, image_.GetWidth() - 1);
  } else {
    left = image_.GetPixel(row, col - 1);
  }
  if (col == image_.GetWidth() - 1) {  // right edge case
    right = image_.GetPixel(row, 0);
  } else {
    right = image_.GetPixel(row, col + 1);
  }
  if (row == 0) {  // top edge case
    top = image_.GetPixel(image_.GetHeight() - 1, col);
  } else {
    top = image_.GetPixel(row - 1, col);
  }
  if (row == image_.GetHeight() - 1) {  // bottom edge case
    bottom = image_.GetPixel(0, col);
  } else {
    bottom = image_.GetPixel(row + 1, col);
  }
  int col_squared =
      ((left.GetRed() - right.GetRed()) * (left.GetRed() - right.GetRed())) +
      ((left.GetGreen() - right.GetGreen()) *
       (left.GetGreen() - right.GetGreen())) +
      ((left.GetBlue() - right.GetBlue()) * (left.GetBlue() - right.GetBlue()));
  int row_squared =
      ((top.GetRed() - bottom.GetRed()) * (top.GetRed() - bottom.GetRed())) +
      ((top.GetGreen() - bottom.GetGreen()) *
       (top.GetGreen() - bottom.GetGreen())) +
      ((top.GetBlue() - bottom.GetBlue()) * (top.GetBlue() - bottom.GetBlue()));
  return col_squared + row_squared;
}

int* SeamCarver::GetHorizontalSeam() const {
  int** arr = new int*[height_];
  for (int row = 0; row < height_; row++) {
    arr[row] = new int[width_];
  }
  InitializeArrHorizontal(arr);
  int* path = FindMinHorizontalPath(arr);
  for (int row = 0; row < height_; row++) {
    delete[] arr[row];
  }
  delete[] arr;
  return path;
}

int* SeamCarver::GetVerticalSeam() const {
  int** arr = new int*[height_];
  for (int row = 0; row < height_; row++) {
    arr[row] = new int[width_];
  }
  InitializeArrVertical(arr);
  int* path = FindMinVerticalPath(arr);
  for (int row = 0; row < height_; row++) {
    delete[] arr[row];
  }
  delete[] arr;
  return path;
}

void SeamCarver::RemoveHorizontalSeam() {
  auto* removing = GetHorizontalSeam();
  image_.CarveH(removing);
  height_--;
  delete[] removing;
}
void SeamCarver::RemoveVerticalSeam() {
  auto* removing = GetVerticalSeam();
  image_.CarveV(removing);
  width_--;
  delete[] removing;
}

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
