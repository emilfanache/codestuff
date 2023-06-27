#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "strings_fun.hpp"

TEST(StringsFunTest, TestLeftShifting) {
    std::string test_string = "AbCdEfG";
    std::string result = ShiftStringLeft(test_string, 4);

    EXPECT_STREQ("EfGAbCd", result.c_str());
}

TEST(StringsFunTest, TestLeftShiftEmptyString) {
    std::string test_string = "";
    std::string result = ShiftStringLeft(test_string, 4);

    EXPECT_STREQ("", result.c_str());
}

TEST(StringsFunTest, TestRightShifting) {
    std::string test_string = "AbCdEfG";
    std::string result = ShiftStringRight(test_string, 4);

    EXPECT_STREQ("dEfGAbC", result.c_str());
}

TEST(StringsFunTest, TestRightShiftEmptyString) {
    std::string test_string = "";
    std::string result = ShiftStringRight(test_string, 4);

    EXPECT_STREQ("", result.c_str());
}

TEST(StringsFunTest, TestShiftBothStrings) {
    std::string test_string = "AbCdEfGiJkLmN";
    std::string result = ShiftBothStrings(test_string, 8, 2);

    EXPECT_STREQ("GiJkLmNAbCdEf", result.c_str());
}

TEST(StringsFunTest, TestStringIsCommonDivisor) {
    std::string test_string = "abcabcabcabc";
    std::string result = GetGreatestCommonDivisor(test_string, "abcabc");

    EXPECT_STREQ("abcabc", result.c_str());
}

TEST(StringsFunTest, TestStringNoCommonDivisor) {
    std::string test_string = "abcabcabcabc";
    std::string result = GetGreatestCommonDivisor(test_string, "abcdef");

    EXPECT_STREQ("", result.c_str());
}

TEST(StringsFunTest, TestReverseWordsInPhrase) {
    std::string test_string = "This is a test!";
    std::string result = ReverseWordsInPhrase(test_string);

    EXPECT_STREQ("test! a is This", result.c_str());
}
