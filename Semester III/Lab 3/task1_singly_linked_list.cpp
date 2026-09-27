/**
 * LAB ASSIGNMENT 3 - Task 1: Singly Linked List (SLL)
 * 
 * Objective:
 * Create a complete custom Singly Linked List (SLL) program supporting:
 * 1. Dynamic node generation and entry insertion (at head, tail, or specified index position).
 * 2. Node deletion using a matching target data key.
 * 3. Forward list traversal printing all live data links.
 */

#include <iostream>
#include <string>
#include <limits>

struct Node {
    int data;
    Node* next;

    explicit Node(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;
    Node* tail;
    int listSize;

public:
    SinglyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

    ~SinglyLinkedList() {
        clear();
    }

    // Disable copy for safety
    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    int size() const {
        return listSize;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void clear() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* temp = curr->next;
            delete curr;
            curr = temp;
        }
        head = nullptr;
        tail = nullptr;
        listSize = 0;
    }

    /**
     * 1. Dynamic node generation and entry insertion at Head: O(1)
     */
    void insertHead(int val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        ++listSize;
        std::cout << "[SUCCESS] Inserted " << val << " at Head.\n";
    }

    /**
     * 1. Dynamic node generation and entry insertion at Tail: O(1)
     */
    void insertTail(int val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++listSize;
        std::cout << "[SUCCESS] Inserted " << val << " at Tail.\n";
    }

    /**
     * 1. Dynamic node generation and entry insertion at specified index position
     * Valid index range: [0, listSize]
     */
    bool insertAtIndex(int index, int val) {
        if (index < 0 || index > listSize) {
            std::cout << "[ERROR] Invalid index " << index 
                      << ". Valid range is [0, " << listSize << "].\n";
            return false;
        }

        if (index == 0) {
            insertHead(val);
            return true;
        }
        if (index == listSize) {
            insertTail(val);
            return true;
        }

        Node* newNode = new Node(val);
        Node* curr = head;
        for (int i = 0; i < index - 1; ++i) {
            curr = curr->next;
        }

        newNode->next = curr->next;
        curr->next = newNode;
        ++listSize;
        std::cout << "[SUCCESS] Inserted " << val << " at index " << index << ".\n";
        return true;
    }

    /**
     * 2. Node deletion using a matching target data key.
     * Deletes the first occurrence of the specified key.
     */
    bool deleteByKey(int targetKey) {
        if (isEmpty()) {
            std::cout << "[ERROR] List is empty. Cannot delete key " << targetKey << ".\n";
            return false;
        }

        // Case 1: Head contains the matching target key
        if (head->data == targetKey) {
            Node* temp = head;
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
            }
            delete temp;
            --listSize;
            std::cout << "[SUCCESS] Deleted node with key " << targetKey << " from Head.\n";
            return true;
        }

        // Case 2: Key is located elsewhere in the list
        Node* curr = head;
        while (curr->next != nullptr && curr->next->data != targetKey) {
            curr = curr->next;
        }

        if (curr->next != nullptr) {
            Node* toDelete = curr->next;
            curr->next = toDelete->next;
            if (toDelete == tail) {
                tail = curr; // Update tail pointer
            }
            delete toDelete;
            --listSize;
            std::cout << "[SUCCESS] Deleted node with key " << targetKey << ".\n";
            return true;
        }

        std::cout << "[NOT FOUND] Key " << targetKey << " not found in the list.\n";
        return false;
    }

    /**
     * 3. Forward list traversal printing all live data links.
     */
    void displayForward() const {
        std::cout << "\n--- Forward List Traversal ---\n";
        if (isEmpty()) {
            std::cout << " [List is empty: (HEAD) -> NULL]\n\n";
            return;
        }

        std::cout << " [HEAD] -> ";
        Node* curr = head;
        while (curr != nullptr) {
            std::cout << "[" << curr->data << "] -> ";
            curr = curr->next;
        }
        std::cout << "NULL  (Size: " << listSize << ")\n\n";
    }
};

void runAutomatedDemo() {
    std::cout << "\n===============================================================\n";
    std::cout << "     RUNNING AUTOMATED TEST SUITE FOR SINGLY LINKED LIST       \n";
    std::cout << "===============================================================\n";

    SinglyLinkedList sll;

    std::cout << "\n--- 1. Testing Dynamic Insertions ---\n";
    sll.insertHead(20);
    sll.insertHead(10);
    sll.insertTail(40);
    sll.insertAtIndex(2, 30); // Insert in middle
    sll.insertAtIndex(0, 5);  // Insert at head
    sll.insertAtIndex(5, 50); // Insert at tail
    sll.displayForward();

    std::cout << "\n--- 2. Testing Boundary Insertions ---\n";
    sll.insertAtIndex(-1, 999);
    sll.insertAtIndex(100, 999);

    std::cout << "\n--- 3. Testing Deletion by Matching Key ---\n";
    sll.deleteByKey(5);   // Delete head
    sll.displayForward();

    sll.deleteByKey(30);  // Delete middle node
    sll.displayForward();

    sll.deleteByKey(50);  // Delete tail node
    sll.displayForward();

    std::cout << "\n--- 4. Testing Deletion of Non-Existent Key ---\n";
    sll.deleteByKey(999);
    sll.displayForward();

    std::cout << "===============================================================\n";
    std::cout << "             AUTOMATED TEST SUITE COMPLETED                    \n";
    std::cout << "===============================================================\n\n";
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--demo") {
        runAutomatedDemo();
        return 0;
    }

    SinglyLinkedList sll;
    int choice = 0;

    std::cout << "===============================================================\n";
    std::cout << "           SINGLY LINKED LIST (SLL) SYSTEM (LAB 3)             \n";
    std::cout << "===============================================================\n";

    while (true) {
        std::cout << "MENU OPTIONS:\n";
        std::cout << " 1. Insert at Head\n";
        std::cout << " 2. Insert at Tail\n";
        std::cout << " 3. Insert at specified index position\n";
        std::cout << " 4. Delete node by matching target data key\n";
        std::cout << " 5. Forward list traversal (print all links)\n";
        std::cout << " 6. Run automated test demonstration\n";
        std::cout << " 7. Exit\n";
        std::cout << "Enter your choice (1-7): ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERROR] Invalid choice. Please enter a valid number.\n\n";
            continue;
        }

        if (choice == 1) {
            int val;
            std::cout << "Enter value to insert at Head: ";
            std::cin >> val;
            sll.insertHead(val);
            sll.displayForward();
        } else if (choice == 2) {
            int val;
            std::cout << "Enter value to insert at Tail: ";
            std::cin >> val;
            sll.insertTail(val);
            sll.displayForward();
        } else if (choice == 3) {
            int idx, val;
            std::cout << "Enter index [0 to " << sll.size() << "]: ";
            std::cin >> idx;
            std::cout << "Enter value to insert: ";
            std::cin >> val;
            if (sll.insertAtIndex(idx, val)) {
                sll.displayForward();
            }
        } else if (choice == 4) {
            int key;
            std::cout << "Enter target key to delete: ";
            std::cin >> key;
            sll.deleteByKey(key);
            sll.displayForward();
        } else if (choice == 5) {
            sll.displayForward();
        } else if (choice == 6) {
            runAutomatedDemo();
        } else if (choice == 7) {
            std::cout << "Exiting Singly Linked List program. Goodbye!\n";
            break;
        } else {
            std::cout << "[ERROR] Invalid option selected. Choose 1-7.\n\n";
        }
    }

    return 0;
}
