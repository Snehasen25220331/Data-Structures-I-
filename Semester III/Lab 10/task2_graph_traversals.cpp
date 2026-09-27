/**
 * LAB SHEET 10 - Task 2: Graph Representations & Traversals (DFS & BFS)
 * 
 * Objective:
 * Map network graphs via Adjacency Matrices and Adjacency Lists, then process
 * node exploration orders using DFS and BFS tracking steps.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>
#include <string>

class NetworkGraph {
private:
    int numVertices;
    std::vector<std::vector<int>> adjMatrix;
    std::vector<std::vector<int>> adjList;
    std::vector<std::string> vertexNames;

public:
    NetworkGraph(int vertices, const std::vector<std::string>& names = {}) 
        : numVertices(vertices) {
        adjMatrix.assign(vertices, std::vector<int>(vertices, 0));
        adjList.resize(vertices);

        if (!names.empty() && static_cast<int>(names.size()) == vertices) {
            vertexNames = names;
        } else {
            for (int i = 0; i < vertices; ++i) {
                vertexNames.push_back("V" + std::to_string(i));
            }
        }
    }

    void addEdge(int u, int v, bool bidirectional = true) {
        if (u < 0 || u >= numVertices || v < 0 || v >= numVertices) return;

        // Adjacency Matrix
        adjMatrix[u][v] = 1;
        if (bidirectional) adjMatrix[v][u] = 1;

        // Adjacency List
        adjList[u].push_back(v);
        if (bidirectional) adjList[v].push_back(u);
    }

    void displayAdjacencyMatrix() const {
        std::cout << "\n--- 1. ADJACENCY MATRIX REPRESENTATION ---\n";
        std::cout << std::setw(8) << " ";
        for (int i = 0; i < numVertices; ++i) {
            std::cout << std::setw(6) << vertexNames[i];
        }
        std::cout << "\n";

        for (int i = 0; i < numVertices; ++i) {
            std::cout << std::setw(6) << vertexNames[i] << " [";
            for (int j = 0; j < numVertices; ++j) {
                std::cout << std::setw(5) << adjMatrix[i][j];
            }
            std::cout << "  ]\n";
        }
        std::cout << "\n";
    }

    void displayAdjacencyList() const {
        std::cout << "--- 2. ADJACENCY LIST REPRESENTATION ---\n";
        for (int i = 0; i < numVertices; ++i) {
            std::cout << std::setw(6) << vertexNames[i] << " -> ";
            if (adjList[i].empty()) {
                std::cout << "None";
            } else {
                for (size_t j = 0; j < adjList[i].size(); ++j) {
                    std::cout << vertexNames[adjList[i][j]] 
                              << (j + 1 < adjList[i].size() ? ", " : "");
                }
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    // ========================================================================
    // BREADTH-FIRST SEARCH (BFS) WITH STEP TRACKING
    // ========================================================================
    void runBFS(int startVertex) const {
        std::cout << "====================================================================\n";
        std::cout << "    BREADTH-FIRST SEARCH (BFS) STEP TRACE (Starting at " 
                  << vertexNames[startVertex] << ")   \n";
        std::cout << "====================================================================\n";

        std::vector<bool> visited(numVertices, false);
        std::vector<int> distance(numVertices, -1);
        std::queue<int> q;
        std::vector<int> traversalOrder;

        visited[startVertex] = true;
        distance[startVertex] = 0;
        q.push(startVertex);

        int step = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            traversalOrder.push_back(u);

            std::cout << "Step " << std::setw(2) << step++ << ": Dequeued node [" 
                      << vertexNames[u] << "] (Distance from start: " << distance[u] << ")\n";

            std::cout << "         Checking neighbors: ";
            std::vector<int> newlyAdded;

            for (int v : adjList[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    distance[v] = distance[u] + 1;
                    q.push(v);
                    newlyAdded.push_back(v);
                }
            }

            if (newlyAdded.empty()) {
                std::cout << "(No unvisited neighbors)\n";
            } else {
                std::cout << "Discovered & Enqueued -> ";
                for (size_t i = 0; i < newlyAdded.size(); ++i) {
                    std::cout << vertexNames[newlyAdded[i]] 
                              << (i + 1 < newlyAdded.size() ? ", " : "\n");
                }
            }

            // Print current queue content
            std::cout << "         Queue State: [ ";
            std::queue<int> tempQ = q;
            while (!tempQ.empty()) {
                std::cout << vertexNames[tempQ.front()] << " ";
                tempQ.pop();
            }
            std::cout << "]\n--------------------------------------------------------------------\n";
        }

        std::cout << "Final BFS Traversal Order: ";
        for (size_t i = 0; i < traversalOrder.size(); ++i) {
            std::cout << vertexNames[traversalOrder[i]] 
                      << (i + 1 < traversalOrder.size() ? " -> " : "\n\n");
        }
    }

    // ========================================================================
    // DEPTH-FIRST SEARCH (DFS) WITH STEP TRACKING
    // ========================================================================
    void dfsRecursiveHelper(int u, std::vector<bool>& visited, 
                            std::vector<int>& order, int depth, int& step) const {
        visited[u] = true;
        order.push_back(u);

        std::string indent(depth * 3, ' ');
        std::cout << "Step " << std::setw(2) << step++ << ": " << indent 
                  << "Entering Node [" << vertexNames[u] << "] (Recursion Depth: " 
                  << depth << ")\n";

        for (int v : adjList[u]) {
            if (!visited[v]) {
                std::cout << "         " << indent << "  Edge (" << vertexNames[u] 
                          << " -> " << vertexNames[v] << ") is unexplored -> Visiting\n";
                dfsRecursiveHelper(v, visited, order, depth + 1, step);
            } else {
                std::cout << "         " << indent << "  Edge (" << vertexNames[u] 
                          << " -> " << vertexNames[v] << ") already visited -> Backtracking/Skipping\n";
            }
        }

        std::cout << "         " << indent << "Finished all paths from [" 
                  << vertexNames[u] << "]. Backtracking up...\n";
    }

    void runDFS(int startVertex) const {
        std::cout << "====================================================================\n";
        std::cout << "    DEPTH-FIRST SEARCH (DFS) STEP TRACE (Starting at " 
                  << vertexNames[startVertex] << ")   \n";
        std::cout << "====================================================================\n";

        std::vector<bool> visited(numVertices, false);
        std::vector<int> order;
        int step = 1;

        dfsRecursiveHelper(startVertex, visited, order, 0, step);

        std::cout << "--------------------------------------------------------------------\n";
        std::cout << "Final DFS Traversal Order: ";
        for (size_t i = 0; i < order.size(); ++i) {
            std::cout << vertexNames[order[i]] 
                      << (i + 1 < order.size() ? " -> " : "\n\n");
        }
    }
};

int main() {
    std::cout << "====================================================================\n";
    std::cout << "       LAB 10 - TASK 2: GRAPH MAPPING & TRAVERSALS (DFS & BFS)      \n";
    std::cout << "====================================================================\n";

    // Setup network graph of 6 servers/routers: Router_A to Router_F
    std::vector<std::string> names = {"A", "B", "C", "D", "E", "F"};
    NetworkGraph net(6, names);

    // Network topology:
    // A - B, A - C
    // B - D, B - E
    // C - F
    // E - F
    net.addEdge(0, 1); // A - B
    net.addEdge(0, 2); // A - C
    net.addEdge(1, 3); // B - D
    net.addEdge(1, 4); // B - E
    net.addEdge(2, 5); // C - F
    net.addEdge(4, 5); // E - F

    // 1. Display representations
    net.displayAdjacencyMatrix();
    net.displayAdjacencyList();

    // 2. Run BFS
    net.runBFS(0); // Start from node A

    // 3. Run DFS
    net.runDFS(0); // Start from node A

    std::cout << "====================================================================\n";
    return 0;
}
