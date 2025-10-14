#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Employee {
    string name;
    float height;
    float weight;
};

// Function to compute average of height and weight
float getAverage(const Employee& emp) {
    return (emp.height + emp.weight) / 2.0f;
}

// Utility to print employee list
void printEmployees(const vector<Employee>& emps) {
    cout << left << setw(15) << "Name" << setw(10) << "Height" << setw(10) << "Weight" << setw(10) << "Avg" << endl;
    cout << "------------------------------------------------" << endl;
    for(const auto& e : emps) {
        cout << left << setw(15) << e.name << setw(10) << e.height << setw(10) << e.weight << setw(10) << getAverage(e) << endl;
    }
    cout << endl;
}

// ---- Selection Sort ----
void selectionSort(vector<Employee>& emps) {
    int n = emps.size();
    for(int i = 0; i < n-1; ++i) {
        int minIdx = i;
        for(int j = i+1; j < n; ++j) {
            if(getAverage(emps[j]) < getAverage(emps[minIdx])) {
                minIdx = j;
            }
        }
        if (minIdx != i) swap(emps[i], emps[minIdx]);
    }
}

// ---- Merge Sort ----
void merge(vector<Employee>& emps, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<Employee> left(n1), right(n2);
    for (int i = 0; i < n1; ++i) left[i] = emps[l + i];
    for (int j = 0; j < n2; ++j) right[j] = emps[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (getAverage(left[i]) <= getAverage(right[j])) {
            emps[k++] = left[i++];
        } else {
            emps[k++] = right[j++];
        }
    }
    while (i < n1) emps[k++] = left[i++];
    while (j < n2) emps[k++] = right[j++];
}
void mergeSort(vector<Employee>& emps, int l, int r) {
    if (l < r) {
        int m = l + (r-l)/2;
        mergeSort(emps, l, m);
        mergeSort(emps, m+1, r);
        merge(emps, l, m, r);
    }
}

int main() {
    int n;
    cout << "Enter number of employees: ";
    cin >> n;
    vector<Employee> emps(n);
    for(int i = 0; i < n; ++i) {
        cout << "Enter name: ";
        cin >> emps[i].name;
        cout << "Enter height: ";
        cin >> emps[i].height;
        cout << "Enter weight: ";
        cin >> emps[i].weight;
    }
    cout << "\nOriginal List:\n";
    printEmployees(emps);

    // Selection Sort
    vector<Employee> selSorted = emps;
    selectionSort(selSorted);
    cout << "List after Selection Sort (by avg. height and weight):\n";
    printEmployees(selSorted);

    // Merge Sort
    vector<Employee> mergeSorted = emps;
    mergeSort(mergeSorted, 0, n-1);
    cout << "List after Merge Sort (by avg. height and weight):\n";
    printEmployees(mergeSorted);

   return 0;
}
