#include<iostream>
#include<string>

using namespace std;

struct node{
    string name;
    string role;
    long int PRN;
    node* next;
};

node* createNode(string name, long int PRN){
    node* newNode = new node();
    newNode->name = name;
    newNode->role = "member"; 
    newNode->PRN = PRN;
    newNode->next = NULL;
    return newNode;
}

void insertLast(node** head, string name, long int PRN){
    node* newNode = createNode(name, PRN);
    newNode->role = "secretary";
    
    if(*head == NULL){
        *head = newNode;
        (*head)->role = "president/secretary"; 
        return;
    }
    
    node* temp = *head;
    while(temp->next != NULL){
        temp = temp->next;
    }

    if (temp->role == "president/secretary") {
        temp->role = "president";
    } else {
        temp->role = "member";
    }
    
    temp->next = newNode;
}

node* insertLast(node* head,node* ele){
    if(head==NULL){
        head = ele;
        return head;
    }
    node* temp = head;
    while(temp->next!=NULL){
        temp = temp->next;
    }
    temp->next = ele;
    ele->next = NULL;
    return head;
}

void insertFirst(node** head, string name, long int PRN){
    node* newNode = createNode(name, PRN);
    newNode->role = "president";
    
    if(*head == NULL){
        *head = newNode;
        (*head)->role = "president/secretary";
        return;
    }
    
    newNode->next = *head;
    
    if ((*head)->role == "president" || (*head)->role == "president/secretary") {
         (*head)->role = "member";
    }

    *head = newNode;
}

void displayList(node* head){
    if (head == NULL) {
        cout << "The list is empty." << endl << endl;
        return;
    }
    node* temp = head;
    while(temp != NULL){
        cout << "PRN: " << temp->PRN << ", Name: " << temp->name << ", Role: " << temp->role << endl;
        temp = temp->next;
    }
    cout << endl;
}

void countMembers(node* head){
    int count = 0;
    node* temp = head;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    cout << "Total members in the list: " << count << endl << endl;
}


void deleteFirst(node** head){
    if(*head == NULL){
        cout << "List is empty, nothing to delete." << endl << endl;
        return;
    }
    node* temp = *head;
    *head = (*head)->next; 
    delete temp; 
    
    
    if(*head != NULL){
        
        if ((*head)->next == NULL) {
            (*head)->role = "president/secretary";
        } else {
            (*head)->role = "president";
        }
    }
    cout << "President deleted successfully!" << endl << endl;
}


void deleteLast(node** head){
    if(*head == NULL){
        cout << "List is empty, nothing to delete." << endl << endl;
        return;
    }
    
    
    if((*head)->next == NULL){
        delete *head;
        *head = NULL;
        cout << "The only member was deleted. The list is now empty." << endl << endl;
        return;
    }
    
    node* temp = *head;
    
    while(temp->next->next != NULL){
        temp = temp->next;
    }
    
    delete temp->next; 
    temp->next = NULL; 
    temp->role = "secretary"; 

    cout << "Secretary deleted successfully!" << endl << endl;
}

// Concatenates list 2 onto the end of list 1
void concatinateLists(node** head1, node** head2){
    if(*head1 == NULL){
        *head1 = *head2;
        *head2 = NULL; 
        cout << "List 1 was empty. It now contains List 2." << endl << endl;
        return;
    }
    if (*head2 == NULL) {
        cout << "List 2 is empty. Nothing to concatenate." << endl << endl;
        return;
    }

    node* temp = *head1;
    while(temp->next != NULL){
        temp = temp->next;
    }
    
    temp->next = *head2;
    *head2 = NULL;

    cout << "Lists concatenated successfully! The combined list is in List 1." << endl << endl;
}

node* reverseList(node* temp) {
    node* rev = temp;
    if(temp->next!=NULL){
        rev = insertLast(reverseList(temp->next),temp);
    }
    return rev;
}

void printReverse(node* temp){
    if(temp->next!=NULL){
        printReverse(temp->next);
    }
    cout<<"Name : "<<temp->name<<", Role : "<<temp->role<<", PRN"<<temp->PRN<<endl;
}

