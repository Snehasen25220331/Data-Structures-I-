# Lab Assignment 2: Basic Array Operations

## Part A: Programming Exercises

### Objectives
Implement an array-backed database program that prompts a user for structural actions:
1. **Insert a numeric element** at a specified valid index location (shifting trailing entries right).
2. **Delete an element** from a target index location (shifting trailing entries left to close gaps).
3. **Search the array sequentially** to return the first index match of a specific value.

---

## File Structure

| File | Description | Complexity |
| :--- | :--- | :--- |
| `array_database.cpp` | Complete interactive CLI array database with bounds validation, dynamic expansion, shift operations, sequential search, and self-test demo mode | Insert/Delete: $O(n)$, Search: $O(n)$, Access: $O(1)$ |

---

## Features & Implementation Details
- **Insertion (`insertAt`)**:
  - Validates index in range $[0, \text{size}]$.
  - Dynamically resizes the underlying array buffer if capacity is reached.
  - Shifts all trailing elements right by one slot to make room:
    $$\text{arr}[i] = \text{arr}[i-1] \quad \text{for } i \in [\text{size}, \text{index}+1]$$
- **Deletion (`deleteAt`)**:
  - Validates index in range $[0, \text{size}-1]$.
  - Records deleted element.
  - Shifts all subsequent elements left by one slot to close the gap:
    $$\text{arr}[i] = \text{arr}[i+1] \quad \text{for } i \in [\text{index}, \text{size}-2]$$
- **Sequential Search (`searchSequential`)**:
  - Scans from index $0$ to $\text{size}-1$.
  - Returns the index of the first occurrence and logs comparison count.

---

## How to Compile and Run

### Interactive Mode:
```bash
clang++ -std=c++17 -O2 array_database.cpp -o array_database
./array_database
```

### Automated Self-Test Demo:
```bash
./array_database --demo
```
