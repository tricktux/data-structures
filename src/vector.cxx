#include "vector.hpp"

template <Vector T> bool vector<T>::insert(T &&el, size_t index) {
  if (!insert_generic(index))
    return false;

  data_[index] = std::move(el);
  return true;
}

template <Vector T> bool vector<T>::insert_generic(size_t index) {
  if (data_ == nullptr)
    return false;
  if (index >= size_)
    return false;
  if (size_ + 1 >= capacity_)
    return false;
  size_++;

  for (size_t k{size_}; k > index; k--)
    data_[k] = data_[k - 1];

  return true;
}

template <Vector T> bool vector<T>::insert(const T &el, size_t index) {
  if (!insert_generic(index))
    return false;

  data_[index] = el;
  return true;
}
