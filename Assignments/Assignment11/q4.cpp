// Store and retrieve student records using roll numbers.
#include<iostream>
#include<vector>
#include<string>

using namespace std;

struct student{
    int rollNo;
    string name;
};

class HashTable {
private:
    int size;
    //array of vectors for separate chaining
    vector<student>* table;

public:
    HashTable(int n) {
        size = n;
        table = new vector<student>[size];
    }
    int hashFunction(int key) {
        return key % size;
    }
    // insert method with separate chaining
    void insert(int rno,string name) {
        int index = hashFunction(rno);
        student* temp = new student{rno,name};
        table[index].push_back(*temp);
        cout<< "Inserted " << name << " with roll number " << rno << " at index " << index << endl;
    }
    // display method
    void display() {
        cout<<"Hash Table contents: \n";
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "] : ";
            if (table[i].empty()) {
                cout << "Empty";
            } else {
                for (const student& stu : table[i]) {
                    cout << "(" << stu.rollNo << ", " << stu.name << ") -> ";
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

    int choice, rno;
    string name;
    do {
        cout << "\nMenu:\n";
        cout << "1. Insert student record\n";
        cout << "2. Display hash table\n";
        cout << "3. Empty hash table\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter roll number: ";
                cin >> rno;
                cout << "Enter name: ";
                cin >> name;
                ht.insert(rno, name);
                break;
            case 2:
                ht.display();
                break;
            case 3:
                ht.emptyTable();
                cout << "Hash table emptied.\n";
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}