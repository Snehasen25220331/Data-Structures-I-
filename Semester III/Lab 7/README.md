# Lab Sheet 7: Data Compression & File Optimization

## Syllabus Reference: Unit 7 (Lab Manual)
**Target Concepts**: Huffman Tree builds, greedy merge patterns.

---

## Objectives
Apply binary tree properties to practical optimization problems like file size reduction and data merge patterns.

---

## File Structure

| File | Description | Complexity | Key Concept |
| :--- | :--- | :--- | :--- |
| `task1_huffman_encoding.cpp` | Greedy Huffman tree builder, codebook generator, and bitstream encoder/decoder | $O(n \log n)$ | Variable-length prefix codes, min-heap |
| `task2_optimal_merge_patterns.cpp` | Optimal 2-way file merge simulation minimizing total record move operations | $O(n \log n)$ | Greedy merge tree, cumulative move cost |

---

## How to Compile and Run

```bash
# Task 1: Huffman Encoding Engine
clang++ -std=c++17 -O2 task1_huffman_encoding.cpp -o huffman && ./huffman

# Task 2: Optimal Merge Patterns
clang++ -std=c++17 -O2 task2_optimal_merge_patterns.cpp -o merge_sim && ./merge_sim
```
