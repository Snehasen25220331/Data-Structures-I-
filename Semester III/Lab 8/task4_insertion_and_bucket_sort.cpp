/**
 * LAB SHEET 8 - Task 4: Insertion Sort and Bucket Sort
 * 
 * Objective:
 * Implement and demonstrate both Insertion Sort and Bucket Sort algorithms.
 * 
 * Theory:
 * 1. Insertion Sort:
 *    - Incremental sorting algorithm.
 *    - Invariant: Elements A[0 .. i-1] are sorted at the start of step i.
 *    - Time Complexity: O(n) best case (pre-sorted), O(n^2) worst/average case.
 * 
 * 2. Bucket Sort:
 *    - Distribution sorting algorithm.
 *    - Divides elements into uniform interval buckets, sorts buckets individually,
 *      and concatenates the results.
 *    - Time Complexity: O(n + k) average case when elements are uniformly distributed.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

void printArray(const std::vector<int>& arr) {
    std::cout << "[ ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "]\n";
}

// 1. Insertion Sort with Step-by-Step Logging
void insertionSort(std::vector<int> arr) {
    std::cout << "\n======================================================================\n";
    std::cout << "              INSERTION SORT STEP-BY-STEP TRACE                       \n";
    std::cout << "======================================================================\n";
    std::cout << "Initial Array: ";
    printArray(arr);

    int n = static_cast<int>(arr.size());
    long long shifts = 0;

    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // Shift right
            --j;
            ++shifts;
        }
        arr[j + 1] = key;

        std::cout << "Pass " << std::setw(2) << i << " (Inserted key " << std::setw(3) << key 
                  << " at index " << (j + 1) << "): ";
        printArray(arr);
    }

    std::cout << "Final Sorted Array: ";
    printArray(arr);
    std::cout << "Total Shifts: " << shifts << "\n";
    std::cout << "======================================================================\n";
}

// 2. Bucket Sort with Distribution Logging
void bucketSort(std::vector<int> arr, int numBuckets = 5) {
    std::cout << "\n======================================================================\n";
    std::cout << "                BUCKET SORT STEP-BY-STEP TRACE                        \n";
    std::cout << "======================================================================\n";
    std::cout << "Initial Array: ";
    printArray(arr);

    if (arr.empty()) return;

    int minVal = *std::min_element(arr.begin(), arr.end());
    int maxVal = *std::max_element(arr.begin(), arr.end());
    double range = static_cast<double>(maxVal - minVal + 1);

    std::vector<std::vector<int>> buckets(numBuckets);

    // Step 1: Distribute elements into buckets
    std::cout << "\n--- STEP 1: Distributing elements into " << numBuckets << " buckets ---\n";
    for (int x : arr) {
        int bIdx = static_cast<int>(((x - minVal) / range) * numBuckets);
        if (bIdx >= numBuckets) bIdx = numBuckets - 1;
        buckets[bIdx].push_back(x);
    }

    for (int i = 0; i < numBuckets; ++i) {
        std::cout << "Bucket [" << i << "]: ";
        printArray(buckets[i]);
    }

    // Step 2: Sort individual buckets and concatenate
    std::cout << "\n--- STEP 2: Sorting individual buckets & Concatenating ---\n";
    std::vector<int> sortedArr;
    for (int i = 0; i < numBuckets; ++i) {
        std::sort(buckets[i].begin(), buckets[i].end());
        std::cout << "Sorted Bucket [" << i << "]: ";
        printArray(buckets[i]);
        for (int x : buckets[i]) {
            sortedArr.push_back(x);
        }
    }

    std::cout << "\nFinal Sorted Array: ";
    printArray(sortedArr);
    std::cout << "======================================================================\n";
}

int main() {
    std::cout << "======================================================================\n";
    std::cout << "          LAB 8 - TASK 4: INSERTION SORT & BUCKET SORT                \n";
    std::cout << "======================================================================\n";

    std::vector<int> data = {42, 17, 88, 35, 12, 65, 91, 23, 54, 9};

    // Run Insertion Sort
    insertionSort(data);

    // Run Bucket Sort
    bucketSort(data, 5);

    return 0;
}
