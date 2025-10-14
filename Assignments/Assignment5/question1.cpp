#include <iostream>
using namespace std;
// WAP to build a simple stock price tracker that keeps a history of
// daily stock prices entered by the user. To allow users to go back
// and view or remove the most recent price, implement a stack
// using a linked list to store these integer prices.
// Implement the following operations:
struct node
{
    int price;
    node* next;
};

// Forward declarations
bool isEmpty(node* head);
void record(node*& head, int price);
int removeLatest(node*& head);
int latest(node* head);
void viewStack(node* head);
void printReverce(node* head);

// 1. record(price) – Add a new stock price (an integer) to the stack.
void record(node*& head, int price){
    node* newNode = new node;
    newNode->price = price;
    newNode->next = head;
    head = newNode;
}

// 2. remove() – Remove and return the most recent price (top of the stack).
int removeLatest(node*& head){
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
// 3. latest() – Return the most recent stock price without removing it.
int latest(node* head){
    if (isEmpty(head)) {
        cerr << "Stack is empty. No latest price available." << endl;
        return -1;  // Meaningful value indicating empty stack
    }
    return head->price;
}

// 4. isEmpty() – Check if there are no prices recorded.
bool isEmpty(node* head){
    return head == nullptr;
}

// Function to view all prices in the stack (for debugging purposes) (use recusrion to print in reverce)
void viewStack(node* head) {
    if (isEmpty(head)) {
        cout << "No prices recorded." << endl;
        return;
    }
    // Recursive call to reach the bottom of the stack
    printReverce(head);
    cout << endl;
}

void printReverce(node* head) {
    if (head == nullptr) {
        return;
    }
    // Recursive call to reach the bottom of the stack
    printReverce(head->next);
    cout << head->price << " ";
}

int main(){
    node* head = nullptr;
    int choice, price;
    do {
        cout << "Menu:\n1. Record Price\n2. Remove Latest Price\n3. View Latest Price\n4. Check if Empty\n5. View Price History\n6. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter stock price to record: ";
                cin >> price;
                record(head, price);
                cout << "Price " << price << " recorded.\n";
                break;
            case 2:
                price = removeLatest(head);
                if (price != -1)
                    cout << "Removed latest price: " << price << endl;
                break;
            case 3:
                price = latest(head);
                if (price != -1)
                    cout << "Latest price: " << price << endl;
                break;
            case 4:
                if (isEmpty(head))
                    cout << "No prices recorded.\n";
                else
                    cout << "Prices are recorded.\n";
                break;
            case 5:
                viewStack(head);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
    return 0;
}