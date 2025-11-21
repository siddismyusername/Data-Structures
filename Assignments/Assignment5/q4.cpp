// You are given a string containing only parentheses characters: '(', ')', '{', '}', '[', and ']'.
// Your task is to check whether the parentheses are balanced or not.
// A string is considered balanced if:
// 1. Every opening bracket has a corresponding closing bracket of the same type
// 2. Brackets are closed in the correct order.

#include <iostream>
#include <string>
using namespace std;

#define MAX_SIZE 100

class Stack {
private:
    char arr[MAX_SIZE];
    int top;
    
public:
    Stack() : top(-1) {}
    
    bool isEmpty() {
        return top == -1;
    }
    
    bool isFull() {
        return top == MAX_SIZE - 1;
    }
    
    void push(char ch) {
        if (isFull()) {
            cout << "Stack Overflow!\n";
            return;
        }
        arr[++top] = ch;
    }
    
    char pop() {
        if (isEmpty()) {
            return '\0';
        }
        return arr[top--];
    }
    
    char peek() {
        if (isEmpty()) {
            return '\0';
        }
        return arr[top];
    }
};

// Check if character is opening bracket
bool isOpeningBracket(char ch) {
    return (ch == '(' || ch == '{' || ch == '[');
}

// Check if character is closing bracket
bool isClosingBracket(char ch) {
    return (ch == ')' || ch == '}' || ch == ']');
}

// Check if opening and closing brackets match
bool isMatchingPair(char opening, char closing) {
    if (opening == '(' && closing == ')') return true;
    if (opening == '{' && closing == '}') return true;
    if (opening == '[' && closing == ']') return true;
    return false;
}

// Check if parentheses are balanced
bool isBalanced(string expr) {
    Stack stack;
    
    for (int i = 0; i < expr.length(); i++) {
        char ch = expr[i];
        
        // If opening bracket, push to stack
        if (isOpeningBracket(ch)) {
            stack.push(ch);
        }
        // If closing bracket, check matching
        else if (isClosingBracket(ch)) {
            // If stack is empty, no matching opening bracket
            if (stack.isEmpty()) {
                return false;
            }
            
            char top = stack.pop();
            
            // Check if brackets match
            if (!isMatchingPair(top, ch)) {
                return false;
            }
        }
        // Ignore other characters (if any)
    }
    
    // If stack is empty, all brackets are balanced
    return stack.isEmpty();
}

// Display detailed checking process
void checkBalancedWithDetails(string expr) {
    Stack stack;
    bool isValid = true;
    
    cout << "\nChecking expression: " << expr << endl;
    cout << "========================================\n";
    
    for (int i = 0; i < expr.length(); i++) {
        char ch = expr[i];
        
        if (isOpeningBracket(ch)) {
            stack.push(ch);
            cout << "Position " << i << ": '" << ch << "' -> Push to stack\n";
        }
        else if (isClosingBracket(ch)) {
            if (stack.isEmpty()) {
                cout << "Position " << i << ": '" << ch << "' -> ERROR: No matching opening bracket!\n";
                isValid = false;
                break;
            }
            
            char top = stack.pop();
            
            if (isMatchingPair(top, ch)) {
                cout << "Position " << i << ": '" << ch << "' -> Matches with '" << top << "' (Popped)\n";
            } else {
                cout << "Position " << i << ": '" << ch << "' -> ERROR: Does not match with '" << top << "'!\n";
                isValid = false;
                break;
            }
        }
    }
    
    cout << "========================================\n";
    
    if (isValid && !stack.isEmpty()) {
        cout << "ERROR: Unmatched opening brackets remain in stack!\n";
        isValid = false;
    }
    
    if (isValid) {
        cout << "Result: BALANCED ✓\n";
    } else {
        cout << "Result: NOT BALANCED ✗\n";
    }
}

int main() {
    string expression;
    int choice;
    
    cout << "========================================\n";
    cout << "  Balanced Parentheses Checker\n";
    cout << "========================================\n";
    cout << "Supported brackets: ( ) { } [ ]\n";
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Check if Balanced (Quick)\n";
        cout << "2. Check with Detailed Steps\n";
        cout << "3. Test Sample Cases\n";
        cout << "4. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline
        
        switch (choice) {
            case 1:
                cout << "\nEnter expression with brackets: ";
                getline(cin, expression);
                
                if (isBalanced(expression)) {
                    cout << "\nResult: The expression is BALANCED ✓\n";
                } else {
                    cout << "\nResult: The expression is NOT BALANCED ✗\n";
                }
                break;
                
            case 2:
                cout << "\nEnter expression with brackets: ";
                getline(cin, expression);
                checkBalancedWithDetails(expression);
                break;
                
            case 3:
                cout << "\n========== Sample Test Cases ==========\n";
                
                // Test case 1: Valid
                cout << "\nTest 1: ()";
                cout << "\nResult: " << (isBalanced("()") ? "BALANCED ✓" : "NOT BALANCED ✗") << "\n";
                
                // Test case 2: Valid
                cout << "\nTest 2: ()[]{}";
                cout << "\nResult: " << (isBalanced("()[]{}") ? "BALANCED ✓" : "NOT BALANCED ✗") << "\n";
                
                // Test case 3: Valid
                cout << "\nTest 3: {[()]}";
                cout << "\nResult: " << (isBalanced("{[()]}") ? "BALANCED ✓" : "NOT BALANCED ✗") << "\n";
                
                // Test case 4: Valid
                cout << "\nTest 4: {[(a+b)*(c-d)]}";
                cout << "\nResult: " << (isBalanced("{[(a+b)*(c-d)]}") ? "BALANCED ✓" : "NOT BALANCED ✗") << "\n";
                
                // Test case 5: Invalid - mismatched
                cout << "\nTest 5: (]";
                cout << "\nResult: " << (isBalanced("(]") ? "BALANCED ✓" : "NOT BALANCED ✗") << "\n";
                
                // Test case 6: Invalid - wrong order
                cout << "\nTest 6: ([)]";
                cout << "\nResult: " << (isBalanced("([)]") ? "BALANCED ✓" : "NOT BALANCED ✗") << "\n";
                
                // Test case 7: Invalid - extra closing
                cout << "\nTest 7: {[}]";
                cout << "\nResult: " << (isBalanced("{[}]") ? "BALANCED ✓" : "NOT BALANCED ✗") << "\n";
                
                // Test case 8: Invalid - unclosed
                cout << "\nTest 8: {[(";
                cout << "\nResult: " << (isBalanced("{[(") ? "BALANCED ✓" : "NOT BALANCED ✗") << "\n";
                
                // Test case 9: Invalid - extra closing
                cout << "\nTest 9: )";
                cout << "\nResult: " << (isBalanced(")") ? "BALANCED ✓" : "NOT BALANCED ✗") << "\n";
                
                // Test case 10: Valid - empty
                cout << "\nTest 10: (empty string)";
                cout << "\nResult: " << (isBalanced("") ? "BALANCED ✓" : "NOT BALANCED ✗") << "\n";
                
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
