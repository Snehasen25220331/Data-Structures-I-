/**
 * LAB ASSIGNMENT 4 - Task 4: Queue using Dynamic Pointer-Linked Node Setup
 * 
 * Objective:
 * Rewrite the Queue infrastructure using a dynamic pointer-linked node setup.
 * Maintains front and rear pointers for O(1) enqueue and dequeue operations.
 */

#include <iostream>
#include <limits>
#include <string>

struct QueueNode {
    int data;
    QueueNode* next;

    explicit QueueNode(int val) : data(val), next(nullptr) {}
};

class LinkedListQueue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;
    int queueSize;

public:
    LinkedListQueue() : frontNode(nullptr), rearNode(nullptr), queueSize(0) {}

    ~LinkedListQueue() {
        clear();
    }

    LinkedListQueue(const LinkedListQueue&) = delete;
    LinkedListQueue& operator=(const LinkedListQueue&) = delete;

    void clear() {
        while (frontNode != nullptr) {
            QueueNode* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }
        rearNode = nullptr;
        queueSize = 0;
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

    int size() const {
        return queueSize;
    }

    /**
     * Enqueue: Adds a new dynamically allocated node to the rear of the queue in O(1).
     */
    void enqueue(int val) {
        QueueNode* newNode = new QueueNode(val);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        ++queueSize;
        std::cout << "[SUCCESS] Enqueued " << val << " at Rear. (Queue size: " << queueSize << ")\n";
    }

    /**
     * Dequeue: Removes the node from the front of the queue, frees memory, in O(1).
     */
    bool dequeue(int& dequeuedVal) {
        if (isEmpty()) {
            std::cout << "[UNDERFLOW ERROR] Dynamic queue is empty. Cannot dequeue.\n";
            return false;
        }
        QueueNode* temp = frontNode;
        dequeuedVal = temp->data;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete temp;
        --queueSize;
        std::cout << "[SUCCESS] Dequeued " << dequeuedVal << " from Front.\n";
        return true;
    }

    bool peekFront(int& val) const {
        if (isEmpty()) {
            std::cout << "[ERROR] Queue is empty.\n";
            return false;
        }
        val = frontNode->data;
        return true;
    }

    void display() const {
        std::cout << "\n+------------------------------------------------+\n";
        std::cout << "|           LINKED LIST QUEUE (DYNAMIC)          |\n";
        std::cout << "+------------------------------------------------+\n";
        std::cout << " Total Elements: " << queueSize << "\n";
        if (isEmpty()) {
            std::cout << " [Queue is EMPTY: (FRONT) NULL <- (REAR)]\n";
        } else {
            std::cout << " (FRONT) ";
            QueueNode* curr = frontNode;
            while (curr != nullptr) {
                std::cout << "[" << curr->data << "] -> ";
                curr = curr->next;
            }
            std::cout << "NULL (REAR)\n";
        }
        std::cout << "+------------------------------------------------+\n\n";
    }
};

void runAutomatedDemo() {
    std::cout << "\n====================================================\n";
    std::cout << "     RUNNING DEMO: DYNAMIC LINKED LIST QUEUE        \n";
    std::cout << "====================================================\n";

    LinkedListQueue queue;
    int val;

    std::cout << "\n--- 1. Testing Dynamic Enqueues ---\n";
    for (int i = 100; i <= 600; i += 100) {
        queue.enqueue(i);
    }
    queue.display();

    std::cout << "\n--- 2. Testing Peek Front ---\n";
    if (queue.peekFront(val)) {
        std::cout << "Current Front Element: " << val << "\n";
    }

    std::cout << "\n--- 3. Testing Dequeue Operations ---\n";
    queue.dequeue(val);
    queue.dequeue(val);
    queue.display();

    std::cout << "\n--- 4. Emptying Dynamic Queue & Underflow ---\n";
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

    LinkedListQueue queue;
    int choice = 0;

    std::cout << "====================================================\n";
    std::cout << "     DYNAMIC LINKED LIST QUEUE INTERACTIVE          \n";
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
