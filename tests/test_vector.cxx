#include <gtest/gtest.h>
#include <iostream>

#include "dsa/vector/vector.hpp"

TEST(vector, constructor)
{
  // Constructor with capacity
  vector<int> v(10);
  // Constructor with initializer list
  vector<float> f{ 8.8f, 7.0f, 79.9f };

  // Iterators
  std::cout << "f =\n";
  for (auto d : f)
    std::cout << "\td = '" << d << "'\n";

  // Move constructor
  const auto f2(std::move(f));
  std::cout << "f2 =\n";
  for (int i = 0; i < f2.size(); i++)
    std::cout << "\td = '" << f2[i] << "'\n";

  // Copy constructor
  auto f3(f2);
  std::cout << "f3 =\n";
  for (auto d : f3)
    std::cout << "\td = '" << d << "'\n";
  std::cout << "f (was moved)=\n";
  for (auto d : f)
    std::cout << "\td = '" << d << "'\n";

  // Copy assignment
  vector<float> f4{ 1.0f, 2.0f, 3.0f };
  std::cout << "f4 originally =\n";
  for (auto d : f4)
    std::cout << "\td = '" << d << "'\n";
  f4 = f3;
  std::cout << "f4 after the copy =\n";
  for (auto d : f4)
    std::cout << "\td = '" << d << "'\n";
  std::cout << "f3\n";
  for (auto d : f3)
    std::cout << "\td = '" << d << "'\n";
}
