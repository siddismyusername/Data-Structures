// WAP to simulate student databases as a hash table. A student database management system
// using hashing techniques to allow efficient insertion, search, and deletion of student records.

#include <iostream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    string department;
    float cgpa;
    bool isDeleted;
};

class StudentHashTable {
private:
    Student** table;
    bool* occupied;
    int size;
    
    int hashFunction(int rollNo) {
        return rollNo % size;
    }
    
public:
    StudentHashTable(int n) {
        size = n;
        table = new Student*[size];
        occupied = new bool[size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
            occupied[i] = false;
        }
    }
    
    void insert(int rollNo, string name, string department, float cgpa) {
        int index = hashFunction(rollNo);
        int originalIndex = index;
        
        // Linear probing
        while (occupied[index] && !table[index]->isDeleted) {
            if (table[index]->rollNo == rollNo) {
                cout << "Student already exists!\n";
                return;
            }
            index = (index + 1) % size;
            if (index == originalIndex) {
                cout << "Hash Table is full!\n";
                return;
            }
        }
        
        Student* newStudent = new Student;
        newStudent->rollNo = rollNo;
        newStudent->name = name;
        newStudent->department = department;
        newStudent->cgpa = cgpa;
        newStudent->isDeleted = false;
        
        table[index] = newStudent;
        occupied[index] = true;
        
        cout << "Inserted student " << name << " at index " << index << endl;
    }
    
    bool search(int rollNo) {
        int index = hashFunction(rollNo);
        int originalIndex = index;
        
        cout << "\nSearching for student with Roll No " << rollNo << "...\n";
        
        while (occupied[index]) {
            if (table[index]->rollNo == rollNo && !table[index]->isDeleted) {
                cout << "\nStudent found at index " << index << "!\n";
                cout << "Roll No: " << table[index]->rollNo << endl;
                cout << "Name: " << table[index]->name << endl;
                cout << "Department: " << table[index]->department << endl;
                cout << "CGPA: " << table[index]->cgpa << endl;
                return true;
            }
            index = (index + 1) % size;
            if (index == originalIndex) {
                break;
            }
        }
        
        cout << "Student not found!\n";
        return false;
    }
    
    bool deleteStudent(int rollNo) {
        int index = hashFunction(rollNo);
        int originalIndex = index;
        
        cout << "\nDeleting student with Roll No " << rollNo << "...\n";
        
        while (occupied[index]) {
            if (table[index]->rollNo == rollNo && !table[index]->isDeleted) {
                table[index]->isDeleted = true;
                cout << "Student " << table[index]->name << " deleted from index " << index << endl;
                return true;
            }
            index = (index + 1) % size;
            if (index == originalIndex) {
                break;
            }
        }
        
        cout << "Student not found!\n";
        return false;
    }
    
    void display() {
        cout << "\nStudent Hash Table:\n";
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "] : ";
            if (occupied[i] && !table[i]->isDeleted) {
                cout << table[i]->name << " (Roll:" << table[i]->rollNo 
                     << ", CGPA:" << table[i]->cgpa << ")";
            } else if (occupied[i] && table[i]->isDeleted) {
                cout << "Deleted";
            } else {
                cout << "Empty";
            }
            cout << endl;
        }
    }
    
    ~StudentHashTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] != nullptr) {
                delete table[i];
            }
        }
        delete[] table;
        delete[] occupied;
    }
};

int main() {
    int tableSize;
    
    cout << "Enter size of hash table: ";
    cin >> tableSize;
    
    StudentHashTable ht(tableSize);
    int choice;
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Insert Student\n";
        cout << "2. Search Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Display Table\n";
        cout << "5. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int rollNo;
                string name, department;
                float cgpa;
                
                cout << "Enter Roll No: ";
                cin >> rollNo;
                cin.ignore();
                
                cout << "Enter Name: ";
                getline(cin, name);
                
                cout << "Enter Department: ";
                getline(cin, department);
                
                cout << "Enter CGPA: ";
                cin >> cgpa;
                
                ht.insert(rollNo, name, department, cgpa);
                break;
            }
            
            case 2: {
                int rollNo;
                cout << "Enter Roll No to search: ";
                cin >> rollNo;
                ht.search(rollNo);
                break;
            }
            
            case 3: {
                int rollNo;
                cout << "Enter Roll No to delete: ";
                cin >> rollNo;
                ht.deleteStudent(rollNo);
                break;
            }
            
            case 4:
                ht.display();
                break;
            
            case 5:
                cout << "\nExiting...\n";
                break;
            
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);
    
    return 0;
}
