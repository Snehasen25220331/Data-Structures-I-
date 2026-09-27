/**
 * LAB SHEET 10 - Task 3: Minimum Cost Spanning Tree (MST)
 * 
 * Objective:
 * Write code to compute the minimum spanning tree of a weighted graph using
 * both Kruskal's and Prim's algorithms.
 * 
 * Theory:
 * An MST of a connected, undirected weighted graph is a spanning tree whose
 * total edge weight is minimized. For V vertices, any MST has exactly V - 1 edges.
 * 
 * 1. Kruskal's Algorithm:
 *    - Edge-centric greedy approach.
 *    - Uses Disjoint Set Union (DSU) with Union-by-Rank and Path Compression.
 *    - Time Complexity: O(E log E) or O(E log V).
 * 
 * 2. Prim's Algorithm:
 *    - Vertex-centric greedy approach.
 *    - Uses Min-Heap (Priority Queue) to pick minimum incident cut-edge.
 *    - Time Complexity: O(E log V) with binary heap.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <string>

// ============================================================================
// DATA STRUCTURES & DSU
// ============================================================================
struct Edge {
    int u;
    int v;
    int weight;

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class DSU {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    explicit DSU(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    bool unionSets(int i, int j) {
        int rootI = find(i);
        int rootJ = find(j);
        if (rootI == rootJ) return false; // Cycle detected

        // Union by rank
        if (rank[rootI] < rank[rootJ]) {
            parent[rootI] = rootJ;
        } else if (rank[rootI] > rank[rootJ]) {
            parent[rootJ] = rootI;
        } else {
            parent[rootJ] = rootI;
            ++rank[rootI];
        }
        return true;
    }
};

// ============================================================================
// KRUSKAL'S ALGORITHM
// ============================================================================
int runKruskalMST(int numVertices, std::vector<Edge> edges, 
                  const std::vector<std::string>& nodeNames, 
                  std::vector<Edge>& mstEdges) {
    mstEdges.clear();
    std::sort(edges.begin(), edges.end()); // Sort edges in ascending order of weight

    DSU dsu(numVertices);
    int totalCost = 0;

    std::cout << "\n--- KRUSKAL'S ALGORITHM STEP-BY-STEP TRACE ---\n";
    std::cout << std::left 
              << std::setw(8) << "Edge" 
              << std::setw(10) << "Weight" 
              << std::setw(14) << "Forms Cycle?" 
              << std::setw(15) << "Action" 
              << "\n";
    std::cout << "----------------------------------------------\n";

    for (const auto& edge : edges) {
        std::string edgeName = "(" + nodeNames[edge.u] + " - " + nodeNames[edge.v] + ")";
        int rootU = dsu.find(edge.u);
        int rootV = dsu.find(edge.v);

        if (rootU != rootV) {
            dsu.unionSets(rootU, rootV);
            mstEdges.push_back(edge);
            totalCost += edge.weight;

            std::cout << std::left 
                      << std::setw(8) << edgeName 
                      << std::setw(10) << edge.weight 
                      << std::setw(14) << "No" 
                      << std::setw(15) << "ACCEPTED" 
                      << "\n";

            if (static_cast<int>(mstEdges.size()) == numVertices - 1) {
                break; // MST completed
            }
        } else {
            std::cout << std::left 
                      << std::setw(8) << edgeName 
                      << std::setw(10) << edge.weight 
                      << std::setw(14) << "Yes (Cycle)" 
                      << std::setw(15) << "REJECTED" 
                      << "\n";
        }
    }

    std::cout << "----------------------------------------------\n";
    std::cout << "Kruskal's Total MST Cost = " << totalCost << "\n";
    return totalCost;
}

// ============================================================================
// PRIM'S ALGORITHM
// ============================================================================
struct PrimEdge {
    int weight;
    int from;
    int to;

    bool operator>(const PrimEdge& other) const {
        return weight > other.weight; // Min-heap comparator
    }
};

int runPrimMST(int numVertices, 
               const std::vector<std::vector<std::pair<int, int>>>& adjList, 
               const std::vector<std::string>& nodeNames, 
               std::vector<Edge>& mstEdges) {
    mstEdges.clear();
    std::vector<bool> inMST(numVertices, false);
    std::priority_queue<PrimEdge, std::vector<PrimEdge>, std::greater<PrimEdge>> pq;

    int totalCost = 0;
    int startNode = 0;

    std::cout << "\n--- PRIM'S ALGORITHM STEP-BY-STEP TRACE ---\n";
    std::cout << "Starting from initial vertex [" << nodeNames[startNode] << "]\n";
    std::cout << std::left 
              << std::setw(8) << "Edge" 
              << std::setw(10) << "Weight" 
              << std::setw(20) << "Connected Vertex" 
              << "\n";
    std::cout << "----------------------------------------------\n";

    inMST[startNode] = true;
    for (const auto& neighbor : adjList[startNode]) {
        pq.push({neighbor.second, startNode, neighbor.first});
    }

    while (!pq.empty() && static_cast<int>(mstEdges.size()) < numVertices - 1) {
        PrimEdge current = pq.top();
        pq.pop();

        int u = current.from;
        int v = current.to;
        int w = current.weight;

        if (inMST[v]) continue; // Already part of MST

        inMST[v] = true;
        mstEdges.push_back({u, v, w});
        totalCost += w;

        std::string edgeName = "(" + nodeNames[u] + " - " + nodeNames[v] + ")";
        std::cout << std::left 
                  << std::setw(8) << edgeName 
                  << std::setw(10) << w 
                  << std::setw(20) << ("Added " + nodeNames[v] + " to MST") 
                  << "\n";

        for (const auto& neighbor : adjList[v]) {
            if (!inMST[neighbor.first]) {
                pq.push({neighbor.second, v, neighbor.first});
            }
        }
    }

    std::cout << "----------------------------------------------\n";
    std::cout << "Prim's Total MST Cost = " << totalCost << "\n";
    return totalCost;
}

int main() {
    std::cout << "====================================================================\n";
    std::cout << "     LAB 10 - TASK 3: MINIMUM SPANNING TREE (KRUSKAL vs PRIM)       \n";
    std::cout << "====================================================================\n\n";

    // Setup network of 6 nodes: A, B, C, D, E, F
    int V = 6;
    std::vector<std::string> nodeNames = {"A", "B", "C", "D", "E", "F"};

    // Graph Edges: (u, v, weight)
    std::vector<Edge> edges = {
        {0, 1, 4},  // A - B (4)
        {0, 2, 4},  // A - C (4)
        {1, 2, 2},  // B - C (2)
        {1, 3, 5},  // B - D (5)
        {2, 3, 5},  // C - D (5)
        {2, 4, 11}, // C - E (11)
        {3, 4, 2},  // D - E (2)
        {3, 5, 2},  // D - F (2)
        {4, 5, 1}   // E - F (1)
    };

    // Construct adjacency list for Prim's
    std::vector<std::vector<std::pair<int, int>>> adjList(V);
    for (const auto& e : edges) {
        adjList[e.u].push_back({e.v, e.weight});
        adjList[e.v].push_back({e.u, e.weight});
    }

    // Print Graph Summary
    std::cout << "Weighted Graph Configuration:\n";
    std::cout << "Vertices: " << V << " | Total Edges: " << edges.size() << "\n";
    for (const auto& e : edges) {
        std::cout << "  (" << nodeNames[e.u] << " <---> " << nodeNames[e.v] 
                  << ") with weight " << e.weight << "\n";
    }

    // 1. Run Kruskal's Algorithm
    std::vector<Edge> kruskalMST;
    int kruskalCost = runKruskalMST(V, edges, nodeNames, kruskalMST);

    // 2. Run Prim's Algorithm
    std::vector<Edge> primMST;
    int primCost = runPrimMST(V, adjList, nodeNames, primMST);

    // Cross-Verification
    std::cout << "\n====================================================================\n";
    std::cout << "                     MST ALGORITHM COMPARISON                       \n";
    std::cout << "====================================================================\n";
    std::cout << "  - Kruskal's MST Total Cost: " << kruskalCost << "\n";
    std::cout << "  - Prim's MST Total Cost   : " << primCost << "\n";
    std::cout << "  - Verification Result     : " 
              << (kruskalCost == primCost ? "IDENTICAL COST (PASSED)" : "FAILED") << "\n";
    std::cout << "  - Number of MST Edges     : " << kruskalMST.size() << " (V - 1 = " << (V - 1) << ")\n";
    std::cout << "====================================================================\n";

    return 0;
}
