#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// WAP to store and manage an appointment schedule for a single day.
// Appointments are scheduled randomly using a linked list.
// Define start time, end time, and minimum/maximum duration for each appointment slot.
// Implement the following operations:
// a) Display the list of currently available time slots.
// b) Book a new appointment within the defined time limits.
// c) Cancel an existing appointment after validating its time, availability, and correctness.
// d) Sort the appointment list in order of appointment times.
// e) Sort the list based on appointment times using pointer manipulation (without swapping data values).

struct Appointment {
    int startHour;
    int startMinute;
    int endHour;
    int endMinute;
    bool isBooked;
    string clientName;
    Appointment* next;
};

// Configuration constants
const int DAY_START_HOUR = 9;      // 9 AM
const int DAY_END_HOUR = 18;       // 6 PM
const int MIN_DURATION = 30;       // 30 minutes
const int MAX_DURATION = 120;      // 2 hours

// Forward declarations
void initializeSchedule(Appointment*& head);
void displaySchedule(Appointment* head);
void bookAppointment(Appointment*& head);
void cancelAppointment(Appointment* head);
void sortByTimeData(Appointment* head);
void sortByTimePointer(Appointment*& head);
int timeToMinutes(int hour, int minute);
void displayTime(int hour, int minute);
bool isTimeOverlap(Appointment* slot, int startH, int startM, int endH, int endM);
void displayAppointment(Appointment* apt, int index);

// Convert time to minutes for easy comparison
int timeToMinutes(int hour, int minute) {
    return hour * 60 + minute;
}

// Display time in HH:MM format
void displayTime(int hour, int minute) {
    cout << setfill('0') << setw(2) << hour << ":" 
         << setfill('0') << setw(2) << minute;
}

// Initialize schedule with random appointments
void initializeSchedule(Appointment*& head) {
    head = nullptr;
    Appointment* tail = nullptr;
    
    int currentHour = DAY_START_HOUR;
    int currentMinute = 0;
    
    while (currentHour < DAY_END_HOUR) {
        // Random duration between MIN and MAX
        int duration = MIN_DURATION + (rand() % ((MAX_DURATION - MIN_DURATION) / 30 + 1)) * 30;
        
        int endMinutes = timeToMinutes(currentHour, currentMinute) + duration;
        int endHour = endMinutes / 60;
        int endMinute = endMinutes % 60;
        
        // Don't exceed day end time
        if (endHour > DAY_END_HOUR || (endHour == DAY_END_HOUR && endMinute > 0)) {
            break;
        }
        
        Appointment* newApt = new Appointment;
        newApt->startHour = currentHour;
        newApt->startMinute = currentMinute;
        newApt->endHour = endHour;
        newApt->endMinute = endMinute;
        // Randomly book some appointments (40% probability)
        newApt->isBooked = (rand() % 100 < 40);
        if (newApt->isBooked) {
            newApt->clientName = "Client" + to_string(rand() % 100);
        } else {
            newApt->clientName = "";
        }
        newApt->next = nullptr;
        
        if (head == nullptr) {
            head = newApt;
            tail = newApt;
        } else {
            tail->next = newApt;
            tail = newApt;
        }
        
        currentHour = endHour;
        currentMinute = endMinute;
    }
}

// Display a single appointment
void displayAppointment(Appointment* apt, int index) {
    cout << index << ". ";
    displayTime(apt->startHour, apt->startMinute);
    cout << " - ";
    displayTime(apt->endHour, apt->endMinute);
    
    int duration = timeToMinutes(apt->endHour, apt->endMinute) - 
                   timeToMinutes(apt->startHour, apt->startMinute);
    cout << " (" << duration << " min) ";
    
    if (apt->isBooked) {
        cout << "- BOOKED [" << apt->clientName << "]";
    } else {
        cout << "- AVAILABLE";
    }
    cout << endl;
}

