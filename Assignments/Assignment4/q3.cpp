// Implement Bubble sort using Doubly Linked List

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
    
    void insert(int value) {
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
    }
    
    void display() {
        if (head == nullptr) {
            cout << "List is empty!\n";
            return;
        }
        
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
    
    void bubbleSort() {
        if (head == nullptr || head->next == nullptr) {
            return; // Empty or single element list
        }
        
        bool swapped;
        Node* ptr1;
        Node* lptr = nullptr;
        
        do {
            swapped = false;
            ptr1 = head;
            
            while (ptr1->next != lptr) {
                if (ptr1->data > ptr1->next->data) {
                    // Swap data
                    int temp = ptr1->data;
                    ptr1->data = ptr1->next->data;
                    ptr1->next->data = temp;
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }
    
    int size() {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
    
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
    
    bool isEmpty() {
        return head == nullptr;
    }
    
    ~DoublyLinkedList() {
        clear();
    }
};

int main() {
    DoublyLinkedList list;
    int choice, value, n;
    
    cout << "========================================\n";
    cout << "  Bubble Sort (Doubly Linked List)\n";
    cout << "========================================\n";
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Create List\n";
        cout << "2. Display List\n";
        cout << "3. Sort List (Bubble Sort)\n";
        cout << "4. Insert Element\n";
        cout << "5. Clear List\n";
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
                break;
                
            case 2:
                cout << "\nCurrent List: ";
                list.display();
                cout << "Size: " << list.size() << endl;
                break;
                
            case 3:
                if (list.isEmpty()) {
                    cout << "List is empty! Please create a list first.\n";
                } else {
                    cout << "\nBefore Sorting: ";
                    list.display();
                    
                    list.bubbleSort();
                    
                    cout << "After Sorting:  ";
                    list.display();
                    cout << "List sorted successfully!\n";
                }
                break;
                
            case 4:
                cout << "\nEnter value to insert: ";
                cin >> value;
                list.insert(value);
                cout << "Element inserted successfully!\n";
                cout << "Current List: ";
                list.display();
                break;
                
            case 5:
                list.clear();
                cout << "List cleared successfully!\n";
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
