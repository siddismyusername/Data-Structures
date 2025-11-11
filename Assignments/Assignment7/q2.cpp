// Write a program to perform Binary Search Tree (BST) operations
// (Count the total number of nodes, Compute the height of the BST,
// Mirror Image ).
#include <iostream>
#include <queue>

using namespace std;
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};
class BST {
   private:
    Node* root;

    Node* insert(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->data) {
            node->left = insert(node->left, val);
        } else {
            node->right = insert(node->right, val);
        }
        return node;
    }

    int countNodes(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int computeHeight(Node* node) {
        if (node == nullptr) {
            return -1; // Height of empty tree is -1
        }
        int leftHeight = computeHeight(node->left);
        int rightHeight = computeHeight(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

    void mirrorImage(Node* node) {
        if (node == nullptr) {
            return;
        }
        swap(node->left, node->right);
        mirrorImage(node->left);
        mirrorImage(node->right);
    }

    void inorderTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }

   public:
    BST() : root(nullptr) {}

    void insert(int val) {
        root = insert(root, val);
    }

    int countNodes() {
        return countNodes(root);
    }

    int computeHeight() {
        return computeHeight(root);
    }

    void mirrorImage() {
        mirrorImage(root);
    }

    void inorderTraversal() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    BST tree;
    int choice, val;

    while (true) {
        cout << "1. Insert Node\n2. Count Nodes\n3. Compute Height\n4. Mirror Image\n5. Inorder Traversal\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                tree.insert(val);
                break;
            case 2:
                cout << "Total number of nodes: " << tree.countNodes() << endl;
                break;
            case 3:
                cout << "Height of the BST: " << tree.computeHeight() << endl;
                break;
            case 4:
                tree.mirrorImage();
                cout << "Mirror image created." << endl;
                break;
            case 5:
                cout << "Inorder Traversal: ";
                tree.inorderTraversal();
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}