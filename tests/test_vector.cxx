#include "dsa/vector/vector.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(mytest, this_test) {
  vector<float> v(10);
  vector<float> f{8.8f, 7.0f, 79.9f};
  std::cout << "f =\n";
  for (auto d : f)
    std::cout << "\td = '" << d << "'\n";
  const auto f2(std::move(f));
  std::cout << "f2 =\n";
  for (auto d : f2)
    std::cout << "\td = '" << d << "'\n";
  for (int i = 0; i < f2.size(); i++)
    std::cout << "\td = '" << f2[i] << "'\n";
}
