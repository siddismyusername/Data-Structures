// Write a program, using trees, to assign the roll nos. to the
// students of your class as per their previous years result. i.e topper
// will be roll no. 1
#include <iostream>
using namespace std;
struct Node {
    int marks;
    int rollNo;
    Node* left;
    Node* right;

    Node(int m, int r) : marks(m), rollNo(r), left(nullptr), right(nullptr) {}
};

class BST {
   private:
    Node* root;

    Node* insert(Node* node, int marks, int rollNo) {
        if (node == nullptr) {
            return new Node(marks, rollNo);
        }
        if (marks > node->marks) {
            node->left = insert(node->left, marks, rollNo);
        } else {
            node->right = insert(node->right, marks, rollNo);
        }
        return node;
    }

    void inOrder(Node* node, int& rollCounter) {
        if (node == nullptr) {
            return;
        }
        inOrder(node->left, rollCounter);
        cout << "Roll No: " << rollCounter++ << ", Marks: " << node->marks << ", Original Roll No: " << node->rollNo << endl;
        inOrder(node->right, rollCounter);
    }

   public:
    BST() : root(nullptr) {}

    void insert(int marks, int rollNo) {
        root = insert(root, marks, rollNo);
    }

    void assignRollNumbers() {
        int rollCounter = 1;
        inOrder(root, rollCounter);
    }
};

int main() {
    BST tree;
    int n, marks;

    cout << "Enter number of students: ";
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cout << "Enter marks for student with original roll no " << i << ": ";
        cin >> marks;
        tree.insert(marks, i);
    }

    cout << "\nAssigned Roll Numbers based on marks:\n";
    tree.assignRollNumbers();

    return 0;
}