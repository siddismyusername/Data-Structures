// Implement a hash table with collision resolution using separate chaining.

#include <iostream>
#include <vector>
using namespace std;

class HashTable {
private:
    int size;
    //array of vectors for separate chaining
    vector<int>* table;

public:
    HashTable(int n) {
        size = n;
        table = new vector<int>[size];
    }
    int hashFunction(int key) {
        return key % size;
    }
    // insert method with separate chaining
    void insert(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
        cout << "Inserted " << key << " at index " << index << endl;
    }
    // display method
    void display() {
        cout << "Hash Table contents:\n";
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "] : ";
            if (table[i].empty()) {
                cout << "Empty";
            } else {
                for (const int& key : table[i]) {
                    cout << key << " -> ";
                }
                cout << "NULL";
            }
            cout << endl;
        }
    }
    // empty table method
    void emptyTable() {
        for (int i = 0; i < size; i++) {
            table[i].clear();
        }
    }
};

int main() {
    int tableSize;
    cout << "Enter size of hash table: ";
    cin >> tableSize;

    HashTable ht(tableSize);

    int choice, key;
    do {
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