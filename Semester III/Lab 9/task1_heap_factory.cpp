/**
 * LAB SHEET 9 - Task 1: Heap Factory (Min Heap & Max Heap)
 * 
 * Objective:
 * Implement array-backed Min Heap and Max Heap layouts using explicit
 * bubble-up (sift-up) and bubble-down (sift-down) adjustment steps.
 * 
 * Theory:
 * In a 0-indexed array representation of a complete binary tree:
 * - Parent of node at index i: (i - 1) / 2
 * - Left child of node at index i: 2 * i + 1
 * - Right child of node at index i: 2 * i + 2
 * 
 * Min Heap Property: Parent <= Children (Root is minimum)
 * Max Heap Property: Parent >= Children (Root is maximum)
 */

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <cmath>

// ============================================================================
// MIN HEAP IMPLEMENTATION
// ============================================================================
class MinHeap {
private:
    std::vector<int> heap;

    int parent(int i) const { return (i - 1) / 2; }
    int leftChild(int i) const { return 2 * i + 1; }
    int rightChild(int i) const { return 2 * i + 2; }

    /**
     * Explicit Bubble-Up (Sift-Up) Step:
     * Moves a newly inserted element up the tree while it is smaller than its parent.
     */
    void bubbleUp(int index) {
        std::cout << "  [Bubble-Up] Starting for index " << index << " (val=" << heap[index] << ")\n";
        while (index > 0 && heap[index] < heap[parent(index)]) {
            int p = parent(index);
            std::cout << "    Swapping index " << index << " (" << heap[index] 
                      << ") with parent index " << p << " (" << heap[p] << ")\n";
            std::swap(heap[index], heap[p]);
            index = p;
        }
        std::cout << "  [Bubble-Up] Completed. Element settled at index " << index << ".\n";
    }

    /**
     * Explicit Bubble-Down (Sift-Down) Step:
     * Moves root element down until it is smaller than both children.
     */
    void bubbleDown(int index) {
        int n = static_cast<int>(heap.size());
        std::cout << "  [Bubble-Down] Starting for index " << index << " (val=" << heap[index] << ")\n";

        while (leftChild(index) < n) {
            int smallest = index;
            int left = leftChild(index);
            int right = rightChild(index);

            if (left < n && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < n && heap[right] < heap[smallest]) {
                smallest = right;
            }

            if (smallest != index) {
                std::cout << "    Swapping index " << index << " (" << heap[index] 
                          << ") with smaller child index " << smallest << " (" << heap[smallest] << ")\n";
                std::swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
        std::cout << "  [Bubble-Down] Completed. Element settled at index " << index << ".\n";
    }

public:
    MinHeap() = default;

    bool isEmpty() const { return heap.empty(); }
    int size() const { return static_cast<int>(heap.size()); }

    void insert(int key) {
        std::cout << ">> Inserting key " << key << " into Min Heap:\n";
        heap.push_back(key);
        bubbleUp(static_cast<int>(heap.size()) - 1);
    }

    int peek() const {
        if (isEmpty()) throw std::runtime_error("Heap is empty!");
        return heap[0];
    }

    int extractMin() {
        if (isEmpty()) throw std::runtime_error("Heap underflow!");
        int root = heap[0];
        std::cout << ">> Extracting Min root (" << root << ") from Min Heap:\n";

        int lastVal = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            heap[0] = lastVal;
            bubbleDown(0);
        }
        return root;
    }

    void display() const {
        std::cout << "Array Layout: [ ";
        for (size_t i = 0; i < heap.size(); ++i) {
            std::cout << heap[i] << (i + 1 < heap.size() ? ", " : " ");
        }
        std::cout << "]\n";
    }
};

// ============================================================================
// MAX HEAP IMPLEMENTATION
// ============================================================================
class MaxHeap {
private:
    std::vector<int> heap;

    int parent(int i) const { return (i - 1) / 2; }
    int leftChild(int i) const { return 2 * i + 1; }
    int rightChild(int i) const { return 2 * i + 2; }

