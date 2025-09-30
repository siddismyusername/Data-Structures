//matrix multiplication 
#include <iostream>
#include<iomanip>

using namespace std;

int main(){
    int n;
    cout<<"Enter the size of the matrix: ";
    cin >> n;
    int a[n][n], b[n][n], c[n][n];
    cout<<"Enter the elements of first matrix: "<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> a[i][j];
        }
    }
    cout<<"Enter the elements of second matrix: "<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> b[i][j];
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            c[i][j] = 0;
            for(int k=0; k<n; k++){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    cout<<"Resultant matrix: "<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout <<setw(3)<< c[i][j] << " ";
        }
        cout << endl;
    }
}