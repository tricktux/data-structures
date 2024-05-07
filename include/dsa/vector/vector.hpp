#include <cassert>
#include <concepts>
#include <iostream>
#include <memory>

namespace dsa::vector {

// Use (void) to silence unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))

template <typename T>
concept Vector = requires(T a, T b) {  // clang-format off
{ a < b } -> std::convertible_to<bool>;
{ a > b } -> std::convertible_to<bool>;
{ a >= b } -> std::convertible_to<bool>;
{ a <= b } -> std::convertible_to<bool>;
{ a = b } -> std::same_as<T &>;
};  // clang-format on

template <Vector T> class vector {
  T *data_{};
  size_t capacity_{};
  size_t size_{};

  void delete_data()
  {
    if (data_ != nullptr) {
      delete[] data_;
      data_ = nullptr;
    }
    capacity_ = 0;
    size_ = 0;
  }

  void shift_right_(size_t index)
  {
    for (size_t k{ size_ }; k > index; k--)
      data_[k] = data_[k - 1];
  }

  void shift_left_(size_t index)
  {
    for (size_t k{ index }; k < size_; k++)
      data_[k] = data_[k + 1];
  }

  auto validate_index(size_t index) -> bool
  {
    if (data_ == nullptr)
      return false;

    if (index >= size_)
      return false;

    return true;
  }

  auto increase_size_by_one() -> bool
  {
    if (size_ + 1 > capacity_)
      return false;

    size_++;
    return true;
  }

  auto insert_generic(size_t index) -> bool
  {
    if (!validate_index(index))
      return false;

    if (!increase_size_by_one())
      return false;

    shift_right_(index);
    return true;
  }

 public:
  vector() = default;
  explicit vector(int capacity)
  {
    if (capacity <= 0)
      return;
    capacity_ = capacity;
    data_ = new T[capacity_];
  }
  explicit vector(std::initializer_list<T> init_list) : size_(init_list.size())
  {
    capacity_ = size_;
    data_ = new T[capacity_];
    std::copy(init_list.begin(), init_list.end(), data_);
  }
  ~vector()
  {
    delete_data();
  };

  vector(vector<T> &&other) noexcept
      : data_(other.data_), capacity_(other.capacity_), size_(other.size_)
  {
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
  }
  vector(const vector<T> &other) : capacity_(other.capacity_), size_(other.size_)
  {
    assertm(capacity_ >= size_, "size is greater than capacity");
    if (capacity_ > 0)
      data_ = new T[capacity_];
    if (size_ > 0)
      std::copy(other.begin(), other.end(), data_);
  }

  auto operator=(const vector<T> &other) -> vector<T> &
  {
    if (this == &other)
      return *this;

    delete_data();
    capacity_ = other.capacity_;
    size_ = other.size_;
    assertm(capacity_ >= size_, "size is greater than capacity");
    if (capacity_ > 0)
      data_ = new T[capacity_];

    if (size_ > 0)
      std::copy(other.begin(), other.end(), data_);
    return *this;
  }

  auto operator=(vector<T> &&other) -> vector<T> &
  {
    if (this == &other)
      return *this;

    delete_data();
    capacity_ = other.capacity_;
    size_ = other.size_;
    assertm(capacity_ >= size_, "size is greater than capacity");
    data_ = other.data_;

    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
    return *this;
  }

  auto operator[](int idx) const -> T
  {
    return data_[idx];
  }

  [[nodiscard]] auto empty() const -> bool
  {
    return size_ == 0;
  }

  [[nodiscard]] auto begin() const -> T *
  {
    return &data_[0];
  }
  [[nodiscard]] auto cbegin() const -> const T *
  {
    return &data_[0];
  }
  [[nodiscard]] auto end() const -> T *
  {
    return &data_[size_];
  }
  [[nodiscard]] auto cend() const -> const T *
  {
    return &data_[size_];
  }

  [[nodiscard]] auto size() const -> size_t
  {
    return size_;
  }

  auto insert(T &&elem, size_t index) -> bool
  {
    if (!insert_generic(index))
      return false;

    data_[index] = std::move(elem);
    return true;
  }

  auto insert(const T &elem, size_t index) -> bool
  {
    if (!insert_generic(index))
      return false;

    data_[index] = elem;
    return true;
  }
};

}  // namespace dsa::vector
