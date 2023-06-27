#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "binary_search.hpp"

TEST(BinarySearchTest, TestNonRecursiveSearch) {
    std::vector<int> data = {2, 4, 6, 8, 10, 12};
    int needle = 4;

    int index = BinarySearchNonRecursive(data, needle);

    ASSERT_NE(-1, index);
    EXPECT_EQ(1, index);
}

TEST(BinarySearchTest, TestRecursiveSearch) {
    std::vector<int> data = {2, 4, 6, 8, 10, 12};
    int needle = 10;

    int index = BinarySearchRecursive(data, needle);

    ASSERT_NE(-1, index);
    EXPECT_EQ(4, index);
}
