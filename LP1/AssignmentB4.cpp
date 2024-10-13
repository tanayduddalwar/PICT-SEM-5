#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> 
using namespace std;
// FIFO Page Replacement
int fifoPageReplacement(vector<int> pages, int capacity) {
    vector<int> memory;
    int pageFaults = 0;
    int n=pages.size();
    for (int i=0;i<n;i++) {
        if (find(memory.begin(), memory.end(), pages[i]) == memory.end()) {
            if (memory.size() == capacity) {
                memory.erase(memory.begin()); // Remove the first inserted page
            }
            memory.push_back(pages[i]);
            pageFaults++;
        }
        cout << "Memory: ";
        for (int p : memory) cout << p << " ";
        cout << endl;
    }
    return pageFaults;
}

// LRU Page Replacement
int lruPageReplacement(vector<int> pages, int capacity) {
    vector<int> memory;
    int pageFaults = 0;
    for (int page : pages) {
        auto it = find(memory.begin(), memory.end(), page);
        if (it == memory.end()) {
            if (memory.size() == capacity) {
                memory.erase(memory.begin()); // Remove least recently used page (first element)
            }
            pageFaults++;
        } else {
            memory.erase(it); // Move page to the most recent position
        }
        memory.push_back(page);
        cout << "Memory: ";
        for (int p : memory) cout << p << " ";
        cout << endl;
    }
    return pageFaults;
}

// Optimal Page Replacement
int optimalPageReplacement(vector<int> pages, int capacity) {
    vector<int> memory;
    int pageFaults = 0;
    for (size_t i = 0; i < pages.size(); i++) {
        if (find(memory.begin(), memory.end(), pages[i]) == memory.end()) {
            if (memory.size() == capacity) {
                // Find the page to replace
                int farthest = i + 1;
                int replaceIdx = -1;
                for (size_t j = 0; j < memory.size(); j++) {
                    int nextUse = INT_MAX;
                    for (size_t k = i + 1; k < pages.size(); k++) {
                        if (pages[k] == memory[j]) {
                            nextUse = k;
                            break;
                        }
                    }
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replaceIdx = j;
                    }
                }
                if (replaceIdx == -1) {
                    memory.erase(memory.begin());
                } else {
                    memory.erase(memory.begin() + replaceIdx);
                }
            }
            memory.push_back(pages[i]);
            pageFaults++;
        }
        cout << "Memory: ";
        for (int p : memory) cout << p << " ";
        cout << endl;
    }
    return pageFaults;
}

// Driver code
int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int capacity = 3;

    cout << "\nFIFO Page Replacement" << endl;
    int fifoFaults = fifoPageReplacement(pages, capacity);
    cout << "Page Faults using FIFO: " << fifoFaults << endl;

    cout << "\nLRU Page Replacement" << endl;
    int lruFaults = lruPageReplacement(pages, capacity);
    cout << "Page Faults using LRU: " << lruFaults << endl;

    cout << "\nOptimal Page Replacement" << endl;
    int optimalFaults = optimalPageReplacement(pages, capacity);
    cout << "Page Faults using Optimal: " << optimalFaults << endl;

    return 0;
}
