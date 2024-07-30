#include "cord_utilities.hpp"

#include <stdexcept>

SharedPointer<Cord> ConcatCords(SharedPointer<Cord> left_cord,
                                SharedPointer<Cord> right_cord) {
  if (left_cord.Get() == nullptr || right_cord.Get() == nullptr) {
    throw std::invalid_argument("one of the cords is null");
  }
  Cord* cord = new Cord();
  cord->left_ = left_cord;
  cord->right_ = right_cord;
  cord->length_ = left_cord->length_ + right_cord->length_;

  return *(new SharedPointer<Cord>(cord, kSharedPointerType::kObject));
}

SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord,
                              unsigned int lower_idx,
                              unsigned int upper_idx) {
  if (lower_idx >= upper_idx || upper_idx > curr_cord->Length() ||
      lower_idx < 0) {
    throw std::invalid_argument("not valid indexes or something");
  }
  if (lower_idx == 0 && upper_idx == curr_cord->Length()) {
    return curr_cord;
  }
  // auto* pointer = curr_cord.Get();
  if (!(curr_cord.Get()->IsNull())) {
    Cord* cord = new Cord(
        curr_cord.Get()->Data().substr(lower_idx, upper_idx - lower_idx));
    return {cord, kSharedPointerType::kObject};
  }
  if (upper_idx <= curr_cord->Left()->Length()) {
    return SubString(curr_cord->Left(), lower_idx, upper_idx);
  }
  if (lower_idx >= curr_cord->Left()->Length()) {
    return SubString(curr_cord->Right(),
                     lower_idx - curr_cord->Left()->Length(),
                     upper_idx - curr_cord->Left()->Length());
  }
  // if (lower_idx < curr_cord.Get()->Left()->Length() &&
  //     upper_idx <= curr_cord.Get()->Left()->Length()) {
  //   return SubString(curr_cord.Get()->Left(), lower_idx, upper_idx);
  // }
  // if (lower_idx >= curr_cord.Get()->Left()->Length()) {
  //   return SubString(curr_cord.Get()->Right(),
  //                    lower_idx - curr_cord.Get()->Left()->Length(),
  //                    upper_idx - curr_cord.Get()->Left()->Length());
  // }
  SharedPointer<Cord> left = SubString(
      curr_cord.Get()->Left(), lower_idx, curr_cord.Get()->Left()->Length());
  SharedPointer<Cord> right =
      SubString(curr_cord.Get()->Right(),
                0,
                upper_idx - curr_cord.Get()->Left()->Length());
  return ConcatCords(left, right);
}