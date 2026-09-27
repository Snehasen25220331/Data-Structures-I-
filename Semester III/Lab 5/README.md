# Lab Assignment 5: Expression Conversion & Evaluation

## Part A: Programming Exercises

### Objectives
1. **Infix to Postfix Conversion**:
   - Design an algebraic translation program using a custom operator stack that accepts a valid string expression in Infix format (e.g., `A+(B*C)`) and correctly converts it to Postfix format (e.g., `ABC*+`).
2. **Postfix Evaluation**:
   - Write an Expression Evaluation program that processes a completed string in Postfix format, utilizing an integer stack to compute and print the final mathematical output.

---

## File Structure

| File | Description | Complexity | Key Concept |
| :--- | :--- | :--- | :--- |
| `task1_infix_to_postfix.cpp` | Shunting-Yard conversion algorithm with custom stack and step-by-step trace | $O(n)$ Time, $O(n)$ Space | Operator precedence, associativity, parentheses matching |
| `task2_postfix_evaluation.cpp` | Reverse Polish Notation evaluator with integer stack | $O(n)$ Time, $O(n)$ Space | Binary operator evaluation, stack operands |

---

## How to Compile and Run

```bash
# Task 1: Infix to Postfix Conversion
clang++ -std=c++17 -O2 task1_infix_to_postfix.cpp -o infix2post
./infix2post --demo

# Task 2: Postfix Evaluation
clang++ -std=c++17 -O2 task2_postfix_evaluation.cpp -o eval_post
./eval_post --demo
```
