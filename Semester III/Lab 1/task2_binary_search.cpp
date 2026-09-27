/**
 * LAB ASSIGNMENT 1 - Task 2: Binary Search vs Linear Search Efficiency Analysis
 * 
 * Objective:
 * Implement Binary Search on a pre-sorted array.
 * Measure and log execution times for identical data sizes (n = 10,000, 50,000, and 100,000)
 * to contrast O(log n) efficiency against Linear Search O(n).
 * 
 * Theory:
 * Binary Search halves the search interval at each step.
 * Maximum comparisons = ceil(log2(n + 1))
 * For n = 10,000  -> at most 14 comparisons
 * For n = 50,000  -> at most 16 comparisons
 * For n = 100,000 -> at most 17 comparisons
 * In contrast, Linear Search worst case requires n comparisons (10k, 50k, 100k).
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <numeric>
#include <cmath>

// Binary Search implementation on a pre-sorted array
int binarySearch(const std::vector<int>& arr, int target, long long& comparisons) {
    int low = 0;
    int high = static_cast<int>(arr.size()) - 1;
    comparisons = 0;

    while (low <= high) {
        ++comparisons;
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Target not found
}

// Linear Search implementation for direct comparison
int linearSearch(const std::vector<int>& arr, int target, long long& comparisons) {
    comparisons = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        ++comparisons;
        if (arr[i] == target) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Benchmark Binary Search over multiple repetitions
double benchmarkBinarySearch(const std::vector<int>& arr, int target, int repetitions, long long& comparisons) {
    // Warm-up
    binarySearch(arr, target, comparisons);

    auto start = std::chrono::high_resolution_clock::now();
    for (int r = 0; r < repetitions; ++r) {
        binarySearch(arr, target, comparisons);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::micro> elapsed = end - start;
    return elapsed.count() / repetitions; // Average time in microseconds
}

// Benchmark Linear Search
double benchmarkLinearSearch(const std::vector<int>& arr, int target, int repetitions, long long& comparisons) {
    linearSearch(arr, target, comparisons);

    auto start = std::chrono::high_resolution_clock::now();
    for (int r = 0; r < repetitions; ++r) {
        linearSearch(arr, target, comparisons);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::micro> elapsed = end - start;
    return elapsed.count() / repetitions;
}

void printHeader() {
    std::cout << "\n=======================================================================================================\n";
    std::cout << "                 LAB 1 - TASK 2: BINARY SEARCH vs LINEAR SEARCH EFFICIENCY CONTRAST                    \n";
    std::cout << "=======================================================================================================\n";
    std::cout << std::left 
              << std::setw(10) << "Size (n)" 
              << std::setw(15) << "Algorithm" 
              << std::setw(18) << "Comparisons" 
              << std::setw(18) << "Theory Bound" 
              << std::setw(20) << "Time (microsec)" 
              << std::setw(16) << "Speedup Factor" 
              << "\n";
    std::cout << "-------------------------------------------------------------------------------------------------------\n";
}

int main() {
    const std::vector<int> testSizes = {10000, 50000, 100000};
    const int REPETITIONS = 1000; // 1,000 iterations to measure ultra-fast binary search accurately

    printHeader();

    for (int n : testSizes) {
        // Pre-sorted array: 0, 2, 4, ..., 2*(n-1)
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = i * 2;
        }

        // Search for a target near the end (worst case scenario)
        int target = (n - 1) * 2; // last element

        long long linComparisons = 0;
        double linTime = benchmarkLinearSearch(arr, target, 50, linComparisons);

        long long binComparisons = 0;
        double binTime = benchmarkBinarySearch(arr, target, REPETITIONS, binComparisons);

        double speedup = (binTime > 0.0) ? (linTime / binTime) : 0.0;
        int maxTheoryComparisons = static_cast<int>(std::ceil(std::log2(n + 1)));

        // Print Linear Search Row
        std::cout << std::left 
                  << std::setw(10) << n 
                  << std::setw(15) << "Linear Search" 
                  << std::setw(18) << linComparisons 
                  << std::setw(18) << ("O(n) = " + std::to_string(n)) 
                  << std::setw(20) << std::fixed << std::setprecision(4) << linTime 
                  << std::setw(16) << "1.00x (Baseline)" 
                  << "\n";

        // Print Binary Search Row
        std::cout << std::left 
                  << std::setw(10) << n 
                  << std::setw(15) << "Binary Search" 
                  << std::setw(18) << binComparisons 
                  << std::setw(18) << ("O(log n) <= " + std::to_string(maxTheoryComparisons)) 
                  << std::setw(20) << std::fixed << std::setprecision(5) << binTime 
                  << std::setw(16) << (std::to_string(static_cast<int>(speedup)) + "x faster") 
                  << "\n";

        std::cout << "-------------------------------------------------------------------------------------------------------\n";
    }

    std::cout << "\nCONCLUSION:\n";
    std::cout << "1. Binary Search logarithmic efficiency O(log n) requires at most ceil(log2(n)) comparisons.\n";
    std::cout << "   For n = 100,000, it performs only 17 comparisons vs 100,000 for Linear Search.\n";
    std::cout << "2. This achieves hundreds-to-thousands of times speedup over Linear Search on pre-sorted data.\n";
    std::cout << "=======================================================================================================\n";

    return 0;
}
