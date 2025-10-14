#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int marks;
};

// Utility to print array of students
void printStudents(Student arr[], int n) {
    for(int i=0; i<n; i++)
        cout << arr[i].name << " (" << arr[i].marks << ")  ";
    cout << endl;
}

// Partition function for quicksort on marks
int partition(Student arr[], int low, int high) {
    int pivot = arr[high].marks;
    int i = low - 1;
    for(int j = low; j <= high - 1; j++) {
        if(arr[j].marks < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

// Quicksort with pass reporting
void quickSort(Student arr[], int low, int high, int n, int &pass) {
    if(low < high) {
        int pi = partition(arr, low, high);

        cout << "After pass " << pass++ << ": ";
        printStudents(arr, n);

        quickSort(arr, low, pi - 1, n, pass);
        quickSort(arr, pi + 1, high, n, pass);
    }
}

// Divide and Conquer for Min and Max
void findMinMax(Student arr[], int low, int high, int &minV, int &maxV) {
    // Base cases
    if(low == high) {
        minV = maxV = arr[low].marks;
        return;
    }
    if(high == low + 1) {
        if(arr[low].marks < arr[high].marks) {
            minV = arr[low].marks;
            maxV = arr[high].marks;
        } else {
            minV = arr[high].marks;
            maxV = arr[low].marks;
        }
        return;
    }
    int mid = (low + high) / 2;
    int min1, max1, min2, max2;
    findMinMax(arr, low, mid, min1, max1);
    findMinMax(arr, mid + 1, high, min2, max2);
    minV = min(min1, min2);
    maxV = max(max1, max2);
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student arr[n];
    // Input each student
    for(int i = 0; i < n; ++i) {
        cout << "Enter name for student " << i+1 << ": ";
        cin >> arr[i].name;
        cout << "Enter marks for " << arr[i].name << ": ";
        cin >> arr[i].marks;
    }

    int quickPass = 1;
    quickSort(arr, 0, n-1, n, quickPass);

    cout << "Sorted list (by marks, ascending):\n";
    printStudents(arr, n);

    int minMarks, maxMarks;
    findMinMax(arr, 0, n-1, minMarks, maxMarks);
    cout << "Minimum marks: " << minMarks << endl;
    cout << "Maximum marks: " << maxMarks << endl;

    return 0;
}
