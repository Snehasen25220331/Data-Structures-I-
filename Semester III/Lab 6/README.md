# Lab Sheet 6: Binary Tree Structures & Traversals

## Syllabus Reference: Unit 6 (Lab Manual)
**Target Concepts**: Non-linear structural allocation, pointer tracking, tree recursion vs iteration.

---

## Objectives
1. **Tree Construction**: Create an instantiation tool that maps dynamic node elements with discrete left and right sub-pointers.
2. **Traversals**: Code structural tree parsing loops executing Inorder, Preorder, and Postorder operations.
   - Provide both a clean **recursive framework** and a manual **stack-driven iterative framework**.

---

## File Structure

| File | Description | Complexity |
| :--- | :--- | :--- |
| `task1_tree_construction_and_traversals.cpp` | Dynamic pointer tree building + Inorder, Preorder, Postorder in both Recursive and Iterative Stack implementations | Time: $O(n)$, Space: $O(h)$ where $h$ is tree height |

---

## Traversal Algorithms Summary

1. **Inorder ($L \to \text{Root} \to R$)**:
   - *Recursive*: `inorder(left); print(val); inorder(right);`
   - *Iterative*: Push all left children onto stack; pop, visit, traverse right child.
2. **Preorder ($\text{Root} \to L \to R$)**:
   - *Recursive*: `print(val); preorder(left); preorder(right);`
   - *Iterative*: Stack initialized with root; pop node, push right child then left child.
3. **Postorder ($L \to R \to \text{Root}$)**:
   - *Recursive*: `postorder(left); postorder(right); print(val);`
   - *Iterative*: Two-stack algorithm where $S_1$ drives traversal and $S_2$ collects reversed postorder.

---

## How to Compile and Run

```bash
clang++ -std=c++17 -O2 task1_tree_construction_and_traversals.cpp -o tree_traversals
./tree_traversals
```
