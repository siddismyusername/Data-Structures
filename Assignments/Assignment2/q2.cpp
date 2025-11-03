#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Student {
    string name;
    int marks;
    int rollNo;
};

// Utility to print student table
void print_table_data(Student temp[], int n) {
    cout << "+----------------+-----------+-----------+\n";
    cout << "| " << setw(15) << "Roll number"
         << "| " << setw(10) << "Name"
         << "| " << setw(10) << "Marks" << "|\n";
    cout << "+----------------+-----------+-----------+\n";
    for (int i = 0; i < n; i++) {
        cout << right
             << "| " << right << setw(15) << temp[i].rollNo
             << "| " << setw(10) << temp[i].name
             << "| " << right << setw(10) << temp[i].marks << "|\n";
    }
    cout << "+----------------+-----------+-----------+\n\n";
}

// Bubble sort with swap count on rollNo
int bubbleSort(Student arr[], int n) {
    int swapCount = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j].rollNo > arr[j + 1].rollNo) {
                swap(arr[j], arr[j + 1]);
                swapCount++;
            }
        }
    }
    return swapCount;
}

// Quick Sort partition using rollNo as key, returns number of swaps
int partition(Student arr[], int low, int high, int &swapCount) {
    int pivot = arr[high].rollNo;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].rollNo < pivot) {
            i++;
            swap(arr[i], arr[j]);
            swapCount++;
        }
    }
    swap(arr[i + 1], arr[high]);
    swapCount++;
    return (i + 1);
}

void quickSort(Student arr[], int low, int high, int &swapCount) {
    if (low < high) {
        int pi = partition(arr, low, high, swapCount);
        quickSort(arr, low, pi - 1, swapCount);
        quickSort(arr, pi + 1, high, swapCount);
    }
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student students[n];

    // Input students
    for (int i = 0; i < n; ++i) {
        cout << "Enter name of student " << i + 1 << ": ";
        cin >> students[i].name;
        cout << "Enter roll number for " << students[i].name << ": ";
        cin >> students[i].rollNo;
        cout << "Enter marks of " << students[i].name << ": ";
        cin >> students[i].marks;
    }

    // Make two copies for both sorting methods
    Student bubbleArr[n], quickArr[n];
    for (int i = 0; i < n; ++i) {
        bubbleArr[i] = students[i];
        quickArr[i] = students[i];
    }

    // Bubble Sort
    int bubbleSwaps = bubbleSort(bubbleArr, n);

    // Quick Sort
    int quickSwaps = 0;
    quickSort(quickArr, 0, n - 1, quickSwaps);

    // Results
    cout << "\nBubble Sort result (sorted by rollNo):\n";
    print_table_data(bubbleArr, n);
    cout << "Number of swaps (Bubble Sort): " << bubbleSwaps << "\n\n";

    cout << "Quick Sort result (sorted by rollNo):\n";
    print_table_data(quickArr, n);
    cout << "Number of swaps (Quick Sort): " << quickSwaps << "\n\n";

    return 0;
}
