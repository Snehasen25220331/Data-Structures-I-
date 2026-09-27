# Lab Assignment 3: Singly and Doubly Linked Lists

## Part A: Programming Exercises

### Objectives
1. **Singly Linked List (SLL)**:
   - Dynamic node generation and entry insertion (at head, tail, or specified index position).
   - Node deletion using a matching target data key.
   - Forward list traversal printing all live data links.
2. **Doubly Linked List (DLL)**:
   - Node insertion maintaining both forward (`next`) and backward (`prev`) pointers.
   - Node deletion with proper pointer re-linking.
   - Reverse traversal printing nodes from tail back to head.

---

## File Structure

| File | Description | Complexity |
| :--- | :--- | :--- |
| `task1_singly_linked_list.cpp` | Complete custom SLL with head/tail/index insertion, key deletion, and forward traversal | Insert Head/Tail: $O(1)$, Insert Index: $O(n)$, Delete: $O(n)$ |
| `task2_doubly_linked_list.cpp` | Complete custom DLL with dual-pointer insertion, bidirectional traversal, and pointer re-linking | Insert Head/Tail: $O(1)$, Insert Index: $O(n)$, Delete: $O(n)$ |

---

## Pointer Re-Linking Mechanism in DLL
When deleting node `curr`:
- **Predecessor Link**:
  ```cpp
  if (curr->prev != nullptr) {
      curr->prev->next = curr->next;
  } else {
      head = curr->next; // Deleting head
  }
  ```
- **Successor Link**:
  ```cpp
  if (curr->next != nullptr) {
      curr->next->prev = curr->prev;
  } else {
      tail = curr->prev; // Deleting tail
  }
  ```

---

## How to Compile and Run

### Task 1: Singly Linked List
```bash
clang++ -std=c++17 -O2 task1_singly_linked_list.cpp -o sll
./sll            # Interactive Menu
./sll --demo     # Automated Test Suite
```

### Task 2: Doubly Linked List
```bash
clang++ -std=c++17 -O2 task2_doubly_linked_list.cpp -o dll
./dll            # Interactive Menu
./dll --demo     # Automated Test Suite
```
