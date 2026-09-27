/**
 * LAB ASSIGNMENT 4 - Task 3: Queue ADT using Structural Array Setup (Circular Queue)
 * 
 * Objective:
 * Implement a Queue abstract data type using a structural array setup.
 * Provide options for enqueue(), dequeue(), and display().
 * 
 * Theory:
 * A static linear array causes "false overflow" when elements are dequeued.
 * Implementing a Circular Queue via modulo arithmetic wraps around the buffer,
 * providing optimal O(1) enqueue and dequeue operations without shifting.
 */

#include <iostream>
#include <limits>
#include <string>

class ArrayQueue {
private:
    static const int CAPACITY = 5;
    int arr[CAPACITY];
    int frontIndex;
    int rearIndex;
    int count;

public:
    ArrayQueue() : frontIndex(0), rearIndex(-1), count(0) {}

    bool isFull() const {
        return count == CAPACITY;
    }

    bool isEmpty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    /**
     * Enqueue: Adds an element at the rear of the circular queue.
     */
    bool enqueue(int val) {
        if (isFull()) {
            std::cout << "[OVERFLOW ERROR] Queue is full (Capacity: " << CAPACITY 
                      << "). Cannot enqueue " << val << ".\n";
            return false;
        }
        rearIndex = (rearIndex + 1) % CAPACITY;
        arr[rearIndex] = val;
        ++count;
        std::cout << "[SUCCESS] Enqueued " << val << " at rear index " << rearIndex << ".\n";
        return true;
    }

    /**
     * Dequeue: Removes and returns the front element from the queue.
     */
    bool dequeue(int& dequeuedVal) {
        if (isEmpty()) {
            std::cout << "[UNDERFLOW ERROR] Queue is empty. Cannot dequeue.\n";
            return false;
        }
        dequeuedVal = arr[frontIndex];
        frontIndex = (frontIndex + 1) % CAPACITY;
        --count;
        std::cout << "[SUCCESS] Dequeued " << dequeuedVal << " from front.\n";
        return true;
    }

    bool peekFront(int& val) const {
        if (isEmpty()) {
            std::cout << "[ERROR] Queue is empty.\n";
            return false;
        }
        val = arr[frontIndex];
        return true;
    }

    void display() const {
        std::cout << "\n+------------------------------------------------+\n";
        std::cout << "|            CIRCULAR ARRAY QUEUE STATE          |\n";
        std::cout << "+------------------------------------------------+\n";
        std::cout << " Count: " << count << " / Capacity: " << CAPACITY 
                  << " | Front: " << frontIndex << " | Rear: " << rearIndex << "\n";
        if (isEmpty()) {
            std::cout << " [Queue is EMPTY]\n";
        } else {
            std::cout << " Logical Order (Front to Rear):\n ";
            for (int i = 0; i < count; ++i) {
                int actualIdx = (frontIndex + i) % CAPACITY;
                std::cout << "[" << actualIdx << "]: " << arr[actualIdx];
                if (i == 0) std::cout << " (FRONT)";
                if (i == count - 1) std::cout << " (REAR)";
                std::cout << "\n ";
            }
            std::cout << "\n";
        }
        std::cout << "+------------------------------------------------+\n\n";
    }
};

void runAutomatedDemo() {
    std::cout << "\n====================================================\n";
    std::cout << "     RUNNING DEMO: STRUCTURAL ARRAY QUEUE           \n";
    std::cout << "====================================================\n";

    ArrayQueue queue;
    int val;

    std::cout << "\n--- 1. Enqueue Operations ---\n";
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);
    queue.display();

    std::cout << "\n--- 2. Testing Overflow ---\n";
    queue.enqueue(60);

    std::cout << "\n--- 3. Dequeue Operations ---\n";
    queue.dequeue(val);
    queue.dequeue(val);
    queue.display();

    std::cout << "\n--- 4. Testing Circular Wrap-around ---\n";
    queue.enqueue(60); // Re-uses vacated slots at the front
    queue.enqueue(70);
    queue.display();

    std::cout << "\n--- 5. Emptying Queue & Underflow ---\n";
    while (queue.dequeue(val));
    queue.dequeue(val); // Underflow
    queue.display();

    std::cout << "====================================================\n";
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--demo") {
        runAutomatedDemo();
        return 0;
    }

    ArrayQueue queue;
    int choice = 0;

    std::cout << "====================================================\n";
    std::cout << "       STRUCTURAL ARRAY QUEUE INTERACTIVE           \n";
    std::cout << "====================================================\n";

    while (true) {
        std::cout << "1. Enqueue\n";
        std::cout << "2. Dequeue\n";
        std::cout << "3. Peek Front\n";
        std::cout << "4. Display\n";
        std::cout << "5. Run Demo\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter choice (1-6): ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERROR] Invalid input.\n\n";
            continue;
        }

        if (choice == 1) {
            int val;
            std::cout << "Enter integer to enqueue: ";
            std::cin >> val;
            queue.enqueue(val);
            queue.display();
        } else if (choice == 2) {
            int val;
            if (queue.dequeue(val)) {
                queue.display();
            }
        } else if (choice == 3) {
            int val;
            if (queue.peekFront(val)) {
                std::cout << "Front element is: " << val << "\n\n";
            }
        } else if (choice == 4) {
            queue.display();
        } else if (choice == 5) {
            runAutomatedDemo();
        } else if (choice == 6) {
            std::cout << "Exiting. Goodbye!\n";
            break;
        } else {
            std::cout << "[ERROR] Invalid choice. Choose 1-6.\n\n";
        }
    }
    return 0;
}
