/**
 * LAB ASSIGNMENT 3 - Task 2: Doubly Linked List (DLL)
 * 
 * Objective:
 * Create a custom Doubly Linked List (DLL) program supporting:
 * 1. Node insertion maintaining forward and backward pointers.
 * 2. Node deletion with proper pointer re-linking.
 * 3. Reverse traversal printing nodes from tail back to head.
 */

#include <iostream>
#include <string>
#include <limits>

struct DNode {
    int data;
    DNode* prev;
    DNode* next;

    explicit DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    DNode* head;
    DNode* tail;
    int listSize;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    // Disable copy for safety
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    int size() const {
        return listSize;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void clear() {
        DNode* curr = head;
        while (curr != nullptr) {
            DNode* temp = curr->next;
            delete curr;
            curr = temp;
        }
        head = nullptr;
        tail = nullptr;
        listSize = 0;
    }

    /**
     * 1. Insertion maintaining forward and backward pointers at Head
     */
    void insertHead(int val) {
        DNode* newNode = new DNode(val);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        ++listSize;
        std::cout << "[SUCCESS] Inserted " << val << " at Head.\n";
    }

    /**
     * 1. Insertion maintaining forward and backward pointers at Tail
     */
    void insertTail(int val) {
        DNode* newNode = new DNode(val);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++listSize;
        std::cout << "[SUCCESS] Inserted " << val << " at Tail.\n";
    }

    /**
     * 1. Insertion maintaining forward and backward pointers at specified index
     * Valid range: [0, listSize]
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

        DNode* newNode = new DNode(val);
        DNode* curr = head;
        for (int i = 0; i < index; ++i) {
            curr = curr->next;
        }

        // Insert newNode right before curr
        DNode* predecessor = curr->prev;

        newNode->next = curr;
        newNode->prev = predecessor;

        predecessor->next = newNode;
        curr->prev = newNode;

        ++listSize;
        std::cout << "[SUCCESS] Inserted " << val << " at index " << index << ".\n";
        return true;
    }

    /**
     * 2. Node deletion with proper pointer re-linking using a matching target data key
     */
    bool deleteByKey(int targetKey) {
        if (isEmpty()) {
            std::cout << "[ERROR] List is empty. Cannot delete key " << targetKey << ".\n";
            return false;
        }

        DNode* curr = head;
        while (curr != nullptr && curr->data != targetKey) {
            curr = curr->next;
        }

        if (curr == nullptr) {
            std::cout << "[NOT FOUND] Key " << targetKey << " not found in the Doubly Linked List.\n";
            return false;
        }

        // Re-link previous node
        if (curr->prev != nullptr) {
            curr->prev->next = curr->next;
        } else {
            head = curr->next; // Deleting head
        }

        // Re-link next node
        if (curr->next != nullptr) {
            curr->next->prev = curr->prev;
        } else {
            tail = curr->prev; // Deleting tail
        }

        delete curr;
        --listSize;
        std::cout << "[SUCCESS] Deleted node with key " << targetKey << " and updated both pointers.\n";
        return true;
    }

    /**
     * Forward list traversal printing all live data links
     */
    void displayForward() const {
        std::cout << "\n--- Forward List Traversal (Head to Tail) ---\n";
        if (isEmpty()) {
            std::cout << " [List is empty: NULL <-> NULL]\n\n";
            return;
        }

        std::cout << " [HEAD] NULL <-> ";
        DNode* curr = head;
        while (curr != nullptr) {
            std::cout << "[" << curr->data << "] <-> ";
            curr = curr->next;
        }
        std::cout << "NULL  (Size: " << listSize << ")\n\n";
    }

    /**
     * 3. Reverse traversal printing nodes from tail back to head
     */
    void displayReverse() const {
        std::cout << "\n--- Reverse List Traversal (Tail to Head) ---\n";
        if (isEmpty()) {
            std::cout << " [List is empty: NULL <-> NULL]\n\n";
            return;
        }

        std::cout << " [TAIL] NULL <-> ";
        DNode* curr = tail;
        while (curr != nullptr) {
            std::cout << "[" << curr->data << "] <-> ";
            curr = curr->prev;
        }
        std::cout << "NULL  (Size: " << listSize << ")\n\n";
    }
};

void runAutomatedDemo() {
    std::cout << "\n===============================================================\n";
    std::cout << "     RUNNING AUTOMATED TEST SUITE FOR DOUBLY LINKED LIST       \n";
    std::cout << "===============================================================\n";

    DoublyLinkedList dll;

    std::cout << "\n--- 1. Testing Insertion maintaining forward/backward pointers ---\n";
    dll.insertHead(20);
    dll.insertHead(10);
    dll.insertTail(40);
    dll.insertAtIndex(2, 30); // Insert in middle
    dll.insertAtIndex(0, 5);  // Insert at head
    dll.insertAtIndex(5, 50); // Insert at tail
    
    std::cout << "\nForward and Reverse views after insertions:\n";
    dll.displayForward();
    dll.displayReverse();

    std::cout << "\n--- 2. Testing Deletion with Proper Pointer Re-linking ---\n";
    std::cout << "Deleting Head (5):\n";
    dll.deleteByKey(5);
    dll.displayForward();
    dll.displayReverse();

    std::cout << "Deleting Middle Node (30):\n";
    dll.deleteByKey(30);
    dll.displayForward();
    dll.displayReverse();

    std::cout << "Deleting Tail Node (50):\n";
    dll.deleteByKey(50);
    dll.displayForward();
    dll.displayReverse();

    std::cout << "Attempting to delete non-existent key (999):\n";
    dll.deleteByKey(999);

    std::cout << "===============================================================\n";
    std::cout << "             AUTOMATED TEST SUITE COMPLETED                    \n";
    std::cout << "===============================================================\n\n";
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--demo") {
        runAutomatedDemo();
        return 0;
    }

