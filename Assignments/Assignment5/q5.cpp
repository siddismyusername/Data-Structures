// You are given a postfix expression (also known as Reverse Polish Notation)
// consisting of single-digit operands and binary operators (+, -, *, /).
// Your task is to evaluate the expression using stack and return its result.

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#define MAX_SIZE 100

class Stack {
private:
    int arr[MAX_SIZE];
    int top;
    
public:
    Stack() : top(-1) {}
    
    bool isEmpty() {
        return top == -1;
    }
    
    bool isFull() {
        return top == MAX_SIZE - 1;
    }
    
    void push(int value) {
        if (isFull()) {
            cout << "Stack Overflow!\n";
            return;
        }
        arr[++top] = value;
    }
    
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!\n";
            return -1;
        }
        return arr[top--];
    }
    
    int peek() {
        if (isEmpty()) {
            return -1;
        }
        return arr[top];
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Stack: [Empty]";
            return;
        }
        cout << "Stack: [";
        for (int i = 0; i <= top; i++) {
            cout << arr[i];
            if (i < top) cout << ", ";
        }
        cout << "]";
    }
};

// Check if character is an operator
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Check if character is a digit
bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

// Perform arithmetic operation
int performOperation(int operand1, int operand2, char op) {
    switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 == 0) {
                cout << "\nError: Division by zero!\n";
                return 0;
            }
            return operand1 / operand2;
        default:
            return 0;
    }
}

// Evaluate postfix expression
int evaluatePostfix(string expr) {
    Stack stack;
    
    for (int i = 0; i < expr.length(); i++) {
        char ch = expr[i];
        
        // Skip spaces
        if (ch == ' ') {
            continue;
        }
        
        // If operand (digit), push to stack
        if (isDigit(ch)) {
            stack.push(ch - '0');  // Convert char to int
        }
        // If operator, pop two operands and apply operation
        else if (isOperator(ch)) {
            if (stack.isEmpty()) {
                cout << "\nError: Invalid postfix expression!\n";
                return -1;
            }
            
            int operand2 = stack.pop();
            
            if (stack.isEmpty()) {
                cout << "\nError: Invalid postfix expression!\n";
                return -1;
            }
            
            int operand1 = stack.pop();
            
            int result = performOperation(operand1, operand2, ch);
            stack.push(result);
        }
        else {
            cout << "\nError: Invalid character '" << ch << "' in expression!\n";
            return -1;
        }
    }
    
    // Final result should be single value in stack
    if (stack.isEmpty()) {
        cout << "\nError: Empty expression!\n";
        return -1;
    }
    
    int result = stack.pop();
    
    if (!stack.isEmpty()) {
        cout << "\nError: Invalid postfix expression (extra operands)!\n";
        return -1;
    }
    
    return result;
}

// Evaluate with detailed steps
void evaluatePostfixWithSteps(string expr) {
    Stack stack;
    
    cout << "\nEvaluating postfix expression: " << expr << endl;
    cout << "========================================\n";
    
    for (int i = 0; i < expr.length(); i++) {
        char ch = expr[i];
        
        // Skip spaces
        if (ch == ' ') {
            continue;
        }
        
        cout << "Step " << (i + 1) << ": Character = '" << ch << "'\n";
        
        // If operand (digit), push to stack
        if (isDigit(ch)) {
            int value = ch - '0';
            stack.push(value);
            cout << "  Action: Push " << value << " to stack\n";
            cout << "  ";
            stack.display();
            cout << endl;
        }
        // If operator, pop two operands and apply operation
        else if (isOperator(ch)) {
            if (stack.isEmpty()) {
                cout << "\nError: Invalid postfix expression!\n";
                return;
            }
            
            int operand2 = stack.pop();
            
            if (stack.isEmpty()) {
                cout << "\nError: Invalid postfix expression!\n";
                return;
            }
            
            int operand1 = stack.pop();
            
            int result = performOperation(operand1, operand2, ch);
            
            cout << "  Action: Pop " << operand2 << " and " << operand1 << "\n";
            cout << "  Calculate: " << operand1 << " " << ch << " " << operand2 << " = " << result << "\n";
            
            stack.push(result);
            cout << "  Push result " << result << " to stack\n";
            cout << "  ";
            stack.display();
            cout << endl;
        }
        
        cout << endl;
    }
    
    cout << "========================================\n";
    
    if (stack.isEmpty()) {
        cout << "Error: Empty expression!\n";
        return;
    }
    
    int result = stack.pop();
    
    if (!stack.isEmpty()) {
        cout << "Error: Invalid postfix expression (extra operands)!\n";
        return;
    }
    
    cout << "Final Result: " << result << endl;
}

