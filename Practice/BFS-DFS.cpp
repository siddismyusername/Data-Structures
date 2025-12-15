#include<iostream>
#include<vector>

using namespace std;

struct node{
    int data;
    node* left;
    node* right;
    
    node(int d, node* n) : data(d), left(n), right(n) {}
};

//queue implimentation
class queue{
    vector<node*> s;
public:
    void insert(node* e){
        s.push_back(e);    
    }
    node* pop(){
        node* temp = s.front();
        s.erase(s.begin());
        return temp;
    }
    bool isEmpty(){
        return s.empty();
    }
};

//stack implimentation
class stack{
    vector<node*> s;
public:
    void insert(node* e){
        s.push_back(e);    
    }
    node* pop(){
        node* temp = s.back();
        s.pop_back();
        return temp;
    }
    bool isEmpty(){
        return s.empty();
    }
};

class BST{
    node* root;
public:
    BST(){
        root = nullptr;
    }
    void insert(int e){
        node* ele = new node(e,nullptr);
        node* temp = root;
        if(root == nullptr){
            root = ele;
            return;
        }
        while(true){
            if(e < temp->data){
                if(temp->left == nullptr){
                    temp->left = ele;
                    break;
                }
                temp = temp->left;
            }
            else{
                if(temp->right == nullptr){
                    temp->right = ele;
                    break;
                }
                temp = temp->right;
            }
        }
    }
    void BFS(){
        queue q;
        q.insert(root);
        node* temp;
        while(!q.isEmpty()){
            temp = q.pop();
            cout<<"Current Element: " << temp->data << endl;
            if(temp->left) q.insert(temp->left);
            if(temp->right) q.insert(temp->right);
        }
    }

    void DFS(){
        stack s;
        s.insert(root);
        node* temp;
        while(!s.isEmpty()){
            temp = s.pop();
            cout<<"Current Element: " << temp->data << endl;
            if(temp->right) s.insert(temp->right);
            if(temp->left) s.insert(temp->left);
        }
    }
};

int main(){
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(18);

    cout << "BFS Traversal:" << endl;
    tree.BFS();

    cout << "DFS Traversal:" << endl;
    tree.DFS();

    return 0;
}