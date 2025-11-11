// Write a Program to create a Binary Tree Search and Find
// Minimum/Maximum in BST

#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};
class BST
{
private:
    Node *root;

    Node *insert(Node *node, int val)
    {
        if (node == nullptr)
        {
            return new Node(val);
        }
        if (val < node->data)
        {
            node->left = insert(node->left, val);
        }
        else
        {
            node->right = insert(node->right, val);
        }
        return node;
    }

    int findMin(Node *node)
    {
        if (node == nullptr)
        {
            throw runtime_error("Tree is empty");
        }
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node->data;
    }

    int findMax(Node *node)
    {
        if (node == nullptr)
        {
            throw runtime_error("Tree is empty");
        }
        while (node->right != nullptr)
        {
            node = node->right;
        }
        return node->data;
    }

public:
    BST() : root(nullptr) {}

    void insert(int val)
    {
        root = insert(root, val);
    }

    int findMin()
    {
        return findMin(root);
    }

    int findMax()
    {
        return findMax(root);
    }
};

int main()
{
    BST tree;
    int choice, val;

    while (true)
    {
        cout << "1. Insert Node\n2. Find Minimum\n3. Find Maximum\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> val;
            tree.insert(val);
            break;
        case 2:
            cout << "Minimum value in BST: " << tree.findMin() << endl;
            break;
        case 3:
            cout << "Maximum value in BST: " << tree.findMax() << endl;
            break;
        case 4:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}