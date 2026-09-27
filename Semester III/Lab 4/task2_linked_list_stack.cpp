/**
 * LAB ASSIGNMENT 4 - Task 2: Stack using Dynamic Pointer-Linked Node Allocation
 * 
 * Objective:
 * Rewrite the Stack infrastructure using a dynamic pointer-linked node allocation framework.
 * Dynamic stacks grow/shrink arbitrarily without fixed static capacity bounds.
 */

#include <iostream>
#include <limits>
#include <string>

struct StackNode {
    int data;
    StackNode* next;

    explicit StackNode(int val) : data(val), next(nullptr) {}
};

class LinkedListStack {
private:
    StackNode* topNode;
    int stackSize;

public:
    LinkedListStack() : topNode(nullptr), stackSize(0) {}

    ~LinkedListStack() {
        clear();
    }

    LinkedListStack(const LinkedListStack&) = delete;
    LinkedListStack& operator=(const LinkedListStack&) = delete;

    void clear() {
        while (topNode != nullptr) {
            StackNode* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
        stackSize = 0;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    int size() const {
        return stackSize;
    }

    /**
     * Push: Dynamically allocates a new node and places it at the top of the stack.
     */
    void push(int val) {
        StackNode* newNode = new StackNode(val);
        newNode->next = topNode;
        topNode = newNode;
        ++stackSize;
        std::cout << "[SUCCESS] Dynamically allocated and pushed " << val 
                  << " onto stack. (Current size: " << stackSize << ")\n";
    }

    /**
     * Pop: Removes the top node, frees heap memory, and decrements size.
     */
    bool pop(int& poppedVal) {
        if (isEmpty()) {
            std::cout << "[UNDERFLOW ERROR] Dynamic stack is empty. Cannot pop.\n";
            return false;
        }
        StackNode* temp = topNode;
        poppedVal = temp->data;
        topNode = topNode->next;
        delete temp; // Reclaim heap memory
        --stackSize;
        std::cout << "[SUCCESS] Popped " << poppedVal << " and deallocated node.\n";
        return true;
    }

    bool peek(int& topVal) const {
        if (isEmpty()) {
            std::cout << "[ERROR] Stack is empty. No top element.\n";
            return false;
        }
        topVal = topNode->data;
        return true;
    }

    void display() const {
        std::cout << "\n+------------------------------------------------+\n";
        std::cout << "|           LINKED LIST STACK (DYNAMIC)          |\n";
        std::cout << "+------------------------------------------------+\n";
        std::cout << " Total Elements: " << stackSize << "\n";
        if (isEmpty()) {
            std::cout << " [Stack is EMPTY: (TOP) -> NULL]\n";
        } else {
            StackNode* curr = topNode;
            std::cout << " (TOP) -> ";
            while (curr != nullptr) {
                std::cout << "[" << curr->data << "] -> ";
                curr = curr->next;
            }
            std::cout << "NULL\n";
        }
        std::cout << "+------------------------------------------------+\n\n";
    }
};

void runAutomatedDemo() {
    std::cout << "\n====================================================\n";
    std::cout << "     RUNNING DEMO: DYNAMIC LINKED LIST STACK        \n";
    std::cout << "====================================================\n";

    LinkedListStack stack;
    int val;

    std::cout << "\n--- 1. Testing Dynamic Pushes (No fixed overflow) ---\n";
    for (int i = 10; i <= 60; i += 10) {
        stack.push(i);
    }
    stack.display();

    std::cout << "\n--- 2. Testing Peek ---\n";
    if (stack.peek(val)) {
        std::cout << "Current Top Element: " << val << "\n";
    }

    std::cout << "\n--- 3. Testing Dynamic Pops ---\n";
    stack.pop(val);
    stack.pop(val);
    stack.display();

    std::cout << "\n--- 4. Testing Emptying Stack & Underflow ---\n";
    while (stack.pop(val));
    stack.display();

    std::cout << "====================================================\n";
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--demo") {
        runAutomatedDemo();
        return 0;
    }

    LinkedListStack stack;
    int choice = 0;

    std::cout << "====================================================\n";
    std::cout << "     DYNAMIC LINKED LIST STACK INTERACTIVE          \n";
    std::cout << "====================================================\n";

    while (true) {
        std::cout << "1. Push\n";
        std::cout << "2. Pop\n";
        std::cout << "3. Peek Top\n";
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
            std::cout << "Enter integer to push: ";
            std::cin >> val;
            stack.push(val);
            stack.display();
        } else if (choice == 2) {
            int popped;
            if (stack.pop(popped)) {
                stack.display();
            }
        } else if (choice == 3) {
            int top;
            if (stack.peek(top)) {
                std::cout << "Top element is: " << top << "\n\n";
            }
        } else if (choice == 4) {
            stack.display();
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
