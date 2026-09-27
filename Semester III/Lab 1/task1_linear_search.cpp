/**
 * LAB ASSIGNMENT 1 - Task 1: Linear Search Time Complexity Analysis
 * 
 * Objective:
 * Implement Linear Search to find a target value in an array.
 * Measure and log execution time in microseconds for array sizes
 * n = 10,000, 50,000, and 100,000 to demonstrate O(n) linear behavior.
 * 
 * Theory:
 * Linear Search scans each element one-by-one from left to right.
 * Best Case: Target at index 0 -> O(1)
 * Worst Case: Target at index n-1 or not present -> O(n) comparisons
 * Average Case: Target at random position -> n/2 comparisons -> O(n)
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <numeric>
#include <random>

// Linear Search implementation
// Returns index if found, or -1 if not found. Also records comparison count.
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

// Benchmark Linear Search over multiple repetitions for precision
double benchmarkLinearSearch(const std::vector<int>& arr, int target, int repetitions, long long& comparisons) {
    // Warm-up run
    linearSearch(arr, target, comparisons);

    auto start = std::chrono::high_resolution_clock::now();
    for (int r = 0; r < repetitions; ++r) {
        linearSearch(arr, target, comparisons);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::micro> elapsed = end - start;
    return elapsed.count() / repetitions; // Average time in microseconds
}

void printHeader() {
    std::cout << "\n========================================================================================\n";
    std::cout << "               LAB 1 - TASK 1: LINEAR SEARCH TIME COMPLEXITY ANALYSIS                    \n";
    std::cout << "========================================================================================\n";
    std::cout << std::left 
              << std::setw(12) << "Array Size (n)" 
              << std::setw(16) << "Case" 
              << std::setw(18) << "Target Found?" 
              << std::setw(16) << "Comparisons" 
              << std::setw(18) << "Time (microsec)" 
              << std::setw(14) << "Ratio T(n)/n" 
              << "\n";
    std::cout << "----------------------------------------------------------------------------------------\n";
}

int main() {
    const std::vector<int> testSizes = {10000, 50000, 100000};
    const int REPETITIONS = 100; // Average over 100 iterations for precision

    printHeader();

    for (int n : testSizes) {
        // Construct array populated with 0, 1, 2, ..., n-1
        std::vector<int> arr(n);
        std::iota(arr.begin(), arr.end(), 0);

        // 1. Worst Case: Target is not present (or at very end)
        int worstTarget = n + 999;
        long long comparisons = 0;
        double worstTime = benchmarkLinearSearch(arr, worstTarget, REPETITIONS, comparisons);
        double ratio = (worstTime / n) * 1e3; // Scaled for readability

        std::cout << std::left 
                  << std::setw(12) << n 
                  << std::setw(16) << "Worst (Not Found)" 
                  << std::setw(18) << "No (-1)" 
                  << std::setw(16) << comparisons 
                  << std::setw(18) << std::fixed << std::setprecision(3) << worstTime 
                  << std::setw(14) << std::fixed << std::setprecision(5) << ratio 
                  << "\n";

        // 2. Average Case: Target in the middle
        int avgTarget = n / 2;
        double avgTime = benchmarkLinearSearch(arr, avgTarget, REPETITIONS, comparisons);
        double avgRatio = (avgTime / (n / 2.0)) * 1e3;

        std::cout << std::left 
                  << std::setw(12) << n 
                  << std::setw(16) << "Average (Middle)" 
                  << std::setw(18) << "Yes" 
                  << std::setw(16) << comparisons 
                  << std::setw(18) << std::fixed << std::setprecision(3) << avgTime 
                  << std::setw(14) << std::fixed << std::setprecision(5) << avgRatio 
                  << "\n";

        // 3. Best Case: Target at index 0
        int bestTarget = 0;
        double bestTime = benchmarkLinearSearch(arr, bestTarget, REPETITIONS, comparisons);

        std::cout << std::left 
                  << std::setw(12) << n 
                  << std::setw(16) << "Best (Index 0)" 
                  << std::setw(18) << "Yes (0)" 
                  << std::setw(16) << comparisons 
                  << std::setw(18) << std::fixed << std::setprecision(4) << bestTime 
                  << std::setw(14) << "O(1)" 
                  << "\n";

        std::cout << "----------------------------------------------------------------------------------------\n";
    }

    std::cout << "\nCONCLUSION:\n";
    std::cout << "1. In the worst case, as size n increases by 5x (10k -> 50k) and 10x (10k -> 100k),\n";
    std::cout << "   execution time scales linearly with n. The ratio T(n)/n remains approximately constant.\n";
    std::cout << "2. This experimentally validates that Linear Search exhibits O(n) time complexity.\n";
    std::cout << "========================================================================================\n";

    return 0;
}
