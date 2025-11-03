#include<iostream>
using namespace std;

struct student{
    string name;
    string year;
    string div;
    int rollNo;
};

int main(){
    int n;
    cout<<"Enter number of students: ";
    cin>>n;

    student students[n+1];

    for(int i=0; i<n; i++){
        cout<<"Enter name of student "<<i+1<<": ";
        cin>>students[i].name;
        cout<<"Enter year of "<<students[i].name<<": ";
        cin>>students[i].year;
        cout<<"Enter division of "<<students[i].name<<": ";
        cin>>students[i].div;
        cout<<"Enter roll number of "<<students[i].name<<": ";
        cin>>students[i].rollNo;
        cout<<"\n";
    }
    
    students[n] = {"XYZ","SY","X",17};

    string Sname;
    string Syear;
    string Sdiv;
    int SrollNo;
    bool found = false;

    cout<<"Enter the Name of the student to be searched: ";
    cin>>Sname;
    cout<<"Enter the Year of the student to be searched: ";
    cin>>Syear;
    cout<<"Enter the Division of the student to be searched: ";
    cin>>Sdiv;
    cout<<"Enter the Roll Number of the student to be searched: ";
    cin>>SrollNo;

    for(int i=0; i<=n; i++){
        if(students[i].name==Sname && students[i].year==Syear && students[i].div==Sdiv && students[i].rollNo==SrollNo){
            cout<<"\nStudent Found!\n";
            cout<<"Name: "<<students[i].name<<"\n";
            cout<<"Year: "<<students[i].year<<"\n";
            cout<<"Division: "<<students[i].div<<"\n";
            cout<<"Roll Number: "<<students[i].rollNo<<"\n";
            found = true;
            break;
        }
    }
    if (found == false)
    {
        cout<<"\nStudent Not Found!\n";
    }
    


    
    return 0;
}