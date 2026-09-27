# Lab Assignment 4: Stacks and Queues

## Part A: Programming Exercises

### Objectives
1. Implement a **Stack ADT** using a static array framework with `push()`, `pop()`, and `display()`.
2. Rewrite the **Stack infrastructure** using a dynamic pointer-linked node allocation framework.
3. Implement a **Queue ADT** using a structural array setup (Circular Queue) with `enqueue()`, `dequeue()`, and `display()`.
4. Rewrite the **Queue infrastructure** using a dynamic pointer-linked node setup with front and rear pointers.

---

## File Structure

| File | Structure Type | Complexity | Characteristics |
| :--- | :--- | :--- | :--- |
| `task1_static_array_stack.cpp` | Static Array Stack | Push/Pop: $O(1)$ | Fixed capacity with overflow detection |
| `task2_linked_list_stack.cpp` | Linked List Stack | Push/Pop: $O(1)$ | Dynamic heap allocation, unbounded growth |
| `task3_circular_array_queue.cpp`| Circular Array Queue | Enqueue/Dequeue: $O(1)$ | Modulo wrap-around avoiding false overflow |
| `task4_linked_list_queue.cpp` | Linked List Queue | Enqueue/Dequeue: $O(1)$ | Front & Rear pointers for constant time operations |

---

## How to Compile and Run

```bash
# Task 1: Static Array Stack
clang++ -std=c++17 -O2 task1_static_array_stack.cpp -o stack_arr && ./stack_arr --demo

# Task 2: Linked List Stack
clang++ -std=c++17 -O2 task2_linked_list_stack.cpp -o stack_ll && ./stack_ll --demo

# Task 3: Circular Array Queue
clang++ -std=c++17 -O2 task3_circular_array_queue.cpp -o queue_arr && ./queue_arr --demo

# Task 4: Linked List Queue
clang++ -std=c++17 -O2 task4_linked_list_queue.cpp -o queue_ll && ./queue_ll --demo
```
