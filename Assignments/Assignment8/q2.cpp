// Write a program to illustrate operations on a BST holding numeric
// keys.
// The menu must include: • Insert • Delete • Find • Show

#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
   private:
    Node* root;

    Node* insert(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* deleteNode(Node* node, int key) {
        if (node == nullptr) {
            return node;
        }
        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }

    bool find(Node* node, int key) {
        if (node == nullptr) {
            return false;
        }
        if (key == node->key) {
            return true;
        } else if (key < node->key) {
            return find(node->left, key);
        } else {
            return find(node->right, key);
        }
    }

    void inOrder(Node* node) {
        if (node == nullptr) {
            return;
        }
        inOrder(node->left);
        cout << node->key << " ";
        inOrder(node->right);
    }

   public:
    BST() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void deleteKey(int key) {
        root = deleteNode(root, key);
    }

    bool find(int key) {
        return find(root, key);
    }

    void show() {
        inOrder(root);
        cout << endl;
    }
};

int main() {
    BST tree;
    int choice, key;

    do {
        cout << "Menu:\n1. Insert\n2. Delete\n3. Find\n4. Show\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                tree.insert(key);
                break;
            case 2:
                cout << "Enter key to delete: ";
                cin >> key;
                tree.deleteKey(key);
                break;
            case 3:
                cout << "Enter key to find: ";
                cin >> key;
                if (tree.find(key)) {
                    cout << "Key " << key << " found in the BST.\n";
                } else {
                    cout << "Key " << key << " not found in the BST.\n";
                }
                break;
            case 4:
                cout << "BST elements in order: ";
                tree.show();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}