/**
 * LAB SHEET 6: Binary Tree Structures & Traversals
 * 
 * Objectives:
 * 1. Tree Construction: Create an instantiation tool that maps dynamic node elements
 *    with discrete left and right sub-pointers.
 * 2. Traversals: Code structural tree parsing loops executing Inorder, Preorder, and Postorder operations.
 *    Provide both a clean recursive framework and a manual stack-driven iterative framework.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>
#include <queue>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        destroy(root);
    }

    void destroy(TreeNode* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    // Dynamic node connection methods
    static TreeNode* createNode(int val) {
        return new TreeNode(val);
    }

    void attachLeft(TreeNode* parent, TreeNode* child) {
        if (parent) parent->left = child;
    }

    void attachRight(TreeNode* parent, TreeNode* child) {
        if (parent) parent->right = child;
    }

    // ========================================================================
    // RECURSIVE TRAVERSALS
    // ========================================================================
    void inorderRecursive(TreeNode* node, std::vector<int>& out) const {
        if (!node) return;
        inorderRecursive(node->left, out);
        out.push_back(node->val);
        inorderRecursive(node->right, out);
    }

    void preorderRecursive(TreeNode* node, std::vector<int>& out) const {
        if (!node) return;
        out.push_back(node->val);
        preorderRecursive(node->left, out);
        preorderRecursive(node->right, out);
    }

    void postorderRecursive(TreeNode* node, std::vector<int>& out) const {
        if (!node) return;
        postorderRecursive(node->left, out);
        postorderRecursive(node->right, out);
        out.push_back(node->val);
    }

    // ========================================================================
    // ITERATIVE TRAVERSALS (STACK-DRIVEN)
    // ========================================================================
    std::vector<int> inorderIterative() const {
        std::vector<int> out;
        std::stack<TreeNode*> s;
        TreeNode* curr = root;

        while (curr != nullptr || !s.empty()) {
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            out.push_back(curr->val);
            curr = curr->right;
        }
        return out;
    }

    std::vector<int> preorderIterative() const {
        std::vector<int> out;
        if (!root) return out;

        std::stack<TreeNode*> s;
        s.push(root);

        while (!s.empty()) {
            TreeNode* curr = s.top();
            s.pop();
            out.push_back(curr->val);

            // Push right child first so left is processed first
            if (curr->right) s.push(curr->right);
            if (curr->left) s.push(curr->left);
        }
        return out;
    }

    std::vector<int> postorderIterative() const {
        std::vector<int> out;
        if (!root) return out;

        // Two-stack technique for clean postorder
        std::stack<TreeNode*> s1, s2;
        s1.push(root);

        while (!s1.empty()) {
            TreeNode* curr = s1.top();
            s1.pop();
            s2.push(curr);

            if (curr->left) s1.push(curr->left);
            if (curr->right) s1.push(curr->right);
        }

        while (!s2.empty()) {
            out.push_back(s2.top()->val);
            s2.pop();
        }
        return out;
    }

    // Visual ASCII tree printer
    void printHierarchy(TreeNode* node, int indent = 0) const {
        if (node != nullptr) {
            if (node->right) printHierarchy(node->right, indent + 6);
            if (indent) std::cout << std::setw(indent) << ' ';
            std::cout << "[" << node->val << "]\n";
            if (node->left) printHierarchy(node->left, indent + 6);
        }
    }
};

void printVector(const std::vector<int>& v) {
    std::cout << "[ ";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << (i + 1 < v.size() ? " -> " : " ");
    }
    std::cout << "]\n";
}

int main() {
    std::cout << "======================================================================\n";
    std::cout << "      LAB 6: BINARY TREE CONSTRUCTION & DUAL TRAVERSAL SUITE          \n";
    std::cout << "======================================================================\n\n";

    BinaryTree tree;

    // --- 1. Tree Construction using discrete sub-pointers ---
    //            1
    //          /   \
    //         2     3
    //        / \   / \
    //       4   5 6   7
    tree.root = BinaryTree::createNode(1);
    TreeNode* n2 = BinaryTree::createNode(2);
    TreeNode* n3 = BinaryTree::createNode(3);
    TreeNode* n4 = BinaryTree::createNode(4);
    TreeNode* n5 = BinaryTree::createNode(5);
    TreeNode* n6 = BinaryTree::createNode(6);
    TreeNode* n7 = BinaryTree::createNode(7);

    tree.attachLeft(tree.root, n2);
    tree.attachRight(tree.root, n3);

    tree.attachLeft(n2, n4);
    tree.attachRight(n2, n5);

    tree.attachLeft(n3, n6);
    tree.attachRight(n3, n7);

    std::cout << "1. Tree Visual Hierarchy (Rotated 90 deg counter-clockwise):\n";
    tree.printHierarchy(tree.root);
    std::cout << "\n";

    // --- 2. Inorder Traversals ---
    std::vector<int> inRec;
    tree.inorderRecursive(tree.root, inRec);
    std::vector<int> inIter = tree.inorderIterative();

    std::cout << "----------------------------------------------------------------------\n";
    std::cout << ">>> INORDER TRAVERSAL (Left -> Root -> Right) <<<\n";
    std::cout << "  - Recursive Framework: ";
    printVector(inRec);
    std::cout << "  - Iterative Framework: ";
    printVector(inIter);
    std::cout << "  - Equivalence Check  : " << (inRec == inIter ? "MATCHED (PASSED)" : "FAILED") << "\n";

    // --- 3. Preorder Traversals ---
    std::vector<int> preRec;
    tree.preorderRecursive(tree.root, preRec);
    std::vector<int> preIter = tree.preorderIterative();

    std::cout << "----------------------------------------------------------------------\n";
    std::cout << ">>> PREORDER TRAVERSAL (Root -> Left -> Right) <<<\n";
    std::cout << "  - Recursive Framework: ";
    printVector(preRec);
    std::cout << "  - Iterative Framework: ";
    printVector(preIter);
    std::cout << "  - Equivalence Check  : " << (preRec == preIter ? "MATCHED (PASSED)" : "FAILED") << "\n";

    // --- 4. Postorder Traversals ---
    std::vector<int> postRec;
    tree.postorderRecursive(tree.root, postRec);
    std::vector<int> postIter = tree.postorderIterative();

    std::cout << "----------------------------------------------------------------------\n";
    std::cout << ">>> POSTORDER TRAVERSAL (Left -> Right -> Root) <<<\n";
    std::cout << "  - Recursive Framework: ";
    printVector(postRec);
    std::cout << "  - Iterative Framework: ";
    printVector(postIter);
    std::cout << "  - Equivalence Check  : " << (postRec == postIter ? "MATCHED (PASSED)" : "FAILED") << "\n";

    std::cout << "======================================================================\n";
    return 0;
}
