// Write a program to implement deletion operations in the
// product inventory system using a search tree.
// Each product must store the following information:
// ● Unique Product Code
// ● Product Name
// ● Price
// ● Quantity in Stock
// ● Date Received
// ● Expiration Date
// Implement the following operations:
// 1. Delete a product using its unique product code.
// 2. Delete all expired products based on the current date.

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

    Product* deleteByCode(Product* node, const string& code) {
        if (node == nullptr) return node;

        if (code < node->productCode) {
            node->left = deleteByCode(node->left, code);
        } else if (code > node->productCode) {
            node->right = deleteByCode(node->right, code);
        } else {
            // Node with only one child or no child
            if (node->left == nullptr) {
                Product* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Product* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Product* temp = minValueNode(node->right);
            node->productCode = temp->productCode;
            node->productName = temp->productName;
            node->price = temp->price;
            node->quantityInStock = temp->quantityInStock;
            node->dateReceived = temp->dateReceived;
            node->expirationDate = temp->expirationDate;
            node->right = deleteByCode(node->right, temp->productCode);
        }
        return node;
    }
    Product* minValueNode(Product* node) {
        Product* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    Product* deleteExpired(Product* node, const Date& currentDate) {
        if (node == nullptr) return node;

        node->left = deleteExpired(node->left, currentDate);
        node->right = deleteExpired(node->right, currentDate);

        if (node->expirationDate.isExpired(currentDate)) {
            return deleteByCode(node, node->productCode);
        }
        return node;
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
    void deleteProductByCode(string code) {
        root = deleteByCode(root, code);
    }
    void deleteExpiredProducts(const Date& currentDate) {
        root = deleteExpired(root, currentDate);
    }
};


int main(){
    ProductInventory inventory;

    inventory.insertProduct("P001", "Milk", 2.5, 100, {1, 1, 2024}, {1, 2, 2024});
    inventory.insertProduct("P002", "Bread", 1.5, 200, {5, 1, 2024}, {10, 1, 2024});
    inventory.insertProduct("P003", "Eggs", 3.0, 150, {3, 1, 2024}, {20, 1, 2024});
    cout << "Initial Inventory:" << endl;
    inventory.displayInventory();
    cout << "Deleting product with code P002..." << endl;
    inventory.deleteProductByCode("P002");
    cout << "Inventory after deletion:" << endl;
    inventory.displayInventory();
    Date currentDate = {15, 1, 2024};
    cout << "Deleting expired products as of " << currentDate.day << "/" << currentDate
            .month << "/" << currentDate.year << "..." << endl; 
    inventory.deleteExpiredProducts(currentDate);
    cout << "Inventory after deleting expired products:" << endl;
    inventory.displayInventory();

    return 0;
}