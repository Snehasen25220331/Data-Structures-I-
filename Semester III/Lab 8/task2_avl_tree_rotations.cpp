/**
 * LAB SHEET 8 - Task 2: AVL Tree Rotations (LL, RR, LR, RL)
 * 
 * Objective:
 * Implement an AVL insertion tracker that monitors balance factors
 * and executes single or double transformations (LL, RR, LR, RL)
 * when a node becomes unbalanced.
 * 
 * Theory:
 * Balance Factor (BF) = Height(Left Subtree) - Height(Right Subtree)
 * Valid AVL Property: -1 <= BF <= 1
 * Rebalancing Transformations:
 * 1. LL (Left-Left): Single Right Rotation
 * 2. RR (Right-Right): Single Left Rotation
 * 3. LR (Left-Right): Left Rotation on Left Child, then Right Rotation on Root
 * 4. RL (Right-Left): Right Rotation on Right Child, then Left Rotation on Root
 */

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

struct AVLNode {
    int key;
    int height;
    AVLNode* left;
    AVLNode* right;

    explicit AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* n) const {
        return n ? n->height : 0;
    }

    int getBalanceFactor(AVLNode* n) const {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    void updateHeight(AVLNode* n) {
        if (n) {
            n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
        }
    }

    // Right Rotation (LL fix)
    AVLNode* rightRotate(AVLNode* y) {
        std::cout << "    [ROTATION] Executing Right Rotation around node " << y->key << "\n";
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        return x; // New root
    }

    // Left Rotation (RR fix)
    AVLNode* leftRotate(AVLNode* x) {
        std::cout << "    [ROTATION] Executing Left Rotation around node " << x->key << "\n";
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        return y; // New root
    }

    AVLNode* insertHelper(AVLNode* node, int key) {
        // Step 1: Normal BST Insertion
        if (!node) {
            std::cout << "  Inserted key " << key << "\n";
            return new AVLNode(key);
        }

        if (key < node->key) {
            node->left = insertHelper(node->left, key);
        } else if (key > node->key) {
            node->right = insertHelper(node->right, key);
        } else {
            return node; // Duplicate keys not allowed
        }

        // Step 2: Update height of this ancestor node
        updateHeight(node);

        // Step 3: Check Balance Factor
        int balance = getBalanceFactor(node);

        // Step 4: Rebalance if unbalanced

        // LL Case: Left-Left Imbalance
        if (balance > 1 && key < node->left->key) {
            std::cout << "  >>> IMBALANCE at Node " << node->key 
                      << " (BF=" << balance << "): Triggering LL Transformation (Single Right Rotate) <<<\n";
            return rightRotate(node);
        }

        // RR Case: Right-Right Imbalance
        if (balance < -1 && key > node->right->key) {
            std::cout << "  >>> IMBALANCE at Node " << node->key 
                      << " (BF=" << balance << "): Triggering RR Transformation (Single Left Rotate) <<<\n";
            return leftRotate(node);
        }

        // LR Case: Left-Right Imbalance
        if (balance > 1 && key > node->left->key) {
            std::cout << "  >>> IMBALANCE at Node " << node->key 
                      << " (BF=" << balance << "): Triggering LR Transformation (Double: Left-Right Rotate) <<<\n";
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL Case: Right-Left Imbalance
        if (balance < -1 && key < node->right->key) {
            std::cout << "  >>> IMBALANCE at Node " << node->key 
                      << " (BF=" << balance << "): Triggering RL Transformation (Double: Right-Left Rotate) <<<\n";
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void printTreeHelper(AVLNode* node, int indent) const {
        if (node != nullptr) {
            if (node->right) printTreeHelper(node->right, indent + 8);
            if (indent) std::cout << std::setw(indent) << ' ';
            std::cout << "[" << node->key << " | BF=" << getBalanceFactor(node) << "]\n";
            if (node->left) printTreeHelper(node->left, indent + 8);
        }
    }

    void freeTree(AVLNode* node) {
        if (node) {
            freeTree(node->left);
            freeTree(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { freeTree(root); }

    void insert(int key) {
        std::cout << ">> Inserting key " << key << ":\n";
        root = insertHelper(root, key);
        std::cout << "Current Tree State:\n";
        printTreeHelper(root, 0);
        std::cout << "----------------------------------------------------------------------\n";
    }
};

int main() {
    std::cout << "======================================================================\n";
    std::cout << "            LAB 8 - TASK 2: AVL TREE ROTATION TRACKER                 \n";
    std::cout << "======================================================================\n\n";

    AVLTree avl;

    // 1. LL Rotation demonstration: Insert 30, 20, 10
    std::cout << ">>> 1. DEMONSTRATING LL ROTATION (Single Right Rotation) <<<\n";
    avl.insert(30);
    avl.insert(20);
    avl.insert(10); // Causes LL imbalance at 30

    // 2. RR Rotation demonstration: Insert 40, 50
    std::cout << "\n>>> 2. DEMONSTRATING RR ROTATION (Single Left Rotation) <<<\n";
    avl.insert(40);
    avl.insert(50); // Causes RR imbalance

    // 3. LR Rotation demonstration: Insert 25
    std::cout << "\n>>> 3. DEMONSTRATING LR ROTATION (Double: Left-Right) <<<\n";
    avl.insert(25);

    std::cout << "======================================================================\n";
    std::cout << "                 AVL ROTATION DEMO COMPLETE                           \n";
    std::cout << "======================================================================\n";

    return 0;
}
