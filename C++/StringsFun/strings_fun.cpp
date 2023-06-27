/*
 * strings_fun.cpp
 *
 *  Created on: Feb. 16, 2021
 *      Author: Emil Fanache
 */

#include <algorithm>
#include <iostream>
#include <sstream>

#include <vector>

// left shift = abcde -> bcdea -> cdeab -> deabc -> eabcd > abcde
std::string ShiftStringLeft(std::string s, unsigned int leftShift) {
    std::string l_part;
    std::string r_part;
    unsigned int lShift;

    if (s.empty())
        return "";

    lShift = leftShift >= (s.length() - 1) ? leftShift % s.length() : leftShift;
    l_part = s.substr(0, lShift);
    r_part = s.substr(lShift, s.length());

    // std::cout << "left shift => " << l_part << " | " << r_part << " | "
    //           << (r_part + l_part) << std::endl;
    return (r_part + l_part);
}

// right shift = abcde -> eabcd -> deabc -> cdeab -> bcdea > abcde
std::string ShiftStringRight(std::string s, unsigned int rightShift) {
    std::string l_part;
    std::string r_part;
    unsigned int rShift;

    if (s.empty())
        return "";

    rShift =
        rightShift >= (s.length() - 1) ? rightShift % s.length() : rightShift;
    l_part = s.substr(0, s.length() - rShift);
    r_part = s.substr(s.length() - rShift, s.length());

    // std::cout << "right shift => " << l_part << " | " << r_part << " | "
    //           << (r_part + l_part) << std::endl;
    return (r_part + l_part);
}

std::string ShiftString(std::string s, unsigned int leftShift,
                        unsigned int rightShift) {
    if (s.empty())
        return "";

    if (leftShift == rightShift)
        return s;
    else if (leftShift < rightShift)
        return ShiftStringRight(s, rightShift - leftShift);
    else
        return ShiftStringLeft(s, leftShift - rightShift);
}

// This is to check if the result if ok when shifting the difference
std::string ShiftBothStrings(std::string s, unsigned int leftShift,
                             unsigned int rightShift) {
    std::string result;

    if (s.empty())
        return "";

    result = ShiftStringLeft(s, leftShift);

    result = ShiftStringRight(result, rightShift);
    return result;
}

static bool isDivisorOfString(std::string sub, std::string main) {
    std::string res = sub;
    int count = sub.length();

    while (res.length() < main.length()) {
        if (res != main.substr(0, count))
            return false;

        res += sub;
        count += sub.length();
    }

    return (res == main);
}

std::string GetGreatestCommonDivisor(std::string s1, std::string s2) {
    std::string divisor;
    std::string sub;

    for (unsigned int i = 0; i < s1.length() / 2; i++) {
        sub += s1[i];

        if (isDivisorOfString(sub, s1) && isDivisorOfString(sub, s2)) {
            divisor = sub;
        }
    }

    return divisor;
}

std::string ReverseWordsInPhrase(std::string inputText) {
    std::vector<std::string> reverse;
    std::istringstream ss(inputText);
    std::string token;
    std::string result;

    if (inputText.empty()) {
        return "empty";
    }

    while (std::getline(ss, token, ' ')) {
        reverse.push_back(token);
    }

    for (int i = reverse.size() - 1; i >= 0; i--) {
        result += reverse[i];
        if (i > 0)
            result += ' ';
    }
    return result;
}
