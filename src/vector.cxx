#include <concepts>
#include <iostream>
#include <memory>
#include <cassert>

#include "dsa/vector/vector.hpp"

template <Vector T> auto vector<T>::insert(T &&elem, size_t index) -> bool
{
  if (!insert_generic(index)) {
    return false;
  }

  data_[index] = std::move(elem);
  return true;
}

// TODO: rename this function
template <Vector T> auto vector<T>::insert_generic(size_t index) -> bool
{
  if (data_ == nullptr) {
    return false;
  }
  if (index >= size_) {
    return false;
  }
  if (size_ + 1 >= capacity_) {
    return false;
  }
  size_++;

  for (size_t k{ size_ }; k > index; k--) {
    data_[k] = data_[k - 1];
  }

  return true;
}

template <Vector T> auto vector<T>::insert(const T &elem, size_t index) -> bool
{
  if (!insert_generic(index)) {
    return false;
  }

  data_[index] = elem;
  return true;
}
