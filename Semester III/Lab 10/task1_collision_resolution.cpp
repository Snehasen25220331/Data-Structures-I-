/**
 * LAB SHEET 10 - Task 1: Collision Resolution Framework
 * 
 * Objectives:
 * 1. Open Hashing structure using linked lists for separate chaining.
 * 2. Closed Hashing structure using linear probing and an automatic table
 *    resizing function (rehashing when load factor >= 0.70).
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

// ============================================================================
// PART 1: OPEN HASHING (SEPARATE CHAINING)
// ============================================================================
struct ChainNode {
    int key;
    std::string value;
    ChainNode* next;

    ChainNode(int k, const std::string& v) : key(k), value(v), next(nullptr) {}
};

class OpenHashTable {
private:
    int bucketCount;
    std::vector<ChainNode*> table;
    int totalElements;

    int hashFunction(int key) const {
        return (key % bucketCount + bucketCount) % bucketCount;
    }

public:
    explicit OpenHashTable(int buckets = 7) 
        : bucketCount(buckets), table(buckets, nullptr), totalElements(0) {}

    ~OpenHashTable() {
        for (int i = 0; i < bucketCount; ++i) {
            ChainNode* curr = table[i];
            while (curr != nullptr) {
                ChainNode* temp = curr->next;
                delete curr;
                curr = temp;
            }
        }
    }

    void insert(int key, const std::string& value) {
        int idx = hashFunction(key);
        ChainNode* curr = table[idx];

        // Update if key already exists
        while (curr != nullptr) {
            if (curr->key == key) {
                curr->value = value;
                std::cout << "  [Open Hash] Key " << key << " updated in bucket " << idx << ".\n";
                return;
            }
            curr = curr->next;
        }

        // Insert at beginning of bucket chain
        ChainNode* newNode = new ChainNode(key, value);
        newNode->next = table[idx];
        table[idx] = newNode;
        ++totalElements;
        std::cout << "  [Open Hash] Inserted (" << key << ", \"" << value 
                  << "\") into bucket " << idx << " (Chain length increased).\n";
    }

    bool search(int key, std::string& resultValue) const {
        int idx = hashFunction(key);
        ChainNode* curr = table[idx];
        int probes = 0;
        while (curr != nullptr) {
            ++probes;
            if (curr->key == key) {
                resultValue = curr->value;
                std::cout << "  [Open Hash] Found key " << key << " with value \"" 
                          << resultValue << "\" in bucket " << idx 
                          << " after " << probes << " probe(s).\n";
                return true;
            }
            curr = curr->next;
        }
        std::cout << "  [Open Hash] Key " << key << " not found in bucket " << idx << ".\n";
        return false;
    }

    bool remove(int key) {
        int idx = hashFunction(key);
        ChainNode* curr = table[idx];
        ChainNode* prev = nullptr;

        while (curr != nullptr) {
            if (curr->key == key) {
                if (prev == nullptr) {
                    table[idx] = curr->next;
                } else {
                    prev->next = curr->next;
                }
                delete curr;
                --totalElements;
                std::cout << "  [Open Hash] Key " << key << " removed from bucket " << idx << ".\n";
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        std::cout << "  [Open Hash] Key " << key << " not found. Deletion failed.\n";
        return false;
    }

    void display() const {
        std::cout << "\n--- Open Hash Table (Separate Chaining) State ---\n";
        for (int i = 0; i < bucketCount; ++i) {
            std::cout << "Bucket [" << i << "]: ";
            ChainNode* curr = table[i];
            if (curr == nullptr) {
                std::cout << "EMPTY\n";
            } else {
                while (curr != nullptr) {
                    std::cout << "-> [" << curr->key << ": \"" << curr->value << "\"] ";
                    curr = curr->next;
                }
                std::cout << "-> NULL\n";
            }
        }
        std::cout << "Total elements: " << totalElements 
                  << " | Load Factor: " << std::fixed << std::setprecision(2) 
                  << static_cast<double>(totalElements) / bucketCount << "\n\n";
    }
};

// ============================================================================
// PART 2: CLOSED HASHING (LINEAR PROBING WITH AUTOMATIC REHASHING)
// ============================================================================
enum EntryState { EMPTY, OCCUPIED, DELETED };

struct HashEntry {
    int key;
    std::string value;
    EntryState state;

    HashEntry() : key(0), value(""), state(EMPTY) {}
};

class ClosedHashTable {
private:
    int capacity;
    int currentSize;
    std::vector<HashEntry> table;
    const double LOAD_FACTOR_THRESHOLD = 0.70;

    int hashFunction(int key, int cap) const {
        return (key % cap + cap) % cap;
    }

    bool isPrime(int n) const {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    int nextPrime(int n) const {
        while (!isPrime(n)) {
            ++n;
        }
        return n;
    }

    /**
     * Automatic Rehashing Function:
     * Triggered when load factor (size / capacity) >= 0.70.
     * Doubles capacity to the next prime, rehashes all active entries.
     */
    void rehash() {
        int oldCapacity = capacity;
        int newCapacity = nextPrime(capacity * 2);
        std::cout << "\n  >>> [REHASH TRIGGERED] Load factor >= " << LOAD_FACTOR_THRESHOLD 
                  << "! Resizing table from " << oldCapacity << " to " << newCapacity << " <<<\n";

        std::vector<HashEntry> oldTable = table;

        capacity = newCapacity;
        currentSize = 0;
        table.assign(newCapacity, HashEntry());

        for (const auto& entry : oldTable) {
            if (entry.state == OCCUPIED) {
                insertWithoutRehash(entry.key, entry.value);
            }
        }
        std::cout << "  >>> [REHASH COMPLETE] All entries rehashed successfully into new table. <<<\n\n";
    }

    void insertWithoutRehash(int key, const std::string& value) {
        int idx = hashFunction(key, capacity);
        for (int i = 0; i < capacity; ++i) {
            int probeIdx = (idx + i) % capacity;
            if (table[probeIdx].state == EMPTY || table[probeIdx].state == DELETED) {
                table[probeIdx].key = key;
                table[probeIdx].value = value;
                table[probeIdx].state = OCCUPIED;
                ++currentSize;
                return;
            } else if (table[probeIdx].state == OCCUPIED && table[probeIdx].key == key) {
                table[probeIdx].value = value;
                return;
            }
        }
    }

