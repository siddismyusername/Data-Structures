// WAP to simulate a faculty database as a hash table. Search a particular faculty by using
// MOD as a hash function for linear probing with chaining with replacement method
// of collision handling technique. Assume suitable data for faculty record.

#include <iostream>
#include <string>
using namespace std;

struct Faculty {
    int id;
    string name;
    string department;
    string designation;
    Faculty* next;  // For chaining with replacement
};

class FacultyHashTable {
private:
    Faculty** table;
    int size;
    
    int hashFunction(int id) {
        return id % size;  // MOD hash function
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
        int homeIndex = index;
        
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
            // Chaining with replacement
            Faculty* current = table[index];
            int currentHome = hashFunction(current->id);
            
            // If current element is at its home position
            if (currentHome == index) {
                // Add new faculty to chain
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newFaculty;
                cout << "Collision at index " << index 
                     << ". Added " << name << " to chain at home position\n";
            }
            else {
                // Current element is not at home - replace it
                Faculty* displaced = table[index];
                table[index] = newFaculty;
                
                // Find new position for displaced element using linear probing
                index = (index + 1) % size;
                while (table[index] != nullptr) {
                    current = table[index];
                    currentHome = hashFunction(current->id);
                    
                    if (currentHome == index) {
                        // Found home position, add to chain
                        while (current->next != nullptr) {
                            current = current->next;
                        }
                        current->next = displaced;
                        cout << "Replaced element at index " << homeIndex 
                             << ". Inserted " << name << " at index " << homeIndex
                             << " and chained displaced element\n";
                        return;
                    }
                    index = (index + 1) % size;
                }
                table[index] = displaced;
                cout << "Replaced element at index " << homeIndex 
                     << ". Inserted " << name << " at index " << homeIndex
                     << " and placed displaced element at index " << index << endl;
            }
        }
    }
    
    bool search(int id) {
        int index = hashFunction(id);
        int originalIndex = index;
        
        cout << "\nSearching for faculty with ID " << id << "...\n";
        cout << "Hash index: " << index << endl;
        
        // Search starting from hash index
        do {
            if (table[index] != nullptr) {
                Faculty* temp = table[index];
                while (temp != nullptr) {
                    if (temp->id == id) {
                        cout << "\nFaculty found at index " << index << "!\n";
                        cout << "ID: " << temp->id << endl;
                        cout << "Name: " << temp->name << endl;
                        cout << "Department: " << temp->department << endl;
                        cout << "Designation: " << temp->designation << endl;
                        return true;
                    }
                    temp = temp->next;
                }
            }
            index = (index + 1) % size;
        } while (index != originalIndex);
        
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
