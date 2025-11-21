// Write a program to implement multiple queues i.e. two queues using array
// and perform following operations on it.
// A. Add Queue, B. Delete from Queue, C. Display Queue

#include <iostream>
using namespace std;

class MultipleQueues {
private:
    int* arr;           // Single array to hold both queues
    int totalSize;      // Total size of array
    int numQueues;      // Number of queues (2 in this case)
    int queueSize;      // Size allocated to each queue
    
    // Front and rear indices for each queue
    int* front;
    int* rear;
    int* count;         // Count of elements in each queue
    
    // Get the starting index for a queue in the array
    int getStartIndex(int queueNum) {
        return queueNum * queueSize;
    }
    
    // Get the ending index for a queue in the array
    int getEndIndex(int queueNum) {
        return (queueNum + 1) * queueSize - 1;
    }
    
public:
    MultipleQueues(int size, int numQ) {
        numQueues = numQ;
        queueSize = size;
        totalSize = queueSize * numQueues;
        
        arr = new int[totalSize];
        front = new int[numQueues];
        rear = new int[numQueues];
        count = new int[numQueues];
        
        // Initialize all queues
        for (int i = 0; i < numQueues; i++) {
            front[i] = getStartIndex(i);
            rear[i] = getEndIndex(i);
            count[i] = 0;
        }
    }
    
    bool isEmpty(int queueNum) {
        if (queueNum < 0 || queueNum >= numQueues) return true;
        return count[queueNum] == 0;
    }
    
    bool isFull(int queueNum) {
        if (queueNum < 0 || queueNum >= numQueues) return true;
        return count[queueNum] == queueSize;
    }
    
    // Add element to queue (Enqueue)
    bool addToQueue(int queueNum, int value) {
        if (queueNum < 0 || queueNum >= numQueues) {
            cout << "Invalid queue number!\n";
            return false;
        }
        
        if (isFull(queueNum)) {
            cout << "Queue " << (queueNum + 1) << " is full! Cannot add element.\n";
            return false;
        }
        
        int start = getStartIndex(queueNum);
        int end = getEndIndex(queueNum);
        
        rear[queueNum] = (rear[queueNum] + 1);
        if (rear[queueNum] > end) {
            rear[queueNum] = start;
        }
        
        arr[rear[queueNum]] = value;
        count[queueNum]++;
        
        cout << "Element " << value << " added to Queue " << (queueNum + 1) << endl;
        return true;
    }
    
    // Delete element from queue (Dequeue)
    bool deleteFromQueue(int queueNum) {
        if (queueNum < 0 || queueNum >= numQueues) {
            cout << "Invalid queue number!\n";
            return false;
        }
        
        if (isEmpty(queueNum)) {
            cout << "Queue " << (queueNum + 1) << " is empty! Cannot delete element.\n";
            return false;
        }
        
        int start = getStartIndex(queueNum);
        int end = getEndIndex(queueNum);
        
        int deletedValue = arr[front[queueNum]];
        
        front[queueNum] = (front[queueNum] + 1);
        if (front[queueNum] > end) {
            front[queueNum] = start;
        }
        
        count[queueNum]--;
        
        cout << "Element " << deletedValue << " deleted from Queue " << (queueNum + 1) << endl;
        return true;
    }
    
    // Display queue elements
    void displayQueue(int queueNum) {
        if (queueNum < 0 || queueNum >= numQueues) {
            cout << "Invalid queue number!\n";
            return;
        }
        
        if (isEmpty(queueNum)) {
            cout << "Queue " << (queueNum + 1) << " is empty!\n";
            return;
        }
        
        cout << "\n--- Queue " << (queueNum + 1) << " ---\n";
        cout << "Elements (" << count[queueNum] << "/" << queueSize << "): ";
        
        int start = getStartIndex(queueNum);
        int end = getEndIndex(queueNum);
        int index = front[queueNum];
        
        for (int i = 0; i < count[queueNum]; i++) {
            cout << arr[index];
            if (i < count[queueNum] - 1) cout << " <- ";
            
            index++;
            if (index > end) {
                index = start;
            }
        }
        cout << "\n(Front)";
        for (int i = 0; i < count[queueNum] - 1; i++) {
            cout << "     ";
        }
        cout << "(Rear)\n";
    }
    
