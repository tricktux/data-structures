#include <concepts>
#include <iostream>
#include <memory>

template <typename T>
concept Vector = requires(T a, T b)
{  // clang-format off
  { a < b } -> std::convertible_to<bool>;
  { a > b } -> std::convertible_to<bool>;
  { a >= b } -> std::convertible_to<bool>;
  { a <= b } -> std::convertible_to<bool>;
  { a = b } -> std::same_as<T &>;
};  // clang-format on

template <Vector T> class vector {
  T *data_{};
  // std::unique_ptr<T[]> data_{};
  size_t capacity_{};
  size_t size_{};

  auto insert_generic(size_t index) -> bool;

 public:
  vector() = default;
  explicit vector(int capacity)
  {
    if (capacity <= 0) {
      return;
    }
    capacity_ = capacity;
    // data_ = std::make_unique<T[]>(capacity_);
    data_ = new T[capacity_];
    std::cout << "allocated '" << capacity << "' elements from capacity\n";
  }
  vector(std::initializer_list<T> init_list) : size_(init_list.size())
  {
    capacity_ = size_;
    data_ = new T[capacity_];
    std::copy(init_list.begin(), init_list.end(), data_);
    std::cout << "allocated '" << size_ << "' bytes from initializer_list\n";
  }
  ~vector()
  {
    if (data_ != nullptr) {
      delete[] data_;
    }
  };

  // TODO: realloc
  vector(vector<T> &&other) noexcept
      : data_(other.data_), capacity_(other.capacity_), size_(other.size_)
  {
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = 0;
  }
  vector(const vector<T> &other)
  {
    std::cout << "copy ctor!!!\n";
    if (other.capacity_ > 0) {
      capacity_ = other.capacity_;
      data_ = new T[capacity_];
    }
    if (other.size_ > 0) {
      std::copy(other.begin(), other.end(), data_);
      size_ = other.size_;
    }
  }

  // TODO
  auto operator=(const vector<T> &other) -> vector<T> & = delete;
  auto operator=(vector<T> &&other) -> vector<T> & = delete;
  auto operator[](int idx) const -> T
  {
    return data_[idx];
  }

  auto insert(T &&elem, size_t index) -> bool;
  auto insert(const T &elem, size_t index) -> bool;

  auto begin() const -> T *
  {
    return &data_[0];
  }
  auto cbegin() const -> const T *
  {
    return &data_[0];
  }
  auto end() const -> T *
  {
    return &data_[size_];
  }
  auto cend() const -> const T *
  {
    return &data_[size_];
  }

  [[nodiscard]] auto size() const -> size_t
  {
    return size_;
  }
};
