// Use (void) to silence unused warnings.

namespace dsa::vector {

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
  // std::unique_ptr<T[]> data_{};
  size_t capacity_{};
  size_t size_{};

  auto insert_generic(size_t index) -> bool;
  void delete_data()
  {
    if (data_ != nullptr) {
      delete[] data_;
      data_ = nullptr;
    }
    capacity_ = 0;
    size_ = 0;
  }

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

    assertm(capacity_ >= size_, "size is greater than capacity");
    delete_data();
    capacity_ = other.capacity_;
    size_ = other.size_;
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

  auto insert(T &&elem, size_t index) -> bool;
  auto insert(const T &elem, size_t index) -> bool;

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
};

}  // namespace dsa::vector
