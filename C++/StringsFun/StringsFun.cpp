/*
 * StringsFun.cpp
 *
 *  Created on: Feb. 16, 2021
 *      Author: Emil Fanache
 */


#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

// left shift = abcde -> bcdea -> cdeab -> deabc -> eabcd > abcde
string shiftStringLeft(string s, unsigned int leftShift)
{
    string l_part;
    string r_part;
    unsigned int lShift;

    if (s.empty())
        return "";

    lShift = leftShift >= (s.length() - 1) ? leftShift % s.length() : leftShift;
    l_part = s.substr(0, lShift);
    r_part = s.substr(lShift, s.length());

    cout << "left shift => " << l_part << " | " << r_part << " | " << (r_part + l_part) << endl;
    return (r_part + l_part);
}

// right shift = abcde -> eabcd -> deabc -> cdeab -> bcdea > abcde
string shiftStringRight(string s, unsigned int rightShift)
{
    string l_part;
    string r_part;
    unsigned int rShift;

    if (s.empty())
        return "";

    rShift = rightShift >= (s.length() - 1) ? rightShift % s.length() : rightShift;
    l_part = s.substr(0, s.length() - rShift);
    r_part = s.substr(s.length() - rShift, s.length());

    cout << "right shift => " << l_part << " | " << r_part << " | " << (r_part + l_part) << endl;
    return (r_part + l_part);
}


string shiftString(string s, unsigned int leftShift, unsigned int rightShift)
{
    if (s.empty())
        return "";

    if (leftShift == rightShift)
        return s;
    else if (leftShift < rightShift)
        return shiftStringRight(s, rightShift - leftShift);
    else
        return shiftStringLeft(s, leftShift-rightShift);
}

// This is to check if the result if ok when shifting the difference
string shiftBothStrings(string s, unsigned int leftShift, unsigned int rightShift)
{
    string result;

    if (s.empty())
        return "";

    result = shiftStringLeft(s, leftShift);

    result = shiftStringRight(result, rightShift);
    return result;
}


bool isDivisorOfString(string sub, string main)
{
    string res = sub;
    int count = sub.length();

    while (res.length() < main.length())
    {
        if (res != main.substr(0, count))
            return false;

        res += sub;
        count += sub.length();
    }

    return (res == main);
}

string GetGreatestCommonDivisor(string s1, string s2)
{
    string divisor;
    string sub;

    for (unsigned int i = 0; i < s1.length() / 2; i++)
    {
        sub += s1[i];

        if (isDivisorOfString(sub, s1) &&
            isDivisorOfString(sub, s2))
        {
            divisor = sub;
        }
    }

    return divisor;
}

std::string ReverseString(std::string inputText)
{
    std::vector<std::string> reverse;
    std::istringstream ss(inputText);
    std::string token;
    std::string result;

    if (inputText.empty())
    {
        return "empty";
    }

    while(std::getline(ss, token, ' ')) {
        reverse.push_back(token);
    }

    for (int i = reverse.size() - 1; i >= 0; i--)
    {
        result += reverse[i];
        if (i > 0)
            result += ' ';
    }
    return result;
}

int main()
{
    string s;
    string result;
    string check;

    cout << "=== Shift Test 1 ===" << endl;
    s = "abcde";
    result = shiftString(s, 4, 2);
    cout << "result=" << result << endl << endl;
    check = shiftBothStrings(s, 4, 2);
    cout << "Double check result: " << check << endl << endl;

    cout << "=== Shift Test 2 ===" << endl;
    s = "abcde";
    shiftString(s, 20, 26);
    cout << "result=" << result << endl << endl;
    check = shiftBothStrings(s, 20, 26);
    cout << "Double check result: " << check << endl << endl;

    cout << "=== Divisors test 1 ===" << endl;
    string s1 = "abcabc";
    string s2 = "abcabcabcabcabc";
    string divisor = GetGreatestCommonDivisor(s1, s2);
    if (divisor.empty())
        cout << "There is no divisor" << endl << endl;
    else
        cout << "The divisor is \"" <<  divisor.c_str() << "\" with size " << divisor.length() << endl << endl;

    cout << "=== Divisors test 2 ===" << endl;
    s1 = "1111";
    s2 = "11111";
    divisor = GetGreatestCommonDivisor(s1, s2);
    if (divisor.empty())
        cout << "There is no divisor" << endl << endl;
    else
        cout << "The divisor is \"" <<  divisor.c_str() << "\" with size " << divisor.length() << endl << endl;

    cout << "=== Divisors test 3 ===" << endl;
    s1 = "abnfdaa";
    s2 = "abhkhkh";
    divisor = GetGreatestCommonDivisor(s1, s2);
    if (divisor.empty())
        cout << "There is no divisor" << endl << endl;
    else
        cout << "The divisor is \"" <<  divisor.c_str() << "\" with size " << divisor.length() << endl << endl;


    cout << "=== Reverse words in a phrase Test 1 ===" << endl;
    std::string inputString("lorem ipsum dolor sit amet");
    std::cout << "Initial string: "  << inputString << std::endl;
    std::string outputString = ReverseString(inputString);
    std::cout << "After reverse: "  << outputString << std::endl;

    return 0;
}
