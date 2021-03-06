/*
 * BinarySearch.cpp
 *
 *  Created on: Jun 5, 2021
 *      Author: Emil Fanache
 */

#include <iostream>
#include <vector>
#include <random>

using namespace std;

int BinarySearchNonRecursive(vector<int> data, int needle)
{
    int low, middle, high;

    low = 0;
    high = data.size() - 1;

    while (low <= high)
    {
        middle = (high + low) / 2;
        if (data[middle] == needle)
        {
            return middle;
        }

        if (data[middle] < needle)
        {
            low = middle + 1;
        }
        else // (data[middle] > needle)
        {
            high = middle - 1;
        }
    }

    // didn't find anything
    return -1;
}

int BinarySearchRecursive(vector<int> data, int needle, int low, int high)
{
    int middle = (high + low) / 2;

    if (high < low)
    {
        return -1;
    }

    if (data[middle] == needle)
    {
        return middle;
    }

    if (data[middle] < needle)
    {
        return BinarySearchRecursive(data, needle, middle + 1, high);
    }
    else
    {
        return BinarySearchRecursive(data, needle, low, middle - 1);
    }

    return -1;
}

void PrintData(vector<int> data)
{
    if (data.empty())
    {
        return;
    }

    for (unsigned int i = 0; i < data.size(); i++)
    {
        if (i  == 0)
        {
            cout << "Start idx: 0" << endl;
        }

        cout << data[i] << " ";
        if ((i != 0) && (i % 20) == 0)
        {
            cout << endl;
            cout << "Start idx: " << i << endl;
        }
    }
    cout << endl;
}

unsigned int PickNeedle(unsigned int num, unsigned int ratio, unsigned int first)
{
    std::random_device rd;
    // Mersenne Twister random number generator
    std::mt19937 generator(rd());
    // I want to pick a random number in the range
    std::uniform_int_distribution<> distribution(0, num - 1);

    unsigned int randomIdx = distribution(generator);

    // compute the arithmetic progression value for that Idx
    return (first + (randomIdx - 1) * ratio);
}

int main()
{
    unsigned int num, ratio, first;
    vector<int> data;
    unsigned int i;
    unsigned int needle;

    cout << "Insert the total number of values: ";
    cin >> num;

    cout << "Insert the ratio: ";
    cin >> ratio;

    cout << "Insert the first number: ";
    cin >> first;

    data.push_back(first);
    // i = 1 <==> first number in the arithmetic progression
    // formula  a_n = a_1 + (n-1) * ratio;
    i = 2;
    while (i < num)
    {
        int a_i = data[0] + (i - 1) * ratio;
        data.push_back(a_i);
        i++;
    }

    // pick the number to search in the vector
    needle = PickNeedle(num, ratio, first);

    // print and test data and implementation
    PrintData(data);

    cout << "I picked needle: " << needle << endl;
    cout << "Index found with binary search non recursively is: ";
    cout << BinarySearchNonRecursive(data, needle) << endl;
    cout << "Index found with binary search recursively is: ";
    cout << BinarySearchRecursive(data, needle, 0, data.size() - 1);

    return 0;
}
