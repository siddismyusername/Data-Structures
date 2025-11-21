// WAP to create a doubly linked list and perform following operations on it.
// A) Insert (all cases) B) Delete (all cases)

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    
    // Insert at beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->prev = nullptr;
        newNode->next = head;
        
        if (head != nullptr) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        cout << "Inserted " << value << " at beginning.\n";
    }
    
    // Insert at end
    void insertAtEnd(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;
        newNode->prev = tail;
        
        if (tail != nullptr) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        cout << "Inserted " << value << " at end.\n";
    }
    
    // Insert at specific position
    void insertAtPosition(int value, int position) {
        if (position <= 1) {
            insertAtBeginning(value);
            return;
        }
        
        Node* current = head;
        int count = 1;
        
        while (current != nullptr && count < position - 1) {
            current = current->next;
            count++;
        }
        
        if (current == nullptr) {
            cout << "Position out of range! Inserting at end.\n";
            insertAtEnd(value);
            return;
        }
        
        if (current->next == nullptr) {
            insertAtEnd(value);
            return;
        }
        
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = current->next;
        newNode->prev = current;
        
        current->next->prev = newNode;
        current->next = newNode;
        
        cout << "Inserted " << value << " at position " << position << ".\n";
    }
    
    // Insert after a value
    void insertAfterValue(int value, int afterValue) {
        Node* current = head;
        
        while (current != nullptr && current->data != afterValue) {
            current = current->next;
        }
        
        if (current == nullptr) {
            cout << "Value " << afterValue << " not found in list!\n";
            return;
        }
        
        if (current->next == nullptr) {
            insertAtEnd(value);
            return;
        }
        
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = current->next;
        newNode->prev = current;
        
        current->next->prev = newNode;
        current->next = newNode;
        
        cout << "Inserted " << value << " after " << afterValue << ".\n";
    }
    
    // Insert before a value
    void insertBeforeValue(int value, int beforeValue) {
        Node* current = head;
        
        while (current != nullptr && current->data != beforeValue) {
            current = current->next;
        }
        
        if (current == nullptr) {
            cout << "Value " << beforeValue << " not found in list!\n";
            return;
        }
        
        if (current->prev == nullptr) {
            insertAtBeginning(value);
            return;
        }
        
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = current;
        newNode->prev = current->prev;
        
        current->prev->next = newNode;
        current->prev = newNode;
        
        cout << "Inserted " << value << " before " << beforeValue << ".\n";
    }
    
    // Delete from beginning
    void deleteFromBeginning() {
        if (head == nullptr) {
            cout << "List is empty! Cannot delete.\n";
            return;
        }
        
        Node* temp = head;
        int value = temp->data;
        
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        
        delete temp;
        cout << "Deleted " << value << " from beginning.\n";
    }
    
    // Delete from end
    void deleteFromEnd() {
        if (tail == nullptr) {
            cout << "List is empty! Cannot delete.\n";
            return;
        }
        
        Node* temp = tail;
        int value = temp->data;
        
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        
        delete temp;
        cout << "Deleted " << value << " from end.\n";
    }
    
    // Delete from specific position
    void deleteFromPosition(int position) {
        if (head == nullptr) {
            cout << "List is empty! Cannot delete.\n";
            return;
        }
        
        if (position <= 1) {
            deleteFromBeginning();
            return;
        }
        
        Node* current = head;
        int count = 1;
        
        while (current != nullptr && count < position) {
            current = current->next;
            count++;
        }
        
        if (current == nullptr) {
            cout << "Position out of range!\n";
            return;
        }
        
        int value = current->data;
        
        if (current->next == nullptr) {
            deleteFromEnd();
            return;
        }
        
        current->prev->next = current->next;
        current->next->prev = current->prev;
        
        delete current;
        cout << "Deleted " << value << " from position " << position << ".\n";
    }
    
    // Delete by value
    void deleteByValue(int value) {
        if (head == nullptr) {
            cout << "List is empty! Cannot delete.\n";
            return;
        }
        
        Node* current = head;
        
        while (current != nullptr && current->data != value) {
            current = current->next;
        }
        
        if (current == nullptr) {
            cout << "Value " << value << " not found in list!\n";
            return;
        }
        
        if (current == head) {
            deleteFromBeginning();
            return;
        }
        
        if (current == tail) {
            deleteFromEnd();
            return;
        }
        
        current->prev->next = current->next;
        current->next->prev = current->prev;
        
        delete current;
        cout << "Deleted " << value << " from list.\n";
    }
    
    // Display list forward
    void displayForward() {
        if (head == nullptr) {
            cout << "List is empty!\n";
            return;
        }
        
        cout << "List (Forward): ";
        Node* current = head;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " <-> ";
            }
            current = current->next;
        }
        cout << endl;
    }
    
    // Display list backward
    void displayBackward() {
        if (tail == nullptr) {
            cout << "List is empty!\n";
            return;
        }
        
        cout << "List (Backward): ";
        Node* current = tail;
        while (current != nullptr) {
            cout << current->data;
            if (current->prev != nullptr) {
                cout << " <-> ";
            }
            current = current->prev;
        }
        cout << endl;
    }
    
    bool isEmpty() {
        return head == nullptr;
    }
    
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
    
    ~DoublyLinkedList() {
        clear();
    }
};

