// Write a C++ program to implement a Set using a Generalized
// Linked List (GLL). For example:
// Let S = { p, q, {r, s, t, {}, {u, v}, w, x, {y, z}, a1, b1} }
// Store this structure using a Generalized Linked List and display
// the elements in correct set notation format.
#include <iostream>
using namespace std;

struct Node {
    bool flag;
    char ch;
    Node* down;
    
    Node* next;
};

void createSet(Node** head) {
    char ch;
    cout << "Enter element (or '.' to end this set, '}' to end all): ";
    cin >> ch;

    if (ch == '}') {
        *head = nullptr;
        return;
    }

    *head = new Node();
    if (ch == '{') {
        (*head)->flag = true;
        (*head)->down = nullptr;
        createSet(&((*head)->down));
    } else if (ch == '.') {
        (*head)->flag = false;
        (*head)->ch = '\0';
        (*head)->down = nullptr;
    } else {
        (*head)->flag = false;
        (*head)->ch = ch;
        (*head)->down = nullptr;
    }
    createSet(&((*head)->next));
}

void displaySet(Node* head) {
    if (!head) return;

    cout << "{ ";
    Node* temp = head;
    while (temp) {
        if (temp->flag) {
            displaySet(temp->down);
        } else if (temp->ch != '\0') {
            cout << temp->ch << " ";
        }
        temp = temp->next;
    }
    cout << "} ";
}


void freeSet(Node* head) {
    if (!head) return;

    freeSet(head->down);
    freeSet(head->next);
    delete head;
}

int main() {
    Node* setHead = nullptr;
    cout << "Create the set (use '{' to start a subset, '.' to end a subset, '}' to end all):\n";
    createSet(&setHead);

    cout << "The set is: ";
    displaySet(setHead);
    cout << endl;

    freeSet(setHead);
    return 0;
}