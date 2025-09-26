#include <iostream>
#include <vector>
using namespace std;

int main()
{
        int n, i, j, k = 1;
        cout << "Enter the value of n: ";
        cin >> n;
        vector<vector<int>> res(n, vector<int>(n, 0));
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
        for (i = 0; i < n; i++)
        {
                for (j = 0; j < n; j++)
                {
                        cout << res[i][j] << " ";
                }
                cout << endl;
        }
        return 0;
}