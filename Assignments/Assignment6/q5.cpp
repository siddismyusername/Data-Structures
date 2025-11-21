// In a call center, customer calls are handled on a first-come, first-served basis.
// Implement a queue system using Linked list where:
// - Each customer call is enqueued as it arrives.
// - Customer service agents dequeue calls to assist customers.
// - If there are no calls, the system waits

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// Forward declarations
struct Call;
class CallQueue;

struct Call {
    int callId;
    string customerName;
    string phoneNumber;
    string issueType;
    string arrivalTime;
    Call* next;
};

class CallQueue {
private:
    Call* front;
    Call* rear;
    int count;
    int nextCallId;
    
    // Get current time as string
    string getCurrentTime() {
        time_t now = time(0);
        char* dt = ctime(&now);
        string timeStr(dt);
        // Remove newline character
        if (!timeStr.empty() && timeStr[timeStr.length()-1] == '\n') {
            timeStr.erase(timeStr.length()-1);
        }
        return timeStr;
    }
    
public:
    CallQueue() {
        front = NULL;
        rear = NULL;
        count = 0;
        nextCallId = 1001; // Starting call ID
    }
    
    bool isEmpty() {
        return front == NULL;
    }
    
    // Enqueue a customer call
    void enqueueCall(string customerName, string phoneNumber, string issueType) {
        Call* newCall = new Call;
        newCall->callId = nextCallId++;
        newCall->customerName = customerName;
        newCall->phoneNumber = phoneNumber;
        newCall->issueType = issueType;
        newCall->arrivalTime = getCurrentTime();
        newCall->next = NULL;
        
        if (isEmpty()) {
            front = rear = newCall;
        } else {
            rear->next = newCall;
            rear = newCall;
        }
        
        count++;
        
        cout << "\n========== Incoming Call Enqueued ==========\n";
        cout << "Call ID: " << newCall->callId << endl;
        cout << "Customer: " << customerName << endl;
        cout << "Phone: " << phoneNumber << endl;
        cout << "Issue: " << issueType << endl;
        cout << "Arrival Time: " << newCall->arrivalTime << endl;
        cout << "Position in queue: " << count << endl;
        cout << "============================================\n";
    }
    
    // Dequeue a call for customer service agent
    bool dequeueCall() {
        if (isEmpty()) {
            cout << "\n*** No calls in queue! System waiting for calls... ***\n";
            return false;
        }
        
        Call* callToHandle = front;
        
        cout << "\n========== Call Dequeued for Agent ==========\n";
        cout << "Call ID: " << callToHandle->callId << endl;
        cout << "Customer: " << callToHandle->customerName << endl;
        cout << "Phone: " << callToHandle->phoneNumber << endl;
        cout << "Issue: " << callToHandle->issueType << endl;
        cout << "Arrival Time: " << callToHandle->arrivalTime << endl;
        cout << "Current Time: " << getCurrentTime() << endl;
        cout << "=============================================\n";
        
        front = front->next;
        
        // If queue becomes empty
        if (front == NULL) {
            rear = NULL;
        }
        
        delete callToHandle;
        count--;
        
        cout << "Remaining calls in queue: " << count << endl;
        
        return true;
    }
    
    // Display the next call in queue
    void displayNextCall() {
        if (isEmpty()) {
            cout << "\n*** No calls waiting! System is idle. ***\n";
            return;
        }
        
        cout << "\n--- Next Call in Queue ---\n";
        cout << "Call ID: " << front->callId << endl;
        cout << "Customer: " << front->customerName << endl;
        cout << "Phone: " << front->phoneNumber << endl;
        cout << "Issue: " << front->issueType << endl;
        cout << "Waiting since: " << front->arrivalTime << endl;
        cout << "--------------------------\n";
    }
    
    // Display all calls in queue
    void displayAllCalls() {
        if (isEmpty()) {
            cout << "\n*** No calls in queue! System waiting for calls... ***\n";
            return;
        }
        
        cout << "\n========== All Calls in Queue ==========\n";
        cout << "Total calls waiting: " << count << endl;
        cout << "=========================================\n";
        
        Call* current = front;
        int position = 1;
        
        while (current != NULL) {
            cout << "\nPosition " << position << ":\n";
            cout << "  Call ID: " << current->callId << endl;
            cout << "  Customer: " << current->customerName << endl;
            cout << "  Phone: " << current->phoneNumber << endl;
            cout << "  Issue: " << current->issueType << endl;
            cout << "  Waiting since: " << current->arrivalTime << endl;
            
            current = current->next;
            position++;
        }
        cout << "=========================================\n";
    }
    
    // Display queue status
    void displayStatus() {
        cout << "\n========== Call Center Status ==========\n";
        cout << "Total calls in queue: " << count << endl;
        
        if (isEmpty()) {
            cout << "Status: IDLE - Waiting for calls\n";
        } else {
            cout << "Status: ACTIVE - Processing calls\n";
            cout << "Next call ID: " << front->callId << endl;
            cout << "Oldest call customer: " << front->customerName << endl;
        }
        cout << "========================================\n";
    }
    
    int getCount() {
        return count;
    }
    
    ~CallQueue() {
        while (!isEmpty()) {
            Call* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

int main() {
    CallQueue callCenter;
    int choice;
    
    cout << "================================================\n";
    cout << "  Call Center Queue System (FCFS - Linked List)\n";
    cout << "================================================\n";
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Enqueue Call (Customer calling)\n";
        cout << "2. Dequeue Call (Agent handling call)\n";
        cout << "3. Display Next Call\n";
        cout << "4. Display All Calls in Queue\n";
        cout << "5. Display Call Center Status\n";
        cout << "6. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                string customerName, phoneNumber, issueType;
                
                cout << "\n--- New Incoming Call ---\n";
                cout << "Customer Name: ";
                getline(cin, customerName);
                
                cout << "Phone Number: ";
                getline(cin, phoneNumber);
                
                cout << "Issue Type (e.g., Billing, Technical, General): ";
                getline(cin, issueType);
                
                callCenter.enqueueCall(customerName, phoneNumber, issueType);
                break;
            }
            
            case 2:
                cout << "\nAgent ready to handle call...\n";
                callCenter.dequeueCall();
                break;
            
            case 3:
                callCenter.displayNextCall();
                break;
            
            case 4:
                callCenter.displayAllCalls();
                break;
            
            case 5:
                callCenter.displayStatus();
                break;
            
            case 6:
                cout << "\n========== Closing Call Center ==========\n";
                if (callCenter.getCount() > 0) {
                    cout << "Warning: " << callCenter.getCount() << " calls still in queue!\n";
                    cout << "Displaying pending calls:\n";
                    callCenter.displayAllCalls();
                } else {
                    cout << "No pending calls. All calls handled.\n";
                }
                cout << "\nThank you for using the Call Center System!\n";
                cout << "=========================================\n";
                break;
            
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);
    
    return 0;
}
