/**
 * LAB ASSIGNMENT 2: Basic Array Operations
 * 
 * Objective:
 * Implement an array-backed database program that prompts a user for structural actions:
 * 1. Insert a numeric element at a specified valid index location (shifting trailing entries right).
 * 2. Delete an element from a target index location (shifting trailing entries left to close gaps).
 * 3. Search the array sequentially to return the first index match of a specific value.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

class ArrayDatabase {
private:
    int* data;
    int capacity;
    int currentSize;

    void resize(int newCapacity) {
        int* newData = new int[newCapacity];
        for (int i = 0; i < currentSize; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    explicit ArrayDatabase(int initialCapacity = 10) 
        : capacity(initialCapacity), currentSize(0) {
        data = new int[capacity];
    }

    ~ArrayDatabase() {
        delete[] data;
    }

    // Disable copy for safety
    ArrayDatabase(const ArrayDatabase&) = delete;
    ArrayDatabase& operator=(const ArrayDatabase&) = delete;

    int size() const {
        return currentSize;
    }

    int getCapacity() const {
        return capacity;
    }

    bool isEmpty() const {
        return currentSize == 0;
    }

    /**
     * Action 1: Insert numeric element at specified valid index.
     * Elements at and after index are shifted one position to the right.
     * Valid index range: [0, currentSize].
     */
    bool insertAt(int index, int value) {
        if (index < 0 || index > currentSize) {
            std::cout << "[ERROR] Invalid insertion index " << index 
                      << ". Valid range is [0, " << currentSize << "].\n";
            return false;
        }

        // Expand capacity if array is full
        if (currentSize == capacity) {
            resize(capacity * 2);
        }

        // Shift trailing elements right
        for (int i = currentSize; i > index; --i) {
            data[i] = data[i - 1];
        }

        data[index] = value;
        ++currentSize;
        std::cout << "[SUCCESS] Inserted value " << value << " at index " << index << ".\n";
        return true;
    }

    /**
     * Action 2: Delete element from target index location.
     * Elements after index are shifted one position to the left.
     * Valid index range: [0, currentSize - 1].
     */
    bool deleteAt(int index, int& deletedValue) {
        if (isEmpty()) {
            std::cout << "[ERROR] Database is empty. Cannot delete.\n";
            return false;
        }

        if (index < 0 || index >= currentSize) {
            std::cout << "[ERROR] Invalid deletion index " << index 
                      << ". Valid range is [0, " << (currentSize - 1) << "].\n";
            return false;
        }

        deletedValue = data[index];

        // Shift trailing elements left
        for (int i = index; i < currentSize - 1; ++i) {
            data[i] = data[i + 1];
        }

        --currentSize;
        std::cout << "[SUCCESS] Deleted element " << deletedValue << " from index " << index << ".\n";
        return true;
    }

    /**
     * Action 3: Search sequentially to return first index match of specific value.
     */
    int searchSequential(int target, int& comparisons) const {
        comparisons = 0;
        for (int i = 0; i < currentSize; ++i) {
            ++comparisons;
            if (data[i] == target) {
                return i; // First match index
            }
        }
        return -1; // Not found
    }

    void display() const {
        std::cout << "\n+-------------------------------------------------------------+\n";
        std::cout << "|                     DATABASE CONTENTS                       |\n";
        std::cout << "+-------------------------------------------------------------+\n";
        std::cout << " Current Size: " << currentSize << " / Capacity: " << capacity << "\n";
        if (isEmpty()) {
            std::cout << " [Array is currently empty]\n";
        } else {
            std::cout << " Index : ";
            for (int i = 0; i < currentSize; ++i) {
                std::cout << std::setw(5) << i << " ";
            }
            std::cout << "\n Value : ";
            for (int i = 0; i < currentSize; ++i) {
                std::cout << std::setw(5) << data[i] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "+-------------------------------------------------------------+\n\n";
    }
};

void runAutomatedDemo() {
    std::cout << "\n===============================================================\n";
    std::cout << "       RUNNING AUTOMATED TEST SUITE FOR ARRAY DATABASE         \n";
    std::cout << "===============================================================\n";

    ArrayDatabase db;

    std::cout << "\n--- 1. Testing Insertions ---\n";
    db.insertAt(0, 50); // Insert at head
    db.insertAt(1, 70); // Insert at tail
    db.insertAt(1, 60); // Insert in middle
    db.insertAt(0, 40); // Insert at new head
    db.insertAt(4, 80); // Insert at tail
    db.display();

    std::cout << "\n--- 2. Testing Boundary / Invalid Insertion ---\n";
    db.insertAt(10, 999); // Invalid out of bounds
    db.insertAt(-1, 111); // Invalid negative index

    std::cout << "\n--- 3. Testing Sequential Search ---\n";
    int comps = 0;
    int foundIdx = db.searchSequential(60, comps);
    std::cout << "Searching for 60: Found at index " << foundIdx 
              << " after " << comps << " comparison(s).\n";

    foundIdx = db.searchSequential(999, comps);
    std::cout << "Searching for 999: Found at index " << foundIdx 
              << " (" << (foundIdx == -1 ? "NOT FOUND" : "FOUND") 
              << ") after " << comps << " comparison(s).\n";

    std::cout << "\n--- 4. Testing Deletion ---\n";
    int removedVal = 0;
    db.deleteAt(2, removedVal); // Delete middle element (60)
    db.display();

    db.deleteAt(0, removedVal); // Delete head (40)
    db.display();

    std::cout << "\n--- 5. Testing Invalid Deletion ---\n";
    db.deleteAt(15, removedVal); // Out of bounds
    db.deleteAt(-1, removedVal);

    std::cout << "===============================================================\n";
    std::cout << "                  AUTOMATED TESTS COMPLETED                     \n";
    std::cout << "===============================================================\n\n";
}

int main(int argc, char* argv[]) {
    // If user passed --demo flag, run automated test suite
    if (argc > 1 && std::string(argv[1]) == "--demo") {
        runAutomatedDemo();
        return 0;
    }

    ArrayDatabase db;
    int choice = 0;

    std::cout << "===============================================================\n";
    std::cout << "            ARRAY-BACKED DATABASE SYSTEM (LAB 2)               \n";
    std::cout << "===============================================================\n";

    while (true) {
        std::cout << "MENU OPTIONS:\n";
        std::cout << " 1. Insert numeric element at index (shift right)\n";
        std::cout << " 2. Delete element from index (shift left)\n";
        std::cout << " 3. Search element sequentially (first match)\n";
        std::cout << " 4. Display database contents\n";
        std::cout << " 5. Run automated test demonstration\n";
        std::cout << " 6. Exit\n";
        std::cout << "Enter your choice (1-6): ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERROR] Invalid input. Please enter a number between 1 and 6.\n\n";
            continue;
        }

        if (choice == 1) {
            int index, value;
            std::cout << "Enter valid index [0 to " << db.size() << "]: ";
            std::cin >> index;
            std::cout << "Enter numeric value to insert: ";
            std::cin >> value;
            db.insertAt(index, value);
            db.display();
        } else if (choice == 2) {
            if (db.isEmpty()) {
                std::cout << "[ERROR] Database is empty! Nothing to delete.\n\n";
                continue;
            }
            int index, deletedVal;
            std::cout << "Enter target index to delete [0 to " << (db.size() - 1) << "]: ";
            std::cin >> index;
            if (db.deleteAt(index, deletedVal)) {
                db.display();
            }
        } else if (choice == 3) {
            int target, comparisons;
            std::cout << "Enter numeric value to search: ";
            std::cin >> target;
            int matchIdx = db.searchSequential(target, comparisons);
            if (matchIdx != -1) {
                std::cout << "[FOUND] First match for " << target << " is at index " 
                          << matchIdx << " (Comparisons made: " << comparisons << ").\n\n";
            } else {
                std::cout << "[NOT FOUND] Value " << target << " does not exist in array (Comparisons made: " 
                          << comparisons << ").\n\n";
            }
        } else if (choice == 4) {
            db.display();
        } else if (choice == 5) {
            runAutomatedDemo();
        } else if (choice == 6) {
            std::cout << "Exiting program. Goodbye!\n";
            break;
        } else {
            std::cout << "[ERROR] Invalid option selected. Please choose 1-6.\n\n";
        }
    }

    return 0;
}
