/**
 * LAB ASSIGNMENT 5 - Task 1: Infix to Postfix Conversion
 * 
 * Objective:
 * Design an algebraic translation program using a custom operator stack
 * that accepts a valid string expression in Infix format (e.g., A+(B*C))
 * and correctly converts it to Postfix format (e.g., ABC*+).
 * 
 * Theory:
 * Infix: <Operand> <Operator> <Operand>
 * Postfix (Reverse Polish Notation): <Operand> <Operand> <Operator>
 * Uses Shunting-Yard Algorithm with operator precedence and associativity:
 *   - Parentheses '(' and ')' enforce grouping
 *   - '^' (Power) has highest precedence (right-associative)
 *   - '*', '/', '%' have medium precedence (left-associative)
 *   - '+', '-' have lowest precedence (left-associative)
 */

#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <vector>

// Custom Operator Stack Implementation
class CharStack {
private:
    std::vector<char> data;

public:
    void push(char c) { data.push_back(c); }
    bool isEmpty() const { return data.empty(); }
    char peek() const { return data.empty() ? '\0' : data.back(); }
    char pop() {
        if (data.empty()) return '\0';
        char top = data.back();
        data.pop_back();
        return top;
    }
    std::string toString() const {
        std::string s = "";
        for (char c : data) s += c;
        return s.empty() ? "(empty)" : s;
    }
};

int getPrecedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0; // For '(' and other characters
}

bool isRightAssociative(char op) {
    return op == '^';
}

std::string infixToPostfix(const std::string& infix, bool verbose = true) {
    CharStack opStack;
    std::string postfix = "";

    if (verbose) {
        std::cout << "\n----------------------------------------------------------------------\n";
        std::cout << "               INFIX TO POSTFIX STEP-BY-STEP TRACE                    \n";
        std::cout << "----------------------------------------------------------------------\n";
        std::cout << std::left 
                  << std::setw(8) << "Token" 
                  << std::setw(20) << "Operator Stack" 
                  << std::setw(22) << "Postfix Output" 
                  << std::setw(20) << "Action Taken" 
                  << "\n";
        std::cout << "----------------------------------------------------------------------\n";
    }

    for (char token : infix) {
        if (std::isspace(token)) continue;

        if (std::isalnum(token)) {
            // Operands are appended directly to output
            postfix += token;
            if (verbose) {
                std::cout << std::left 
                          << std::setw(8) << token 
                          << std::setw(20) << opStack.toString() 
                          << std::setw(22) << postfix 
                          << std::setw(20) << "Operand -> Append" 
                          << "\n";
            }
        } else if (token == '(') {
            opStack.push(token);
            if (verbose) {
                std::cout << std::left 
                          << std::setw(8) << token 
                          << std::setw(20) << opStack.toString() 
                          << std::setw(22) << postfix 
                          << std::setw(20) << "Push '('" 
                          << "\n";
            }
        } else if (token == ')') {
            // Pop until matching '(' is found
            while (!opStack.isEmpty() && opStack.peek() != '(') {
                postfix += opStack.pop();
            }
            if (!opStack.isEmpty() && opStack.peek() == '(') {
                opStack.pop(); // Discard '('
            }
            if (verbose) {
                std::cout << std::left 
                          << std::setw(8) << token 
                          << std::setw(20) << opStack.toString() 
                          << std::setw(22) << postfix 
                          << std::setw(20) << "Pop until '('" 
                          << "\n";
            }
        } else {
            // Operator (+, -, *, /, ^, %)
            while (!opStack.isEmpty() && opStack.peek() != '(') {
                char top = opStack.peek();
                int precTop = getPrecedence(top);
                int precCurr = getPrecedence(token);

                if (precTop > precCurr || (precTop == precCurr && !isRightAssociative(token))) {
                    postfix += opStack.pop();
                } else {
                    break;
                }
            }
            opStack.push(token);
            if (verbose) {
                std::cout << std::left 
                          << std::setw(8) << token 
                          << std::setw(20) << opStack.toString() 
                          << std::setw(22) << postfix 
                          << std::setw(20) << "Push Operator" 
                          << "\n";
            }
        }
    }

    // Drain remaining operators from stack
    while (!opStack.isEmpty()) {
        char top = opStack.pop();
        if (top != '(') {
            postfix += top;
        }
    }

    if (verbose) {
        std::cout << "----------------------------------------------------------------------\n";
        std::cout << "Final Postfix String: " << postfix << "\n\n";
    }

    return postfix;
}

void runAutomatedDemo() {
    std::cout << "======================================================================\n";
    std::cout << "        RUNNING DEMO: INFIX TO POSTFIX CONVERSION                     \n";
    std::cout << "======================================================================\n";

    std::vector<std::string> testExpressions = {
        "A+(B*C)",
        "A+B*C+D",
        "(A+B)*(C-D)",
        "A^B*C-D+E/F/(G+H)",
        "((A+B)*C-(D-E))^(F+G)"
    };

    for (const auto& expr : testExpressions) {
        std::cout << "\n>>> Converting Infix: " << expr << " <<<\n";
        std::string res = infixToPostfix(expr, true);
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--demo") {
        runAutomatedDemo();
        return 0;
    }

    std::cout << "======================================================================\n";
    std::cout << "              INFIX TO POSTFIX CONVERTER (LAB 5)                      \n";
    std::cout << "======================================================================\n";
    std::cout << "Enter an Infix expression (e.g., A+(B*C)) or 'demo' for automated test:\n";
    std::cout << "> ";

    std::string input;
    if (std::cin >> input) {
        if (input == "demo" || input == "--demo") {
            runAutomatedDemo();
        } else {
            infixToPostfix(input, true);
        }
    }

    return 0;
}