public:
    explicit ClosedHashTable(int initialCap = 5) 
        : capacity(initialCap), currentSize(0), table(initialCap) {}

    double loadFactor() const {
        return static_cast<double>(currentSize) / capacity;
    }

    void insert(int key, const std::string& value) {
        // Check load factor before insertion
        if (loadFactor() >= LOAD_FACTOR_THRESHOLD) {
            rehash();
        }

        int idx = hashFunction(key, capacity);
        for (int i = 0; i < capacity; ++i) {
            int probeIdx = (idx + i) % capacity;

            if (table[probeIdx].state == EMPTY || table[probeIdx].state == DELETED) {
                table[probeIdx].key = key;
                table[probeIdx].value = value;
                table[probeIdx].state = OCCUPIED;
                ++currentSize;
                std::cout << "  [Closed Hash] Key " << key << " inserted at slot " << probeIdx 
                          << " (Probed steps: " << i << ")\n";
                return;
            } else if (table[probeIdx].state == OCCUPIED && table[probeIdx].key == key) {
                table[probeIdx].value = value;
                std::cout << "  [Closed Hash] Key " << key << " updated at slot " << probeIdx << ".\n";
                return;
            }
        }
        std::cerr << "  [Closed Hash] Table is full! Insertion failed.\n";
    }

    bool search(int key, std::string& resultValue) const {
        int idx = hashFunction(key, capacity);
        for (int i = 0; i < capacity; ++i) {
            int probeIdx = (idx + i) % capacity;
            if (table[probeIdx].state == EMPTY) {
                // Empty slot terminates search in linear probing
                break;
            }
            if (table[probeIdx].state == OCCUPIED && table[probeIdx].key == key) {
                resultValue = table[probeIdx].value;
                std::cout << "  [Closed Hash] Found key " << key << " -> \"" 
                          << resultValue << "\" at slot " << probeIdx 
                          << " after " << (i + 1) << " probe(s).\n";
                return true;
            }
        }
        std::cout << "  [Closed Hash] Key " << key << " NOT FOUND.\n";
        return false;
    }

    bool remove(int key) {
        int idx = hashFunction(key, capacity);
        for (int i = 0; i < capacity; ++i) {
            int probeIdx = (idx + i) % capacity;
            if (table[probeIdx].state == EMPTY) {
                break;
            }
            if (table[probeIdx].state == OCCUPIED && table[probeIdx].key == key) {
                table[probeIdx].state = DELETED; // Mark as tombstone
                --currentSize;
                std::cout << "  [Closed Hash] Key " << key << " at slot " << probeIdx 
                          << " deleted (marked DELETED/tombstone).\n";
                return true;
            }
        }
        std::cout << "  [Closed Hash] Key " << key << " not found. Deletion failed.\n";
        return false;
    }

    void display() const {
        std::cout << "\n--- Closed Hash Table (Linear Probing) State ---\n";
        std::cout << "Slot | Status   | Key     | Value\n";
        std::cout << "--------------------------------------\n";
        for (int i = 0; i < capacity; ++i) {
            std::cout << std::setw(4) << i << " | ";
            if (table[i].state == OCCUPIED) {
                std::cout << "OCCUPIED | " << std::setw(7) << table[i].key 
                          << " | " << table[i].value << "\n";
            } else if (table[i].state == DELETED) {
                std::cout << "DELETED  |       - | <tombstone>\n";
            } else {
                std::cout << "EMPTY    |       - | -\n";
            }
        }
        std::cout << "--------------------------------------\n";
        std::cout << "Elements: " << currentSize << "/" << capacity 
                  << " | Load Factor: " << std::fixed << std::setprecision(2) 
                  << loadFactor() << " (Threshold: " << LOAD_FACTOR_THRESHOLD << ")\n\n";
    }
};

