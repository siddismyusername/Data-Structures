// Implement a hash table with collision resolution using linear
// probing.
#include <iostream>

using namespace std;

class HashTable{
private:
    int *table;
    int size;

public:
    HashTable(int n)
    {
        size = n;
        table = new int[size];
        for (int i = 0; i < size; i++)
        {
            table[i] = -1; // -1 indicates empty slot
        }
    }
    int hashFunction(int key)
    {
        return key % size;
    }
    // insert method with linear probing
    void insert(int key)
    {
        int index = hashFunction(key);
        int originalIndex = index;
        while (table[index] != -1)
        {
            index = (index + 1) % size;
            if (index == originalIndex)
            {
                cout << "Hash Table is full! Cannot insert " << key << endl;
                return;
            }
        }
        table[index] = key;
        cout << "Inserted " << key << " at index " << index << endl;
    }
    // display method
    void display(){
        cout << "Hash Table contents:\n";
        for (int i = 0; i < size; i++)
        {
            if (table[i] != -1)
                cout << "[" << i << "] : " << table[i] << endl;
            else
                cout << "[" << i << "] : " << "Empty" << endl;
        }
    }
    // empty table method{
    
    void emptyTable(){
        for (int i = 0; i < size; i++)
        {
            table[i] = -1; // -1 indicates empty slot
        }
        cout << "Hash Table has been emptied.\n";
    }
};

int main() {
    int tableSize, numElements, key;

    cout << "Enter size of hash table: ";
    cin >> tableSize;
    HashTable ht(tableSize);
    int choice;
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Insert Key\n";
        cout << "2. Display Table\n";
        cout << "3. Empty Table\n";
        cout << "4. Exit\n";
        cout << "==========================\n";
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