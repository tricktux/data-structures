#include <concepts>
#include <memory>
#include <iostream>

template <typename T>
concept Vector = requires(T a, T b) {
  { a < b } -> std::convertible_to<bool>;
  { a > b } -> std::convertible_to<bool>;
  { a >= b } -> std::convertible_to<bool>;
  { a <= b } -> std::convertible_to<bool>;
  { a = b } -> std::same_as<T &>;
};

template <Vector T> class vector {
  T *data_{};
  size_t capacity_{};
  size_t size_{};

  bool insert_generic(size_t index);

public:
  vector() = default;
  explicit vector(int capacity) {
    if (capacity <= 0) return;
    capacity_ = capacity;
    data_ = new T[capacity_];
    std::cout << "allocated '" << capacity << "' elements from capacity\n";
  }
  vector(std::initializer_list<T> init_list) {
    size_ = init_list.size();
    capacity_ = size_;
    data_ = new T[capacity_];
    std::copy(init_list.begin(), init_list.end(), data_);
    std::cout << "allocated '" << size_ << "' bytes from initializer_list\n";
  }
  ~vector() {
    if (data_)
    {
      delete[] data_;
      std::cout << "freeing memory\n";
    }
  }

  // TODO: realloc
  // TODO: Figure out why they are not being called
  vector(const T &&other) {
    std::cout << "move ctor!!!\n";
  }
  vector(const T &other) {
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
  T &operator=(const T &other) = delete;
  T &&operator=(const T &&other) = delete;
  T operator[](int idx) const { return data_[idx]; }

  bool insert(T &&el, size_t index);
  bool insert(const T &el, size_t index);

  T* begin() const { return &data_[0]; }
  const T* cbegin() const { return &data_[0]; }
  T* end() const { return &data_[size_]; }
  const T* cend() const { return &data_[size_]; }

  size_t size() const { return size_; }
};
