// Write a program to keep track of patients as they checked into a medical clinic,
// assigning patients to doctors on a first-come, first-served basis.

#include <iostream>
#include <string>
using namespace std;

#define MAX_PATIENTS 100

struct Patient {
    int id;
    string name;
    int age;
    string ailment;
};

class PatientQueue {
private:
    Patient queue[MAX_PATIENTS];
    int front;
    int rear;
    int count;
    int nextPatientId;
    
public:
    PatientQueue() : front(0), rear(-1), count(0), nextPatientId(1) {}
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == MAX_PATIENTS;
    }
    
    // Add patient to queue (check-in)
    bool enqueue(string name, int age, string ailment) {
        if (isFull()) {
            cout << "Queue is full! Cannot add more patients.\n";
            return false;
        }
        
        rear = (rear + 1) % MAX_PATIENTS;
        queue[rear].id = nextPatientId++;
        queue[rear].name = name;
        queue[rear].age = age;
        queue[rear].ailment = ailment;
        count++;
        
        cout << "\nPatient checked in successfully!\n";
        cout << "Patient ID: " << queue[rear].id << endl;
        cout << "Name: " << name << endl;
        cout << "Position in queue: " << count << endl;
        
        return true;
    }
    
    // Assign patient to doctor (remove from queue)
    Patient dequeue() {
        Patient p;
        p.id = -1; // Invalid patient
        
        if (isEmpty()) {
            cout << "No patients in queue!\n";
            return p;
        }
        
        p = queue[front];
        front = (front + 1) % MAX_PATIENTS;
        count--;
        
        return p;
    }
    
    // View next patient without removing
    Patient peek() {
        Patient p;
        p.id = -1;
        
        if (isEmpty()) {
            cout << "No patients in queue!\n";
            return p;
        }
        
        return queue[front];
    }
    
    // Display all patients in queue
    void displayQueue() {
        if (isEmpty()) {
            cout << "\nNo patients in queue.\n";
            return;
        }
        
        cout << "\n========== Patient Queue ==========\n";
        cout << "Total patients waiting: " << count << endl;
        cout << "===================================\n";
        
        int index = front;
        for (int i = 0; i < count; i++) {
            cout << "\nPosition " << (i + 1) << ":\n";
            cout << "  ID: " << queue[index].id << endl;
            cout << "  Name: " << queue[index].name << endl;
            cout << "  Age: " << queue[index].age << endl;
            cout << "  Ailment: " << queue[index].ailment << endl;
            index = (index + 1) % MAX_PATIENTS;
        }
        cout << "===================================\n";
    }
    
    int getCount() {
        return count;
    }
};

class Doctor {
private:
    string name;
    string specialization;
    bool available;
    Patient currentPatient;
    int patientsServed;
    
public:
    Doctor() : name(""), specialization(""), available(true), patientsServed(0) {
        currentPatient.id = -1;
    }
    
    Doctor(string n, string spec) : name(n), specialization(spec), available(true), patientsServed(0) {
        currentPatient.id = -1;
    }
    
    void setDetails(string n, string spec) {
        name = n;
        specialization = spec;
        available = true;
        patientsServed = 0;
        currentPatient.id = -1;
    }
    
    bool isAvailable() {
        return available;
    }
    
    void assignPatient(Patient p) {
        currentPatient = p;
        available = false;
        patientsServed++;
        
        cout << "\n========== Patient Assigned ==========\n";
        cout << "Doctor: " << name << " (" << specialization << ")\n";
        cout << "Patient ID: " << p.id << endl;
        cout << "Patient Name: " << p.name << endl;
        cout << "Age: " << p.age << endl;
        cout << "Ailment: " << p.ailment << endl;
        cout << "======================================\n";
    }
    
    void finishConsultation() {
        if (!available) {
            cout << "\nDr. " << name << " has finished consultation with " << currentPatient.name << endl;
            currentPatient.id = -1;
            available = true;
        } else {
            cout << "\nDr. " << name << " is not currently with any patient.\n";
        }
    }
    
