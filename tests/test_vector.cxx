#include <gtest/gtest.h>
#include <iostream>

#include "dsa/vector/vector.hpp"

using namespace dsa::vector;

class vector_test : public ::testing::Test {
 protected:
  // Initializing Vector object for each test.
  void SetUp() override
  {
    vec = vector<int>();
    v = vector<int>(10);
  }
  // Tears down the test ... not used here.
  void TearDown() override
  {
  }

  vector<int> vec;
  vector<int> v;
  vector<float> f{ 8.8f, 7.0f, 79.9f };
  vector<float> f4{ 1.0f, 2.0f, 3.0f };
};

TEST_F(vector_test, constructor)
{
  EXPECT_EQ(f.size(), 3);
  EXPECT_EQ(f[0], 8.8f);
  EXPECT_EQ(f[1], 7.0f);
  EXPECT_EQ(f[2], 79.9f);
  vector<double> d{};
  EXPECT_TRUE(d.empty());
}

TEST_F(vector_test, iterators)
{
  float arr[] = { 8.8f, 7.0f, 79.9f };
  int i = 0;
  for (auto d : f)
    EXPECT_EQ(d, arr[i++]);
}

TEST_F(vector_test, move_ctor)
{
  // Move constructor
  const auto f2(std::move(f));
  EXPECT_TRUE(f.empty());  // f should be empty after being moved
  EXPECT_EQ(f2.size(), 3);
  EXPECT_EQ(f2[0], 8.8f);
  EXPECT_EQ(f2[1], 7.0f);
  EXPECT_EQ(f2[2], 79.9f);
}

TEST_F(vector_test, copy_ctor)
{
  // Copy constructor
  auto f3(f);
  EXPECT_EQ(f.size(), 3);  // f should remain unchanged after being copied
  EXPECT_EQ(f3.size(), 3);
  EXPECT_EQ(f3[0], 8.8f);
  EXPECT_EQ(f3[1], 7.0f);
  EXPECT_EQ(f3[2], 79.9f);
}

TEST_F(vector_test, copy_assignment)
{
  f4 = f;
  EXPECT_EQ(f.size(), 3);  // f should remain unchanged after being copied
  EXPECT_EQ(f4.size(), 3);
  EXPECT_EQ(f4[0], 8.8f);
  EXPECT_EQ(f4[1], 7.0f);
  EXPECT_EQ(f4[2], 79.9f);
}

TEST_F(vector_test, move_assignment)
{
  f4 = std::move(f);
  EXPECT_TRUE(f.empty());  // f should be empty after being moved
  EXPECT_EQ(f4.size(), 3);
  EXPECT_EQ(f4[0], 8.8f);
  EXPECT_EQ(f4[1], 7.0f);
  EXPECT_EQ(f4[2], 79.9f);
}

TEST_F(vector_test, insert_r_value_element_successful)
{
  // Test the rvalue insert function
  EXPECT_TRUE(vec.insert(5, 0)) << "Failed to insert rvalue at index 0.";
  // If all above tests passed, we assume the insertion is successful.
  // Now, let's check if the value has been actually inserted.
  EXPECT_EQ(vec[0], 5) << "Inserted rvalue does not match the retrieved value.";
}

TEST_F(vector_test, insert_r_value_element_past_size_should_fail)
{
  // Inserting at an index past the size of the vector should fail.
  EXPECT_FALSE(vec.insert(5, 1)) << "Able to insert rvalue at a wrong index.";
}

TEST_F(vector_test, insert_l_value_element_successful)
{
  // Test the lvalue insert function
  int a = 101;
  EXPECT_TRUE(vec.insert(a, 0)) << "Failed to insert lvalue at index 0.";
  // If all above tests passed, we assume the insertion is successful.
  // Now, let's check if the value has been actually inserted.
  EXPECT_EQ(vec[0], 101) << "Inserted lvalue does not match the retrieved value.";
}

TEST_F(vector_test, insert_l_value_element_past_size_should_fail)
{
  // Inserting at an index past the size of the vector should fail.
  int a = 101;
  EXPECT_FALSE(vec.insert(a, 1)) << "Able to insert lvalue at a wrong index.";
}
