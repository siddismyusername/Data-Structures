#include <iostream>
#include <iomanip>

using namespace std;

struct Student
{
    string name;
    int marks;
    int rollNo;
};

void print_table_data(Student temp[], int n)
{
    cout << "+----------------"
         << "+-----------"
         << "+-----------+\n";
    cout << "| " << setw(15) << "Roll number"
         << "| " << setw(10) << "Name"
         << "| " << setw(10) << "Marks" << "|\n";
    cout << "+----------------"
         << "+-----------"
         << "+-----------+\n";
    for (int i = 0; i < n; i++)
    {
        cout << right
             << "| " << right << setw(15) << temp[i].rollNo
             << "| " << setw(10) << temp[i].name
             << "| " << right << setw(10) << temp[i].marks << "|\n";
    }
    cout << "+----------------"
         << "+-----------"
         << "+-----------+\n\n";
}

int main()
{
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student students[n];

    for (int i = 0; i < n; ++i)
    {
        cout << "Enter name of student " << i + 1 << ": ";
        cin >> students[i].name;
        cout << "Enter marks of " << students[i].name << ": ";
        cin >> students[i].marks;
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            if (students[j].marks < students[j + 1].marks)
            {
                swap(students[j], students[j + 1]);
            }
        }
        cout<<"Completed pass number " <<i<<endl;
    }

    for (int i = 0; i < n; ++i)
    {
        students[i].rollNo = i + 1;
    }

    cout << "\nFinal Roll Numbers (Topper is Roll No. 1):\n";
    // for (const auto& s : students) {
    //     cout << "Roll No. " << s.rollNo << ": " << s.name << " (Marks: " << s.marks << ")\n";
    // }

    print_table_data(students, n);

    return 0;
}