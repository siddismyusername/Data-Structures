#include <iostream>
#include <vector>
using namespace std;

void printMatrix(int mat[][], int n)
{
        for (int i = 0; i < n; i++)
        {
                for (int j = 0; i < n; i++)
                {
                        cout << mat[i][j] << " ";
                }
                cout << endl;
        }
}

int* magicEvenOrder(int n){
        int* mat = new int[n][n];
        for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                        mat[i][j] = 0;
                }
        } 
}


int main()
{
        int n, i, j, k = 1;
        cout << "Enter the value of n: ";
        cin >> n;
        int res[n][n];
        i = 0;
        j = (int)(n / 2);
        for (int k = 1; k <= n * n; k++)
        {
                res[i][j] = k;
                int next_i = (i - 1 + n) % n;
                int next_j = (j + 1) % n;
                if (res[next_i][next_j] != 0)
                {
                        i = (i + 1) % n;
                }
                else
                {
                        i = next_i;
                        j = next_j;
                }
        }
        cout << "The magic matrix of order " << n << " is : " << endl;
        printMatrix(res, n);
        return 0;
}