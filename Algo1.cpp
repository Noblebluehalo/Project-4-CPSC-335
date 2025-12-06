// CPSC 335 - Project 3
// Author: Joshua Zamora
// Email: JoshuaMZamora@csu.fullerton.edu
// Algorithm 1: Target Terms or Substrings


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

// Convert a string to lowercase
std::string toLower(const std::string& s) {
    std::string t;
    t.reserve(s.size());
    for (char c : s) t.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
    return t;
}

// Manual substring search
int findSubstring(const std::string& S, const std::string& W) {
    int n = static_cast<int>(S.size());
    int m = static_cast<int>(W.size());
    if (m > n) return -1;
    for (int i = 0; i <= n - m; ++i) {
        bool match = true;
        for (int j = 0; j < m; ++j) {
            if (S[i + j] != W[j]) { match = false; break; }
        }
        if (match) return i;
    }
    return -1;
}

struct FoundWord {
    int index;
    std::string word;
};

// Manual selection sort (by index)
void selectionSort(std::vector<FoundWord>& arr) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; ++i) {
        int minPos = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j].index < arr[minPos].index) minPos = j;
        }
        if (minPos != i) {
            FoundWord tmp = arr[i];
            arr[i] = arr[minPos];
            arr[minPos] = tmp;
        }
    }
}

// trimming helpers
void ltrim(std::string& s) {
    size_t i = 0;
    while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
    if (i) s.erase(0, i);
}
void rtrim(std::string& s) {
    if (s.empty()) return;
    size_t i = s.size();
    while (i > 0 && std::isspace(static_cast<unsigned char>(s[i - 1]))) --i;
    if (i < s.size()) s.erase(i);
}
void trim(std::string& s) { ltrim(s); rtrim(s); }

// extract content between '[' and matching ']' possibly across lines
std::string extractBracketContent(const std::vector<std::string>& lines, int startLine, size_t posInLine, int& outLine) {
    std::string content;
    for (int i = startLine; i < static_cast<int>(lines.size()); ++i) {
        const std::string& line = lines[i];
        size_t j = (i == startLine) ? posInLine + 1 : 0;
        for (; j < line.size(); ++j) {
            char c = line[j];
            if (c == ']') { outLine = i; trim(content); return content; }
            content.push_back(c);
        }
        content.push_back(' ');
    }
    outLine = static_cast<int>(lines.size()) - 1;
    trim(content);
    return content;
}

// Clean A: remove non-alphanumeric and lower-case.
std::string cleanA(const std::string& raw) {
    std::string out;
    out.reserve(raw.size());
    for (unsigned char c : raw) {
        if (std::isalnum(c)) out.push_back(static_cast<char>(std::tolower(c)));
    }
    return out;
}

// Parse B raw content into tokens preserving original casing
std::vector<std::string> parseB(const std::string& raw) {
    std::vector<std::string> tokens;
    std::string cur;
    for (size_t i = 0; i < raw.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(raw[i]);
        if (std::isalnum(c)) cur.push_back(raw[i]);
        else {
            if (!cur.empty()) { tokens.push_back(cur); cur.clear(); }
        }
    }
    if (!cur.empty()) tokens.push_back(cur);
    return tokens;
}

int main() {
    std::ifstream ifs("in2a.txt");
    if (!ifs) {
        std::cerr << "Error: could not open in2a.txt\n";
        return 1;
    }

    // Read file into lines
    std::vector<std::string> lines;
    std::string t;
    while (std::getline(ifs, t)) lines.push_back(t);
    ifs.close();

    std::vector<std::pair<std::string, std::vector<std::string>>> tests; // (Aclean, Btokens)
    std::string pendingA;
    std::vector<std::string> pendingB;

    for (int i = 0; i < static_cast<int>(lines.size()); ++i) {
        std::string low = toLower(lines[i]);
        if (low.find("array") == std::string::npos) continue;

        bool isA = (low.find("1a") != std::string::npos) || (low.find("2a") != std::string::npos) || (low.find("3a") != std::string::npos);
        bool isB = (low.find("1b") != std::string::npos) || (low.find("2b") != std::string::npos) || (low.find("3b") != std::string::npos);

        size_t pos = lines[i].find('[');
        int startLine = i;
        if (pos == std::string::npos) {
            int j = i + 1;
            for (; j < static_cast<int>(lines.size()); ++j) {
                pos = lines[j].find('[');
                if (pos != std::string::npos) { startLine = j; break; }
            }
            if (pos == std::string::npos) continue;
        }

        int endLine = startLine;
        std::string content = extractBracketContent(lines, startLine, pos, endLine);
        trim(content);

        if (isA) pendingA = cleanA(content);
        else if (isB) pendingB = parseB(content);
        else {
            if (content.size() > 40) pendingA = cleanA(content);
            else pendingB = parseB(content);
        }

        if (!pendingA.empty() && !pendingB.empty()) {
            tests.push_back(std::make_pair(pendingA, pendingB));
            pendingA.clear();
            pendingB.clear();
        }

        i = endLine;
    }

    if (tests.empty()) {
        std::cerr << "No test cases parsed from in2a.txt\n";
        return 1;
    }

    // Print final answers only (1-based indices)
    for (size_t ti = 0; ti < tests.size(); ++ti) {
        const std::string& Aclean = tests[ti].first;
        const std::vector<std::string>& Braw = tests[ti].second;

        std::vector<FoundWord> found;
        for (const std::string& wraw : Braw) {
            std::string wl = toLower(wraw);
            int pos = findSubstring(Aclean, wl);
            if (pos != -1) found.push_back({ pos, wraw });
        }

        selectionSort(found);

        std::cout << "Output_order = [";
        for (size_t i = 0; i < found.size(); ++i) {
            std::cout << (found[i].index + 1); // 1-based
            if (i + 1 < found.size()) std::cout << ", ";
        }
        std::cout << "]\n";

        std::cout << "Output_array = [";
        for (size_t i = 0; i < found.size(); ++i) {
            std::cout << found[i].word;
            if (i + 1 < found.size()) std::cout << ", ";
        }
        std::cout << "]\n";
    }

    return 0;
}
