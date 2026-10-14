/**
 * LAB SHEET 7 - Task 2: Optimal Merge Pattern Simulation
 * 
 * Objective:
 * Write a routine that reads various file sizes and designs an optimal merge sequence
 * that minimizes the total number of element moves.
 * 
 * Theory:
 * When merging n sorted files into a single sorted file, merging two files of
 * sizes x and y takes (x + y) operations.
 * To minimize total operations, a Greedy Strategy (equivalent to Huffman's algorithm)
 * is used: at each step, merge the two files with the smallest sizes.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <string>

struct MergeStep {
    int file1;
    int file2;
    int mergedSize;
    int cumulativeMoves;
};

int simulateOptimalMerge(const std::vector<int>& fileSizes, bool verbose = true) {
    if (fileSizes.empty()) return 0;
    if (fileSizes.size() == 1) return 0;

    // Min-heap to always extract the two smallest file sizes
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    for (int size : fileSizes) {
        minHeap.push(size);
    }

    int totalMoves = 0;
    int stepNum = 1;

    if (verbose) {
        std::cout << "\n======================================================================\n";
        std::cout << "             OPTIMAL MERGE PATTERN SIMULATION STEP TRACE              \n";
        std::cout << "======================================================================\n";
        std::cout << "Initial File Sizes: [ ";
        for (int sz : fileSizes) std::cout << sz << " ";
        std::cout << "]\n";
        std::cout << "----------------------------------------------------------------------\n";
        std::cout << std::left 
                  << std::setw(8) << "Step" 
                  << std::setw(22) << "Selected Files" 
                  << std::setw(18) << "Step Merge Cost" 
                  << std::setw(20) << "Cumulative Moves" 
                  << "\n";
        std::cout << "----------------------------------------------------------------------\n";
    }

    while (minHeap.size() > 1) {
        int f1 = minHeap.top(); minHeap.pop();
        int f2 = minHeap.top(); minHeap.pop();

        int stepCost = f1 + f2;
        totalMoves += stepCost;

        if (verbose) {
            std::string filesStr = std::to_string(f1) + " + " + std::to_string(f2);
            std::cout << std::left 
                      << std::setw(8) << ("#" + std::to_string(stepNum++)) 
                      << std::setw(22) << filesStr 
                      << std::setw(18) << stepCost 
                      << std::setw(20) << totalMoves 
                      << "\n";
        }

        minHeap.push(stepCost);
    }

    if (verbose) {
        std::cout << "----------------------------------------------------------------------\n";
        std::cout << "Final Merged File Size  : " << minHeap.top() << " records\n";
        std::cout << "Total Minimum Move Cost : " << totalMoves << " operations\n";
        std::cout << "======================================================================\n\n";
    }

    return totalMoves;
}

int main() {
    std::cout << "======================================================================\n";
    std::cout << "       LAB 7 - TASK 2: OPTIMAL MERGE PATTERN SIMULATOR                \n";
    std::cout << "======================================================================\n";

    // Dataset 1: Standard university lab example
    std::vector<int> files1 = {20, 30, 10, 5, 35};
    std::cout << ">>> TEST CASE 1: 5 Files {20, 30, 10, 5, 35} <<<\n";
    simulateOptimalMerge(files1, true);

    // Dataset 2: 6 Files
    std::vector<int> files2 = {2, 3, 4, 5, 6, 7};
    std::cout << ">>> TEST CASE 2: 6 Files {2, 3, 4, 5, 6, 7} <<<\n";
    simulateOptimalMerge(files2, true);

    return 0;
}
