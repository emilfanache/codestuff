/*
 * NextGreat.cpp
 *
 *  Created on: Mar. 18, 2021
 *      Author: Emil Fanache
 */

#include <algorithm>
#include <iostream>
#include <string>

std::string findNextGreat(std::string inputNum) {
    // 1. Start from the end, find the digit lower than predecesor
    char lowerDigit;
    char rightLowerDigit;
    unsigned int i = 0;
    int swap_idx1;
    int swap_idx2;
    std::string number = inputNum;

    for (i = number.size() - 1; i > 0; --i) {
        if (number[i - 1] < number[i]) {
            lowerDigit = number[i - 1];
            swap_idx1 = i - 1;
            break;
        }
    }

    if (i == 0) {
        return number;
    }

    // 2 Find the smallest digit at the right of (i-1) greater > lowerDigit
    rightLowerDigit = number[swap_idx1 + 1];
    swap_idx2 = swap_idx1 + 1;
    for (i = swap_idx1; i < number.size(); i++) {
        if (number[i] < rightLowerDigit && number[i] > lowerDigit) {
            rightLowerDigit = number[i];
            swap_idx2 = i;
        }
    }

    // 3 swap lowerDigit found with the lower from the right
    std::swap(number[swap_idx1], number[swap_idx2]);

    // 4 sort the digits from the right
    std::sort(number.begin() + swap_idx1 + 1, number.end());

    return number;
}

int main() {
    std::string number;
    std::string next;

    std::cout << "=== Great Next Number Test 1 ===" << std::endl;
    number = "454652";
    std::cout << "Number is: " << number.c_str() << std::endl;
    next = findNextGreat(number);
    std::cout << "Next great number is: " << next.c_str() << std::endl
              << std::endl;

    std::cout << "=== Great Next Number Test 2 ===" << std::endl;
    number = "4765";
    std::cout << "Number is: " << number.c_str() << std::endl;
    next = findNextGreat(number);
    std::cout << "Next great number is: " << next.c_str() << std::endl
              << std::endl;

    std::cout << "=== Great Next Number Test 3 ===" << std::endl;
    number = "123456";
    std::cout << "Number is: " << number.c_str() << std::endl;
    next = findNextGreat(number);
    std::cout << "Next great number is: " << next.c_str() << std::endl
              << std::endl;

    std::cout << "=== Great Next Number Test 4 ===" << std::endl;
    number = "100";
    std::cout << "Number is: " << number.c_str() << std::endl;
    next = findNextGreat(number);
    std::cout << "Next great number is: " << next.c_str() << std::endl
              << std::endl;

    return 0;
}
