/**
 * LAB SHEET 8 - Task 3: B-Tree (Order-3 / 2-3 Tree) Insertion Simulator
 * 
 * Objective:
 * Write a mock framework managing basic item additions inside an order-3 (M=3)
 * B-Tree node layout, handling node splitting when capacity is exceeded.
 * 
 * Theory:
 * In an Order-3 B-Tree:
 * - Each node holds at most M - 1 = 2 keys.
 * - When a 3rd key is inserted, the node overflows (3 keys: [k0, k1, k2]).
 * - The node splits:
 *     - Left Node keeps k0
 *     - Median key k1 is promoted to parent
 *     - Right Node gets k2
 * - If root splits, a new root is created and tree height increments.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct BTreeNode {
    std::vector<int> keys;
    std::vector<BTreeNode*> children;
    bool isLeaf;

    explicit BTreeNode(bool leaf = true) : isLeaf(leaf) {}

    ~BTreeNode() {
        for (auto child : children) {
            delete child;
        }
    }
};

class BTreeSimulator {
private:
    BTreeNode* root;
    const int MAX_KEYS = 2; // Order-3 allows at most 2 keys

    // Recursive insertion helper. Returns a newly split node (if overflow occurred) along with promoted key
    BTreeNode* insertRecursive(BTreeNode* node, int key, int& promotedKey) {
        if (node->isLeaf) {
            // Insert key into leaf in sorted order
            node->keys.push_back(key);
            std::sort(node->keys.begin(), node->keys.end());

            std::cout << "  Inserted key " << key << " into leaf. Current node keys: [ ";
            for (int k : node->keys) std::cout << k << " ";
            std::cout << "]\n";

            // Check if node exceeded capacity
            if (node->keys.size() > static_cast<size_t>(MAX_KEYS)) {
                return splitNode(node, promotedKey);
            }
            return nullptr;
        }

        // Internal node: find child to descend into
        size_t i = 0;
        while (i < node->keys.size() && key > node->keys[i]) {
            ++i;
        }

        int childPromotedKey = 0;
        BTreeNode* newChild = insertRecursive(node->children[i], key, childPromotedKey);

        if (newChild != nullptr) {
            // Child split! Insert promoted key and new child into current node
            node->keys.insert(node->keys.begin() + i, childPromotedKey);
            node->children.insert(node->children.begin() + i + 1, newChild);

            std::cout << "  Added promoted key " << childPromotedKey << " to parent node. Parent keys: [ ";
            for (int k : node->keys) std::cout << k << " ";
            std::cout << "]\n";

            // If current node also exceeded capacity, split it as well
            if (node->keys.size() > static_cast<size_t>(MAX_KEYS)) {
                return splitNode(node, promotedKey);
            }
        }
        return nullptr;
    }

    BTreeNode* splitNode(BTreeNode* node, int& promotedKey) {
        std::cout << "  >>> [NODE OVERFLOW & SPLIT] Node has 3 keys: [ " 
                  << node->keys[0] << " " << node->keys[1] << " " << node->keys[2] << " ] <<<\n";

        promotedKey = node->keys[1];
        std::cout << "      Promoting median key: " << promotedKey << "\n";

        BTreeNode* rightSibling = new BTreeNode(node->isLeaf);
        rightSibling->keys.push_back(node->keys[2]);

        if (!node->isLeaf) {
            rightSibling->children.push_back(node->children[2]);
            rightSibling->children.push_back(node->children[3]);
            node->children.resize(2);
        }

        node->keys.resize(1); // keeps keys[0]

        std::cout << "      Left node: [" << node->keys[0] << "] | Right node: [" 
                  << rightSibling->keys[0] << "]\n";

        return rightSibling;
    }

    void printTreeHelper(BTreeNode* node, int level) const {
        if (!node) return;
        std::cout << "  Level " << level << ": [ ";
        for (int k : node->keys) std::cout << k << " ";
        std::cout << "]\n";

        if (!node->isLeaf) {
            for (auto child : node->children) {
                printTreeHelper(child, level + 1);
            }
        }
    }

public:
    BTreeSimulator() : root(nullptr) {}
    ~BTreeSimulator() { delete root; }

    void insert(int key) {
        std::cout << "\n>> Inserting key " << key << " into Order-3 B-Tree:\n";
        if (!root) {
            root = new BTreeNode(true);
            root->keys.push_back(key);
            std::cout << "  Initialized root with key " << key << ".\n";
            return;
        }

        int promotedKey = 0;
        BTreeNode* newChild = insertRecursive(root, key, promotedKey);

        if (newChild != nullptr) {
            // Root split! Create new root and increment tree height
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->keys.push_back(promotedKey);
            newRoot->children.push_back(root);
            newRoot->children.push_back(newChild);
            root = newRoot;
            std::cout << "  >>> Tree height grew! New root key: [" << promotedKey << "] <<<\n";
        }

        std::cout << "--- Current B-Tree Layout ---\n";
        printTreeHelper(root, 0);
        std::cout << "----------------------------------------------------------------------\n";
    }
};

int main() {
    std::cout << "======================================================================\n";
    std::cout << "        LAB 8 - TASK 3: B-TREE (ORDER-3 / M=3) INSERTION SIMULATOR    \n";
    std::cout << "======================================================================\n";

    BTreeSimulator btree;
    std::vector<int> dataset = {10, 20, 30, 40, 50, 60, 70};

    for (int key : dataset) {
        btree.insert(key);
    }

    std::cout << "\n======================================================================\n";
    std::cout << "                 B-TREE SIMULATOR DEMO COMPLETE                       \n";
    std::cout << "======================================================================\n";

    return 0;
}
