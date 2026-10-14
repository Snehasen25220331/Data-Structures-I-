# Lab Sheet 7: Data Compression & File Optimization

**Student Name**: Sneha Sen  
**Student UID / Roll No**: CU25220331 / 25220331  
**GitHub**: [@Snehasen25220331](https://github.com/Snehasen25220331)  
**Course**: Data Structures & Algorithms I (Semester III)  
**Faculty Repository**: [aradhyacse/Data-Structures-I-](https://github.com/aradhyacse/Data-Structures-I-)  

---

## Syllabus Reference: Unit 7 (Lab Manual)
**Target Concepts**: Huffman Tree builds, greedy merge patterns.

---

## Objectives
Apply binary tree properties to practical optimization problems like file size reduction and data merge patterns.

---

## Tasks Overview

### Task 1: Huffman Encoding Engine
- Accept a set of characters and their frequencies.
- Continually combine the lowest-frequency node pairs into a binary tree structure using a Min-Heap (Priority Queue).
- Generate variable-length prefix codes (0 for left branch, 1 for right branch).
- Display character-frequency-codebook table and calculate storage space savings.
- Demonstrate bitstream encoding and decoding back to original text.

### Task 2: Optimal Merge Pattern Simulation
- Accept various file sizes.
- Design an optimal merge sequence that minimizes the total number of element moves using a Greedy Min-Heap strategy.
- Display step-by-step trace showing pair of merged files, step merge cost, and cumulative move operations.

---

## File Structure

| File | Language | Description | Time Complexity |
| :--- | :--- | :--- | :--- |
| `labsheet7_SnehaSen.py` | Python 3 | Complete unified implementation for Task 1 and Task 2 | $O(n \log n)$ |
| `task1_huffman_encoding.cpp` | C++17 | Huffman tree builder, codebook generator, and bitstream encoder/decoder | $O(n \log n)$ |
| `task2_optimal_merge_patterns.cpp` | C++17 | 2-way file merge simulation minimizing total record move operations | $O(n \log n)$ |

---

## How to Run

### Python:
```bash
python3 labsheet7_SnehaSen.py
```

### C++:
```bash
# Task 1: Huffman Encoding Engine
clang++ -std=c++17 -O2 task1_huffman_encoding.cpp -o huffman && ./huffman

# Task 2: Optimal Merge Patterns
clang++ -std=c++17 -O2 task2_optimal_merge_patterns.cpp -o merge_sim && ./merge_sim
```
