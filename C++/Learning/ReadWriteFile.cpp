/*
 * ReadWriteFile.cpp
 *
 *  Created on: Dec. 5, 2020
 *      Author: Emil Fanache
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

bool CharToRemove(unsigned char c) {
    return (c == ' ' || c == '.' || c == ',' || c == ';');
}

std::string RemoveTraillingChars(std::string text) {
    text.erase(std::remove_if(text.begin(), text.end(), CharToRemove),
               text.end());

    return text;
}

std::string BreakAndFormat(std::string inputText) {
    std::string formatedStr;
    std::istringstream ss(inputText);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        formatedStr += token + '#' + '\n';
    }

    return RemoveTraillingChars(formatedStr);
}

int main() {
    std::string inputText;
    std::ifstream inputFile("input_file.txt");
    std::ofstream outputFile("output_file.txt");
    int err = 0;

    if (inputFile.is_open()) {
        while (getline(inputFile, inputText)) {
            if (outputFile.is_open()) {
                std::string formated = BreakAndFormat(inputText);
                outputFile << formated;
            } else {
                perror("Unable to open file: ");
                err = 1;
            }
        }
    } else {
        perror("Unable to open file: ");
        err = 1;
    }

    if (!err) {
        std::cout << "File written successfully!" << std::endl;
    }
    inputFile.close();
    outputFile.close();

    return 0;
}
