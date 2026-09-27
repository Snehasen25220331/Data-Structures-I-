# Lab Sheet 10: Hashing Maps & Graph Traversals

## Syllabus Reference: Unit 10 (Lab Manual)
**Target Concepts**: Hashing, graph configurations, shortest path routing, minimum spanning trees.

---

## Objectives
Map direct key-value associations and model network configurations using graph optimization algorithms.

---

## File Structure

| File | Description | Complexity |
| :--- | :--- | :--- |
| `task1_collision_resolution.cpp` | Open Hashing (separate chaining) and Closed Hashing (linear probing with automatic resizing/rehashing at $\alpha \ge 0.70$) | Search/Insert: $O(1)$ average, $O(n)$ worst |
| `task2_graph_traversals.cpp` | Network graphs mapped via Adjacency Matrix and Adjacency List; step traces for BFS and DFS | Time: $O(V + E)$, Space: $O(V)$ |
| `task3_minimum_spanning_tree.cpp` | Minimum Cost Spanning Tree using both Kruskal's (DSU) and Prim's (Min-Heap) algorithms with cost verification | Kruskal: $O(E \log E)$, Prim: $O(E \log V)$ |

---

## Detailed Task Breakdown

### 1. Collision Resolution Framework (`task1_collision_resolution.cpp`)
- **Open Hashing**:
  - Employs linked list chains for collision handling.
  - Bucket arrays dynamically chain multiple keys colliding at the same modulo index.
- **Closed Hashing**:
  - Implements Linear Probing with state markers (`EMPTY`, `OCCUPIED`, `DELETED` / tombstone).
  - Automatically triggers **Rehashing** when load factor $\alpha \ge 0.70$, expanding table size to the next prime $> 2 \times \text{capacity}$.

### 2. Graph Traversals (`task2_graph_traversals.cpp`)
- **Adjacency Matrix**: $V \times V$ binary matrix for $O(1)$ edge existence checks.
- **Adjacency List**: Array of vectors for space-efficient sparse network representations.
- **BFS**: Uses queue to explore level-by-level (computes shortest paths on unweighted graphs).
- **DFS**: Uses recursion/stack to explore down each branch before backtracking.

### 3. Minimum Cost Spanning Tree (`task3_minimum_spanning_tree.cpp`)
- **Kruskal's Algorithm**:
  - Sorts all edges by weight.
  - Utilizes Disjoint Set Union (DSU) with Path Compression and Union-by-Rank to detect and reject cycles.
- **Prim's Algorithm**:
  - Starts from vertex 0 and uses a priority queue (min-heap) to select the minimum cut edge connecting visited vertices to unvisited vertices.
- **Cross-Verification**: Confirms both algorithms independently derive the exact same minimal spanning weight ($W = 14$ for $V = 6$, selecting $V-1 = 5$ edges).

---

## How to Compile and Run

### Task 1: Collision Resolution Framework
```bash
clang++ -std=c++17 -O2 task1_collision_resolution.cpp -o hash_demo
./hash_demo
```

### Task 2: Graph Traversals (BFS & DFS)
```bash
clang++ -std=c++17 -O2 task2_graph_traversals.cpp -o graph_demo
./graph_demo
```

### Task 3: Minimum Cost Spanning Tree (Kruskal & Prim)
```bash
clang++ -std=c++17 -O2 task3_minimum_spanning_tree.cpp -o mst_demo
./mst_demo
```