    void displayStatus() {
        cout << "Dr. " << name << " (" << specialization << ")\n";
        if (available) {
            cout << "  Status: Available\n";
        } else {
            cout << "  Status: Busy with Patient ID " << currentPatient.id << " (" << currentPatient.name << ")\n";
        }
        cout << "  Patients served today: " << patientsServed << endl;
    }
    
    string getName() {
        return name;
    }
};

int main() {
    PatientQueue patientQueue;
    Doctor doctors[5];
    int numDoctors = 0;
    int choice;
    
    cout << "========================================\n";
    cout << "  Medical Clinic Management System\n";
    cout << "========================================\n";
    
    // Initialize doctors
    cout << "\nEnter number of doctors (1-5): ";
    cin >> numDoctors;
    cin.ignore();
    
    if (numDoctors < 1 || numDoctors > 5) {
        numDoctors = 2;
        cout << "Invalid input. Setting to default (2 doctors).\n";
    }
    
    for (int i = 0; i < numDoctors; i++) {
        string name, spec;
        cout << "\nDoctor " << (i + 1) << ":\n";
        cout << "  Name: ";
        getline(cin, name);
        cout << "  Specialization: ";
        getline(cin, spec);
        doctors[i].setDetails(name, spec);
    }
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Check-in Patient\n";
        cout << "2. Assign Patient to Doctor\n";
        cout << "3. Finish Consultation\n";
        cout << "4. View Patient Queue\n";
        cout << "5. View Doctor Status\n";
        cout << "6. View Next Patient\n";
        cout << "7. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                string name, ailment;
                int age;
                
                cout << "\n--- Patient Check-in ---\n";
                cout << "Patient Name: ";
                getline(cin, name);
                cout << "Age: ";
                cin >> age;
                cin.ignore();
                cout << "Ailment/Reason for visit: ";
                getline(cin, ailment);
                
                patientQueue.enqueue(name, age, ailment);
                break;
            }
            
            case 2: {
                if (patientQueue.isEmpty()) {
                    cout << "\nNo patients in queue!\n";
                    break;
                }
                
                // Find available doctor
                int availableDoc = -1;
                for (int i = 0; i < numDoctors; i++) {
                    if (doctors[i].isAvailable()) {
                        availableDoc = i;
                        break;
                    }
                }
                
                if (availableDoc == -1) {
                    cout << "\nAll doctors are currently busy. Please wait.\n";
                } else {
                    Patient p = patientQueue.dequeue();
                    doctors[availableDoc].assignPatient(p);
                }
                break;
            }
            
            case 3: {
                cout << "\nSelect doctor (1-" << numDoctors << "): ";
                int docNum;
                cin >> docNum;
                cin.ignore();
                
                if (docNum < 1 || docNum > numDoctors) {
                    cout << "Invalid doctor number!\n";
                } else {
                    doctors[docNum - 1].finishConsultation();
                }
                break;
            }
            
            case 4:
                patientQueue.displayQueue();
                break;
            
            case 5:
                cout << "\n========== Doctor Status ==========\n";
                for (int i = 0; i < numDoctors; i++) {
                    cout << (i + 1) << ". ";
                    doctors[i].displayStatus();
                    cout << endl;
                }
                cout << "===================================\n";
                break;
            
            case 6: {
                Patient p = patientQueue.peek();
                if (p.id != -1) {
                    cout << "\n--- Next Patient in Queue ---\n";
                    cout << "ID: " << p.id << endl;
                    cout << "Name: " << p.name << endl;
                    cout << "Age: " << p.age << endl;
                    cout << "Ailment: " << p.ailment << endl;
                }
                break;
            }
            
            case 7:
                cout << "\nExiting system...\n";
                cout << "\nSummary:\n";
                cout << "Patients still waiting: " << patientQueue.getCount() << endl;
                cout << "\nThank you for using the clinic management system!\n";
                break;
            
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);
    
    return 0;
}
