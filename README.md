# Data Structures & Algorithms I - Lab Assignments

**Student GitHub**: [Snehasen25220331](https://github.com/Snehasen25220331)  
**Student Repository**: [dsa-labsheet-](https://github.com/Snehasen25220331/dsa-labsheet-)  
**Course Repository**: [aradhyacse/Data-Structures-I-](https://github.com/aradhyacse/Data-Structures-I-)  

---

## Repository Overview

This repository contains the complete, verified, and benchmarked C++ implementations for the Data Structures I laboratory curriculum. Each lab assignment is organized into its own dedicated directory matching the semester structure.

```
.
├── README.md                                          <- Project Documentation & Setup Guide
└── Semester III/
    ├── Lab 1/                                         <- Time Complexity Analysis
    │   ├── task1_linear_search.cpp                    <- Linear Search O(n) with microsecond timing
    │   ├── task2_binary_search.cpp                    <- Binary Search O(log n) vs Linear Search
    │   ├── task3_quadratic_behavior.cpp               <- Nested Loops O(n^2) Scaling & Drop-offs
    │   ├── Add.cpp                                    <- Reference Program
    │   └── README.md
    │
    ├── Lab 2/                                         <- Basic Array Operations
    │   ├── array_database.cpp                         <- Array-backed database (Insert, Delete, Search)
    │   └── README.md
    │
    ├── Lab 3/                                         <- Singly & Doubly Linked Lists
    │   ├── task1_singly_linked_list.cpp               <- Dynamic SLL (Head/Tail/Index Insert, Key Delete)
    │   ├── task2_doubly_linked_list.cpp               <- DLL with Bidirectional Traversal & Re-linking
    │   └── README.md
    │
    ├── Lab 9/                                         <- Heaps, Heap Sort & Sorting Benchmarks
    │   ├── task1_heap_factory.cpp                     <- Array-backed Min/Max Heap with Bubble Up/Down
    │   ├── task2_heap_sort.cpp                        <- O(n) Build-Heap & Root Extraction In-Place Sort
    │   ├── task3_sorting_comparison.cpp               <- Benchmark for 6 Sorts + Linear/Binary Search
    │   └── README.md
    │
    └── Lab 10/                                        <- Hashing Maps & Graph Traversals
        ├── task1_collision_resolution.cpp             <- Open Hashing (Chaining) & Closed Hashing (Rehash)
        ├── task2_graph_traversals.cpp                 <- Matrix & List Representations, BFS & DFS Traces
        ├── task3_minimum_spanning_tree.cpp            <- Kruskal's (DSU) & Prim's (Min-Heap) MST
        └── README.md
```

---

## Detailed Lab Breakdown

### 📘 Lab 1: Time Complexity Analysis
- **Task 1 (`task1_linear_search.cpp`)**: Evaluates Linear Search on sizes $n \in \{10k, 50k, 100k\}$. Proves $O(n)$ worst-case complexity by showing constant $T(n)/n$ ratios.
- **Task 2 (`task2_binary_search.cpp`)**: Contrasts Binary Search on sorted data against Linear Search. For $n = 100,000$, Binary Search requires only **17 comparisons** (achieving up to **1600x speedup**).
- **Task 3 (`task3_quadratic_behavior.cpp`)**: Demonstrates nested loop $O(n^2)$ behavior. Doubling $n$ yields a $4\times$ execution time increase, illustrating performance drop-offs.

### 📘 Lab 2: Basic Array Operations
- **`array_database.cpp`**: Interactive array database program supporting:
  1. Insertion at valid index $[0, \text{size}]$ with right-shifting of trailing elements and dynamic buffer resizing.
  2. Deletion at valid index $[0, \text{size}-1]$ with left-shifting of trailing elements to close gaps.
  3. Sequential search returning the first index match and comparison metrics.
  4. Built-in `--demo` self-test suite.

### 📘 Lab 3: Singly and Doubly Linked Lists
- **Task 1 (`task1_singly_linked_list.cpp`)**: Custom dynamic Singly Linked List (SLL) supporting head/tail/index insertions, deletion by matching data key, and live link traversal.
- **Task 2 (`task2_doubly_linked_list.cpp`)**: Custom Doubly Linked List (DLL) maintaining dual `prev` and `next` pointers, safe pointer re-linking during deletion, and bidirectional (forward & reverse) traversals.

### 📘 Lab 9: Heaps, Heap Sort & Sorting Benchmarks
- **Task 1 (`task1_heap_factory.cpp`)**: Array-backed Min Heap and Max Heap layouts with explicit step-by-step traces for `bubble-up` (sift-up) and `bubble-down` (sift-down).
- **Task 2 (`task2_heap_sort.cpp`)**: Converts arbitrary arrays into a Max Heap in $O(n)$ time and executes in-place sorting by repeatedly extracting root elements.
- **Task 3 (`task3_sorting_comparison.cpp`)**: Profiling framework comparing:
  - **Searching**: Linear Search vs Binary Search.
  - **Quadratic Sorts ($O(n^2)$)**: Bubble Sort, Selection Sort, Insertion Sort.
  - **Log-Linear Sorts ($O(n \log n)$)**: Quick Sort, Merge Sort.
  - **Distribution Sorts ($O(n + k)$)**: Bucket Sort.

### 📘 Lab 10: Hashing Maps & Graph Traversals
- **Task 1 (`task1_collision_resolution.cpp`)**:
  - *Open Hashing*: Dynamic separate chaining using linked lists for bucket collision handling.
  - *Closed Hashing*: Linear probing with automatic rehashing and table resizing to the next prime when load factor $\alpha \ge 0.70$.
- **Task 2 (`task2_graph_traversals.cpp`)**: Network graph modeled using both **Adjacency Matrix** and **Adjacency List**. Provides step traces for **Breadth-First Search (BFS)** and **Depth-First Search (DFS)**.
- **Task 3 (`task3_minimum_spanning_tree.cpp`)**: Minimum Cost Spanning Tree (MST) computation using:
  - *Kruskal's Algorithm* (Disjoint Set Union with Path Compression and Union-by-Rank).
  - *Prim's Algorithm* (Priority Queue / Min-Heap greedy cut approach).
  - Cross-verifies identical minimal cost across both algorithms ($W = 14$).

---

## Compilation & Execution Guide

All programs are written in modern standard C++ (C++17) with zero external dependencies.

```bash
# Lab 1
clang++ -std=c++17 -O2 "Semester III/Lab 1/task1_linear_search.cpp" -o task1 && ./task1
clang++ -std=c++17 -O2 "Semester III/Lab 1/task2_binary_search.cpp" -o task2 && ./task2
clang++ -std=c++17 -O2 "Semester III/Lab 1/task3_quadratic_behavior.cpp" -o task3 && ./task3

# Lab 2
clang++ -std=c++17 -O2 "Semester III/Lab 2/array_database.cpp" -o array_db && ./array_db --demo

# Lab 3
clang++ -std=c++17 -O2 "Semester III/Lab 3/task1_singly_linked_list.cpp" -o sll && ./sll --demo
clang++ -std=c++17 -O2 "Semester III/Lab 3/task2_doubly_linked_list.cpp" -o dll && ./dll --demo

# Lab 9
clang++ -std=c++17 -O2 "Semester III/Lab 9/task1_heap_factory.cpp" -o heap_factory && ./heap_factory
clang++ -std=c++17 -O2 "Semester III/Lab 9/task2_heap_sort.cpp" -o heap_sort && ./heap_sort
clang++ -std=c++17 -O2 "Semester III/Lab 9/task3_sorting_comparison.cpp" -o sort_benchmark && ./sort_benchmark

# Lab 10
clang++ -std=c++17 -O2 "Semester III/Lab 10/task1_collision_resolution.cpp" -o hash_demo && ./hash_demo
clang++ -std=c++17 -O2 "Semester III/Lab 10/task2_graph_traversals.cpp" -o graph_demo && ./graph_demo
clang++ -std=c++17 -O2 "Semester III/Lab 10/task3_minimum_spanning_tree.cpp" -o mst_demo && ./mst_demo
```

---

## Git & GitHub Submission Workflow

### 1. Pushing to Your GitHub Repository
Your local repository is pre-configured with:
- **`origin`**: `https://github.com/Snehasen25220331/dsa-labsheet-.git`
- **`upstream`**: `https://github.com/aradhyacse/Data-Structures-I-.git`

To push the committed lab codes to your GitHub repository:
```bash
git push -u origin main
```
*(If prompted, enter your GitHub Username and Personal Access Token (PAT) with `repo` scope).*

### 2. Submitting to Your Teacher's Repository
1. Visit your repository on GitHub: [Snehasen25220331/dsa-labsheet-](https://github.com/Snehasen25220331/dsa-labsheet-)
2. Click on **Contribute** -> **Open Pull Request** (or visit [aradhyacse/Data-Structures-I- Pull Requests](https://github.com/aradhyacse/Data-Structures-I-/pulls)).
3. Base repository: `aradhyacse/Data-Structures-I-` (branch: `main`).
4. Head repository: `Snehasen25220331/dsa-labsheet-` (branch: `main`).
5. Set PR Title: `Submission: Data Structures I Lab Assignments (Labs 1, 2, 3, 9, 10) - Sneha Sen`
6. Click **Create Pull Request** to submit your work directly to your teacher.