void searchByPRN(node* head, long int prn) {
    if (head == NULL) {
        cout << "List is empty, cannot search." << endl << endl;
        return;
    }
    node* temp = head;
    int position = 1;
    while (temp != NULL) {
        if (temp->PRN == prn) {
            cout << "Member Found at position " << position << "!" << endl;
            cout << "   PRN: " << temp->PRN << ", Name: " << temp->name << ", Role: " << temp->role << endl << endl;
            return; // Exit the function once the member is found.
        }
        temp = temp->next;
        position++;
    }
    cout << "Member with PRN " << prn << " not found in the list." << endl << endl;
}

void sortByPRN(node** head) {
    // // Cannot sort a list with 0 or 1 members.
    // if (*head == NULL || (*head)->next == NULL) {
    //     cout << "List is too short to sort." << endl << endl;
    //     return;
    // }

    // node *i, *j;
    // long int tempPRN;
    // string tempName;

    // // Using bubble sort to swap data between nodes for simplicity.
    // for (i = *head; i->next != NULL; i = i->next) {
    //     for (j = i->next; j != NULL; j = j->next) {
    //         if (i->PRN > j->PRN) {
    //             // Swap PRN
    //             tempPRN = i->PRN;
    //             i->PRN = j->PRN;
    //             j->PRN = tempPRN;
    //             // Swap Name
    //             tempName = i->name;
    //             i->name = j->name;
    //             j->name = tempName;
    //         }
    //     }
    // }
    
    // // --- Re-assign roles after sorting ---
    // node* temp = *head;
    // temp->role = "president"; // The member with the lowest PRN is now president.

    // // Traverse to the end of the list.
    // while (temp->next != NULL) {
    //     if(temp != *head) temp->role = "member";
    //     temp = temp->next;
    // }
    // // The member with the highest PRN is now secretary.
    // temp->role = "secretary";

    // cout << "List sorted successfully by PRN!" << endl << endl;
}

int main(){
    int ch = 0;
    node* head1 = NULL;
    node* head2 = NULL;
    node** currentList = &head1; 
    // node* temp;
    
    string name;
    long int prn;
    
    while(ch != 99){
        cout << "------------------------------------------" << endl;
        cout << "Current working list: " << ((currentList == &head1) ? "List 1" : "List 2") << endl;
        cout << "Menu:" << endl;
        cout << "1. Add a new President (at beginning)" << endl;
        cout << "2. Add a new Secretary (at end)" << endl;
        cout << "3. Delete President" << endl;
        cout << "4. Delete Secretary" << endl;
        cout << "5. Display all members" << endl;
        cout << "6. Count total members" << endl;
        cout << "7. Reverse list" << endl;
        cout << "8. Print Reverse list" << endl;
        cout << "9. Concatenate List 2 to List 1" << endl;
        cout << "10. Switch between List 1 and List 2" << endl;
        cout << "11. Exit" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        cout << endl;
        
        switch(ch){
            case 1:
                cout << "Enter name of the new President: ";
                cin >> name;
                cout << "Enter PRN of the student: ";
                cin >> prn;
                insertFirst(currentList, name, prn); 
                break;
            case 2:
                cout << "Enter name of the new Secretary: ";
                cin >> name;
                cout << "Enter PRN of the student: ";
                cin >> prn;
                insertLast(currentList, name, prn); 
                break;
            case 3:
                deleteFirst(currentList);
                break;
            case 4:
                deleteLast(currentList);
                break;
            case 5:
                displayList(*currentList); 
                break;
            case 6:
                countMembers(*currentList);
                break;
            case 7:
                head2 = reverseList(*currentList);
                break;
            case 8:
                printReverse(*currentList);
                break;
            case 9:
                concatinateLists(&head1, &head2);
                currentList = &head1; 
                break;
            case 10:
                if (currentList == &head1) {
                    currentList = &head2;
                    cout << "Switched. Now working on List 2." << endl << endl;
                } else {
                    currentList = &head1;
                    cout << "Switched. Now working on List 1." << endl << endl;
                }
                break;
            case 11:
                ch = 99;
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl << endl;
                break;
        }
    }
    return 0; 
}