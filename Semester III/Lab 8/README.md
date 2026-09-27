# Lab Sheet 8: Self-Balancing & Multi-way Search Trees

## Syllabus Reference: Unit 8 (Lab Manual)
**Target Concepts**: BST constraints, balance factors, multi-way node insertion rules, comparison vs distribution sorting.

---

## Objectives
Implement search tracking constraints that maintain efficient search bounds under dynamic updates.

---

## File Structure

| File | Description | Complexity | Key Concept |
| :--- | :--- | :--- | :--- |
| `task1_bst_operations.cpp` | Standard Binary Search Tree supporting insertion, searching, and ordered deletion | Search/Insert/Delete: $O(h)$ | In-order successor deletion, BST invariant |
| `task2_avl_tree_rotations.cpp` | AVL self-balancing tree tracking balance factors with automatic rotations | Search/Insert: $O(\log n)$ | LL, RR, LR, RL single/double transformations |
| `task3_btree_insertion_simulator.cpp`| Order-3 ($M=3$) B-Tree node layout simulator handling overflow and splitting | Search/Insert: $O(\log n)$ | Multi-way search tree, median promotion, node splitting |
| `task4_insertion_and_bucket_sort.cpp`| Insertion Sort and Bucket Sort step-by-step algorithms | Insertion: $O(n^2)$, Bucket: $O(n+k)$ | Incremental shifting vs interval distribution |

---

## How to Compile and Run

```bash
# Task 1: BST Operations
clang++ -std=c++17 -O2 task1_bst_operations.cpp -o bst && ./bst

# Task 2: AVL Tree Rotations
clang++ -std=c++17 -O2 task2_avl_tree_rotations.cpp -o avl && ./avl

# Task 3: B-Tree Simulator
clang++ -std=c++17 -O2 task3_btree_insertion_simulator.cpp -o btree && ./btree

# Task 4: Insertion and Bucket Sort
clang++ -std=c++17 -O2 task4_insertion_and_bucket_sort.cpp -o sort_demo && ./sort_demo
```
