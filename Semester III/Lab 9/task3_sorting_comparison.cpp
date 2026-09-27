/**
 * LAB SHEET 9 - Task 3: Comprehensive Sorting Comparison Framework
 * 
 * Objective:
 * Implement:
 * 1. Linear Search
 * 2. Binary Search
 * 3. Bubble Sort
 * 4. Selection Sort
 * 5. Insertion Sort
 * 6. Quick Sort
 * 7. Merge Sort
 * 8. Bucket Sort
 * 
 * Profile their execution times on identical input data sets (e.g. n = 1k, 5k, 10k, 20k).
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <random>
#include <string>

// ============================================================================
// 1. SEARCHING ALGORITHMS
// ============================================================================
int linearSearch(const std::vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) return static_cast<int>(i);
    }
    return -1;
}

int binarySearch(const std::vector<int>& arr, int target) {
    int low = 0, high = static_cast<int>(arr.size()) - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// ============================================================================
// 2. SORTING ALGORITHMS
// ============================================================================

// (A) Bubble Sort: O(n^2)
void bubbleSort(std::vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n; ++i) {
        bool swapped = false;
        for (size_t j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// (B) Selection Sort: O(n^2)
void selectionSort(std::vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            std::swap(arr[i], arr[minIdx]);
        }
    }
}

// (C) Insertion Sort: O(n^2)
void insertionSort(std::vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 1; i < n; ++i) {
        int key = arr[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// (D) Quick Sort: O(n log n) average
int partition(std::vector<int>& arr, int low, int high) {
    // Median-of-three pivot selection to prevent worst-case on pre-sorted data
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low]) std::swap(arr[low], arr[mid]);
    if (arr[high] < arr[low]) std::swap(arr[low], arr[high]);
    if (arr[high] < arr[mid]) std::swap(arr[mid], arr[high]);
    std::swap(arr[mid], arr[high]); // Put median at pivot position

    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(std::vector<int>& arr) {
    if (!arr.empty()) {
        quickSortHelper(arr, 0, static_cast<int>(arr.size()) - 1);
    }
}

// (E) Merge Sort: O(n log n)
void merge(std::vector<int>& arr, int l, int m, int r, std::vector<int>& temp) {
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];
    for (int idx = l; idx <= r; ++idx) arr[idx] = temp[idx];
}

void mergeSortHelper(std::vector<int>& arr, int l, int r, std::vector<int>& temp) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortHelper(arr, l, m, temp);
        mergeSortHelper(arr, m + 1, r, temp);
        merge(arr, l, m, r, temp);
    }
}

void mergeSort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;
    std::vector<int> temp(arr.size());
    mergeSortHelper(arr, 0, static_cast<int>(arr.size()) - 1, temp);
}

// (F) Bucket Sort: O(n + k)
void bucketSort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;

    int minVal = *std::min_element(arr.begin(), arr.end());
    int maxVal = *std::max_element(arr.begin(), arr.end());
    if (minVal == maxVal) return;

    size_t bucketCount = arr.size();
    std::vector<std::vector<int>> buckets(bucketCount);

    double range = static_cast<double>(maxVal - minVal + 1);

    for (int x : arr) {
        size_t bIdx = static_cast<size_t>(((x - minVal) / range) * bucketCount);
        if (bIdx >= bucketCount) bIdx = bucketCount - 1;
        buckets[bIdx].push_back(x);
    }

    size_t idx = 0;
    for (size_t i = 0; i < bucketCount; ++i) {
        std::sort(buckets[i].begin(), buckets[i].end());
        for (int val : buckets[i]) {
            arr[idx++] = val;
        }
    }
}

// ============================================================================
// BENCHMARK HARNESS
// ============================================================================
template <typename Func>
double timeSort(Func sortFunc, std::vector<int> arr) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = std::chrono::high_resolution_clock::now();
    if (!std::is_sorted(arr.begin(), arr.end())) {
        std::cerr << "[ERROR] Sorting verification failed!\n";
    }
    std::chrono::duration<double, std::milli> ms = end - start;
    return ms.count();
}

int main() {
    std::cout << "=========================================================================================================\n";
    std::cout << "                     LAB 9 - TASK 3: SORTING & SEARCHING BENCHMARK FRAMEWORK                             \n";
    std::cout << "=========================================================================================================\n\n";

    const std::vector<int> testSizes = {1000, 5000, 10000, 20000};

    // Print Header
    std::cout << std::left 
              << std::setw(10) << "Size (n)"
              << std::setw(15) << "Bubble (ms)"
              << std::setw(15) << "Select (ms)"
              << std::setw(15) << "Insert (ms)"
              << std::setw(15) << "Quick (ms)"
              << std::setw(15) << "Merge (ms)"
              << std::setw(15) << "Bucket (ms)"
              << "\n";
    std::cout << "---------------------------------------------------------------------------------------------------------\n";

    std::mt19937 rng(42); // Deterministic seed for fair comparisons

    for (int n : testSizes) {
        std::vector<int> dataset(n);
        std::uniform_int_distribution<int> dist(1, 100000);
        for (int i = 0; i < n; ++i) {
            dataset[i] = dist(rng);
        }

        double tBubble = timeSort(bubbleSort, dataset);
        double tSelect = timeSort(selectionSort, dataset);
        double tInsert = timeSort(insertionSort, dataset);
        double tQuick  = timeSort(quickSort, dataset);
        double tMerge  = timeSort(mergeSort, dataset);
        double tBucket = timeSort(bucketSort, dataset);

        std::cout << std::left 
                  << std::setw(10) << n
                  << std::setw(15) << std::fixed << std::setprecision(2) << tBubble
                  << std::setw(15) << std::fixed << std::setprecision(2) << tSelect
                  << std::setw(15) << std::fixed << std::setprecision(2) << tInsert
                  << std::setw(15) << std::fixed << std::setprecision(2) << tQuick
                  << std::setw(15) << std::fixed << std::setprecision(2) << tMerge
                  << std::setw(15) << std::fixed << std::setprecision(2) << tBucket
                  << "\n";
    }

    std::cout << "---------------------------------------------------------------------------------------------------------\n";

    // Searching Comparison on largest dataset (n = 20,000)
    int nSearch = 20000;
    std::vector<int> searchData(nSearch);
    for (int i = 0; i < nSearch; ++i) searchData[i] = i * 2;
    int target = (nSearch - 1) * 2;
    volatile int sink = 0;

    auto tStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 2000; ++i) {
        sink += linearSearch(searchData, target);
    }
    auto tEnd = std::chrono::high_resolution_clock::now();
    double linUs = std::chrono::duration<double, std::micro>(tEnd - tStart).count() / 2000.0;

    tStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 20000; ++i) {
        sink += binarySearch(searchData, target);
    }
    tEnd = std::chrono::high_resolution_clock::now();
    double binUs = std::chrono::duration<double, std::micro>(tEnd - tStart).count() / 20000.0;

    std::cout << "\nSEARCHING PROFILING (n = " << nSearch << "):\n";
    std::cout << "  - Linear Search Time : " << std::fixed << std::setprecision(4) << linUs << " microsec (O(n))\n";
    std::cout << "  - Binary Search Time : " << std::fixed << std::setprecision(5) << binUs << " microsec (O(log n))\n";
    if (binUs > 0) {
        std::cout << "  - Binary Search Speedup: " << static_cast<int>(linUs / binUs) << "x faster\n";
    }

    std::cout << "\nCOMPLEXITY SUMMARY:\n";
    std::cout << "  - O(n^2) Algorithms       : Bubble, Selection, Insertion Sort (steep quadratic growth)\n";
    std::cout << "  - O(n log n) Algorithms   : Quick Sort, Merge Sort (sub-millisecond scaling)\n";
    std::cout << "  - Distribution Sort O(n+k): Bucket Sort (linear-like speed for uniform keys)\n";
    std::cout << "=========================================================================================================\n";

    return 0;
}