int main() {
    DoublyLinkedList list;
    int choice, value, position, refValue;
    
    cout << "========================================\n";
    cout << "  Doubly Linked List Operations\n";
    cout << "========================================\n";
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "INSERT OPERATIONS:\n";
        cout << "1. Insert at Beginning\n";
        cout << "2. Insert at End\n";
        cout << "3. Insert at Position\n";
        cout << "4. Insert After a Value\n";
        cout << "5. Insert Before a Value\n";
        cout << "\nDELETE OPERATIONS:\n";
        cout << "6. Delete from Beginning\n";
        cout << "7. Delete from End\n";
        cout << "8. Delete from Position\n";
        cout << "9. Delete by Value\n";
        cout << "\nDISPLAY OPERATIONS:\n";
        cout << "10. Display List (Forward)\n";
        cout << "11. Display List (Backward)\n";
        cout << "12. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                list.insertAtBeginning(value);
                list.displayForward();
                break;
                
            case 2:
                cout << "Enter value to insert: ";
                cin >> value;
                list.insertAtEnd(value);
                list.displayForward();
                break;
                
            case 3:
                cout << "Enter value to insert: ";
                cin >> value;
                cout << "Enter position: ";
                cin >> position;
                list.insertAtPosition(value, position);
                list.displayForward();
                break;
                
            case 4:
                cout << "Enter value to insert: ";
                cin >> value;
                cout << "Insert after which value? ";
                cin >> refValue;
                list.insertAfterValue(value, refValue);
                list.displayForward();
                break;
                
            case 5:
                cout << "Enter value to insert: ";
                cin >> value;
                cout << "Insert before which value? ";
                cin >> refValue;
                list.insertBeforeValue(value, refValue);
                list.displayForward();
                break;
                
            case 6:
                list.deleteFromBeginning();
                if (!list.isEmpty()) list.displayForward();
                break;
                
            case 7:
                list.deleteFromEnd();
                if (!list.isEmpty()) list.displayForward();
                break;
                
            case 8:
                cout << "Enter position to delete: ";
                cin >> position;
                list.deleteFromPosition(position);
                if (!list.isEmpty()) list.displayForward();
                break;
                
            case 9:
                cout << "Enter value to delete: ";
                cin >> value;
                list.deleteByValue(value);
                if (!list.isEmpty()) list.displayForward();
                break;
                
            case 10:
                list.displayForward();
                break;
                
            case 11:
                list.displayBackward();
                break;
                
            case 12:
                cout << "\nExiting...\n";
                break;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 12);
    
    return 0;
}
