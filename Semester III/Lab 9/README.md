# Lab Sheet 9: Heaps, Heap Sort & Sorting Benchmarks

## Syllabus Reference: Unit 9 (Lab Manual)
**Target Concepts**: Array-backed structural heaps, sorting algorithms.

---

## Objectives
Understand structural priorities through binary heap properties and benchmark various classic sorting styles.

---

## File Structure

| File | Description | Complexity |
| :--- | :--- | :--- |
| `task1_heap_factory.cpp` | Array-backed Min Heap & Max Heap with explicit `bubble-up` and `bubble-down` step traces | Insert / Extract: $O(\log n)$, Peek: $O(1)$ |
| `task2_heap_sort.cpp` | Bottom-up $O(n)$ build-heap + in-place root extraction sorting with step-by-step trace | Time: $O(n \log n)$, Space: $O(1)$ |
| `task3_sorting_comparison.cpp` | Benchmark framework for Linear & Binary Search + Bubble, Selection, Insertion, Quick, Merge, and Bucket Sort | $O(n^2)$ vs $O(n \log n)$ vs $O(n + k)$ |

---

## Algorithms Summary

### 1. Heap Factory (`task1_heap_factory.cpp`)
- **Min-Heap Property**: $A[\text{parent}(i)] \le A[i]$. Root stores the minimum element.
- **Max-Heap Property**: $A[\text{parent}(i)] \ge A[i]$. Root stores the maximum element.
- Explicit traces demonstrate how elements bubble up during insertion and bubble down after extracting the root.

### 2. Heap Sort (`task2_heap_sort.cpp`)
1. **Build-Heap**: Bottom-up construction starting from index $\lfloor n/2 \rfloor - 1$ down to 0 in $O(n)$ time.
2. **Sorting Loop**: Swaps `arr[0]` with `arr[i]`, reduces heap size, and calls sift-down on root.

### 3. Benchmark Comparison (`task3_sorting_comparison.cpp`)
Profiles execution times on identical uniformly distributed datasets ($n = 1k, 5k, 10k, 20k$):
- **$O(n^2)$ Family**: Bubble Sort, Selection Sort, Insertion Sort
- **$O(n \log n)$ Family**: Quick Sort, Merge Sort
- **Distribution Sort $O(n + k)$**: Bucket Sort

---

## How to Compile and Run

### Task 1: Heap Factory
```bash
clang++ -std=c++17 -O2 task1_heap_factory.cpp -o heap_factory
./heap_factory
```

### Task 2: Heap Sort
```bash
clang++ -std=c++17 -O2 task2_heap_sort.cpp -o heap_sort
./heap_sort
```

### Task 3: Sorting Comparison Framework
```bash
clang++ -std=c++17 -O2 task3_sorting_comparison.cpp -o sort_benchmark
./sort_benchmark
```
