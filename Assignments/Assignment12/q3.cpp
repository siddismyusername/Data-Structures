// WAP to simulate employee databases as a hash table. Search a particular faculty by using
// Mid square method as a hash function for linear probing method of collision handling technique.
// Assume suitable data for faculty record.

#include <iostream>
#include <string>
using namespace std;

struct Employee {
    int id;
    string name;
    string department;
    string designation;
};

class EmployeeHashTable {
private:
    Employee** table;
    bool* occupied;
    int size;
    
    int midSquareHash(int id) {
        long long square = (long long)id * id;
        
        // Convert to string to extract middle digits
        string squareStr = to_string(square);
        int len = squareStr.length();
        
        // Extract middle digits
        int mid = len / 2;
        int extractLen = 2;  // Extract 2 middle digits
        
        if (len < 2) {
            return square % size;
        }
        
        int startPos = mid - extractLen / 2;
        if (startPos < 0) startPos = 0;
        
        string midDigits = squareStr.substr(startPos, extractLen);
        int hashValue = stoi(midDigits);
        
        return hashValue % size;
    }
    
public:
    EmployeeHashTable(int n) {
        size = n;
        table = new Employee*[size];
        occupied = new bool[size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
            occupied[i] = false;
        }
    }
    
    void insert(int id, string name, string department, string designation) {
        int index = midSquareHash(id);
        int originalIndex = index;
        
        // Linear probing
        while (occupied[index]) {
            index = (index + 1) % size;
            if (index == originalIndex) {
                cout << "Hash Table is full!\n";
                return;
            }
        }
        
        Employee* newEmployee = new Employee;
        newEmployee->id = id;
        newEmployee->name = name;
        newEmployee->department = department;
        newEmployee->designation = designation;
        
        table[index] = newEmployee;
        occupied[index] = true;
        
        if (index != originalIndex) {
            cout << "Collision at index " << originalIndex 
                 << ". Inserted " << name << " at index " << index << endl;
        } else {
            cout << "Inserted employee " << name << " at index " << index << endl;
        }
    }
    
    bool search(int id) {
        int index = midSquareHash(id);
        int originalIndex = index;
        
        cout << "\nSearching for employee with ID " << id << "...\n";
        cout << "Hash index: " << index << endl;
        
        // Linear probing search
        while (occupied[index]) {
            if (table[index]->id == id) {
                cout << "\nEmployee found at index " << index << "!\n";
                cout << "ID: " << table[index]->id << endl;
                cout << "Name: " << table[index]->name << endl;
                cout << "Department: " << table[index]->department << endl;
                cout << "Designation: " << table[index]->designation << endl;
                return true;
            }
            index = (index + 1) % size;
            if (index == originalIndex) {
                break;
            }
        }
        
        cout << "Employee not found!\n";
        return false;
    }
    
    void display() {
        cout << "\nEmployee Hash Table:\n";
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "] : ";
            if (occupied[i]) {
                cout << table[i]->name << " (ID:" << table[i]->id << ")";
            } else {
                cout << "Empty";
            }
            cout << endl;
        }
    }
    
    ~EmployeeHashTable() {
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
    
    EmployeeHashTable ht(tableSize);
    int choice;
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Insert Employee\n";
        cout << "2. Search Employee\n";
        cout << "3. Display Table\n";
        cout << "4. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int id;
                string name, department, designation;
                
                cout << "Enter Employee ID: ";
                cin >> id;
                cin.ignore();
                
                cout << "Enter Name: ";
                getline(cin, name);
                
                cout << "Enter Department: ";
                getline(cin, department);
                
                cout << "Enter Designation: ";
                getline(cin, designation);
                
                ht.insert(id, name, department, designation);
                break;
            }
            
            case 2: {
                int id;
                cout << "Enter Employee ID to search: ";
                cin >> id;
                ht.search(id);
                break;
            }
            
            case 3:
                ht.display();
                break;
            
            case 4:
                cout << "\nExiting...\n";
                break;
            
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);
    
    return 0;
}
