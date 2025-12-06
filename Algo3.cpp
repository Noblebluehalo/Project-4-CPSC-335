// CPSC 335 - Project 3
// Author: Joshua Zamora
// Email: JoshuaMZamora@csu.fullerton.edu
// Algorithm 3: Merging Techniques

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <filesystem> // add near other includes

// ----- Min-heap structures & functions -----

struct HeapNode {
    int value;      // integer value
    int listIndex;  // which sub-array it came from
    int elemIndex;  // index within that sub-array
};

// Simple min-heap for HeapNode (based on value)
class MinHeap {
private:
    std::vector<HeapNode> data;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void siftUp(int i) {
        while (i > 0 && data[i].value < data[parent(i)].value) {
            HeapNode tmp = data[i];
            data[i] = data[parent(i)];
            data[parent(i)] = tmp;
            i = parent(i);
        }
    }

    void siftDown(int i) {
        int n = static_cast<int>(data.size());
        while (true) {
            int l = left(i);
            int r = right(i);
            int smallest = i;

            if (l < n && data[l].value < data[smallest].value) {
                smallest = l;
            }
            if (r < n && data[r].value < data[smallest].value) {
                smallest = r;
            }
            if (smallest == i) {
                break;
            }

            HeapNode tmp = data[i];
            data[i] = data[smallest];
            data[smallest] = tmp;
            i = smallest;
        }
    }

public:
    bool empty() const {
        return data.empty();
    }

    void push(const HeapNode& node) {
        data.push_back(node);
        siftUp(static_cast<int>(data.size()) - 1);
    }

    HeapNode top() const {
        return data[0];
    }

    void pop() {
        if (data.empty()) return;
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) {
            siftDown(0);
        }
    }
};

// Merge k sorted arrays into one sorted array
std::vector<int> mergeKSorted(const std::vector<std::vector<int>>& allLists) {
    MinHeap heap;
    std::vector<int> result;

    // Put first element of each non-empty list into heap
    for (int i = 0; i < static_cast<int>(allLists.size()); ++i) {
        if (!allLists[i].empty()) {
            HeapNode node;
            node.value = allLists[i][0];
            node.listIndex = i;
            node.elemIndex = 0;
            heap.push(node);
        }
    }

    // Extract min and push next element from same sub-array
    while (!heap.empty()) {
        HeapNode minNode = heap.top();
        heap.pop();

        result.push_back(minNode.value);

        int nextIdx = minNode.elemIndex + 1;
        int listIdx = minNode.listIndex;

        if (nextIdx < static_cast<int>(allLists[listIdx].size())) {
            HeapNode next;
            next.value = allLists[listIdx][nextIdx];
            next.listIndex = listIdx;
            next.elemIndex = nextIdx;
            heap.push(next);
        }
    }

    return result;
}

// Helper to trim line (check if it's blank)
bool isBlankLine(const std::string& line) {
    for (char c : line) {
        if (!std::isspace(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

// Print a vector like [a, b, c]
void printVector(const std::vector<int>& v) {
    std::cout << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << ", ";
    }
    std::cout << "]";
}

int main() {
    // Change the filename here if your file is named differently
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    std::ifstream fin("in2c.txt");
    if (!fin) {
        std::cerr << "Error: could not open in2c.txt\n";
        return 1;
    }

    std::vector<std::vector<std::vector<int>>> allGroups; // 3 groups
    std::vector<std::vector<int>> currentGroup;

    std::string line;
    while (std::getline(fin, line)) {
        if (isBlankLine(line)) {
            // blank line: end of a group (if we have one)
            if (!currentGroup.empty()) {
                allGroups.push_back(currentGroup);
                currentGroup.clear();
            }
            continue;
        }

        // skip header-only lines like "Array_1  =" but still parse if this line contains data
        if (line.find("Array_") != std::string::npos && line.find('[') == std::string::npos) {
            continue;
        }

        // lines with actual integer arrays: like "[2, 5, 9, 21],"
        if (line.find('[') != std::string::npos) {
            std::vector<int> sub;
            std::stringstream ss(line);
            char ch;
            int num;

            while (ss >> ch) {
                if (ch == '-' || std::isdigit(static_cast<unsigned char>(ch))) {
                    ss.putback(ch);
                    ss >> num;
                    sub.push_back(num);
                }
            }

            if (!sub.empty()) {
                currentGroup.push_back(sub);
            }
        }
    }

    // push last group if file didn't end with a blank line
    if (!currentGroup.empty()) {
        allGroups.push_back(currentGroup);
    }

    // Now we should have 3 groups: Array_1, Array_2, Array_3
    for (std::size_t g = 0; g < allGroups.size(); ++g) {
        std::vector<int> merged = mergeKSorted(allGroups[g]);
        std::cout << "Merged Array_" << (g + 1) << " = ";
        printVector(merged);
        std::cout << "\n";
    }

    return 0;
}