// Display all appointments
void displaySchedule(Appointment* head) {
    if (head == nullptr) {
        cout << "\nNo appointments scheduled.\n";
        return;
    }
    
    cout << "\n========== Appointment Schedule ==========\n";
    cout << "Day Hours: ";
    displayTime(DAY_START_HOUR, 0);
    cout << " - ";
    displayTime(DAY_END_HOUR, 0);
    cout << "\nDuration Limits: " << MIN_DURATION << " - " << MAX_DURATION << " minutes\n";
    cout << "==========================================\n\n";
    
    Appointment* current = head;
    int index = 1;
    int availableCount = 0;
    int bookedCount = 0;
    
    while (current != nullptr) {
        displayAppointment(current, index);
        if (current->isBooked) {
            bookedCount++;
        } else {
            availableCount++;
        }
        current = current->next;
        index++;
    }
    
    cout << "\n==========================================\n";
    cout << "Total Slots: " << (availableCount + bookedCount) 
         << " | Available: " << availableCount 
         << " | Booked: " << bookedCount << endl;
    cout << "==========================================\n";
}

// Check if times overlap
bool isTimeOverlap(Appointment* slot, int startH, int startM, int endH, int endM) {
    int slotStart = timeToMinutes(slot->startHour, slot->startMinute);
    int slotEnd = timeToMinutes(slot->endHour, slot->endMinute);
    int newStart = timeToMinutes(startH, startM);
    int newEnd = timeToMinutes(endH, endM);
    
    // Check if there's any overlap
    return !(newEnd <= slotStart || newStart >= slotEnd);
}

// Book a new appointment
void bookAppointment(Appointment*& head) {
    int startH, startM, endH, endM;
    string clientName;
    
    cout << "\n========== Book New Appointment ==========\n";
    cout << "Enter start time (HH MM): ";
    cin >> startH >> startM;
    
    cout << "Enter end time (HH MM): ";
    cin >> endH >> endM;
    
    cin.ignore();
    cout << "Enter client name: ";
    getline(cin, clientName);
    
    // Validate time range
    if (startH < DAY_START_HOUR || endH > DAY_END_HOUR || 
        (endH == DAY_END_HOUR && endM > 0)) {
        cout << "Error: Appointment outside working hours!\n";
        return;
    }
    
    int duration = timeToMinutes(endH, endM) - timeToMinutes(startH, startM);
    
    if (duration < MIN_DURATION) {
        cout << "Error: Appointment duration too short (min " << MIN_DURATION << " min)!\n";
        return;
    }
    
    if (duration > MAX_DURATION) {
        cout << "Error: Appointment duration too long (max " << MAX_DURATION << " min)!\n";
        return;
    }
    
    if (timeToMinutes(startH, startM) >= timeToMinutes(endH, endM)) {
        cout << "Error: End time must be after start time!\n";
        return;
    }
    
    // Check for conflicts with existing appointments
    Appointment* current = head;
    while (current != nullptr) {
        if (isTimeOverlap(current, startH, startM, endH, endM)) {
            cout << "Error: Time slot conflicts with existing appointment (";
            displayTime(current->startHour, current->startMinute);
            cout << " - ";
            displayTime(current->endHour, current->endMinute);
            cout << ")!\n";
            return;
        }
        current = current->next;
    }
    
    // Create and add new appointment
    Appointment* newApt = new Appointment;
    newApt->startHour = startH;
    newApt->startMinute = startM;
    newApt->endHour = endH;
    newApt->endMinute = endM;
    newApt->isBooked = true;
    newApt->clientName = clientName;
    newApt->next = nullptr;
    
    // Add to list
    if (head == nullptr) {
        head = newApt;
    } else {
        Appointment* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newApt;
    }
    
    cout << "\nAppointment booked successfully for " << clientName << "!\n";
}

// Cancel an existing appointment
void cancelAppointment(Appointment* head) {
    if (head == nullptr) {
        cout << "\nNo appointments to cancel.\n";
        return;
    }
    
    int startH, startM;
    
    cout << "\n========== Cancel Appointment ==========\n";
    cout << "Enter appointment start time (HH MM): ";
    cin >> startH >> startM;
    
    Appointment* current = head;
    bool found = false;
    
    while (current != nullptr) {
        if (current->startHour == startH && current->startMinute == startM) {
            found = true;
            
            if (!current->isBooked) {
                cout << "Error: This slot is not booked!\n";
                return;
            }
            
            cout << "Appointment details:\n";
            cout << "Time: ";
            displayTime(current->startHour, current->startMinute);
            cout << " - ";
            displayTime(current->endHour, current->endMinute);
            cout << "\nClient: " << current->clientName << endl;
            
            cout << "\nAre you sure you want to cancel? (y/n): ";
            char confirm;
            cin >> confirm;
            
            if (confirm == 'y' || confirm == 'Y') {
                current->isBooked = false;
                current->clientName = "";
                cout << "Appointment cancelled successfully!\n";
            } else {
                cout << "Cancellation aborted.\n";
            }
            return;
        }
        current = current->next;
    }
    
    if (!found) {
        cout << "Error: No appointment found at the specified time!\n";
    }
}

