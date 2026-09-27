/**
 * LAB SHEET 9 - Task 2: Heap Sort
 * 
 * Objective:
 * Convert an arbitrary array into a heap structure and sort it by
 * repeatedly extracting the root node.
 * 
 * Theory:
 * 1. Bottom-up Build-Heap:
 *    Convert an unsorted array of size n into a Max-Heap in O(n) time
 *    by heapifying from the last non-leaf node (n/2 - 1) down to index 0.
 * 2. In-place Heap Sort:
 *    Repeatedly swap the maximum element at root (arr[0]) with the last
 *    element in the active heap (arr[i]), reduce heap size by 1, and
 *    sift-down the root. The array is sorted in ascending order in O(n log n).
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

// Helper to print array
void printArray(const std::vector<int>& arr, int activeHeapSize = -1) {
    std::cout << "[ ";
    for (size_t i = 0; i < arr.size(); ++i) {
        if (activeHeapSize != -1 && static_cast<int>(i) == activeHeapSize) {
            std::cout << "| "; // Separator between active heap and sorted portion
        }
        std::cout << arr[i] << (i + 1 < arr.size() ? " " : "");
    }
    std::cout << " ]\n";
}

/**
 * Sift-down (heapify) a subtree rooted at index i in an array of size n
 */
void maxHeapify(std::vector<int>& arr, int n, int i, long long& comparisons, long long& swaps) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        ++comparisons;
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }

    if (right < n) {
        ++comparisons;
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        ++swaps;
        std::swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest, comparisons, swaps);
    }
}

/**
 * Complete Heap Sort algorithm with step logging
 */
void heapSort(std::vector<int>& arr, bool verbose = true) {
    int n = static_cast<int>(arr.size());
    long long comparisons = 0;
    long long swaps = 0;

    if (verbose) {
        std::cout << "Original Unsorted Array:\n";
        printArray(arr);
        std::cout << "\n--- PHASE 1: Bottom-Up Max-Heap Construction (O(n)) ---\n";
    }

    // Step 1: Build max heap (rearrange array)
    // Last non-leaf node is at (n / 2) - 1
    for (int i = (n / 2) - 1; i >= 0; --i) {
        maxHeapify(arr, n, i, comparisons, swaps);
    }

    if (verbose) {
        std::cout << "Array after Max-Heap Construction:\n";
        printArray(arr);
        std::cout << "(Root " << arr[0] << " is the maximum element in the dataset)\n\n";
        std::cout << "--- PHASE 2: Repeated Root Extraction & In-Place Sorting (O(n log n)) ---\n";
    }

    // Step 2: One by one extract an element from heap
    for (int i = n - 1; i > 0; --i) {
        // Move current root (maximum) to end (index i)
        std::swap(arr[0], arr[i]);
        ++swaps;

        if (verbose) {
            std::cout << "Extracted root " << std::setw(3) << arr[i] 
                      << " -> Moved to position " << std::setw(2) << i 
                      << " | Current Array: ";
            printArray(arr, i);
        }

        // Call maxHeapify on the reduced heap [0 .. i-1]
        maxHeapify(arr, i, 0, comparisons, swaps);
    }

    if (verbose) {
        std::cout << "\nFinal Sorted Array (Ascending):\n";
        printArray(arr);
        std::cout << "Total Comparisons: " << comparisons 
                  << " | Total Swaps: " << swaps << "\n";
    }
}

int main() {
    std::cout << "====================================================================\n";
    std::cout << "              LAB 9 - TASK 2: HEAP SORT DEMONSTRATION               \n";
    std::cout << "====================================================================\n\n";

    // Test 1: Arbitrary unsorted array
    std::vector<int> sample = {64, 34, 25, 12, 22, 11, 90, 88, 45, 5};
    heapSort(sample, true);

    bool correct = std::is_sorted(sample.begin(), sample.end());
    std::cout << "Verification: " << (correct ? "PASSED (Array is sorted!)" : "FAILED") << "\n\n";

    // Test 2: Reverse-sorted array
    std::cout << "--------------------------------------------------------------------\n";
    std::cout << "Testing Reverse-Sorted Input:\n";
    std::vector<int> reverseSample = {99, 88, 77, 66, 55, 44, 33, 22, 11};
    heapSort(reverseSample, true);
    std::cout << "Verification: " << (std::is_sorted(reverseSample.begin(), reverseSample.end()) ? "PASSED" : "FAILED") << "\n";

    std::cout << "====================================================================\n";
    return 0;
}
