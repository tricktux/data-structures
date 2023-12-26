#include <concepts>
#include <memory>

template <typename T>
concept Vector = requires(T a, T b) {
  { a < b } -> std::convertible_to<bool>;
  { a > b } -> std::convertible_to<bool>;
  { a >= b } -> std::convertible_to<bool>;
  { a <= b } -> std::convertible_to<bool>;
  { a = b } -> std::same_as<T&>;
};

template <Vector T>
class vector {
  T *data_{};
  size_t capacity_{};
  size_t size_{};
  size_t data_size_{};

  bool insert_generic(size_t index);

public:
  vector() { data_size_ = sizeof(T); }
  vector(size_t capacity) : capacity_(capacity) {
    data_size_ = sizeof(T);
    data_ = (T *)malloc(capacity_ * data_size_);
  }
  ~vector() {
    if (data_)
      free(data_);
  }

  bool insert(T&& el, size_t index);
  bool insert(const T& el, size_t index);

  // Not copiable
  vector(const T &other) = delete;
  T &operator=(const T &other) = delete;
  T &&operator=(const T &&other) = delete;
};
