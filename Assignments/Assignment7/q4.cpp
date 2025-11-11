// Write a Program to create a Binary Tree and perform following
// Nonrecursive operations on it. a. Inorder Traversal b. Preorder
// Traversal c. Display Number of Leaf Nodes d. Mirror Image

#include <iostream>
#include <stack>

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
    
    void insertNode(Node*& node, int val) {
        if (node == nullptr) {
            node = new Node(val);
            return;
        }
        if (val < node->data) {
            insertNode(node->left, val);
        } else {
            insertNode(node->right, val);
        }
    }
    
public:
    BinaryTree() : root(nullptr) {}
    
    void insert(int val) {
        insertNode(root, val);
    }
    
    // Non-recursive Inorder Traversal
    void inorder() {
        if (root == nullptr) {
            cout << "Tree is empty!\n";
            return;
        }
        
        stack<Node*> s;
        Node* current = root;
        
        cout << "Inorder Traversal: ";
        while (current != nullptr || !s.empty()) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }
            current = s.top();
            s.pop();
            cout << current->data << " ";
            current = current->right;
        }
        cout << endl;
    }
    
    // Non-recursive Preorder Traversal
    void preorder() {
        if (root == nullptr) {
            cout << "Tree is empty!\n";
            return;
        }
        
        stack<Node*> s;
        s.push(root);
        
        cout << "Preorder Traversal: ";
        while (!s.empty()) {
            Node* current = s.top();
            s.pop();
            cout << current->data << " ";
            
            // Push right child first so left is processed first
            if (current->right != nullptr) {
                s.push(current->right);
            }
            if (current->left != nullptr) {
                s.push(current->left);
            }
        }
        cout << endl;
    }
    
    // Non-recursive count of leaf nodes
    int leafNodeCount() {
        if (root == nullptr) {
            return 0;
        }
        
        stack<Node*> s;
        s.push(root);
        int count = 0;
        
        while (!s.empty()) {
            Node* current = s.top();
            s.pop();
            
            // If it's a leaf node (no left and right children)
            if (current->left == nullptr && current->right == nullptr) {
                count++;
            }
            
            if (current->right != nullptr) {
                s.push(current->right);
            }
            if (current->left != nullptr) {
                s.push(current->left);
            }
        }
        
        return count;
    }
    
    // Non-recursive mirror image
    void mirror() {
        if (root == nullptr) {
            cout << "Tree is empty!\n";
            return;
        }
        
        stack<Node*> s;
        s.push(root);
        
        while (!s.empty()) {
            Node* current = s.top();
            s.pop();
            
            // Swap left and right children
            Node* temp = current->left;
            current->left = current->right;
            current->right = temp;
            
            // Push children to stack for processing
            if (current->left != nullptr) {
                s.push(current->left);
            }
            if (current->right != nullptr) {
                s.push(current->right);
            }
        }
    }
    
    bool isEmpty() {
        return root == nullptr;
    }
};

int main() {
    BinaryTree tree;
    int choice, value, n;
    
    cout << "========================================\n";
    cout << "  Binary Tree (Non-Recursive Operations)\n";
    cout << "========================================\n";
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Create/Build Binary Tree\n";
        cout << "2. Inorder Traversal (Non-Recursive)\n";
        cout << "3. Preorder Traversal (Non-Recursive)\n";
        cout << "4. Display Number of Leaf Nodes (Non-Recursive)\n";
        cout << "5. Create Mirror Image (Non-Recursive)\n";
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
                tree.inorder();
                break;
                
            case 3:
                tree.preorder();
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