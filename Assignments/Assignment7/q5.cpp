// Write a Program to create a Binary Tree and perform the
// following Recursive operations on it. a. Inorder Traversal b.
// Preorder Traversal c. Display Number of Leaf Nodes d. Mirror
// Image

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;

    void insertRecursive(Node*& node, int val) {
        if (node == nullptr) {
            node = new Node(val);
            return;
        }
        if (val < node->data) {
            insertRecursive(node->left, val);
        } else {
            insertRecursive(node->right, val);
        }
    }
    
    void inorderRecursive(Node* node) {
        if (node == nullptr) return;
        inorderRecursive(node->left);
        cout << node->data << " ";
        inorderRecursive(node->right);
    }
    
    void preorderRecursive(Node* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorderRecursive(node->left);
        preorderRecursive(node->right);
    }
    
    int countLeafNodes(Node* node) {
        if (node == nullptr) return 0;
        if (node->left == nullptr && node->right == nullptr) return 1;
        return countLeafNodes(node->left) + countLeafNodes(node->right);
    }
    
    Node* mirrorImage(Node* node) {
        if (node == nullptr) return nullptr;
        Node* leftMirror = mirrorImage(node->left);
        Node* rightMirror = mirrorImage(node->right);
        node->left = rightMirror;
        node->right = leftMirror;
        return node;
    }
public:
    BinaryTree() : root(nullptr) {}
    
    void insert(int val) {
        insertRecursive(root, val);
    }
    
    void inorder() {
        cout << "Inorder Traversal: ";
        inorderRecursive(root);
        cout << endl;
    }
    
    void preorder() {
        cout << "Preorder Traversal: ";
        preorderRecursive(root);
        cout << endl;
    }
    
    int leafNodeCount() {
        return countLeafNodes(root);
    }
    
    void mirror() {
        root = mirrorImage(root);
    }
    
    bool isEmpty() {
        return root == nullptr;
    }
};

int main() {
    BinaryTree tree;
    int choice, value, n;
    
    cout << "========================================\n";
    cout << "     Binary Tree Operations\n";
    cout << "========================================\n";
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Create/Build Binary Tree\n";
        cout << "2. Inorder Traversal\n";
        cout << "3. Preorder Traversal\n";
        cout << "4. Display Number of Leaf Nodes\n";
        cout << "5. Create Mirror Image\n";
        cout << "6. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "\nEnter number of nodes: ";
                cin >> n;
                cout << "Enter " << n << " values:\n";
                for (int i = 0; i < n; i++) {
                    cout << "Value " << (i + 1) << ": ";
                    cin >> value;
                    tree.insert(value);
                }
                cout << "Binary Tree created successfully!\n";
                break;
                
            case 2:
                if (tree.isEmpty()) {
                    cout << "Tree is empty! Please create a tree first.\n";
                } else {
                    tree.inorder();
                }
                break;
                
            case 3:
                if (tree.isEmpty()) {
                    cout << "Tree is empty! Please create a tree first.\n";
                } else {
                    tree.preorder();
                }
                break;
                
            case 4:
                if (tree.isEmpty()) {
                    cout << "Tree is empty! Please create a tree first.\n";
                } else {
                    cout << "Number of Leaf Nodes: " << tree.leafNodeCount() << endl;
                }
                break;
                
            case 5:
                if (tree.isEmpty()) {
                    cout << "Tree is empty! Please create a tree first.\n";
                } else {
                    tree.mirror();
                    cout << "Mirror image created successfully!\n";
                    cout << "Tree after mirroring:\n";
                    tree.inorder();
                }
                break;
                
            case 6:
                cout << "\nExiting...\n";
                break;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);
    
    return 0;
}