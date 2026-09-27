# Lab Assignment 1: Time Complexity Analysis

## Part A: Programming Exercises

### Objectives
1. Implement **Linear Search** to find a target value in an array. Measure and log execution time in microseconds for $n = 10,000$, $50,000$, and $100,000$ to demonstrate $O(n)$ behavior.
2. Implement **Binary Search** on a pre-sorted array. Measure and log execution times for identical data sizes ($n = 10,000$, $50,000$, and $100,000$) to contrast $O(\log n)$ efficiency against linear search.
3. Create a program containing **two nested loops** (bubble comparison loop / matrix operation). Record performance drop-offs as data size scales upward to demonstrate $O(n^2)$ behavior.

---

## File Structure

| File | Description | Complexity |
| :--- | :--- | :--- |
| `task1_linear_search.cpp` | Linear Search with timing in microseconds for $n \in \{10k, 50k, 100k\}$ | Best: $O(1)$, Worst/Avg: $O(n)$ |
| `task2_binary_search.cpp` | Binary Search contrasted directly with Linear Search on identical arrays | $O(\log n)$ vs $O(n)$ |
| `task3_quadratic_behavior.cpp` | Nested comparison loops showing quadratic growth and ratio scaling | $O(n^2)$ |

---

## How to Compile and Run

### Task 1: Linear Search
```bash
clang++ -std=c++17 -O2 task1_linear_search.cpp -o task1
./task1
```

### Task 2: Binary Search vs Linear Search
```bash
clang++ -std=c++17 -O2 task2_binary_search.cpp -o task2
./task2
```

### Task 3: Quadratic $O(n^2)$ Behavior
```bash
clang++ -std=c++17 -O2 task3_quadratic_behavior.cpp -o task3
./task3
```

---

## Key Observations & Conclusions
- **Linear Search**: Checks each element sequentially. Worst-case execution time grows proportionally to $n$ ($T(n)/n \approx \text{constant}$).
- **Binary Search**: Halves the search space each step. For $n = 100,000$, it takes at most **17 comparisons** (achieving over **1600x speedup** compared to Linear Search).
- **Nested Loops $O(n^2)$**: When input size $n$ doubles, the number of operations quadruples ($4\times$), leading to steep performance degradation for larger inputs.
