// Given a list, split it into two sublists — one for the front half, and one for the back half.
// If the number of elements is odd, the extra element should go in the front list.
// So FrontBackSplit() on the list {2, 3, 5, 7, 11} should yield the two lists {2, 3, 5} and {7, 11}.

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class LinkedList {
private:
    Node* head;
    
public:
    LinkedList() : head(nullptr) {}
    
    // Insert at end
    void insert(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;
        
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    
    // Display list
    void display() {
        if (head == nullptr) {
            cout << "Empty";
            return;
        }
        
        Node* current = head;
        cout << "{";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << ", ";
            }
            current = current->next;
        }
        cout << "}";
    }
    
    // Get length of list
    int length() {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
    
    // Split list into front and back halves
    void frontBackSplit(LinkedList& frontList, LinkedList& backList) {
        // Clear the front and back lists
        frontList.clear();
        backList.clear();
        
        int len = length();
        
        // Special case: length < 2
        if (len < 2) {
            frontList.head = head;
            backList.head = nullptr;
            return;
        }
        
        // Calculate split point
        // For odd length, extra element goes to front
        int frontLen = (len + 1) / 2;
        
        Node* current = head;
        Node* frontTail = nullptr;
        
        // Traverse to split point
        for (int i = 0; i < frontLen; i++) {
            Node* newNode = new Node;
            newNode->data = current->data;
            newNode->next = nullptr;
            
            if (frontList.head == nullptr) {
                frontList.head = newNode;
                frontTail = newNode;
            } else {
                frontTail->next = newNode;
                frontTail = newNode;
            }
            
            current = current->next;
        }
        
        // Rest goes to back list
        while (current != nullptr) {
            backList.insert(current->data);
            current = current->next;
        }
    }
    
    // Alternative efficient split (modifies original list)
    void frontBackSplitInPlace(LinkedList& frontList, LinkedList& backList) {
        frontList.clear();
        backList.clear();
        
        int len = length();
        
        // Special case: length < 2
        if (len < 2) {
            frontList.head = head;
            backList.head = nullptr;
            head = nullptr;
            return;
        }
        
        // Calculate split point
        int frontLen = (len + 1) / 2;
        
        Node* current = head;
        
        // Move to the node before split
        for (int i = 1; i < frontLen; i++) {
            current = current->next;
        }
        
        // Split the list
        frontList.head = head;
        backList.head = current->next;
        current->next = nullptr;
        
        // Original list is now empty (split into front and back)
        head = nullptr;
    }
    
    // Clear list
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // Check if empty
    bool isEmpty() {
        return head == nullptr;
    }
    
    // Set head (for split operations)
    void setHead(Node* newHead) {
        head = newHead;
    }
    
    ~LinkedList() {
        clear();
    }
};

