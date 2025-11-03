#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// WAP to implement a ticket reservation system for Galaxy Multiplex using C++.
// The multiplex has 8 rows with 8 seats in each row.
// Use a doubly circular linked list to track availability of seats in each row.
// Initially, some seats are randomly booked.
// An array will store head pointers for each row's linked list.
// Implement the following operations:
// a) Display the current list of available seats.
// b) Book one or more seats as per customer request.
// c) Cancel an existing booking when requested.

struct Node {
    int seatNumber;
    bool isBooked;
    Node* next;
    Node* prev;
};

const int ROWS = 8;
const int SEATS_PER_ROW = 8;

// Forward declarations
void initializeRow(Node*& head, int rowNum);
void displaySeats(Node* rowHeads[]);
void bookSeats(Node* rowHeads[]);
void cancelBooking(Node* rowHeads[]);
void displayRow(Node* head, int rowNum);
Node* findSeat(Node* head, int seatNum);

// Initialize a doubly circular linked list for a row
void initializeRow(Node*& head, int rowNum) {
    Node* first = nullptr;
    Node* prev = nullptr;
    
    for (int i = 1; i <= SEATS_PER_ROW; i++) {
        Node* newNode = new Node;
        newNode->seatNumber = i;
        // Randomly book some seats (30% probability)
        newNode->isBooked = (rand() % 100 < 30);
        newNode->next = nullptr;
        newNode->prev = prev;
        
        if (first == nullptr) {
            first = newNode;
        }
        
        if (prev != nullptr) {
            prev->next = newNode;
        }
        
        prev = newNode;
    }
    
    // Make it circular
    if (first != nullptr && prev != nullptr) {
        prev->next = first;
        first->prev = prev;
    }
    
    head = first;
}

// Display a single row's seat status
void displayRow(Node* head, int rowNum) {
    if (head == nullptr) {
        cout << "Row " << rowNum << ": Empty" << endl;
        return;
    }
    
    cout << "Row " << rowNum << ": ";
    Node* current = head;
    do {
        if (current->isBooked) {
            cout << "[X" << current->seatNumber << "] ";
        } else {
            cout << "[ " << current->seatNumber << "] ";
        }
        current = current->next;
    } while (current != head);
    cout << endl;
}

// Display all seats in the multiplex
void displaySeats(Node* rowHeads[]) {
    cout << "\n========== Galaxy Multiplex Seating ==========\n";
    cout << "Legend: [X#] = Booked, [ #] = Available\n";
    cout << "=============================================\n\n";
    
    for (int i = 0; i < ROWS; i++) {
        displayRow(rowHeads[i], i + 1);
    }
    
    cout << "\n=============================================\n";
}

// Find a seat node in a row
Node* findSeat(Node* head, int seatNum) {
    if (head == nullptr) return nullptr;
    
    Node* current = head;
    do {
        if (current->seatNumber == seatNum) {
            return current;
        }
        current = current->next;
    } while (current != head);
    
    return nullptr;
}

// Book one or more seats
void bookSeats(Node* rowHeads[]) {
    int row, numSeats;
    
    cout << "\nEnter row number (1-" << ROWS << "): ";
    cin >> row;
    
    if (row < 1 || row > ROWS) {
        cout << "Invalid row number!\n";
        return;
    }
    
    cout << "How many seats do you want to book? ";
    cin >> numSeats;
    
    if (numSeats < 1 || numSeats > SEATS_PER_ROW) {
        cout << "Invalid number of seats!\n";
        return;
    }
    
    int* seatNumbers = new int[numSeats];
    cout << "Enter seat numbers: ";
    for (int i = 0; i < numSeats; i++) {
        cin >> seatNumbers[i];
    }
    
    // Validate and book seats
    int booked = 0;
    for (int i = 0; i < numSeats; i++) {
        if (seatNumbers[i] < 1 || seatNumbers[i] > SEATS_PER_ROW) {
            cout << "Seat " << seatNumbers[i] << " is invalid!\n";
            continue;
        }
        
        Node* seat = findSeat(rowHeads[row - 1], seatNumbers[i]);
        if (seat == nullptr) {
            cout << "Seat " << seatNumbers[i] << " not found!\n";
            continue;
        }
        
        if (seat->isBooked) {
            cout << "Seat " << seatNumbers[i] << " is already booked!\n";
        } else {
            seat->isBooked = true;
            cout << "Seat " << seatNumbers[i] << " booked successfully!\n";
            booked++;
        }
    }
    
    cout << "\nTotal seats booked: " << booked << endl;
    delete[] seatNumbers;
}

// Cancel an existing booking
void cancelBooking(Node* rowHeads[]) {
    int row, numSeats;
    
    cout << "\nEnter row number (1-" << ROWS << "): ";
    cin >> row;
    
    if (row < 1 || row > ROWS) {
        cout << "Invalid row number!\n";
        return;
    }
    
    cout << "How many seats do you want to cancel? ";
    cin >> numSeats;
    
    if (numSeats < 1 || numSeats > SEATS_PER_ROW) {
        cout << "Invalid number of seats!\n";
        return;
    }
    
    int* seatNumbers = new int[numSeats];
    cout << "Enter seat numbers to cancel: ";
    for (int i = 0; i < numSeats; i++) {
        cin >> seatNumbers[i];
    }
    
    // Validate and cancel bookings
    int cancelled = 0;
    for (int i = 0; i < numSeats; i++) {
        if (seatNumbers[i] < 1 || seatNumbers[i] > SEATS_PER_ROW) {
            cout << "Seat " << seatNumbers[i] << " is invalid!\n";
            continue;
        }
        
        Node* seat = findSeat(rowHeads[row - 1], seatNumbers[i]);
        if (seat == nullptr) {
            cout << "Seat " << seatNumbers[i] << " not found!\n";
            continue;
        }
        
        if (!seat->isBooked) {
            cout << "Seat " << seatNumbers[i] << " is not booked!\n";
        } else {
            seat->isBooked = false;
            cout << "Seat " << seatNumbers[i] << " cancelled successfully!\n";
            cancelled++;
        }
    }
    
    cout << "\nTotal bookings cancelled: " << cancelled << endl;
    delete[] seatNumbers;
}

int main() {
    // Seed random number generator
    srand(time(0));
    
    // Array to store head pointers for each row
    Node* rowHeads[ROWS];
    
    // Initialize all rows
    for (int i = 0; i < ROWS; i++) {
        rowHeads[i] = nullptr;
        initializeRow(rowHeads[i], i + 1);
    }
    
    int choice;
    
    cout << "========================================\n";
    cout << "  Welcome to Galaxy Multiplex System\n";
    cout << "========================================\n";
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Display Available Seats\n";
        cout << "2. Book Seats\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                displaySeats(rowHeads);
                break;
            case 2:
                bookSeats(rowHeads);
                break;
            case 3:
                cancelBooking(rowHeads);
                break;
            case 4:
                cout << "\nThank you for using Galaxy Multiplex System!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);
    
    // Clean up memory
    for (int i = 0; i < ROWS; i++) {
        if (rowHeads[i] != nullptr) {
            Node* current = rowHeads[i];
            Node* temp;
            do {
                temp = current;
                current = current->next;
                delete temp;
            } while (current != rowHeads[i]);
        }
    }
    
    return 0;
}
