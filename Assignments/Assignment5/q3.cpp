// Write a program to implement multiple stack i.e more than two stack using array
// and perform following operations on it.
// A. Push B. Pop C. Stack Overflow D. Stack Underflow E. Display

#include <iostream>
using namespace std;

class MultipleStacks {
private:
    int* arr;           // Array to store all stacks
    int* top;           // Array to store top indices for each stack
    int* stackSize;     // Array to store size of each stack
    int numStacks;      // Number of stacks
    int totalSize;      // Total size of array
    
    // Calculate start index for each stack
    int getStartIndex(int stackNum) {
        int start = 0;
        for (int i = 0; i < stackNum; i++) {
            start += stackSize[i];
        }
        return start;
    }
    
public:
    MultipleStacks(int n, int size) {
        numStacks = n;
        totalSize = n * size;
        
        arr = new int[totalSize];
        top = new int[numStacks];
        stackSize = new int[numStacks];
        
        // Initialize each stack with equal size
        for (int i = 0; i < numStacks; i++) {
            stackSize[i] = size;
            top[i] = -1; // Empty stack
        }
        
        cout << "Created " << numStacks << " stacks, each of size " << size << endl;
    }
    
    // Push element to specific stack
    bool push(int stackNum, int value) {
        if (stackNum < 0 || stackNum >= numStacks) {
            cout << "Invalid stack number!\n";
            return false;
        }
        
        // Check for overflow
        if (top[stackNum] == stackSize[stackNum] - 1) {
            cout << "Stack Overflow! Stack " << (stackNum + 1) << " is full.\n";
            return false;
        }
        
        top[stackNum]++;
        int index = getStartIndex(stackNum) + top[stackNum];
        arr[index] = value;
        
        cout << "Pushed " << value << " to Stack " << (stackNum + 1) << endl;
        return true;
    }
    
    // Pop element from specific stack
    int pop(int stackNum) {
        if (stackNum < 0 || stackNum >= numStacks) {
            cout << "Invalid stack number!\n";
            return -1;
        }
        
        // Check for underflow
        if (top[stackNum] == -1) {
            cout << "Stack Underflow! Stack " << (stackNum + 1) << " is empty.\n";
            return -1;
        }
        
        int index = getStartIndex(stackNum) + top[stackNum];
        int value = arr[index];
        top[stackNum]--;
        
        cout << "Popped " << value << " from Stack " << (stackNum + 1) << endl;
        return value;
    }
    
    // Display specific stack
    void displayStack(int stackNum) {
        if (stackNum < 0 || stackNum >= numStacks) {
            cout << "Invalid stack number!\n";
            return;
        }
        
        if (top[stackNum] == -1) {
            cout << "Stack " << (stackNum + 1) << " is empty.\n";
            return;
        }
        
        cout << "Stack " << (stackNum + 1) << ": [";
        int start = getStartIndex(stackNum);
        for (int i = 0; i <= top[stackNum]; i++) {
            cout << arr[start + i];
            if (i < top[stackNum]) cout << ", ";
        }
        cout << "] (Top -> Bottom)\n";
    }
    
    // Display all stacks
    void displayAll() {
        cout << "\n========== All Stacks ==========\n";
        for (int i = 0; i < numStacks; i++) {
            cout << "Stack " << (i + 1) << " [Size: " << (top[i] + 1) << "/" << stackSize[i] << "]: ";
            if (top[i] == -1) {
                cout << "Empty\n";
            } else {
                cout << "[";
                int start = getStartIndex(i);
                for (int j = 0; j <= top[i]; j++) {
                    cout << arr[start + j];
                    if (j < top[i]) cout << ", ";
                }
                cout << "]\n";
            }
        }
        cout << "================================\n";
    }
    
    // Check if stack is full (overflow condition)
    bool isFull(int stackNum) {
        if (stackNum < 0 || stackNum >= numStacks) {
            return false;
        }
        return top[stackNum] == stackSize[stackNum] - 1;
    }
    
    // Check if stack is empty (underflow condition)
    bool isEmpty(int stackNum) {
        if (stackNum < 0 || stackNum >= numStacks) {
            return false;
        }
        return top[stackNum] == -1;
    }
    
    // Get top element without removing
    int peek(int stackNum) {
        if (stackNum < 0 || stackNum >= numStacks) {
            cout << "Invalid stack number!\n";
            return -1;
        }
        
        if (isEmpty(stackNum)) {
            cout << "Stack " << (stackNum + 1) << " is empty!\n";
            return -1;
        }
        
        int index = getStartIndex(stackNum) + top[stackNum];
        return arr[index];
    }
    
    ~MultipleStacks() {
        delete[] arr;
        delete[] top;
        delete[] stackSize;
    }
};

int main() {
    int numStacks, stackSize;
    MultipleStacks* ms = nullptr;
    
    cout << "========================================\n";
    cout << "  Multiple Stacks Using Array\n";
    cout << "========================================\n";
    
    cout << "\nEnter number of stacks: ";
    cin >> numStacks;
    cout << "Enter size of each stack: ";
    cin >> stackSize;
    
    ms = new MultipleStacks(numStacks, stackSize);
    
    int choice, stackNum, value;
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Check Stack Overflow\n";
        cout << "4. Check Stack Underflow\n";
        cout << "5. Display Specific Stack\n";
        cout << "6. Display All Stacks\n";
        cout << "7. Peek (View Top Element)\n";
        cout << "8. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter stack number (1-" << numStacks << "): ";
                cin >> stackNum;
                cout << "Enter value to push: ";
                cin >> value;
                ms->push(stackNum - 1, value);
                break;
                
            case 2:
                cout << "Enter stack number (1-" << numStacks << "): ";
                cin >> stackNum;
                ms->pop(stackNum - 1);
                break;
                
            case 3:
                cout << "Enter stack number to check (1-" << numStacks << "): ";
                cin >> stackNum;
                if (ms->isFull(stackNum - 1)) {
                    cout << "Stack " << stackNum << " is FULL (Overflow condition exists).\n";
                } else {
                    cout << "Stack " << stackNum << " is NOT full (Can accept more elements).\n";
                }
                break;
                
            case 4:
                cout << "Enter stack number to check (1-" << numStacks << "): ";
                cin >> stackNum;
                if (ms->isEmpty(stackNum - 1)) {
                    cout << "Stack " << stackNum << " is EMPTY (Underflow condition exists).\n";
                } else {
                    cout << "Stack " << stackNum << " is NOT empty (Contains elements).\n";
                }
                break;
                
            case 5:
                cout << "Enter stack number to display (1-" << numStacks << "): ";
                cin >> stackNum;
                ms->displayStack(stackNum - 1);
                break;
                
            case 6:
                ms->displayAll();
                break;
                
            case 7:
                cout << "Enter stack number (1-" << numStacks << "): ";
                cin >> stackNum;
                value = ms->peek(stackNum - 1);
                if (value != -1) {
                    cout << "Top element of Stack " << stackNum << ": " << value << endl;
                }
                break;
                
            case 8:
                cout << "\nExiting...\n";
                break;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);
    
    delete ms;
    return 0;
}
