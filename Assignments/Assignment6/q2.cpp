// Pizza parlour accepting maximum n orders. Orders are served on an FCFS basis.
// Order once placed can't be cancelled. Write C++ program to simulate the system using circular QUEUE.

#include <iostream>
#include <string>
using namespace std;

struct Order {
    int orderId;
    string customerName;
    string pizzaType;
    int quantity;
    string size;
};

class CircularQueue {
private:
    Order* queue;
    int front;
    int rear;
    int maxSize;
    int count;
    int nextOrderId;
    
public:
    CircularQueue(int n) {
        maxSize = n;
        queue = new Order[maxSize];
        front = 0;
        rear = -1;
        count = 0;
        nextOrderId = 1001; // Starting order ID
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == maxSize;
    }
    
    // Place a new order (enqueue)
    bool placeOrder(string customerName, string pizzaType, int quantity, string size) {
        if (isFull()) {
            cout << "\nSorry! Pizza parlour is at maximum capacity.\n";
            cout << "Cannot accept more orders at this time.\n";
            return false;
        }
        
        rear = (rear + 1) % maxSize;
        queue[rear].orderId = nextOrderId++;
        queue[rear].customerName = customerName;
        queue[rear].pizzaType = pizzaType;
        queue[rear].quantity = quantity;
        queue[rear].size = size;
        count++;
        
        cout << "\n========== Order Placed Successfully ==========\n";
        cout << "Order ID: " << queue[rear].orderId << endl;
        cout << "Customer: " << customerName << endl;
        cout << "Pizza: " << pizzaType << " (" << size << ")\n";
        cout << "Quantity: " << quantity << endl;
        cout << "Position in queue: " << count << endl;
        cout << "===============================================\n";
        
        return true;
    }
    
    // Serve an order (dequeue)
    bool serveOrder() {
        if (isEmpty()) {
            cout << "\nNo orders to serve!\n";
            return false;
        }
        
        Order servedOrder = queue[front];
        
        cout << "\n========== Order Served ==========\n";
        cout << "Order ID: " << servedOrder.orderId << endl;
        cout << "Customer: " << servedOrder.customerName << endl;
        cout << "Pizza: " << servedOrder.pizzaType << " (" << servedOrder.size << ")\n";
        cout << "Quantity: " << servedOrder.quantity << endl;
        cout << "==================================\n";
        
        front = (front + 1) % maxSize;
        count--;
        
        cout << "Remaining orders in queue: " << count << endl;
        
        return true;
    }
    
    // Display all pending orders
    void displayOrders() {
        if (isEmpty()) {
            cout << "\nNo pending orders.\n";
            return;
        }
        
        cout << "\n========== Pending Orders (FCFS) ==========\n";
        cout << "Total orders in queue: " << count << "/" << maxSize << endl;
        cout << "===========================================\n";
        
        int index = front;
        for (int i = 0; i < count; i++) {
            cout << "\nPosition " << (i + 1) << ":\n";
            cout << "  Order ID: " << queue[index].orderId << endl;
            cout << "  Customer: " << queue[index].customerName << endl;
            cout << "  Pizza: " << queue[index].pizzaType << " (" << queue[index].size << ")\n";
            cout << "  Quantity: " << queue[index].quantity << endl;
            index = (index + 1) % maxSize;
        }
        cout << "===========================================\n";
    }
    
    // View next order to be served
    void viewNextOrder() {
        if (isEmpty()) {
            cout << "\nNo orders in queue.\n";
            return;
        }
        
        cout << "\n--- Next Order to be Served ---\n";
        cout << "Order ID: " << queue[front].orderId << endl;
        cout << "Customer: " << queue[front].customerName << endl;
        cout << "Pizza: " << queue[front].pizzaType << " (" << queue[front].size << ")\n";
        cout << "Quantity: " << queue[front].quantity << endl;
    }
    
    // Get current queue status
    void displayStatus() {
        cout << "\n========== Pizza Parlour Status ==========\n";
        cout << "Maximum capacity: " << maxSize << " orders\n";
        cout << "Current orders: " << count << endl;
        cout << "Available slots: " << (maxSize - count) << endl;
        
        if (isFull()) {
            cout << "Status: FULL - Not accepting new orders\n";
        } else if (isEmpty()) {
            cout << "Status: EMPTY - No pending orders\n";
        } else {
            cout << "Status: ACCEPTING ORDERS\n";
        }
        cout << "==========================================\n";
    }
    
    int getCount() {
        return count;
    }
    
    ~CircularQueue() {
        delete[] queue;
    }
};

int main() {
    int maxOrders;
    
    cout << "========================================\n";
    cout << "  Pizza Parlour Order System (FCFS)\n";
    cout << "========================================\n";
    
    cout << "\nEnter maximum number of orders parlour can accept: ";
    cin >> maxOrders;
    cin.ignore();
    
    if (maxOrders < 1) {
        cout << "Invalid capacity! Setting to default (5).\n";
        maxOrders = 5;
    }
    
    CircularQueue orderQueue(maxOrders);
    int choice;
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Place New Order\n";
        cout << "2. Serve Order (FCFS)\n";
        cout << "3. Display All Pending Orders\n";
        cout << "4. View Next Order\n";
        cout << "5. View Parlour Status\n";
        cout << "6. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                if (orderQueue.isFull()) {
                    cout << "\nSorry! Maximum capacity reached.\n";
                    cout << "Please wait for some orders to be served.\n";
                    break;
                }
                
                string customerName, pizzaType, size;
                int quantity;
                
                cout << "\n--- Place New Order ---\n";
                cout << "Customer Name: ";
                getline(cin, customerName);
                
                cout << "Pizza Type (e.g., Margherita, Pepperoni, Veggie): ";
                getline(cin, pizzaType);
                
                cout << "Size (Small/Medium/Large): ";
                getline(cin, size);
                
                cout << "Quantity: ";
                cin >> quantity;
                cin.ignore();
                
                if (quantity < 1) {
                    cout << "Invalid quantity!\n";
                    break;
                }
                
                orderQueue.placeOrder(customerName, pizzaType, quantity, size);
                break;
            }
            
            case 2:
                orderQueue.serveOrder();
                break;
            
            case 3:
                orderQueue.displayOrders();
                break;
            
            case 4:
                orderQueue.viewNextOrder();
                break;
            
            case 5:
                orderQueue.displayStatus();
                break;
            
            case 6:
                cout << "\n========== Closing Pizza Parlour ==========\n";
                if (orderQueue.getCount() > 0) {
                    cout << "Warning: " << orderQueue.getCount() << " orders still pending!\n";
                    cout << "Displaying pending orders:\n";
                    orderQueue.displayOrders();
                }
                cout << "\nThank you for using the Pizza Parlour System!\n";
                cout << "===========================================\n";
                break;
            
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);
    
    return 0;
}
