#include <gtest/gtest.h>
#include <iostream>

#include "dsa/vector/vector.hpp"

TEST(vector, constructor)
{
  vector<int> v(10);
  vector<float> f{ 8.8f, 7.0f, 79.9f };
  std::cout << "f =\n";
  for (auto d : f)
    std::cout << "\td = '" << d << "'\n";
  const auto f2(std::move(f));
  std::cout << "f2 =\n";
  for (int i = 0; i < f2.size(); i++)
    std::cout << "\td = '" << f2[i] << "'\n";
  const auto f3(f2);
  std::cout << "f3 =\n";
  for (auto d : f3)
    std::cout << "\td = '" << d << "'\n";
  std::cout << "f (was moved)=\n";
  for (auto d : f)
    std::cout << "\td = '" << d << "'\n";
  // f3 = f;
}