// Sort appointments by time (swapping data)
void sortByTimeData(Appointment* head) {
    if (head == nullptr || head->next == nullptr) {
        cout << "\nList is already sorted or empty.\n";
        return;
    }
    
    bool swapped;
    Appointment* ptr1;
    Appointment* lptr = nullptr;
    
    do {
        swapped = false;
        ptr1 = head;
        
        while (ptr1->next != lptr) {
            int time1 = timeToMinutes(ptr1->startHour, ptr1->startMinute);
            int time2 = timeToMinutes(ptr1->next->startHour, ptr1->next->startMinute);
            
            if (time1 > time2) {
                // Swap data
                int tempSH = ptr1->startHour;
                int tempSM = ptr1->startMinute;
                int tempEH = ptr1->endHour;
                int tempEM = ptr1->endMinute;
                bool tempBooked = ptr1->isBooked;
                string tempName = ptr1->clientName;
                
                ptr1->startHour = ptr1->next->startHour;
                ptr1->startMinute = ptr1->next->startMinute;
                ptr1->endHour = ptr1->next->endHour;
                ptr1->endMinute = ptr1->next->endMinute;
                ptr1->isBooked = ptr1->next->isBooked;
                ptr1->clientName = ptr1->next->clientName;
                
                ptr1->next->startHour = tempSH;
                ptr1->next->startMinute = tempSM;
                ptr1->next->endHour = tempEH;
                ptr1->next->endMinute = tempEM;
                ptr1->next->isBooked = tempBooked;
                ptr1->next->clientName = tempName;
                
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    
    cout << "\nAppointments sorted by time (data swap method)!\n";
}

// Sort appointments by time (pointer manipulation)
void sortByTimePointer(Appointment*& head) {
    if (head == nullptr || head->next == nullptr) {
        cout << "\nList is already sorted or empty.\n";
        return;
    }
    
    bool swapped;
    Appointment** h;
    Appointment* ptr1;
    Appointment* lptr = nullptr;
    
    do {
        swapped = false;
        h = &head;
        
        while ((*h)->next != lptr) {
            ptr1 = *h;
            
            int time1 = timeToMinutes(ptr1->startHour, ptr1->startMinute);
            int time2 = timeToMinutes(ptr1->next->startHour, ptr1->next->startMinute);
            
            if (time1 > time2) {
                // Swap nodes by pointer manipulation
                Appointment* temp = ptr1->next;
                ptr1->next = temp->next;
                temp->next = ptr1;
                *h = temp;
                
                swapped = true;
            }
            h = &(*h)->next;
        }
        lptr = *h;
    } while (swapped);
    
    cout << "\nAppointments sorted by time (pointer manipulation method)!\n";
}

int main() {
    srand(time(0));
    
    Appointment* head = nullptr;
    
    // Initialize schedule with random appointments
    initializeSchedule(head);
    
    int choice;
    
    cout << "==========================================\n";
    cout << "  Appointment Schedule Management System\n";
    cout << "==========================================\n";
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Display Schedule\n";
        cout << "2. Book Appointment\n";
        cout << "3. Cancel Appointment\n";
        cout << "4. Sort by Time (Data Swap)\n";
        cout << "5. Sort by Time (Pointer Manipulation)\n";
        cout << "6. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                displaySchedule(head);
                break;
            case 2:
                bookAppointment(head);
                break;
            case 3:
                cancelAppointment(head);
                break;
            case 4:
                sortByTimeData(head);
                break;
            case 5:
                sortByTimePointer(head);
                break;
            case 6:
                cout << "\nThank you for using the Appointment System!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);
    
    // Clean up memory
    while (head != nullptr) {
        Appointment* temp = head;
        head = head->next;
        delete temp;
    }
    
    return 0;
}