int main() {
    std::cout << "========================================================================\n";
    std::cout << "         LAB 10 - TASK 1: COLLISION RESOLUTION FRAMEWORK                \n";
    std::cout << "========================================================================\n\n";

    // --- 1. OPEN HASHING (CHAINING) ---
    std::cout << ">>> 1. DEMONSTRATING OPEN HASHING (CHAINING) <<<\n";
    OpenHashTable openTable(5); // 5 buckets

    // Keys chosen to trigger deliberate collisions (modulo 5: 10, 15, 20 all map to bucket 0)
    openTable.insert(10, "Alice");
    openTable.insert(15, "Bob");     // Collides with 10
    openTable.insert(20, "Charlie"); // Collides with 10, 15
    openTable.insert(7, "David");    // Maps to bucket 2
    openTable.insert(12, "Eve");     // Maps to bucket 2 (collides with 7)
    openTable.display();

    std::string val;
    openTable.search(15, val);
    openTable.search(99, val);

    openTable.remove(15);
    openTable.display();

    // --- 2. CLOSED HASHING (LINEAR PROBING + REHASHING) ---
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << ">>> 2. DEMONSTRATING CLOSED HASHING (LINEAR PROBING & REHASHING) <<<\n";
    ClosedHashTable closedTable(5); // Initial capacity 5 (threshold 0.70 => 3 elements max before rehash)

    closedTable.insert(10, "Node_A"); // 10 % 5 = 0
    closedTable.insert(15, "Node_B"); // 15 % 5 = 0 (collides -> probed to slot 1)
    closedTable.insert(20, "Node_C"); // 20 % 5 = 0 (collides -> probed to slot 2)
    closedTable.display();

    // Inserting 4th element will trigger load factor >= 0.70 (3/5 = 0.60 -> inserting 4th triggers rehash!)
    std::cout << "Inserting 4th element (triggers automatic resizing & rehashing):\n";
    closedTable.insert(25, "Node_D");
    closedTable.display();

    closedTable.insert(33, "Node_E");
    closedTable.display();

    closedTable.search(20, val);
    closedTable.remove(15);
    closedTable.display();

    // Ensure search still works past the tombstone
    closedTable.search(20, val);

    std::cout << "========================================================================\n";
    std::cout << "                   COLLISION FRAMEWORK DEMO COMPLETE                    \n";
    std::cout << "========================================================================\n";

    return 0;
}
