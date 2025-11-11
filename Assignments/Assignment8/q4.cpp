// Write a program to implement a product inventory management
// system for a shop using a search tree data structure. Each product
// must store the following information:
// ● Unique Product Code
// ● Product Name
// ● Price
// ● Quantity in Stock
// ● Date Received
// ● Expiration Date
// Implement the following operations:
// 1. Insert a product into the tree ( organized by product
// name).
// 2. Display all items in the inventory using inorder traversal.
// 3. List expired items in prefix (preorder) order of their
// names.

#include <iostream>
#include <string>

using namespace std;

struct Date {
    int day;
    int month;
    int year;

    bool isExpired(const Date& currentDate) const {
        if (year < currentDate.year) return true;
        if (year == currentDate.year && month < currentDate.month) return true;
        if (year == currentDate.year && month == currentDate.month && day < currentDate.day) return true;
        return false;
    }
};

struct Product {
    string productCode;
    string productName;
    double price;
    int quantityInStock;
    Date dateReceived;
    Date expirationDate;
    Product* left;
    Product* right;

    Product(string code, string name, double pr, int qty, Date received, Date expiry)
        : productCode(code), productName(name), price(pr), quantityInStock(qty),
          dateReceived(received), expirationDate(expiry), left(nullptr), right(nullptr) {}
};

class ProductInventory {
private:
    Product* root;

    Product* insert(Product* node, Product* newProduct) {
        if (node == nullptr) {
            return newProduct;
        }
        if (newProduct->productName < node->productName) {
            node->left = insert(node->left, newProduct);
        } else {
            node->right = insert(node->right, newProduct);
        }
        return node;
    }

    void inorder(Product* node) {
        if (node != nullptr) {
            inorder(node->left);
            displayProduct(node);
            inorder(node->right);
        }
    }

    void preorderExpired(Product* node, const Date& currentDate) {
        if (node != nullptr) {
            if (node->expirationDate.isExpired(currentDate)) {
                displayProduct(node);
            }
            preorderExpired(node->left, currentDate);
            preorderExpired(node->right, currentDate);
        }
    }

    void displayProduct(Product* product) {
        cout << "Product Code: " << product->productCode << endl;
        cout << "Product Name: " << product->productName << endl;
        cout << "Price: " << product->price << endl;
        cout << "Quantity in Stock: " << product->quantityInStock << endl;
        cout << "Date Received: " << product->dateReceived.day << "/" 
             << product->dateReceived.month << "/" << product->dateReceived.year << endl;
        cout << "Expiration Date: " << product->expirationDate.day << "/" 
             << product->expirationDate.month << "/" << product->expirationDate.year << endl;
        cout << "-----------------------------------" << endl;
    }
public:
    ProductInventory() : root(nullptr) {}
    void insertProduct(string code, string name, double price, int qty, Date received, Date expiry) {
        Product* newProduct = new Product(code, name, price, qty, received, expiry);
        root = insert(root, newProduct);
    }
    void displayInventory() {
        inorder(root);
    }
    void displayExpiredItems(const Date& currentDate) {
        preorderExpired(root, currentDate);
    }
};


int main(){
    ProductInventory inventory;

    inventory.insertProduct("P001", "Apple", 0.5, 100, {1, 1, 2024}, {1, 2, 2024});
    inventory.insertProduct("P002", "Banana", 0.3, 150, {5, 1, 2024}, {5, 2, 2024});
    inventory.insertProduct("P003", "Orange", 0.7, 80, {10, 1, 2024}, {10, 3, 2024});

    cout << "Inventory (Inorder Traversal):" << endl;
    inventory.displayInventory();

    Date currentDate = {15, 2, 2024};
    cout << "\nExpired Items (Preorder Traversal):" << endl;
    inventory.displayExpiredItems(currentDate);

    return 0;
}