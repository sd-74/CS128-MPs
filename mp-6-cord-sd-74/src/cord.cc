#include "cord.hpp"

#include <stdexcept>

#include "cord_utilities.hpp"

bool Cord::IsNull() { return data_ == nullptr; }

Cord::Cord(std::string_view sv) {
  if (sv.empty()) {
    throw std::runtime_error("sv is empty");
  }
  data_ = new char[sv.size() + 1];
  for (size_t i = 0; i < sv.size(); i++) {
    data_[i] = sv.at(i);
  }
  data_[sv.size()] = '\0';
  length_ = sv.size();
}

Cord::~Cord() { delete[] data_; }

SharedPointer<char> Cord::ToString() const {
  char* to_string = new char[length_ + 1];
  int count = 0;
  this->Helper(to_string, count);
  to_string[length_] = '\0';
  return *(new SharedPointer<char>(to_string, kSharedPointerType::kArray));
}

void Cord::Helper(char* to_string, int& count) const {
  if (data_ != nullptr) {
    for (size_t i = 0; i < length_; i++) {
      to_string[count] = data_[i];
      count++;
    }
    return;
  }
  left_.Get()->Helper(to_string, count);
  right_.Get()->Helper(to_string, count);
}