// Design and implement a smart college placement portal that uses advanced hashing techniques
// to efficiently manage student placement records with high performance and low collision
// probability, even under dynamic data growth.

#include <iostream>
#include <string>
using namespace std;

struct PlacementRecord {
    int studentId;
    string name;
    string department;
    float cgpa;
    string companyName;
    float package;
    bool isPlaced;
    PlacementRecord* next;  // For separate chaining
};

class PlacementPortal {
private:
    PlacementRecord** table;
    int size;
    int count;
    float loadFactorThreshold;
    
    // Advanced hash function: combination of division and multiplication
    int hashFunction(int studentId) {
        const float A = 0.6180339887;  // (sqrt(5) - 1) / 2
        float temp = studentId * A;
        temp = temp - (int)temp;  // Fractional part
        return (int)(size * temp);
    }
    
    // Secondary hash for double hashing (if needed)
    int hashFunction2(int studentId) {
        return (studentId % size);
    }
    
    void rehash() {
        int oldSize = size;
        PlacementRecord** oldTable = table;
        
        // Double the size
        size = size * 2;
        count = 0;
        table = new PlacementRecord*[size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
        
        cout << "\nRehashing... New size: " << size << endl;
        
        // Reinsert all records
        for (int i = 0; i < oldSize; i++) {
            PlacementRecord* current = oldTable[i];
            while (current != nullptr) {
                PlacementRecord* next = current->next;
                insertRecord(current);
                current = next;
            }
        }
        
        delete[] oldTable;
        cout << "Rehashing complete!\n";
    }
    
    void insertRecord(PlacementRecord* record) {
        int index = hashFunction(record->studentId);
        
        record->next = table[index];
        table[index] = record;
        count++;
    }
    
public:
    PlacementPortal(int initialSize = 10) {
        size = initialSize;
        count = 0;
        loadFactorThreshold = 0.75;
        table = new PlacementRecord*[size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
    }
    
    void addStudent(int studentId, string name, string department, float cgpa) {
        // Check load factor and rehash if needed
        if ((float)count / size > loadFactorThreshold) {
            rehash();
        }
        
        int index = hashFunction(studentId);
        
        // Check if student already exists
        PlacementRecord* current = table[index];
        while (current != nullptr) {
            if (current->studentId == studentId) {
                cout << "Student already exists!\n";
                return;
            }
            current = current->next;
        }
        
        // Create new record
        PlacementRecord* newRecord = new PlacementRecord;
        newRecord->studentId = studentId;
        newRecord->name = name;
        newRecord->department = department;
        newRecord->cgpa = cgpa;
        newRecord->companyName = "";
        newRecord->package = 0.0;
        newRecord->isPlaced = false;
        
        newRecord->next = table[index];
        table[index] = newRecord;
        count++;
        
        cout << "Student added successfully at index " << index << endl;
    }
    
    bool updatePlacement(int studentId, string companyName, float package) {
        int index = hashFunction(studentId);
        
        PlacementRecord* current = table[index];
        while (current != nullptr) {
            if (current->studentId == studentId) {
                current->companyName = companyName;
                current->package = package;
                current->isPlaced = true;
                cout << "Placement updated for " << current->name << endl;
                return true;
            }
            current = current->next;
        }
        
        cout << "Student not found!\n";
        return false;
    }
    
    bool searchStudent(int studentId) {
        int index = hashFunction(studentId);
        
        cout << "\nSearching for student ID " << studentId << "...\n";
        cout << "Hash index: " << index << endl;
        
        PlacementRecord* current = table[index];
        while (current != nullptr) {
            if (current->studentId == studentId) {
                cout << "\nStudent found!\n";
                cout << "ID: " << current->studentId << endl;
                cout << "Name: " << current->name << endl;
                cout << "Department: " << current->department << endl;
                cout << "CGPA: " << current->cgpa << endl;
                if (current->isPlaced) {
                    cout << "Status: PLACED\n";
                    cout << "Company: " << current->companyName << endl;
                    cout << "Package: " << current->package << " LPA\n";
                } else {
                    cout << "Status: NOT PLACED\n";
                }
                return true;
            }
            current = current->next;
        }
        
        cout << "Student not found!\n";
        return false;
    }
    
    void displayPlacedStudents() {
        cout << "\n========== Placed Students ==========\n";
        bool found = false;
        
        for (int i = 0; i < size; i++) {
            PlacementRecord* current = table[i];
            while (current != nullptr) {
                if (current->isPlaced) {
                    cout << current->name << " (ID:" << current->studentId 
                         << ") - " << current->companyName 
                         << " - " << current->package << " LPA\n";
                    found = true;
                }
                current = current->next;
            }
        }
        
        if (!found) {
            cout << "No placements recorded yet.\n";
        }
        cout << "====================================\n";
    }
    
    void displayStatistics() {
        cout << "\n========== Portal Statistics ==========\n";
        cout << "Table Size: " << size << endl;
        cout << "Total Students: " << count << endl;
        cout << "Load Factor: " << (float)count / size << endl;
        
        int placed = 0;
        float totalPackage = 0.0;
        float maxPackage = 0.0;
        
        for (int i = 0; i < size; i++) {
            PlacementRecord* current = table[i];
            while (current != nullptr) {
                if (current->isPlaced) {
                    placed++;
                    totalPackage += current->package;
                    if (current->package > maxPackage) {
                        maxPackage = current->package;
                    }
                }
                current = current->next;
            }
        }
        
        cout << "Placed Students: " << placed << endl;
        cout << "Unplaced Students: " << (count - placed) << endl;
        if (placed > 0) {
            cout << "Average Package: " << (totalPackage / placed) << " LPA\n";
            cout << "Highest Package: " << maxPackage << " LPA\n";
        }
        cout << "=======================================\n";
    }
    
    void display() {
        cout << "\n========== All Students ==========\n";
        for (int i = 0; i < size; i++) {
            if (table[i] != nullptr) {
                cout << "[" << i << "] : ";
                PlacementRecord* current = table[i];
                while (current != nullptr) {
                    cout << current->name << " (ID:" << current->studentId << ")";
                    if (current->next != nullptr) {
                        cout << " -> ";
                    }
                    current = current->next;
                }
                cout << endl;
            }
        }
        cout << "==================================\n";
    }
    
    ~PlacementPortal() {
        for (int i = 0; i < size; i++) {
            PlacementRecord* current = table[i];
            while (current != nullptr) {
                PlacementRecord* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }
};

int main() {
    PlacementPortal portal(5);  // Start with small size to demonstrate dynamic growth
    int choice;
    
    cout << "========================================\n";
    cout << " Smart College Placement Portal\n";
    cout << "========================================\n";
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Add Student\n";
        cout << "2. Update Placement\n";
        cout << "3. Search Student\n";
        cout << "4. Display Placed Students\n";
        cout << "5. Display All Students\n";
        cout << "6. Display Statistics\n";
        cout << "7. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int id;
                string name, department;
                float cgpa;
                
                cout << "Enter Student ID: ";
                cin >> id;
                cin.ignore();
                
                cout << "Enter Name: ";
                getline(cin, name);
                
                cout << "Enter Department: ";
                getline(cin, department);
                
                cout << "Enter CGPA: ";
                cin >> cgpa;
                
                portal.addStudent(id, name, department, cgpa);
                break;
            }
            
            case 2: {
                int id;
                string company;
                float package;
                
                cout << "Enter Student ID: ";
                cin >> id;
                cin.ignore();
                
                cout << "Enter Company Name: ";
                getline(cin, company);
                
                cout << "Enter Package (LPA): ";
                cin >> package;
                
                portal.updatePlacement(id, company, package);
                break;
            }
            
            case 3: {
                int id;
                cout << "Enter Student ID to search: ";
                cin >> id;
                portal.searchStudent(id);
                break;
            }
            
            case 4:
                portal.displayPlacedStudents();
                break;
            
            case 5:
                portal.display();
                break;
            
            case 6:
                portal.displayStatistics();
                break;
            
            case 7:
                cout << "\nExiting...\n";
                break;
            
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 7);
    
    return 0;
}
