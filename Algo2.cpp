// CPSC 335 - Project 3
// Author: Joshua Zamora
// Email: JoshuaMZamora@csu.fullerton.edu
// Algorithm 2: Run Encoding Problem

#include <iostream>
#include <string>

// Run-Length Encoding:
// - Single character run: just the character
// - Run of k > 1: the number k followed by that character
std::string runLengthEncode(const std::string &s) {
    if (s.empty()) {
        return "";
    }

    std::string encoded;
    encoded.reserve(s.size());  // small optimization

    char current = s[0];
    int count = 1;

    for (std::size_t i = 1; i < s.size(); ++i) {
        if (s[i] == current) {
            // same run
            ++count;
        } else {
            // flush current run
            if (count == 1) {
                encoded.push_back(current);
            } else {
                // append count as digits, then char
                encoded += std::to_string(count);
                encoded.push_back(current);
            }

            // start new run
            current = s[i];
            count = 1;
        }
    }

    // flush last run
    if (count == 1) {
        encoded.push_back(current);
    } else {
        encoded += std::to_string(count);
        encoded.push_back(current);
    }

    return encoded;
}

int main() {
    std::string input;

    std::cout << "Enter the string to encode: ";
    std::getline(std::cin, input);

    std::string encoded = runLengthEncode(input);

    std::cout << "Encoded string: " << encoded << std::endl;

    return 0;
}
