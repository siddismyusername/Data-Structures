// Write a program to efficiently search a particular employee
// record by using Tree data structure. Also sort the data on emp-id
// in ascending order.
#include <iostream>
using namespace std;

struct Node {
    int empId;
    string name;
    Node* left;
    Node* right;

    Node(int id, const string& n) : empId(id), name(n), left(nullptr), right(nullptr) {}
};
class BST {
   private:
    Node* root;

    Node* insert(Node* node, int empId, const string& name) {
        if (node == nullptr) {
            return new Node(empId, name);
        }
        if (empId < node->empId) {
            node->left = insert(node->left, empId, name);
        } else if (empId > node->empId) {
            node->right = insert(node->right, empId, name);
        }
        return node;
    }

    bool find(Node* node, int empId) {
        if (node == nullptr) {
            return false;
        }
        if (empId == node->empId) {
            return true;
        } else if (empId < node->empId) {
            return find(node->left, empId);
        } else {
            return find(node->right, empId);
        }
    }

    void inOrder(Node* node) {
        if (node == nullptr) {
            return;
        }
        inOrder(node->left);
        cout << "Emp ID: " << node->empId << ", Name: " << node->name << endl;
        inOrder(node->right);
    }
    public:
    BST() : root(nullptr) {}
    void insert(int empId, const string& name) {
        root = insert(root, empId, name);
    }
    bool find(int empId) {
        return find(root, empId);
    }
    void show() {
        inOrder(root);
    }
};

int main() {
    BST tree;
    int n, empId;
    string name;

    cout << "Enter number of employees: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cout << "Enter emp-id and name for employee " << (i + 1) << ": ";
        cin >> empId >> name;
        tree.insert(empId, name);
    }

    cout << "\nEmployees sorted by emp-id:\n";
    tree.show();

    cout << "\nEnter emp-id to search: ";
    cin >> empId;
    if (tree.find(empId)) {
        cout << "Employee with emp-id " << empId << " found.\n";
    } else {
        cout << "Employee with emp-id " << empId << " not found.\n";
    }

    return 0;
}