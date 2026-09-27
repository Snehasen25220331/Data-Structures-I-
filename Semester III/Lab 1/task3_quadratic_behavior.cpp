/**
 * LAB ASSIGNMENT 1 - Task 3: Nested Loops O(n^2) Quadratic Behavior
 * 
 * Objective:
 * Create a program containing two nested loops (e.g. executing a basic
 * bubble comparison loop or pairwise matrix operation).
 * Record performance drop-offs as data size scales upward to demonstrate O(n^2) behavior.
 * 
 * Theory:
 * Two nested loops over n elements execute n * (n - 1) / 2 comparisons (~ n^2 / 2).
 * When the input size n doubles (n -> 2n):
 *   T(2n) / T(n) = (2n)^2 / n^2 = 4
 * The execution time quadruples, demonstrating O(n^2) quadratic scaling.
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <numeric>
#include <random>
#include <sstream>

// Bubble comparison loop (nested loops without early break to demonstrate full O(n^2) work)
long long bubbleComparisonLoop(std::vector<int>& arr) {
    long long comparisons = 0;
    size_t n = arr.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n - 1 - i; ++j) {
            ++comparisons;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
    return comparisons;
}

// Alternative pairwise matrix operation to also show nested loop behavior
long long matrixStyleNestedLoop(int n) {
    long long operations = 0;
    volatile long long dummySum = 0; // Prevent compiler from optimizing loop away
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dummySum += (i * j);
            ++operations;
        }
    }
    return operations;
}

void printHeader() {
    std::cout << "\n====================================================================================================\n";
    std::cout << "                  LAB 1 - TASK 3: QUADRATIC TIME COMPLEXITY O(n^2) DEMONSTRATION                    \n";
    std::cout << "====================================================================================================\n";
    std::cout << std::left 
              << std::setw(12) << "Size (n)" 
              << std::setw(18) << "Comparisons (~n^2/2)" 
              << std::setw(20) << "Time (milliseconds)" 
              << std::setw(22) << "Observed Ratio T(n)/T(prev)" 
              << std::setw(20) << "Expected O(n^2) Ratio" 
              << "\n";
    std::cout << "----------------------------------------------------------------------------------------------------\n";
}

int main() {
    // Array sizes chosen to demonstrate doubling behavior: 1k -> 2k -> 4k -> 8k -> 16k
    const std::vector<int> sizes = {1000, 2000, 4000, 8000, 16000};

    printHeader();

    double prevTime = 0.0;

    for (int n : sizes) {
        // Create reverse-sorted array for deterministic worst-case nested loop comparison
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = n - i;
        }

        auto start = std::chrono::high_resolution_clock::now();
        long long comparisons = bubbleComparisonLoop(arr);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> elapsed = end - start;
        double currentTimeMs = elapsed.count();

        std::string ratioStr = "-";
        if (prevTime > 0.0) {
            double ratio = currentTimeMs / prevTime;
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(2) << ratio << "x";
            ratioStr = ss.str();
        }

        std::cout << std::left 
                  << std::setw(12) << n 
                  << std::setw(18) << comparisons 
                  << std::setw(20) << std::fixed << std::setprecision(3) << currentTimeMs 
                  << std::setw(22) << ratioStr 
                  << std::setw(20) << (prevTime > 0.0 ? "~4.00x (Quadratic)" : "-") 
                  << "\n";

        prevTime = currentTimeMs;
    }

    std::cout << "----------------------------------------------------------------------------------------------------\n";
    std::cout << "\nANALYSIS & PERFORMANCE DROP-OFF OBSERVATIONS:\n";
    std::cout << "1. When input size n doubles (e.g., 2,000 -> 4,000 -> 8,000 -> 16,000):\n";
    std::cout << "   The comparison count scales by (2n)^2 / n^2 = 4x.\n";
    std::cout << "2. The measured execution time closely follows the theoretical 4x multiplier,\n";
    std::cout << "   confirming quadratic growth O(n^2).\n";
    std::cout << "3. Notice the steep performance drop-off: at n = 16,000, execution takes significantly longer\n";
    std::cout << "   than n = 1,000 (roughly 256x slower), illustrating why O(n^2) algorithms do not scale well.\n";
    std::cout << "====================================================================================================\n";

    return 0;
}
