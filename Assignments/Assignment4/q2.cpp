// WAP to perform addition of two polynomials using singly linked list

#include <iostream>
using namespace std;

struct Node {
    int coeff;
    int exp;
    Node* next;
};

class Polynomial {
private:
    Node* head;
    
    void insertTerm(int coeff, int exp) {
        if (coeff == 0) return; // Don't insert zero coefficients
        
        Node* newNode = new Node;
        newNode->coeff = coeff;
        newNode->exp = exp;
        newNode->next = nullptr;
        
        if (head == nullptr || head->exp < exp) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr && current->next->exp > exp) {
                current = current->next;
            }
            
            if (current->exp == exp) {
                current->coeff += coeff;
                delete newNode;
            } else {
                newNode->next = current->next;
                current->next = newNode;
            }
        }
    }
    
public:
    Polynomial() : head(nullptr) {}
    
    void createPolynomial() {
        int n, coeff, exp;
        cout << "Enter number of terms: ";
        cin >> n;
        
        for (int i = 0; i < n; i++) {
            cout << "Term " << (i + 1) << ":\n";
            cout << "  Coefficient: ";
            cin >> coeff;
            cout << "  Exponent: ";
            cin >> exp;
            insertTerm(coeff, exp);
        }
    }
    
    void display() {
        if (head == nullptr) {
            cout << "0";
            return;
        }
        
        Node* current = head;
        bool first = true;
        
        while (current != nullptr) {
            if (!first && current->coeff > 0) {
                cout << " + ";
            } else if (current->coeff < 0) {
                cout << " - ";
            }
            
            int absCoeff = abs(current->coeff);
            
            if (current->exp == 0) {
                cout << absCoeff;
            } else if (current->exp == 1) {
                if (absCoeff == 1) {
                    cout << "x";
                } else {
                    cout << absCoeff << "x";
                }
            } else {
                if (absCoeff == 1) {
                    cout << "x^" << current->exp;
                } else {
                    cout << absCoeff << "x^" << current->exp;
                }
            }
            
            first = false;
            current = current->next;
        }
    }
    
    static Polynomial addPolynomials(Polynomial& p1, Polynomial& p2) {
        Polynomial result;
        Node* ptr1 = p1.head;
        Node* ptr2 = p2.head;
        
        while (ptr1 != nullptr && ptr2 != nullptr) {
            if (ptr1->exp == ptr2->exp) {
                result.insertTerm(ptr1->coeff + ptr2->coeff, ptr1->exp);
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            } else if (ptr1->exp > ptr2->exp) {
                result.insertTerm(ptr1->coeff, ptr1->exp);
                ptr1 = ptr1->next;
            } else {
                result.insertTerm(ptr2->coeff, ptr2->exp);
                ptr2 = ptr2->next;
            }
        }
        
        while (ptr1 != nullptr) {
            result.insertTerm(ptr1->coeff, ptr1->exp);
            ptr1 = ptr1->next;
        }
        
        while (ptr2 != nullptr) {
            result.insertTerm(ptr2->coeff, ptr2->exp);
            ptr2 = ptr2->next;
        }
        
        return result;
    }
    
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    bool isEmpty() {
        return head == nullptr;
    }
    
    ~Polynomial() {
        clear();
    }
};

int main() {
    Polynomial poly1, poly2;
    int choice;
    
    cout << "========================================\n";
    cout << "  Polynomial Addition (Singly Linked List)\n";
    cout << "========================================\n";
    
    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Enter First Polynomial\n";
        cout << "2. Enter Second Polynomial\n";
        cout << "3. Display First Polynomial\n";
        cout << "4. Display Second Polynomial\n";
        cout << "5. Add Polynomials\n";
        cout << "6. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                poly1.clear();
                cout << "\nEnter First Polynomial:\n";
                poly1.createPolynomial();
                cout << "First polynomial entered successfully!\n";
                break;
                
            case 2:
                poly2.clear();
                cout << "\nEnter Second Polynomial:\n";
                poly2.createPolynomial();
                cout << "Second polynomial entered successfully!\n";
                break;
                
            case 3:
                if (poly1.isEmpty()) {
                    cout << "First polynomial is empty!\n";
                } else {
                    cout << "First Polynomial: ";
                    poly1.display();
                    cout << endl;
                }
                break;
                
            case 4:
                if (poly2.isEmpty()) {
                    cout << "Second polynomial is empty!\n";
                } else {
                    cout << "Second Polynomial: ";
                    poly2.display();
                    cout << endl;
                }
                break;
                
            case 5:
                if (poly1.isEmpty() || poly2.isEmpty()) {
                    cout << "Please enter both polynomials first!\n";
                } else {
                    cout << "\nFirst Polynomial:  ";
                    poly1.display();
                    cout << endl;
                    
                    cout << "Second Polynomial: ";
                    poly2.display();
                    cout << endl;
                    
                    Polynomial sum = Polynomial::addPolynomials(poly1, poly2);
                    cout << "Sum:               ";
                    sum.display();
                    cout << endl;
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
