/**
 * LAB ASSIGNMENT 5 - Task 2: Postfix Expression Evaluation
 * 
 * Objective:
 * Write an Expression Evaluation program that processes a completed string
 * in Postfix format, utilizing an integer stack to compute and print the
 * final mathematical output.
 * 
 * Theory:
 * 1. Read token from left to right.
 * 2. If token is an operand (number), push onto Integer Stack.
 * 3. If token is an operator, pop operand2 then operand1:
 *      result = operand1 <op> operand2
 *    Push result back onto stack.
 * 4. At the end of the expression, the stack contains the final evaluated value.
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include <iomanip>

// Custom Integer Stack
class IntStack {
private:
    std::vector<long long> data;

public:
    void push(long long val) { data.push_back(val); }
    bool isEmpty() const { return data.empty(); }
    size_t size() const { return data.size(); }
    long long pop() {
        if (data.empty()) return 0;
        long long val = data.back();
        data.pop_back();
        return val;
    }
    std::string toString() const {
        std::string s = "[ ";
        for (long long v : data) s += std::to_string(v) + " ";
        s += "]";
        return s;
    }
};

long long evaluatePostfix(const std::string& expr, bool verbose = true) {
    IntStack stack;
    std::istringstream iss(expr);
    std::string token;

    if (verbose) {
        std::cout << "\n----------------------------------------------------------------------\n";
        std::cout << "               POSTFIX EVALUATION STEP-BY-STEP TRACE                  \n";
        std::cout << "----------------------------------------------------------------------\n";
        std::cout << std::left 
                  << std::setw(10) << "Token" 
                  << std::setw(28) << "Operation" 
                  << std::setw(30) << "Stack State After Step" 
                  << "\n";
        std::cout << "----------------------------------------------------------------------\n";
    }

    // Process either space-separated tokens or individual characters
    std::vector<std::string> tokens;
    if (expr.find(' ') != std::string::npos) {
        while (iss >> token) tokens.push_back(token);
    } else {
        for (char c : expr) {
            if (!std::isspace(c)) tokens.push_back(std::string(1, c));
        }
    }

    for (const auto& t : tokens) {
        if (std::isdigit(t[0]) || (t.size() > 1 && t[0] == '-' && std::isdigit(t[1]))) {
            long long val = std::stoll(t);
            stack.push(val);
            if (verbose) {
                std::cout << std::left 
                          << std::setw(10) << t 
                          << std::setw(28) << ("Push Operand: " + std::to_string(val)) 
                          << std::setw(30) << stack.toString() 
                          << "\n";
            }
        } else if (t == "+" || t == "-" || t == "*" || t == "/" || t == "^" || t == "%") {
            if (stack.size() < 2) {
                std::cerr << "[ERROR] Invalid postfix expression (insufficient operands)!\n";
                return 0;
            }
            long long op2 = stack.pop();
            long long op1 = stack.pop();
            long long res = 0;
            std::string opDesc = "";

            if (t == "+") {
                res = op1 + op2;
                opDesc = std::to_string(op1) + " + " + std::to_string(op2) + " = " + std::to_string(res);
            } else if (t == "-") {
                res = op1 - op2;
                opDesc = std::to_string(op1) + " - " + std::to_string(op2) + " = " + std::to_string(res);
            } else if (t == "*") {
                res = op1 * op2;
                opDesc = std::to_string(op1) + " * " + std::to_string(op2) + " = " + std::to_string(res);
            } else if (t == "/") {
                if (op2 == 0) {
                    std::cerr << "[ERROR] Division by zero!\n";
                    return 0;
                }
                res = op1 / op2;
                opDesc = std::to_string(op1) + " / " + std::to_string(op2) + " = " + std::to_string(res);
            } else if (t == "%") {
                res = op1 % op2;
                opDesc = std::to_string(op1) + " % " + std::to_string(op2) + " = " + std::to_string(res);
            } else if (t == "^") {
                res = static_cast<long long>(std::pow(op1, op2));
                opDesc = std::to_string(op1) + " ^ " + std::to_string(op2) + " = " + std::to_string(res);
            }

            stack.push(res);
            if (verbose) {
                std::cout << std::left 
                          << std::setw(10) << t 
                          << std::setw(28) << opDesc 
                          << std::setw(30) << stack.toString() 
                          << "\n";
            }
        }
    }

    long long finalResult = stack.isEmpty() ? 0 : stack.pop();
    if (verbose) {
        std::cout << "----------------------------------------------------------------------\n";
        std::cout << "Final Evaluated Result = " << finalResult << "\n\n";
    }

    return finalResult;
}

void runAutomatedDemo() {
    std::cout << "======================================================================\n";
    std::cout << "          RUNNING DEMO: POSTFIX EXPRESSION EVALUATION                 \n";
    std::cout << "======================================================================\n";

    // 1. Single character expression: "231*+9-" -> 2 + (3 * 1) - 9 = -4
    std::cout << ">>> Test 1: Single-character Postfix: 2 3 1 * + 9 - <<<\n";
    evaluatePostfix("2 3 1 * + 9 -", true);

    // 2. Multi-digit expression: "50 10 2 * + 4 -" -> 50 + (10 * 2) - 4 = 66
    std::cout << ">>> Test 2: Multi-digit Space-Separated: 50 10 2 * + 4 - <<<\n";
    evaluatePostfix("50 10 2 * + 4 -", true);

    // 3. Power expression: "2 3 ^ 4 5 + *" -> (2^3) * (4 + 5) = 8 * 9 = 72
    std::cout << ">>> Test 3: Power & Parenthesized: 2 3 ^ 4 5 + * <<<\n";
    evaluatePostfix("2 3 ^ 4 5 + *", true);
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--demo") {
        runAutomatedDemo();
        return 0;
    }

    std::cout << "======================================================================\n";
    std::cout << "           POSTFIX EXPRESSION EVALUATOR (LAB 5)                       \n";
    std::cout << "======================================================================\n";
    std::cout << "Enter postfix expression with spaces (e.g. '2 3 1 * + 9 -') or 'demo':\n";
    std::cout << "> ";

    std::string line;
    if (std::getline(std::cin, line)) {
        if (line == "demo" || line == "--demo") {
            runAutomatedDemo();
        } else {
            evaluatePostfix(line, true);
        }
    }

    return 0;
}
