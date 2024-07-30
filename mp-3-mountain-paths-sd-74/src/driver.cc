#include <iostream>

#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"

int main() {
  const std::string kTestInputFile = "forward-up-2-3.dat";
  constexpr size_t kTestInputFileWidth = 2;
  constexpr size_t kTestInputFileHeight = 3;
  ElevationDataset ed(
      kTestInputFile, kTestInputFileWidth, kTestInputFileHeight);
  GrayscaleImage gi2(ed);
  gi2.ToPpm("test2.txt");

  PathImage pi(gi2, ed);
  pi.ToPpm("test3.txt");
}