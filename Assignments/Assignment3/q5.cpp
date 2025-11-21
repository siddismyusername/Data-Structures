// Write a C++ program to store a binary number using a doubly linked list.
// Implement the following functions:
// a) Calculate and display the 1's complement and 2's complement of the stored binary number.
// b) Perform addition of two binary numbers represented using doubly linked lists and display the result.

#include <iostream>
#include <string>
using namespace std;

struct Node {
    int bit;
    Node* next;
    Node* prev;
};

class BinaryNumber {
private:
    Node* head;
    Node* tail;
    
    void insertAtEnd(int bit) {
        Node* newNode = new Node;
        newNode->bit = bit;
        newNode->next = nullptr;
        newNode->prev = tail;
        
        if (tail != nullptr) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
    }
    
public:
    BinaryNumber() : head(nullptr), tail(nullptr) {}
    
    // Create binary number from string
    void createFromString(string binary) {
        clear();
        for (int i = 0; i < binary.length(); i++) {
            if (binary[i] == '0' || binary[i] == '1') {
                insertAtEnd(binary[i] - '0');
            }
        }
    }
    
    // Display binary number
    void display() {
        if (head == nullptr) {
            cout << "0";
            return;
        }
        Node* current = head;
        while (current != nullptr) {
            cout << current->bit;
            current = current->next;
        }
    }
    
    // Calculate 1's complement
    BinaryNumber onesComplement() {
        BinaryNumber result;
        Node* current = head;
        
        while (current != nullptr) {
            result.insertAtEnd(current->bit == 0 ? 1 : 0);
            current = current->next;
        }
        
        return result;
    }
    
    // Calculate 2's complement
    BinaryNumber twosComplement() {
        BinaryNumber ones = onesComplement();
        BinaryNumber one;
        one.createFromString("1");
        
        return addBinary(ones, one);
    }
    
    // Add two binary numbers
    static BinaryNumber addBinary(BinaryNumber& num1, BinaryNumber& num2) {
        BinaryNumber result;
        Node* ptr1 = num1.tail;
        Node* ptr2 = num2.tail;
        int carry = 0;
        
        while (ptr1 != nullptr || ptr2 != nullptr || carry) {
            int sum = carry;
            
            if (ptr1 != nullptr) {
                sum += ptr1->bit;
                ptr1 = ptr1->prev;
            }
            
            if (ptr2 != nullptr) {
                sum += ptr2->bit;
                ptr2 = ptr2->prev;
            }
            
            result.insertAtFront(sum % 2);
            carry = sum / 2;
        }
        
        return result;
    }
    
    // Insert at front (for addition result)
    void insertAtFront(int bit) {
        Node* newNode = new Node;
        newNode->bit = bit;
        newNode->next = head;
        newNode->prev = nullptr;
        
        if (head != nullptr) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
    }
    
    // Clear the list
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
    
    // Check if empty
    bool isEmpty() {
        return head == nullptr;
    }
    
    ~BinaryNumber() {
        clear();
    }
};

int main() {
    BinaryNumber bin1, bin2;
    string binary;
    int choice;
    
    cout << "========================================\n";
    cout << "  Binary Number Operations (Doubly Linked List)\n";
    cout << "========================================\n";
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Enter Binary Number\n";
        cout << "2. Display Binary Number\n";
        cout << "3. Calculate 1's Complement\n";
        cout << "4. Calculate 2's Complement\n";
        cout << "5. Add Two Binary Numbers\n";
        cout << "6. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                cout << "\nEnter binary number (0s and 1s only): ";
                cin >> binary;
                
                // Validate input
                bool valid = true;
                for (char c : binary) {
                    if (c != '0' && c != '1') {
                        valid = false;
                        break;
                    }
                }
                
                if (valid) {
                    bin1.createFromString(binary);
                    cout << "Binary number stored successfully!\n";
                } else {
                    cout << "Invalid input! Please enter only 0s and 1s.\n";
                }
                break;
            }
            
            case 2: {
                if (bin1.isEmpty()) {
                    cout << "No binary number stored! Please enter a number first.\n";
                } else {
                    cout << "Binary Number: ";
                    bin1.display();
                    cout << endl;
                }
                break;
            }
            
            case 3: {
                if (bin1.isEmpty()) {
                    cout << "No binary number stored! Please enter a number first.\n";
                } else {
                    cout << "Original Number: ";
                    bin1.display();
                    cout << endl;
                    
                    BinaryNumber ones = bin1.onesComplement();
                    cout << "1's Complement:  ";
                    ones.display();
                    cout << endl;
                }
                break;
            }
            
            case 4: {
                if (bin1.isEmpty()) {
                    cout << "No binary number stored! Please enter a number first.\n";
                } else {
                    cout << "Original Number: ";
                    bin1.display();
                    cout << endl;
                    
                    BinaryNumber twos = bin1.twosComplement();
                    cout << "2's Complement:  ";
                    twos.display();
                    cout << endl;
                }
                break;
            }
            
            case 5: {
                string binary1, binary2;
                cout << "\nEnter first binary number: ";
                cin >> binary1;
                cout << "Enter second binary number: ";
                cin >> binary2;
                
                // Validate inputs
                bool valid = true;
                for (char c : binary1) {
                    if (c != '0' && c != '1') {
                        valid = false;
                        break;
                    }
                }
                for (char c : binary2) {
                    if (c != '0' && c != '1') {
                        valid = false;
                        break;
                    }
                }
                
                if (valid) {
                    BinaryNumber num1, num2;
                    num1.createFromString(binary1);
                    num2.createFromString(binary2);
                    
                    cout << "\nFirst Number:  ";
                    num1.display();
                    cout << endl;
                    
                    cout << "Second Number: ";
                    num2.display();
                    cout << endl;
                    
                    BinaryNumber sum = BinaryNumber::addBinary(num1, num2);
                    cout << "Sum:           ";
                    sum.display();
                    cout << endl;
                } else {
                    cout << "Invalid input! Please enter only 0s and 1s.\n";
                }
                break;
            }
            
            case 6:
                cout << "\nExiting...\n";
                break;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);
    
    return 0;
}
