#ifndef STRINGS_FUN_HPP_
#define STRINGS_FUN_HPP_

#include <string>

std::string ShiftStringLeft(std::string s, unsigned int leftShift);
std::string ShiftStringRight(std::string s, unsigned int rightShift);
std::string ShiftString(std::string s, unsigned int leftShift,
                        unsigned int rightShift);
std::string ShiftBothStrings(std::string s, unsigned int leftShift,
                             unsigned int rightShift);
std::string GetGreatestCommonDivisor(std::string s1, std::string s2);
std::string ReverseWordsInPhrase(std::string inputText);

#endif /* STRINGS_FUN_HPP_*/
