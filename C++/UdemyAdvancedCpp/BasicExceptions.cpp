/*
 * BasicExceptions.cpp
 *
 *  Created on: May 3, 2022
 *      Author: Emil Fanache
 */

#include <iostream>
#include <string>

const int kConstThrowValue = 123;

enum ErrorTypes { IntErr = 1, CharPtrErr, StringErr };

void ErrorSourceCallInteger() {
    throw kConstThrowValue;
}

void ErrorSourceCallCharPtr() {
    throw "this is a char pointer error";
}

void ErrorSourceCallString() {
    throw std::string("this is a string error");
}

int main() {

    void (*ErrSrcCallPtr)();
    int option = 0;

    std::cout << "Choose option:" << std::endl;
    std::cout << "1 - Integer Error" << std::endl;
    std::cout << "2 - Char Ptr. Error" << std::endl;
    std::cout << "3 - String Error" << std::endl;
    std::cout << "Your option: ";
    std::cin >> option;

    switch (static_cast<ErrorTypes>(option)) {
        case IntErr:
            ErrSrcCallPtr = &ErrorSourceCallInteger;
            break;
        case CharPtrErr:
            ErrSrcCallPtr = &ErrorSourceCallCharPtr;
            break;
        case StringErr:
            ErrSrcCallPtr = &ErrorSourceCallString;
            break;
        default:
            std::cout << "Wrong option. Exiting!" << std::endl;
            return -1;
    }

    try {
        ErrSrcCallPtr();
    } catch (int e) {
        std::cout << "Caught an integer error " << e << std::endl;
    } catch (const char* e) {
        std::cout << "Caught an error: " << e << std::endl;
    } catch (std::string& e) {
        std::cout << "Caught an error: " << e << std::endl;
    }

    std::cout << "Execution continued successfully" << std::endl;

    return 0;
}