int main() {
    string expression;
    int choice;
    
    cout << "========================================\n";
    cout << "  Postfix Expression Evaluator\n";
    cout << "========================================\n";
    cout << "Supported operators: + - * /\n";
    cout << "Operands: Single digits (0-9)\n";
    cout << "Example: 23*5+ means (2*3)+5 = 11\n";
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Evaluate Postfix Expression (Quick)\n";
        cout << "2. Evaluate with Detailed Steps\n";
        cout << "3. Test Sample Cases\n";
        cout << "4. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline
        
        switch (choice) {
            case 1:
                cout << "\nEnter postfix expression: ";
                getline(cin, expression);
                {
                    int result = evaluatePostfix(expression);
                    if (result != -1 || expression == "0") {
                        cout << "\nResult: " << result << endl;
                    }
                }
                break;
                
            case 2:
                cout << "\nEnter postfix expression: ";
                getline(cin, expression);
                evaluatePostfixWithSteps(expression);
                break;
                
            case 3:
                cout << "\n========== Sample Test Cases ==========\n";
                
                // Test case 1: Simple addition
                cout << "\nTest 1: 23+\n";
                cout << "Infix: 2 + 3\n";
                cout << "Result: " << evaluatePostfix("23+") << "\n";
                
                // Test case 2: Multiplication and addition
                cout << "\nTest 2: 23*5+\n";
                cout << "Infix: (2 * 3) + 5\n";
                cout << "Result: " << evaluatePostfix("23*5+") << "\n";
                
                // Test case 3: Complex expression
                cout << "\nTest 3: 234*+5-\n";
                cout << "Infix: (2 + (3 * 4)) - 5\n";
                cout << "Result: " << evaluatePostfix("234*+5-") << "\n";
                
                // Test case 4: Division
                cout << "\nTest 4: 82/\n";
                cout << "Infix: 8 / 2\n";
                cout << "Result: " << evaluatePostfix("82/") << "\n";
                
                // Test case 5: Multiple operations
                cout << "\nTest 5: 53+82-*\n";
                cout << "Infix: (5 + 3) * (8 - 2)\n";
                cout << "Result: " << evaluatePostfix("53+82-*") << "\n";
                
                // Test case 6: With spaces
                cout << "\nTest 6: 2 3 * 5 +\n";
                cout << "Infix: (2 * 3) + 5\n";
                cout << "Result: " << evaluatePostfix("2 3 * 5 +") << "\n";
                
                // Test case 7: Subtraction
                cout << "\nTest 7: 95-\n";
                cout << "Infix: 9 - 5\n";
                cout << "Result: " << evaluatePostfix("95-") << "\n";
                
                // Test case 8: Complex with all operators
                cout << "\nTest 8: 62/3-42*+\n";
                cout << "Infix: ((6 / 2) - 3) + (4 * 2)\n";
                cout << "Result: " << evaluatePostfix("62/3-42*+") << "\n";
                
                cout << "\n========================================\n";
                break;
                
            case 4:
                cout << "\nExiting...\n";
                break;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);
    
    return 0;
}