    DoublyLinkedList dll;
    int choice = 0;

    std::cout << "===============================================================\n";
    std::cout << "           DOUBLY LINKED LIST (DLL) SYSTEM (LAB 3)             \n";
    std::cout << "===============================================================\n";

    while (true) {
        std::cout << "MENU OPTIONS:\n";
        std::cout << " 1. Insert at Head\n";
        std::cout << " 2. Insert at Tail\n";
        std::cout << " 3. Insert at specified index position\n";
        std::cout << " 4. Delete node by matching target data key\n";
        std::cout << " 5. Forward list traversal (Head to Tail)\n";
        std::cout << " 6. Reverse list traversal (Tail to Head)\n";
        std::cout << " 7. Run automated test demonstration\n";
        std::cout << " 8. Exit\n";
        std::cout << "Enter your choice (1-8): ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERROR] Invalid input. Please enter a valid number.\n\n";
            continue;
        }

        if (choice == 1) {
            int val;
            std::cout << "Enter value to insert at Head: ";
            std::cin >> val;
            dll.insertHead(val);
            dll.displayForward();
        } else if (choice == 2) {
            int val;
            std::cout << "Enter value to insert at Tail: ";
            std::cin >> val;
            dll.insertTail(val);
            dll.displayForward();
        } else if (choice == 3) {
            int idx, val;
            std::cout << "Enter index [0 to " << dll.size() << "]: ";
            std::cin >> idx;
            std::cout << "Enter value to insert: ";
            std::cin >> val;
            if (dll.insertAtIndex(idx, val)) {
                dll.displayForward();
            }
        } else if (choice == 4) {
            int key;
            std::cout << "Enter target key to delete: ";
            std::cin >> key;
            dll.deleteByKey(key);
            dll.displayForward();
        } else if (choice == 5) {
            dll.displayForward();
        } else if (choice == 6) {
            dll.displayReverse();
        } else if (choice == 7) {
            runAutomatedDemo();
        } else if (choice == 8) {
            std::cout << "Exiting Doubly Linked List program. Goodbye!\n";
            break;
        } else {
            std::cout << "[ERROR] Invalid option selected. Choose 1-8.\n\n";
        }
    }

    return 0;
}
