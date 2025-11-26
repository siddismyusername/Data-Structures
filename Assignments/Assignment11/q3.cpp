// Implement a hash table with collision resolution using linked lists.

#include <iostream>

using namespace std;

struct Node {
    int key;
    Node* next;
};

class HashTable {
private:
    Node** table;
    int size;
public:
    HashTable(int n) {
        size = n;
        table = new Node*[size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
    }
    int hashFunction(int key) {
        return key % size;
    }
    // insert method with linked list collision resolution
    void insert(int key) {
        int index = hashFunction(key);
        Node* newNode = new Node{key, nullptr};
        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            Node* current = table[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        cout << "Inserted " << key << " at index " << index << endl;
    }
    // display method
    void display() {
        cout << "Hash Table contents:\n";
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "] : ";
            Node* current = table[i];
            if (current == nullptr) {
                cout << "Empty";
            } else {
                while (current != nullptr) {
                    cout << current->key << " -> ";
                    current = current->next;
                }
                cout << "NULL";
            }
            cout << endl;
        }
    }
    // empty table method
    void emptyTable() {
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
    }
};

int main(){
    int tableSize;
    cout << "Enter the size of the hash table: ";
    cin >> tableSize;
    HashTable ht(tableSize);

    int choice,key;
    do{
        cout << "\nMenu:\n";
        cout << "1. Insert key\n";
        cout << "2. Display hash table\n";
        cout << "3. Empty hash table\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                ht.insert(key);
                break;
            case 2:
                ht.display();
                break;
            case 3:
                ht.emptyTable();
                cout << "Hash table emptied.\n";
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);
    return 0;
}