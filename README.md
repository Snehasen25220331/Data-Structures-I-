# Data Structures & Algorithms I - Comprehensive Lab Portfolio

**Student GitHub**: [Snehasen25220331](https://github.com/Snehasen25220331)  
**Student Repository**: [dsa-labsheet-](https://github.com/Snehasen25220331/dsa-labsheet-)  
**Course Repository**: [aradhyacse/Data-Structures-I-](https://github.com/aradhyacse/Data-Structures-I-)  
**Pull Request**: [Submission PR #1](https://github.com/aradhyacse/Data-Structures-I-/pull/1)

---

## Repository Overview

This repository contains the complete, tested, and benchmarked C++ implementations for the entire Data Structures & Algorithms I laboratory curriculum (Units 1 through 10). Each lab assignment is organized into its own dedicated directory matching the university semester structure.

```
.
├── README.md                                          <- Project Documentation & Setup Guide
├── push_to_github.sh                                  <- GitHub automated push script
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
    ├── Lab 4/                                         <- Stacks and Queues
    │   ├── task1_static_array_stack.cpp               <- Static Array Stack (push, pop, peek, overflow)
    │   ├── task2_linked_list_stack.cpp                <- Dynamic Pointer-Linked Stack
    │   ├── task3_circular_array_queue.cpp             <- Circular Array Queue (modulo wrap-around)
    │   ├── task4_linked_list_queue.cpp                <- Dynamic Pointer-Linked Queue (Front & Rear)
    │   └── README.md
    │
    ├── Lab 5/                                         <- Expression Conversion & Evaluation
    │   ├── task1_infix_to_postfix.cpp                 <- Shunting-Yard Infix to Postfix with step trace
    │   ├── task2_postfix_evaluation.cpp               <- Postfix Evaluation using Integer Stack
    │   └── README.md
    │
    ├── Lab 6/                                         <- Binary Tree Structures & Traversals
    │   ├── task1_tree_construction_and_traversals.cpp <- Dynamic Tree + Recursive & Iterative In/Pre/Post
    │   └── README.md
    │
    ├── Lab 7/                                         <- Data Compression & File Optimization
    │   ├── task1_huffman_encoding.cpp                 <- Huffman Variable-Length Prefix Code Tree Engine
    │   ├── task2_optimal_merge_patterns.cpp           <- Optimal 2-Way Merge Simulation minimizing moves
    │   └── README.md
    │
    ├── Lab 8/                                         <- Self-Balancing & Multi-way Search Trees
    │   ├── task1_bst_operations.cpp                   <- BST Element Insertion and Ordered Deletion
    │   ├── task2_avl_tree_rotations.cpp               <- AVL Self-Balancing (LL, RR, LR, RL transformations)
    │   ├── task3_btree_insertion_simulator.cpp        <- Order-3 (M=3) B-Tree Node Overflow & Splitting
    │   ├── task4_insertion_and_bucket_sort.cpp        <- Insertion Sort and Bucket Sort Step Traces
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
- **Task 1**: Linear Search on sizes $n \in \{10k, 50k, 100k\}$. Proves $O(n)$ behavior with constant $T(n)/n$ ratios.
- **Task 2**: Binary Search on pre-sorted array contrasted with Linear Search ($n = 100k$ in 17 comparisons vs 100,000, $>1600\times$ speedup).
- **Task 3**: Nested comparison loops demonstrating $O(n^2)$ quadratic growth (doubling $n$ quadruples execution time).

### 📘 Lab 2: Basic Array Operations
- **`array_database.cpp`**: Array-backed database program prompting user for:
  1. Insert at index $[0, \text{size}]$ (shifts trailing right).
  2. Delete from index $[0, \text{size}-1]$ (shifts trailing left).
  3. Sequential search returning first match index and comparison metrics.
  4. Built-in `--demo` verification suite.

### 📘 Lab 3: Singly and Doubly Linked Lists
- **Task 1**: Custom dynamic Singly Linked List (SLL) supporting head, tail, and index insertion, deletion by target key, and forward live link traversal.
- **Task 2**: Custom Doubly Linked List (DLL) maintaining forward and backward pointers, pointer re-linking on deletion, and reverse traversal from tail to head.

### 📘 Lab 4: Stacks and Queues
- **Task 1**: Static Array Stack ADT with `push()`, `pop()`, `peek()`, and `display()`.
- **Task 2**: Dynamic pointer-linked Node Stack with dynamic heap allocation and reclamation.
- **Task 3**: Structural Array Queue (Circular Queue using modulo arithmetic to prevent false overflow).
- **Task 4**: Dynamic pointer-linked Queue with front and rear pointers for $O(1)$ operations.

### 📘 Lab 5: Expression Conversion & Evaluation
- **Task 1**: Shunting-Yard Infix to Postfix converter using custom operator stack with operator precedence, associativity, and step-by-step trace.
- **Task 2**: Postfix Expression Evaluator using an integer stack computing final mathematical output.

### 📘 Lab 6: Binary Tree Structures & Traversals
- **Task 1**: Tree instantiation tool mapping dynamic node elements with discrete left and right sub-pointers.
- **Traversals**: Structural tree parsing executing Inorder, Preorder, and Postorder in both:
  - Clean **recursive framework**
  - Manual **stack-driven iterative framework** with exact output match verification.

### 📘 Lab 7: Data Compression & File Optimization
- **Task 1**: Huffman Encoding Engine using min-heap priority queue, building variable-length prefix code trees, and encoding/decoding bitstreams.
- **Task 2**: Optimal Merge Pattern Simulation minimizing total element move operations through greedy 2-way merge trees.

### 📘 Lab 8: Self-Balancing & Multi-way Search Trees
- **Task 1**: Standard Binary Search Tree (BST) supporting element insertion and ordered deletion (0, 1, or 2 children via in-order successor).
- **Task 2**: AVL Tree tracker monitoring balance factors and executing single (LL, RR) or double (LR, RL) rotations.
- **Task 3**: Order-3 ($M=3$) B-Tree node simulator managing insertions and node splitting upon overflow.
- **Task 4**: Insertion Sort ($O(n^2)$) and Bucket Sort ($O(n+k)$) step-by-step trace and comparison.

### 📘 Lab 9: Heaps, Heap Sort & Sorting Benchmarks
- **Task 1**: Array-backed Min Heap and Max Heap layouts with explicit bubble-up and bubble-down adjustment traces.
- **Task 2**: In-place Heap Sort using bottom-up $O(n)$ build-heap and repeated root extraction.
- **Task 3**: Comprehensive sorting framework comparing Linear/Binary search + Bubble, Selection, Insertion, Quick, Merge, and Bucket Sort on uniform datasets.

### 📘 Lab 10: Hashing Maps & Graph Traversals
- **Task 1**: Collision Resolution Framework: Open Hashing (separate chaining) and Closed Hashing (linear probing with automatic rehashing at $\alpha \ge 0.70$).
- **Task 2**: Network Graph mapped via Adjacency Matrix and Adjacency List; step traces for BFS (queue) and DFS (stack/recursion).
- **Task 3**: Minimum Cost Spanning Tree (MST) computation using both Kruskal's (DSU) and Prim's (Min-Heap) algorithms with cross-verified cost equivalence ($W = 14$).

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

# Lab 4
clang++ -std=c++17 -O2 "Semester III/Lab 4/task1_static_array_stack.cpp" -o stack_arr && ./stack_arr --demo
clang++ -std=c++17 -O2 "Semester III/Lab 4/task2_linked_list_stack.cpp" -o stack_ll && ./stack_ll --demo
clang++ -std=c++17 -O2 "Semester III/Lab 4/task3_circular_array_queue.cpp" -o queue_arr && ./queue_arr --demo
clang++ -std=c++17 -O2 "Semester III/Lab 4/task4_linked_list_queue.cpp" -o queue_ll && ./queue_ll --demo

# Lab 5
clang++ -std=c++17 -O2 "Semester III/Lab 5/task1_infix_to_postfix.cpp" -o infix2post && ./infix2post --demo
clang++ -std=c++17 -O2 "Semester III/Lab 5/task2_postfix_evaluation.cpp" -o eval_post && ./eval_post --demo

# Lab 6
clang++ -std=c++17 -O2 "Semester III/Lab 6/task1_tree_construction_and_traversals.cpp" -o tree_traversals && ./tree_traversals

# Lab 7
clang++ -std=c++17 -O2 "Semester III/Lab 7/task1_huffman_encoding.cpp" -o huffman && ./huffman
clang++ -std=c++17 -O2 "Semester III/Lab 7/task2_optimal_merge_patterns.cpp" -o merge_sim && ./merge_sim

# Lab 8
clang++ -std=c++17 -O2 "Semester III/Lab 8/task1_bst_operations.cpp" -o bst && ./bst
clang++ -std=c++17 -O2 "Semester III/Lab 8/task2_avl_tree_rotations.cpp" -o avl && ./avl
clang++ -std=c++17 -O2 "Semester III/Lab 8/task3_btree_insertion_simulator.cpp" -o btree && ./btree
clang++ -std=c++17 -O2 "Semester III/Lab 8/task4_insertion_and_bucket_sort.cpp" -o sort_demo && ./sort_demo

# Lab 9
clang++ -std=c++17 -O2 "Semester III/Lab 9/task1_heap_factory.cpp" -o heap_factory && ./heap_factory
clang++ -std=c++17 -O2 "Semester III/Lab 9/task2_heap_sort.cpp" -o heap_sort && ./heap_sort
clang++ -std=c++17 -O2 "Semester III/Lab 9/task3_sorting_comparison.cpp" -o sort_benchmark && ./sort_benchmark

# Lab 10
clang++ -std=c++17 -O2 "Semester III/Lab 10/task1_collision_resolution.cpp" -o hash_demo && ./hash_demo
clang++ -std=c++17 -O2 "Semester III/Lab 10/task2_graph_traversals.cpp" -o graph_demo && ./graph_demo
clang++ -std=c++17 -O2 "Semester III/Lab 10/task3_minimum_spanning_tree.cpp" -o mst_demo && ./mst_demo
```
