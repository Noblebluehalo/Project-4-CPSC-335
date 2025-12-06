// CPSC 335 - Project 3
// Author: Joshua Zamora
// Email: JoshuaMZamora@csu.fullerton.edu
// Algorithm 1: Target Terms or Substrings

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

// Convert a string to lowercase
std::string toLower(const std::string& s) {
    std::string t;
    t.reserve(s.size());
    for (char c : s) {
        t.push_back(std::tolower(static_cast<unsigned char>(c)));
    }
    return t;
}

// Manual substring search
int findSubstring(const std::string& S, const std::string& W) {
    int n = S.size();
    int m = W.size();
    if (m > n) return -1;

    for (int i = 0; i <= n - m; ++i) {
        bool match = true;
        for (int j = 0; j < m; ++j) {
            if (S[i + j] != W[j]) {
                match = false;
                break;
            }
        }
        if (match) return i;
    }
    return -1;
}

struct FoundWord {
    int index;
    std::string word;
};

// Manual selection sort
void selectionSort(std::vector<FoundWord>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].index < arr[minPos].index) {
                minPos = j;
            }
        }
        if (minPos != i) {
            FoundWord temp = arr[i];
            arr[i] = arr[minPos];
            arr[minPos] = temp;
        }
    }
}

int main() {
    std::string A;
    int n;

    // Ask for A
    std::cout << "Enter the concatenated string A: ";
    std::getline(std::cin, A);

    // Ask for n
    std::cout << "Enter number of words to search for: ";
    std::cin >> n;
    std::cin.ignore(1000, '\n'); // clear newline

    // Ask for B on one line
    std::cout << "Enter the words on one line: ";
    std::string line;
    std::getline(std::cin, line);

    // Split the line into words
    std::vector<std::string> B;
    std::stringstream ss(line);
    std::string word;
    while (ss >> word) {
        B.push_back(word);
    }

    // Ensure we read exactly n words
    if (B.size() != static_cast<size_t>(n)) {
        std::cout << "\nERROR: You said " << n << " words but typed "
            << B.size() << ".\n";
        return 1;
    }

    // Lowercase A
    std::string lowerA = toLower(A);

    // Find all matches
    std::vector<FoundWord> found;
    for (const std::string& w : B) {
        int pos = findSubstring(lowerA, toLower(w));
        if (pos != -1) {
            found.push_back({ pos, w });
        }
    }

    // Sort by index
    selectionSort(found);

    // Output
    std::cout << "\nOutput_order = [";
    for (size_t i = 0; i < found.size(); ++i) {
        std::cout << found[i].index;
        if (i + 1 < found.size()) std::cout << ", ";
    }
    std::cout << "]\n";

    std::cout << "Output_array = [";
    for (size_t i = 0; i < found.size(); ++i) {
        std::cout << found[i].word;
        if (i + 1 < found.size()) std::cout << ", ";
    }
    std::cout << "]\n";

    return 0;
}