    /**
     * Explicit Bubble-Up (Sift-Up) Step:
     * Moves a newly inserted element up the tree while it is greater than its parent.
     */
    void bubbleUp(int index) {
        std::cout << "  [Bubble-Up] Starting for index " << index << " (val=" << heap[index] << ")\n";
        while (index > 0 && heap[index] > heap[parent(index)]) {
            int p = parent(index);
            std::cout << "    Swapping index " << index << " (" << heap[index] 
                      << ") with parent index " << p << " (" << heap[p] << ")\n";
            std::swap(heap[index], heap[p]);
            index = p;
        }
        std::cout << "  [Bubble-Up] Completed. Element settled at index " << index << ".\n";
    }

    /**
     * Explicit Bubble-Down (Sift-Down) Step:
     * Moves root element down until it is greater than both children.
     */
    void bubbleDown(int index) {
        int n = static_cast<int>(heap.size());
        std::cout << "  [Bubble-Down] Starting for index " << index << " (val=" << heap[index] << ")\n";

        while (leftChild(index) < n) {
            int largest = index;
            int left = leftChild(index);
            int right = rightChild(index);

            if (left < n && heap[left] > heap[largest]) {
                largest = left;
            }
            if (right < n && heap[right] > heap[largest]) {
                largest = right;
            }

            if (largest != index) {
                std::cout << "    Swapping index " << index << " (" << heap[index] 
                          << ") with larger child index " << largest << " (" << heap[largest] << ")\n";
                std::swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
        std::cout << "  [Bubble-Down] Completed. Element settled at index " << index << ".\n";
    }

public:
    MaxHeap() = default;

    bool isEmpty() const { return heap.empty(); }
    int size() const { return static_cast<int>(heap.size()); }

    void insert(int key) {
        std::cout << ">> Inserting key " << key << " into Max Heap:\n";
        heap.push_back(key);
        bubbleUp(static_cast<int>(heap.size()) - 1);
    }

    int peek() const {
        if (isEmpty()) throw std::runtime_error("Heap is empty!");
        return heap[0];
    }

    int extractMax() {
        if (isEmpty()) throw std::runtime_error("Heap underflow!");
        int root = heap[0];
        std::cout << ">> Extracting Max root (" << root << ") from Max Heap:\n";

        int lastVal = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            heap[0] = lastVal;
            bubbleDown(0);
        }
        return root;
    }

    void display() const {
        std::cout << "Array Layout: [ ";
        for (size_t i = 0; i < heap.size(); ++i) {
            std::cout << heap[i] << (i + 1 < heap.size() ? ", " : " ");
        }
        std::cout << "]\n";
    }
};

int main() {
    std::cout << "====================================================================\n";
    std::cout << "      LAB 9 - TASK 1: HEAP FACTORY (MIN HEAP & MAX HEAP DEMO)       \n";
    std::cout << "====================================================================\n\n";

    // --- 1. MIN HEAP DEMO ---
    std::cout << ">>> PART A: TESTING MIN HEAP LAYOUT <<<\n";
    MinHeap minH;
    const std::vector<int> values = {45, 20, 14, 12, 31, 7, 11, 40};

    for (int v : values) {
        minH.insert(v);
        minH.display();
        std::cout << "\n";
    }

    std::cout << "Current Min Heap Root: " << minH.peek() << "\n\n";

    std::cout << "Extracting elements from Min Heap (ascending priority order):\n";
    while (!minH.isEmpty()) {
        int root = minH.extractMin();
        std::cout << "Extracted: " << root << " | Remaining: ";
        minH.display();
        std::cout << "\n";
    }

    // --- 2. MAX HEAP DEMO ---
    std::cout << "--------------------------------------------------------------------\n";
    std::cout << ">>> PART B: TESTING MAX HEAP LAYOUT <<<\n";
    MaxHeap maxH;

    for (int v : values) {
        maxH.insert(v);
        maxH.display();
        std::cout << "\n";
    }

    std::cout << "Current Max Heap Root: " << maxH.peek() << "\n\n";

    std::cout << "Extracting elements from Max Heap (descending priority order):\n";
    while (!maxH.isEmpty()) {
        int root = maxH.extractMax();
        std::cout << "Extracted: " << root << " | Remaining: ";
        maxH.display();
        std::cout << "\n";
    }

    std::cout << "====================================================================\n";
    std::cout << "                     HEAP FACTORY DEMO COMPLETE                     \n";
    std::cout << "====================================================================\n";

    return 0;
}
