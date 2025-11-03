// Convert given infix expression Eg. a-b*c-d/e+f into postfix form
// using stack and show the operations step by step.


#include <iostream>
using namespace std;


struct node
{
    int price;
    node* next;
};

// Forward declarations
bool isEmpty(node* head);
void push(node*& head, int price);
int pop(node*& head);
int getTop(node* head);
void viewStack(node* head);
void printReverse(node* head);

// 1. push(price) – Add a new stock price (an integer) to the stack.
void push(node*& head, int price){
    node* newNode = new node;
    newNode->price = price;
    newNode->next = head;
    head = newNode;
}

// 2. remove() – Remove and return the most recent price (top of the stack).
int pop(node*& head){
    if (isEmpty(head)) {
        cerr << "Stack is empty. Cannot remove price." << endl;
        return -1;  // Meaningful value indicating empty stack
    }
    int removedPrice = head->price;
    node* temp = head;
    head = head->next;
    delete temp;
    return removedPrice;
}
// 3. getTop() – Return the most recent stock price without removing it.
int getTop(node* head){
    if (isEmpty(head)) {
        cerr << "Stack is empty. No getTop price available." << endl;
        return -1;  // Meaningful value indicating empty stack
    }
    return head->price;
}

// 4. isEmpty() – Check if there are no prices pushed.
bool isEmpty(node* head){
    return head == nullptr;
}

// Function to return precedence of operators
int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Function to check if operator is right-associative
bool isRightAssociative(char c) {
    return c == '^';
}

string infixToPostfix(string &s) {
    node* stack = nullptr; // Stack to hold operators
    string res; // Resultant postfix expression
    for (char c : s) {
        // If the character is an operand, add it to the result
        if (isalnum(c)) {
            res += c;
        }
        // If the character is '(', push it to the stack
        else if (c == '(') {
            push(stack, c);
        }
        // If the character is ')', pop from stack until '(' is found
        else if (c == ')') {
            while (!isEmpty(stack) && getTop(stack) != '(') {
                res += pop(stack);
            }
            pop(stack); // Pop the '(' from the stack
        }
        // If the character is an operator
        else {
            while (!isEmpty(stack) && prec(getTop(stack)) >= prec(c) && 
                   !(isRightAssociative(c) && prec(getTop(stack)) > prec(c))) {
                res += pop(stack);
            }
            push(stack, c); // Push current operator onto stack
        }
    }
    return res;
}

int main() {
    //take input from user
    string exp;
    cout << "Enter an infix expression: ";
    getline(cin, exp);
    cout << infixToPostfix(exp);
    return 0;
}