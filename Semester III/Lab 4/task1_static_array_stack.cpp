/**
 * LAB ASSIGNMENT 4 - Task 1: Stack Abstract Data Type using Static Array
 * 
 * Objective:
 * Implement a Stack ADT using a static array framework.
 * Provide options for push(), pop(), and display().
 */

#include <iostream>
#include <limits>
#include <string>

class StaticArrayStack {
private:
    static const int CAPACITY = 5;
    int arr[CAPACITY];
    int topIndex;

public:
    StaticArrayStack() : topIndex(-1) {}

    bool isFull() const {
        return topIndex == CAPACITY - 1;
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    int size() const {
        return topIndex + 1;
    }

    /**
     * Push: Adds an element onto the top of the stack.
     * Checks for stack overflow condition.
     */
    bool push(int val) {
        if (isFull()) {
            std::cout << "[OVERFLOW ERROR] Stack is full (Capacity: " << CAPACITY 
                      << "). Cannot push " << val << ".\n";
            return false;
        }
        arr[++topIndex] = val;
        std::cout << "[SUCCESS] Pushed " << val << " onto stack. (Top Index: " << topIndex << ")\n";
        return true;
    }

    /**
     * Pop: Removes and returns the top element from the stack.
     * Checks for stack underflow condition.
     */
    bool pop(int& poppedVal) {
        if (isEmpty()) {
            std::cout << "[UNDERFLOW ERROR] Stack is empty. Cannot pop.\n";
            return false;
        }
        poppedVal = arr[topIndex--];
        std::cout << "[SUCCESS] Popped " << poppedVal << " from stack.\n";
        return true;
    }

    bool peek(int& topVal) const {
        if (isEmpty()) {
            std::cout << "[ERROR] Stack is empty. No top element.\n";
            return false;
        }
        topVal = arr[topIndex];
        return true;
    }

    /**
     * Display: Shows all elements currently stored in the stack from top to bottom.
     */
    void display() const {
        std::cout << "\n+------------------------------------------------+\n";
        std::cout << "|             STATIC ARRAY STACK STATE           |\n";
        std::cout << "+------------------------------------------------+\n";
        std::cout << " Size: " << size() << " / Capacity: " << CAPACITY << "\n";
        if (isEmpty()) {
            std::cout << " [Stack is EMPTY]\n";
        } else {
            for (int i = topIndex; i >= 0; --i) {
                std::cout << " [" << i << "]: " << arr[i];
                if (i == topIndex) std::cout << "  <-- TOP";
                std::cout << "\n";
            }
        }
        std::cout << "+------------------------------------------------+\n\n";
    }
};

void runAutomatedDemo() {
    std::cout << "\n====================================================\n";
    std::cout << "     RUNNING DEMO: STATIC ARRAY STACK               \n";
    std::cout << "====================================================\n";

    StaticArrayStack stack;
    int val;

    std::cout << "\n--- 1. Testing Push Operations ---\n";
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);
    stack.push(50);
    stack.display();

    std::cout << "\n--- 2. Testing Stack Overflow ---\n";
    stack.push(60); // Exceeds capacity 5

    std::cout << "\n--- 3. Testing Peek ---\n";
    if (stack.peek(val)) {
        std::cout << "Current Top Element: " << val << "\n";
    }

    std::cout << "\n--- 4. Testing Pop Operations ---\n";
    stack.pop(val);
    stack.pop(val);
    stack.display();

    std::cout << "\n--- 5. Testing Underflow ---\n";
    stack.pop(val);
    stack.pop(val);
    stack.pop(val);
    stack.pop(val); // Underflow
    stack.display();

    std::cout << "====================================================\n";
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--demo") {
        runAutomatedDemo();
        return 0;
    }

    StaticArrayStack stack;
    int choice = 0;

    std::cout << "====================================================\n";
    std::cout << "      STATIC ARRAY STACK INTERACTIVE PROGRAM        \n";
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
