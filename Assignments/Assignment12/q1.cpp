// WAP to simulate a faculty database as a hash table. Search a particular faculty by using
// 'divide' as a hash function for linear probing with chaining without replacement method
// of collision handling technique. Assume suitable data for faculty record.

#include <iostream>
#include <string>
using namespace std;

struct Faculty {
    int id;
    string name;
    string department;
    string designation;
    Faculty* next;  // For chaining without replacement
};

class FacultyHashTable {
private:
    Faculty** table;
    int size;
    
    int hashFunction(int id) {
        return id % size;  // Divide hash function
    }
    
public:
    FacultyHashTable(int n) {
        size = n;
        table = new Faculty*[size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
    }
    
    void insert(int id, string name, string department, string designation) {
        int index = hashFunction(id);
        
        Faculty* newFaculty = new Faculty;
        newFaculty->id = id;
        newFaculty->name = name;
        newFaculty->department = department;
        newFaculty->designation = designation;
        newFaculty->next = nullptr;
        
        // If slot is empty
        if (table[index] == nullptr) {
            table[index] = newFaculty;
            cout << "Inserted faculty " << name << " at index " << index << endl;
        }
        else {
            // Linear probing with chaining without replacement
            int originalIndex = index;
            Faculty* temp = table[index];
            
            // Find empty slot using linear probing
            while (table[index] != nullptr) {
                index = (index + 1) % size;
                if (index == originalIndex) {
                    cout << "Hash Table is full!\n";
                    delete newFaculty;
                    return;
                }
            }
            
            // Place new faculty in empty slot
            table[index] = newFaculty;
            
            // Chain without replacement: link from home position
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newFaculty;
            
            cout << "Collision at index " << originalIndex 
                 << ". Inserted " << name << " at index " << index 
                 << " and chained from home position\n";
        }
    }
    
    bool search(int id) {
        int index = hashFunction(id);
        int originalIndex = index;
        
        cout << "\nSearching for faculty with ID " << id << "...\n";
        cout << "Hash index: " << index << endl;
        
        // Check home position first
        if (table[index] != nullptr) {
            Faculty* temp = table[index];
            while (temp != nullptr) {
                if (temp->id == id) {
                    cout << "\nFaculty found!\n";
                    cout << "ID: " << temp->id << endl;
                    cout << "Name: " << temp->name << endl;
                    cout << "Department: " << temp->department << endl;
                    cout << "Designation: " << temp->designation << endl;
                    return true;
                }
                temp = temp->next;
            }
        }
        
        // Linear probing search
        index = (index + 1) % size;
        while (index != originalIndex && table[index] != nullptr) {
            if (table[index]->id == id) {
                cout << "\nFaculty found at index " << index << "!\n";
                cout << "ID: " << table[index]->id << endl;
                cout << "Name: " << table[index]->name << endl;
                cout << "Department: " << table[index]->department << endl;
                cout << "Designation: " << table[index]->designation << endl;
                return true;
            }
            index = (index + 1) % size;
        }
        
        cout << "Faculty not found!\n";
        return false;
    }
    
    void display() {
        cout << "\nFaculty Hash Table:\n";
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "] : ";
            if (table[i] == nullptr) {
                cout << "Empty";
            } else {
                Faculty* temp = table[i];
                while (temp != nullptr) {
                    cout << temp->name << " (ID:" << temp->id << ")";
                    if (temp->next != nullptr) {
                        cout << " -> ";
                    }
                    temp = temp->next;
                }
            }
            cout << endl;
        }
    }
    
    ~FacultyHashTable() {
        for (int i = 0; i < size; i++) {
            Faculty* temp = table[i];
            while (temp != nullptr) {
                Faculty* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
        delete[] table;
    }
};

int main() {
    int tableSize;
    
    cout << "Enter size of hash table: ";
    cin >> tableSize;
    
    FacultyHashTable ht(tableSize);
    int choice;
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Insert Faculty\n";
        cout << "2. Search Faculty\n";
        cout << "3. Display Table\n";
        cout << "4. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int id;
                string name, department, designation;
                
                cout << "Enter Faculty ID: ";
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
                cout << "Enter Faculty ID to search: ";
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
