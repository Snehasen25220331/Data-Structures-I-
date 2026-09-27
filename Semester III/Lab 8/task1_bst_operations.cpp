/**
 * LAB SHEET 8 - Task 1: Binary Search Tree (BST) Operations
 * 
 * Objective:
 * Write a standard Binary Search Tree supporting element insertion
 * and ordered deletion.
 * 
 * Theory:
 * BST Invariant: For any node X, all keys in left subtree < X->val < all keys in right subtree.
 * Deletion Cases:
 * 1. Node is a leaf: Simply remove it.
 * 2. Node has 1 child: Link parent directly to child and delete node.
 * 3. Node has 2 children: Find in-order successor (smallest in right subtree),
 *    copy its value to target node, and recursively delete the successor.
 */

#include <iostream>
#include <iomanip>
#include <vector>

struct BSTNode {
    int val;
    BSTNode* left;
    BSTNode* right;

    explicit BSTNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    BSTNode* root;

    BSTNode* insertHelper(BSTNode* node, int key) {
        if (!node) {
            std::cout << "  [BST Insert] Inserted key " << key << " as new node.\n";
            return new BSTNode(key);
        }
        if (key < node->val) {
            node->left = insertHelper(node->left, key);
        } else if (key > node->val) {
            node->right = insertHelper(node->right, key);
        } else {
            std::cout << "  [BST Insert] Duplicate key " << key << " ignored.\n";
        }
        return node;
    }

    BSTNode* findMin(BSTNode* node) const {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    BSTNode* deleteHelper(BSTNode* node, int key, bool& deleted) {
        if (!node) {
            return nullptr;
        }

        if (key < node->val) {
            node->left = deleteHelper(node->left, key, deleted);
        } else if (key > node->val) {
            node->right = deleteHelper(node->right, key, deleted);
        } else {
            // Found target node
            deleted = true;

            // Case 1 & 2: 0 or 1 child
            if (!node->left) {
                BSTNode* temp = node->right;
                delete node;
                std::cout << "  [BST Delete] Node " << key << " (0 or 1 child) deleted.\n";
                return temp;
            } else if (!node->right) {
                BSTNode* temp = node->left;
                delete node;
                std::cout << "  [BST Delete] Node " << key << " (1 child) deleted.\n";
                return temp;
            }

            // Case 3: 2 children
            // Find in-order successor (minimum in right subtree)
            BSTNode* successor = findMin(node->right);
            std::cout << "  [BST Delete] Node " << key << " has 2 children. Replacing with In-order Successor " 
                      << successor->val << ".\n";
            node->val = successor->val;
            // Delete successor from right subtree
            node->right = deleteHelper(node->right, successor->val, deleted);
        }
        return node;
    }

    void inorderHelper(BSTNode* node, std::vector<int>& out) const {
        if (!node) return;
        inorderHelper(node->left, out);
        out.push_back(node->val);
        inorderHelper(node->right, out);
    }

    void printTreeHelper(BSTNode* node, int indent) const {
        if (node != nullptr) {
            if (node->right) printTreeHelper(node->right, indent + 6);
            if (indent) std::cout << std::setw(indent) << ' ';
            std::cout << "[" << node->val << "]\n";
            if (node->left) printTreeHelper(node->left, indent + 6);
        }
    }

    void freeTree(BSTNode* node) {
        if (node) {
            freeTree(node->left);
            freeTree(node->right);
            delete node;
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { freeTree(root); }

    void insert(int key) {
        root = insertHelper(root, key);
    }

    bool remove(int key) {
        bool deleted = false;
        root = deleteHelper(root, key, deleted);
        return deleted;
    }

    void displayInorder() const {
        std::vector<int> out;
        inorderHelper(root, out);
        std::cout << "In-Order Sequence (Sorted): [ ";
        for (int v : out) std::cout << v << " ";
        std::cout << "]\n";
    }

    void displayHierarchy() const {
        std::cout << "\nTree Structure (Rotated 90 deg CCW):\n";
        printTreeHelper(root, 0);
        std::cout << "\n";
    }
};

int main() {
    std::cout << "======================================================================\n";
    std::cout << "          LAB 8 - TASK 1: BINARY SEARCH TREE OPERATIONS               \n";
    std::cout << "======================================================================\n\n";

    BinarySearchTree bst;

    std::cout << "--- 1. Testing Element Insertions ---\n";
    std::vector<int> keys = {50, 30, 70, 20, 40, 60, 80};
    for (int k : keys) {
        bst.insert(k);
    }
    bst.displayInorder();
    bst.displayHierarchy();

    std::cout << "----------------------------------------------------------------------\n";
    std::cout << "--- 2. Testing Ordered Deletion Cases ---\n";

    // Case 1: Leaf node (20)
    std::cout << "\n>> Deleting Leaf Node (20):\n";
    bst.remove(20);
    bst.displayInorder();

    // Case 2: Node with 1 child (30 has child 40)
    std::cout << "\n>> Deleting Node with 1 Child (30):\n";
    bst.remove(30);
    bst.displayInorder();

    // Case 3: Node with 2 children (Root 50 has children 40 and 70)
    std::cout << "\n>> Deleting Node with 2 Children (Root 50):\n";
    bst.remove(50);
    bst.displayInorder();
    bst.displayHierarchy();

    std::cout << "======================================================================\n";
    return 0;
}
