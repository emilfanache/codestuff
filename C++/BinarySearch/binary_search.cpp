/*
 * binary_search.cpp
 *
 *  Created on: Jun 5, 2021
 *      Author: Emil Fanache
 */

#include <iostream>
#include <random>

#include "binary_search.hpp"

int BinarySearchNonRecursive(std::vector<int> data, int needle) {
    int low, middle, high;

    low = 0;
    high = data.size() - 1;

    while (low <= high) {
        middle = (high + low) / 2;
        if (data[middle] == needle) {
            return middle;
        }

        if (data[middle] < needle) {
            low = middle + 1;
        } else {
            // (data[middle] > needle)
            high = middle - 1;
        }
    }

    // didn't find anything
    return -1;
}

static int BinarySearchRecursive(std::vector<int> data, int needle, int low,
                                 int high) {
    int middle = (high + low) / 2;

    if (high < low) {
        return -1;
    }

    if (data[middle] == needle) {
        return middle;
    }

    if (data[middle] < needle) {
        return BinarySearchRecursive(data, needle, middle + 1, high);
    } else {
        return BinarySearchRecursive(data, needle, low, middle - 1);
    }

    return -1;
}

int BinarySearchRecursive(std::vector<int> data, int needle) {
    return BinarySearchRecursive(data, needle, 0, data.size() - 1);
}

static void PrintData(std::vector<int> data) {
    if (data.empty()) {
        return;
    }

    for (unsigned int i = 0; i < data.size(); i++) {
        if (i == 0) {
            std::cout << "Start idx: 0" << std::endl;
        }

        std::cout << data[i] << " ";
        if ((i != 0) && (i % 20) == 0) {
            std::cout << std::endl;
            std::cout << "Start idx: " << i << std::endl;
        }
    }
    std::cout << std::endl;
}

static unsigned int PickNeedle(unsigned int num, unsigned int ratio,
                               unsigned int first) {
    std::random_device rd;
    // Mersenne Twister random number generator
    std::mt19937 generator(rd());
    // I want to pick a random number in the range
    std::uniform_int_distribution<> distribution(0, num - 1);

    unsigned int randomIdx = distribution(generator);

    // compute the arithmetic progression value for that Idx
    return (first + (randomIdx - 1) * ratio);
}

void TestBinarySearch() {
    unsigned int num, ratio, first;
    std::vector<int> data;
    unsigned int i;
    unsigned int needle;

    std::cout << "Insert the total number of values: ";
    std::cin >> num;

    std::cout << "Insert the ratio: ";
    std::cin >> ratio;

    std::cout << "Insert the first number: ";
    std::cin >> first;

    data.push_back(first);
    // i = 1 <==> first number in the arithmetic progression
    // formula  a_n = a_1 + (n-1) * ratio;
    i = 2;
    while (i < num) {
        int a_i = data[0] + (i - 1) * ratio;
        data.push_back(a_i);
        i++;
    }

    // pick the number to search in the vector
    needle = PickNeedle(num, ratio, first);

    // print and test data and implementation
    PrintData(data);

    std::cout << "I picked needle: " << needle << std::endl;
    std::cout << "Index found with binary search non recursively is: ";
    std::cout << BinarySearchNonRecursive(data, needle) << std::endl;
    std::cout << "Index found with binary search recursively is: ";
    std::cout << BinarySearchRecursive(data, needle) << std::endl;
}
