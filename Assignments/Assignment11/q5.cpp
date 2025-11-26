// WAP to simulate a faculty database as a hash table. Search a
// particular faculty by using MOD as a hash function for linear
// probing method of collision handling technique. 

#include <iostream>

using namespace std;

struct Faculty {
    int id;
    string name;
    string department;
};

class HashTable {
    int size;
    Faculty* table;
public:
    HashTable(int n){
        size = n;
        table = new Faculty[size];
        for(int i = 0; i < size; i++) {
            table[i].id = -1; // indicates empty slot
        }
    }
    int hashFunction(int key) {
        return key % size;
    }
    void insert(Faculty f) {
        int index = hashFunction(f.id);
        int OriginalIndex = index;
        while(table[index].id != -1) {
            index = (index + 1) % size; // linear probing
            if(index == OriginalIndex) {
                cout << "Hash table is full!" << endl;
                return;
            }
        }
        table[index] = f;
    }
    Faculty* search(int id) {
        int index = hashFunction(id);
        int startIndex = index;
        while(table[index].id != -1) {
            if(table[index].id == id) {
                return &table[index];
            }
            index = (index + 1) % size;
            if(index == startIndex) break; // full loop
        }
        return nullptr; // not found
    }

    void display() {
        for(int i = 0; i < size; i++) {
            if(table[i].id != -1) {
                cout << "Index " << i << ": ID=" << table[i].id << ", Name=" << table[i].name << ", Department=" << table[i].department << endl;
            } else {
                cout << "Index " << i << ": Empty" << endl;
            }
        }
    }

    ~HashTable() {
        delete[] table;
    }
};

int main() {
    int n;
    cout << "Enter size of faculty database: ";
    cin >> n;
    HashTable ht(n);

    int choice;
    do {
        cout << "\n1. Insert Faculty\n2. Search Faculty\n3. Display All Faculties\n4. Exit\nEnter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1: {
                Faculty f;
                cout << "Enter Faculty ID: ";
                cin >> f.id;
                cout << "Enter Faculty Name: ";
                cin >> f.name;
                cout << "Enter Faculty Department: ";
                cin >> f.department;
                ht.insert(f);
                break;
            }
            case 2: {
                int id;
                cout << "Enter Faculty ID to search: ";
                cin >> id;
                Faculty* f = ht.search(id);
                if(f) {
                    cout << "Faculty Found: ID=" << f->id << ", Name=" << f->name << ", Department=" << f->department << endl;
                } else {
                    cout << "Faculty with ID " << id << " not found." << endl;
                }
                break;
            }
            case 3:
                ht.display();
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while(choice != 4);

    return 0;
}