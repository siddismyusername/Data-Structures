// Write a program that maintains a queue of passengers waiting to see a ticket agent.
// The program user should be able to insert a new passenger at the rear of the queue,
// Display the passenger at the front of the Queue, or remove the passenger at the front of the queue.
// The program will display the number of passengers left in the queue just before it terminates.

#include <iostream>
#include <string>
using namespace std;

struct Passenger {
    int passengerId;
    string name;
    string destination;
    int ticketClass; // 1: Economy, 2: Business, 3: First Class
};

class PassengerQueue {
private:
    Passenger* queue;
    int front;
    int rear;
    int maxSize;
    int count;
    int nextPassengerId;
    
public:
    PassengerQueue(int size) {
        maxSize = size;
        queue = new Passenger[maxSize];
        front = 0;
        rear = -1;
        count = 0;
        nextPassengerId = 1; // Starting passenger ID
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == maxSize;
    }
    
    // Insert a new passenger at the rear of the queue
    bool insertPassenger(string name, string destination, int ticketClass) {
        if (isFull()) {
            cout << "\nQueue is full! Cannot add more passengers.\n";
            return false;
        }
        
        rear = (rear + 1) % maxSize;
        queue[rear].passengerId = nextPassengerId++;
        queue[rear].name = name;
        queue[rear].destination = destination;
        queue[rear].ticketClass = ticketClass;
        count++;
        
        cout << "\n========== Passenger Added to Queue ==========\n";
        cout << "Passenger ID: " << queue[rear].passengerId << endl;
        cout << "Name: " << name << endl;
        cout << "Destination: " << destination << endl;
        cout << "Class: ";
        switch(ticketClass) {
            case 1: cout << "Economy\n"; break;
            case 2: cout << "Business\n"; break;
            case 3: cout << "First Class\n"; break;
            default: cout << "Unknown\n";
        }
        cout << "Position in queue: " << count << endl;
        cout << "==============================================\n";
        
        return true;
    }
    
    // Display the passenger at the front of the queue
    void displayFrontPassenger() {
        if (isEmpty()) {
            cout << "\nQueue is empty! No passengers waiting.\n";
            return;
        }
        
        cout << "\n--- Passenger at Front of Queue ---\n";
        cout << "Passenger ID: " << queue[front].passengerId << endl;
        cout << "Name: " << queue[front].name << endl;
        cout << "Destination: " << queue[front].destination << endl;
        cout << "Class: ";
        switch(queue[front].ticketClass) {
            case 1: cout << "Economy\n"; break;
            case 2: cout << "Business\n"; break;
            case 3: cout << "First Class\n"; break;
            default: cout << "Unknown\n";
        }
        cout << "-----------------------------------\n";
    }
    
    // Remove the passenger at the front of the queue
    bool removePassenger() {
        if (isEmpty()) {
            cout << "\nQueue is empty! No passengers to remove.\n";
            return false;
        }
        
        Passenger removedPassenger = queue[front];
        
        cout << "\n========== Passenger Served and Removed ==========\n";
        cout << "Passenger ID: " << removedPassenger.passengerId << endl;
        cout << "Name: " << removedPassenger.name << endl;
        cout << "Destination: " << removedPassenger.destination << endl;
        cout << "Class: ";
        switch(removedPassenger.ticketClass) {
            case 1: cout << "Economy\n"; break;
            case 2: cout << "Business\n"; break;
            case 3: cout << "First Class\n"; break;
            default: cout << "Unknown\n";
        }
        cout << "==================================================\n";
        
        front = (front + 1) % maxSize;
        count--;
        
        cout << "Passengers remaining in queue: " << count << endl;
        
        return true;
    }
    
    // Display all passengers in the queue
    void displayAllPassengers() {
        if (isEmpty()) {
            cout << "\nQueue is empty! No passengers waiting.\n";
            return;
        }
        
        cout << "\n========== All Passengers in Queue ==========\n";
        cout << "Total passengers waiting: " << count << endl;
        cout << "=============================================\n";
        
        int index = front;
        for (int i = 0; i < count; i++) {
            cout << "\nPosition " << (i + 1) << ":\n";
            cout << "  Passenger ID: " << queue[index].passengerId << endl;
            cout << "  Name: " << queue[index].name << endl;
            cout << "  Destination: " << queue[index].destination << endl;
            cout << "  Class: ";
            switch(queue[index].ticketClass) {
                case 1: cout << "Economy\n"; break;
                case 2: cout << "Business\n"; break;
                case 3: cout << "First Class\n"; break;
                default: cout << "Unknown\n";
            }
            index = (index + 1) % maxSize;
        }
        cout << "=============================================\n";
    }
    
    int getCount() {
        return count;
    }
    
    ~PassengerQueue() {
        delete[] queue;
    }
};

int main() {
    int maxPassengers;
    
    cout << "============================================\n";
    cout << "  Ticket Agent - Passenger Queue System\n";
    cout << "============================================\n";
    
    cout << "\nEnter maximum queue capacity: ";
    cin >> maxPassengers;
    cin.ignore();
    
    if (maxPassengers < 1) {
        cout << "Invalid capacity! Setting to default (10).\n";
        maxPassengers = 10;
    }
    
    PassengerQueue passengerQueue(maxPassengers);
    int choice;
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Insert Passenger at Rear\n";
        cout << "2. Display Front Passenger\n";
        cout << "3. Remove Front Passenger\n";
        cout << "4. Display All Passengers\n";
        cout << "5. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                if (passengerQueue.isFull()) {
                    cout << "\nQueue is full! Please wait for passengers to be served.\n";
                    break;
                }
                
                string name, destination;
                int ticketClass;
                
                cout << "\n--- Add New Passenger ---\n";
                cout << "Passenger Name: ";
                getline(cin, name);
                
                cout << "Destination: ";
                getline(cin, destination);
                
                cout << "Ticket Class (1-Economy, 2-Business, 3-First Class): ";
                cin >> ticketClass;
                cin.ignore();
                
                if (ticketClass < 1 || ticketClass > 3) {
                    cout << "Invalid class! Defaulting to Economy.\n";
                    ticketClass = 1;
                }
                
                passengerQueue.insertPassenger(name, destination, ticketClass);
                break;
            }
            
            case 2:
                passengerQueue.displayFrontPassenger();
                break;
            
            case 3:
                passengerQueue.removePassenger();
                break;
            
            case 4:
                passengerQueue.displayAllPassengers();
                break;
            
            case 5:
                cout << "\n========== Program Terminating ==========\n";
                cout << "Number of passengers left in queue: " << passengerQueue.getCount() << endl;
                if (passengerQueue.getCount() > 0) {
                    cout << "\nRemaining passengers:\n";
                    passengerQueue.displayAllPassengers();
                }
                cout << "\nThank you for using the Ticket Agent System!\n";
                cout << "=========================================\n";
                break;
            
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);
    
    return 0;
}
