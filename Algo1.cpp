// CPSC 335 - Project 3
// Author: Joshua Zamora
// Email: JoshuaMZamora@csu.fullerton.edu
// Algorithm 1: Target Terms or Substrings

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

// Convert a string to lowercase
std::string toLower(const std::string &s) {
    std::string t = s;
    for (char c : s) {
        t.push_back(std::tolower(static_cast<unsigned char>(c)));
    }
    return t;
}

// Manual substring search: return first index of W in S, or -1 if not found
int findSubstring(const std::string &S, const std::string &W) {
    int n = static_cast<int>(S.size());
    int m = static_cast<int>(W.size());
    if (m == 0 || m > n) return -1;

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

// Struct to hold found word + index
struct FoundWord {
    int index;
    std::string word;
};

// Manual selection sort by index
void selectionSort(std::vector<FoundWord> &arr) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; ++i) {
        int minPos = i;
        for (int j = i + 1; j < n; ++j) {
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

// Do the work for Question 1
void findTargetTerms(const std::string &A,
                     const std::vector<std::string> &B,
                     std::vector<int> &indices,
                     std::vector<std::string> &wordsOut)
{
    std::string lowerA = toLower(A);
    std::vector<FoundWord> results;

    for (const std::string &word : B) {
        std::string lowerW = toLower(word);
        int pos = findSubstring(lowerA, lowerW);
        if (pos != -1) {
            FoundWord fw;
            fw.index = pos;
            fw.word  = word;   // keep original word
            results.push_back(fw);
        }
    }

    // sort by index using our own selection sort
    selectionSort(results);

    // separate into output vectors
    for (const FoundWord &fw : results) {
        indices.push_back(fw.index);
        wordsOut.push_back(fw.word);
    }
}

// Helper to print int vector
void printIntVector(const std::vector<int> &v) {
    std::cout << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << ", ";
    }
    std::cout << "]";
}

// Helper to print string vector
void printStringVector(const std::vector<std::string> &v) {
    std::cout << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << ", ";
    }
    std::cout << "]";
}

int main() {
    std::string A;
    int n;

    std::cout << "Enter the concatenated string A: ";
    std::getline(std::cin, A);

    std::cout << "Enter number of words to search for: ";
    std::cin >> n;

    // clear the rest of the line after reading n
    std::cin.ignore(1000, '\n');

    std::vector<std::string> B(n);
    std::cout << "Enter the words:\n";
    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, B[i]);
    }

    std::vector<int> indices;
    std::vector<std::string> wordsOut;

    findTargetTerms(A, B, indices, wordsOut);

    std::cout << "\nOutput_order = ";
    printIntVector(indices);
    std::cout << "\nOutput_array = ";
    printStringVector(wordsOut);
    std::cout << "\n";

    return 0;
}