    // Display all queues
    void displayAllQueues() {
        cout << "\n========== All Queues ==========\n";
        for (int i = 0; i < numQueues; i++) {
            if (isEmpty(i)) {
                cout << "Queue " << (i + 1) << ": Empty\n";
            } else {
                displayQueue(i);
            }
        }
        cout << "================================\n";
    }
    
    // Display array structure
    void displayArrayStructure() {
        cout << "\n--- Array Structure (Total Size: " << totalSize << ") ---\n";
        for (int i = 0; i < numQueues; i++) {
            cout << "Queue " << (i + 1) << " occupies indices [" 
                 << getStartIndex(i) << " - " << getEndIndex(i) << "]";
            cout << " (Capacity: " << queueSize << ", Used: " << count[i] << ")\n";
        }
        cout << "\nArray contents:\n";
        for (int i = 0; i < totalSize; i++) {
            if (i % queueSize == 0 && i != 0) {
                cout << " | ";
            }
            
            // Check if this index is being used
            bool isUsed = false;
            int qNum = i / queueSize;
            
            if (!isEmpty(qNum)) {
                int start = getStartIndex(qNum);
                int end = getEndIndex(qNum);
                int index = front[qNum];
                
                for (int j = 0; j < count[qNum]; j++) {
                    if (index == i) {
                        isUsed = true;
                        break;
                    }
                    index++;
                    if (index > end) index = start;
                }
            }
            
            if (isUsed) {
                cout << arr[i] << " ";
            } else {
                cout << "- ";
            }
        }
        cout << "\n";
    }
    
    ~MultipleQueues() {
        delete[] arr;
        delete[] front;
        delete[] rear;
        delete[] count;
    }
};

int main() {
    int queueSize;
    
    cout << "================================================\n";
    cout << "  Multiple Queues (2 Queues) using Array\n";
    cout << "================================================\n";
    
    cout << "\nEnter size for each queue: ";
    cin >> queueSize;
    
    if (queueSize < 1) {
        cout << "Invalid size! Setting to default (5).\n";
        queueSize = 5;
    }
    
    MultipleQueues mq(queueSize, 2);  // 2 queues
    int choice, queueNum, value;
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Add to Queue\n";
        cout << "2. Delete from Queue\n";
        cout << "3. Display Queue\n";
        cout << "4. Display All Queues\n";
        cout << "5. Display Array Structure\n";
        cout << "6. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Select Queue (1 or 2): ";
                cin >> queueNum;
                queueNum--; // Convert to 0-based index
                
                if (queueNum < 0 || queueNum >= 2) {
                    cout << "Invalid queue number! Please select 1 or 2.\n";
                    break;
                }
                
                cout << "Enter value to add: ";
                cin >> value;
                mq.addToQueue(queueNum, value);
                break;
            
            case 2:
                cout << "Select Queue (1 or 2): ";
                cin >> queueNum;
                queueNum--; // Convert to 0-based index
                
                if (queueNum < 0 || queueNum >= 2) {
                    cout << "Invalid queue number! Please select 1 or 2.\n";
                    break;
                }
                
                mq.deleteFromQueue(queueNum);
                break;
            
            case 3:
                cout << "Select Queue (1 or 2): ";
                cin >> queueNum;
                queueNum--; // Convert to 0-based index
                
                if (queueNum < 0 || queueNum >= 2) {
                    cout << "Invalid queue number! Please select 1 or 2.\n";
                    break;
                }
                
                mq.displayQueue(queueNum);
                break;
            
            case 4:
                mq.displayAllQueues();
                break;
            
            case 5:
                mq.displayArrayStructure();
                break;
            
            case 6:
                cout << "\nExiting program...\n";
                cout << "Final state of queues:\n";
                mq.displayAllQueues();
                break;
            
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);
    
    return 0;
}
