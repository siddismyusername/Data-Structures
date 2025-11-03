// Set operations with linked lists
// Problem: Two groups of students based on favorite sports
// - Set A: like Cricket
// - Set B: like Football
// Implement operations using singly linked lists:
// a) Students who like BOTH (A intersection B)
// b) Students who like EITHER but NOT BOTH (A symmetric difference B)
// c) Count students who like NEITHER (universe minus (A union B))

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
	int roll;
	Node* next;
};

// Forward declarations
bool contains(Node* head, int roll);
void insertUnique(Node*& head, int roll);
bool removeNode(Node*& head, int roll);
void displayList(Node* head, const char* label);
int size(Node* head);
Node* intersectionSet(Node* A, Node* B);
Node* unionSet(Node* A, Node* B);
Node* symmetricDifferenceSet(Node* A, Node* B);
int countNeither(int totalStudents, Node* A, Node* B);
void clearList(Node*& head);
void generateRandomSets(Node*& A, Node*& B, int totalStudents, int probA = 50, int probB = 50);

// Check if value exists in list
bool contains(Node* head, int roll) {
	for (Node* cur = head; cur != nullptr; cur = cur->next) {
		if (cur->roll == roll) return true;
	}
	return false;
}

// Insert value only if not already present
void insertUnique(Node*& head, int roll) {
	if (contains(head, roll)) return;
	Node* n = new Node{roll, head};
	head = n;
}

// Remove a node by roll; returns true if removed
bool removeNode(Node*& head, int roll) {
	Node* prev = nullptr;
	Node* cur = head;
	while (cur) {
		if (cur->roll == roll) {
			if (prev) prev->next = cur->next; else head = cur->next;
			delete cur;
			return true;
		}
		prev = cur;
		cur = cur->next;
	}
	return false;
}

// Display list contents
void displayList(Node* head, const char* label) {
	cout << label << " = { ";
	bool first = true;
	for (Node* cur = head; cur != nullptr; cur = cur->next) {
		if (!first) cout << ", ";
		cout << cur->roll;
		first = false;
	}
	cout << " }\n";
}

// Count nodes
int size(Node* head) {
	int cnt = 0;
	for (Node* cur = head; cur != nullptr; cur = cur->next) cnt++;
	return cnt;
}

// Intersection (A intersection B)
Node* intersectionSet(Node* A, Node* B) {
	Node* R = nullptr;
	for (Node* cur = A; cur != nullptr; cur = cur->next) {
		if (contains(B, cur->roll)) insertUnique(R, cur->roll);
	}
	return R;
}

// Union (A union B)
Node* unionSet(Node* A, Node* B) {
	Node* R = nullptr;
	for (Node* cur = A; cur != nullptr; cur = cur->next) insertUnique(R, cur->roll);
	for (Node* cur = B; cur != nullptr; cur = cur->next) insertUnique(R, cur->roll);
	return R;
}

// Symmetric difference (either but not both)
Node* symmetricDifferenceSet(Node* A, Node* B) {
	Node* R = nullptr;
	for (Node* cur = A; cur != nullptr; cur = cur->next) {
		if (!contains(B, cur->roll)) insertUnique(R, cur->roll);
	}
	for (Node* cur = B; cur != nullptr; cur = cur->next) {
		if (!contains(A, cur->roll)) insertUnique(R, cur->roll);
	}
	return R;
}

// Count students who like neither = total - size(A union B)
int countNeither(int totalStudents, Node* A, Node* B) {
	Node* U = unionSet(A, B);
	int neither = totalStudents - size(U);
	clearList(U);
	if (neither < 0) neither = 0; // safety
	return neither;
}

// Free all nodes
void clearList(Node*& head) {
	while (head) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}

// Randomly populate A and B from universe 1..totalStudents
// probA/probB are percentage probabilities to include a student in each set
void generateRandomSets(Node*& A, Node*& B, int totalStudents, int probA, int probB) {
	clearList(A);
	clearList(B);
	for (int roll = 1; roll <= totalStudents; ++roll) {
		if (rand() % 100 < probA) insertUnique(A, roll);
		if (rand() % 100 < probB) insertUnique(B, roll);
	}
}

int main() {
	srand((unsigned)time(nullptr));

	cout << "================= Sports Preference (Sets using Linked Lists) =================\n";
	cout << "Set A: Cricket | Set B: Football\n";
	cout << "Operations: A intersection B, A symmetric difference B, count neither (U - (A union B))\n";

	int totalStudents;
	cout << "\nEnter total number of students in class (universe U): ";
	cin >> totalStudents;
	if (totalStudents <= 0) {
		cout << "Total students must be positive. Exiting.\n";
		return 0;
	}

	Node* A = nullptr; // Cricket
	Node* B = nullptr; // Football

	// Initialize with a random distribution to start
	generateRandomSets(A, B, totalStudents, /*probA*/50, /*probB*/50);

	int choice;
	do {
		cout << "\n======================= Menu =======================\n";
		cout << "1. Show students who like BOTH (A intersection B)\n";
		cout << "2. Show students who like EITHER but NOT BOTH (A symmetric difference B)\n";
		cout << "3. Show COUNT of students who like NEITHER\n";
		cout << "4. Exit\n";
		cout << "===================================================\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
			case 1: {
				Node* I = intersectionSet(A, B);
				displayList(I, "A intersection B (Both Cricket & Football)");
				cout << "Count: " << size(I) << "\n";
				clearList(I);
				break;
			}
			case 2: {
				Node* SD = symmetricDifferenceSet(A, B);
				displayList(SD, "A symmetric difference B (Either but not both)");
				cout << "Count: " << size(SD) << "\n";
				clearList(SD);
				break;
			}
			case 3: {
				int neither = countNeither(totalStudents, A, B);
				cout << "Students who like NEITHER: " << neither << "\n";
				break;
			}
			case 4:
				cout << "Exiting...\n";
				break;
			default:
				cout << "Invalid choice. Try again.\n";
		}
	} while (choice != 4);

	clearList(A);
	clearList(B);
	return 0;
}

