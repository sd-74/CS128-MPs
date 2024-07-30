#ifndef PATH_H
#define PATH_H

#include <cstdlib>  // for size_t
#include <vector>

class Path {
public:
  Path(size_t length, size_t starting_row);
  size_t Length() const { return length_; }
  size_t StartingRow() const { return starting_row_; }
  unsigned int EleChange() const { return ele_change_; }
  void IncEleChange(unsigned int value);
  const std::vector<size_t>& GetPath() const { return path_; }
  void SetLoc(size_t col, size_t row);

private:
  size_t length_;
  size_t starting_row_;
  std::vector<size_t> path_;
  unsigned int ele_change_ = 0;
};

#endif