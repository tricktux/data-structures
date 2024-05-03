#include <gtest/gtest.h>
#include <iostream>

#include "dsa/vector/vector.hpp"

using namespace dsa::vector;

TEST(vector, constructor)
{
  // Constructor with capacity
  vector<int> v(10);
  // Constructor with initializer list
  vector<float> f{ 8.8f, 7.0f, 79.9f };
  EXPECT_EQ(f.size(), 3);
  EXPECT_EQ(f[0], 8.8f);
  EXPECT_EQ(f[1], 7.0f);
  EXPECT_EQ(f[2], 79.9f);
  vector<double> d{};
  EXPECT_TRUE(d.empty());
}

TEST(vector, iterators)
{
  vector<float> f{ 8.8f, 7.0f, 79.9f };
  float arr[] = { 8.8f, 7.0f, 79.9f };
  int i = 0;
  for (auto d : f)
    EXPECT_EQ(d, arr[i++]);
}

TEST(vector, move_ctor)
{
  vector<float> f{ 8.8f, 7.0f, 79.9f };
  // Move constructor
  const auto f2(std::move(f));
  EXPECT_TRUE(f.empty());  // f should be empty after being moved
  EXPECT_EQ(f2.size(), 3);
  EXPECT_EQ(f2[0], 8.8f);
  EXPECT_EQ(f2[1], 7.0f);
  EXPECT_EQ(f2[2], 79.9f);
}

TEST(vector, copy_ctor)
{
  vector<float> f{ 8.8f, 7.0f, 79.9f };
  // Copy constructor
  auto f3(f);
  EXPECT_EQ(f.size(), 3);  // f should remain unchanged after being copied
  EXPECT_EQ(f3.size(), 3);
  EXPECT_EQ(f3[0], 8.8f);
  EXPECT_EQ(f3[1], 7.0f);
  EXPECT_EQ(f3[2], 79.9f);
}

TEST(vector, copy_assignment)
{
  vector<float> f{ 8.8f, 7.0f, 79.9f };
  vector<float> f4{ 1.0f, 2.0f, 3.0f };
  f4 = f;
  EXPECT_EQ(f.size(), 3);  // f should remain unchanged after being copied
  EXPECT_EQ(f4.size(), 3);
  EXPECT_EQ(f4[0], 8.8f);
  EXPECT_EQ(f4[1], 7.0f);
  EXPECT_EQ(f4[2], 79.9f);
}

TEST(vector, move_assignment)
{
  vector<float> f{ 8.8f, 7.0f, 79.9f };
  vector<float> f4{ 1.0f, 2.0f, 3.0f };
  f4 = std::move(f);
  EXPECT_TRUE(f.empty());  // f should be empty after being moved
  EXPECT_EQ(f4.size(), 3);
  EXPECT_EQ(f4[0], 8.8f);
  EXPECT_EQ(f4[1], 7.0f);
  EXPECT_EQ(f4[2], 79.9f);
}