int main() {
    LinkedList list, frontList, backList;
    int choice, value, n;
    
    cout << "========================================\n";
    cout << "  Front-Back Split (Linked List)\n";
    cout << "========================================\n";
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Create List\n";
        cout << "2. Display List\n";
        cout << "3. Split List (Front/Back)\n";
        cout << "4. Insert Element\n";
        cout << "5. Test Multiple Cases\n";
        cout << "6. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                list.clear();
                cout << "\nEnter number of elements: ";
                cin >> n;
                cout << "Enter " << n << " elements:\n";
                for (int i = 0; i < n; i++) {
                    cout << "Element " << (i + 1) << ": ";
                    cin >> value;
                    list.insert(value);
                }
                cout << "List created successfully!\n";
                cout << "List: ";
                list.display();
                cout << " (Length: " << list.length() << ")\n";
                break;
                
            case 2:
                cout << "\nCurrent List: ";
                list.display();
                cout << " (Length: " << list.length() << ")\n";
                break;
                
            case 3:
                if (list.isEmpty()) {
                    cout << "List is empty! Please create a list first.\n";
                } else {
                    cout << "\nOriginal List: ";
                    list.display();
                    cout << " (Length: " << list.length() << ")\n";
                    
                    list.frontBackSplit(frontList, backList);
                    
                    cout << "\nAfter Split:\n";
                    cout << "Front Half: ";
                    frontList.display();
                    cout << " (Length: " << frontList.length() << ")\n";
                    
                    cout << "Back Half:  ";
                    backList.display();
                    cout << " (Length: " << backList.length() << ")\n";
                }
                break;
                
            case 4:
                cout << "\nEnter value to insert: ";
                cin >> value;
                list.insert(value);
                cout << "Element inserted successfully!\n";
                cout << "List: ";
                list.display();
                cout << " (Length: " << list.length() << ")\n";
                break;
                
            case 5:
                cout << "\n========== Testing Multiple Cases ==========\n";
                
                // Test case 1: Length = 1
                {
                    LinkedList test1, front1, back1;
                    test1.insert(5);
                    cout << "\nTest Case 1 (Length = 1):\n";
                    cout << "Original: ";
                    test1.display();
                    cout << "\n";
                    test1.frontBackSplit(front1, back1);
                    cout << "Front: ";
                    front1.display();
                    cout << "\nBack:  ";
                    back1.display();
                    cout << "\n";
                }
                
                // Test case 2: Length = 2
                {
                    LinkedList test2, front2, back2;
                    test2.insert(2);
                    test2.insert(3);
                    cout << "\nTest Case 2 (Length = 2):\n";
                    cout << "Original: ";
                    test2.display();
                    cout << "\n";
                    test2.frontBackSplit(front2, back2);
                    cout << "Front: ";
                    front2.display();
                    cout << "\nBack:  ";
                    back2.display();
                    cout << "\n";
                }
                
                // Test case 3: Length = 3
                {
                    LinkedList test3, front3, back3;
                    test3.insert(2);
                    test3.insert(3);
                    test3.insert(5);
                    cout << "\nTest Case 3 (Length = 3):\n";
                    cout << "Original: ";
                    test3.display();
                    cout << "\n";
                    test3.frontBackSplit(front3, back3);
                    cout << "Front: ";
                    front3.display();
                    cout << "\nBack:  ";
                    back3.display();
                    cout << "\n";
                }
                
                // Test case 4: Length = 4
                {
                    LinkedList test4, front4, back4;
                    test4.insert(2);
                    test4.insert(3);
                    test4.insert(5);
                    test4.insert(7);
                    cout << "\nTest Case 4 (Length = 4):\n";
                    cout << "Original: ";
                    test4.display();
                    cout << "\n";
                    test4.frontBackSplit(front4, back4);
                    cout << "Front: ";
                    front4.display();
                    cout << "\nBack:  ";
                    back4.display();
                    cout << "\n";
                }
                
                // Test case 5: Length = 5 (given example)
                {
                    LinkedList test5, front5, back5;
                    test5.insert(2);
                    test5.insert(3);
                    test5.insert(5);
                    test5.insert(7);
                    test5.insert(11);
                    cout << "\nTest Case 5 (Length = 5 - Given Example):\n";
                    cout << "Original: ";
                    test5.display();
                    cout << "\n";
                    test5.frontBackSplit(front5, back5);
                    cout << "Front: ";
                    front5.display();
                    cout << "\nBack:  ";
                    back5.display();
                    cout << "\n";
                }
                
                // Test case 6: Length = 6
                {
                    LinkedList test6, front6, back6;
                    test6.insert(1);
                    test6.insert(2);
                    test6.insert(3);
                    test6.insert(4);
                    test6.insert(5);
                    test6.insert(6);
                    cout << "\nTest Case 6 (Length = 6):\n";
                    cout << "Original: ";
                    test6.display();
                    cout << "\n";
                    test6.frontBackSplit(front6, back6);
                    cout << "Front: ";
                    front6.display();
                    cout << "\nBack:  ";
                    back6.display();
                    cout << "\n";
                }
                
                cout << "\n========================================\n";
                break;
                
            case 6:
                cout << "\nExiting...\n";
                break;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);
    
    return 0;
}
