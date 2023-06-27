#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "next_great.hpp"

using testing::ElementsAre;

TEST(NextGreatTest, TestNextGreatNumber) {
    std::vector<std::string> input_values{"454652", "4765", "123456", "100"};
    std::vector<std::string> expected_values;

    for (const auto& iv : input_values) {
        expected_values.push_back(FindNextGreat(iv));
    }

    EXPECT_THAT(expected_values,
                ElementsAre("455246", "5467", "123465", "100"));
}
