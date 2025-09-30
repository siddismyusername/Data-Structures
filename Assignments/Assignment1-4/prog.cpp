// identify and efficiently store sparse matrix using compact representation
// and perform basic operations like display and simple transpose.
#include <iostream>
#include <algorithm> 

using namespace std;

// Function to display a standard 2D matrix
void displayMatrix(int **arr, int rows, int cols)
{
    cout << "Full Matrix:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int** convertToCompact(int **arr, int rows, int cols, int zeroCount, int& nonZeroCount)
{
    if (zeroCount <= (rows * cols) / 2)
    {
        cout << "Error: The provided matrix is not a sparse matrix." << endl;
        return nullptr;
    }

    nonZeroCount = rows * cols - zeroCount;
    int **compact = new int *[nonZeroCount];
    for (int i = 0; i < nonZeroCount; i++)
    {
        compact[i] = new int[3];
    }

    int k = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (arr[i][j] != 0)
            {
                compact[k][0] = i;       
                compact[k][1] = j;        
                compact[k][2] = arr[i][j]; 
                k++;
            }
        }
    }
    return compact;
}

void displayCompact(int **arr, int rows)
{
    if (arr == nullptr) {
        cout << "No compact matrix to display." << endl;
        return;
    }
    cout << "Compact Representation:" << endl;
    cout << "Row\tCol\tValue" << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << arr[i][0] << "\t" << arr[i][1] << "\t" << arr[i][2] << endl;
    }
}

void transposeCompact(int **arr, int rows) {
    if (arr == nullptr) {
        cout << "No compact matrix to transpose." << endl;
        return;
    }
    for (int i = 0; i < rows; i++) {
        swap(arr[i][0], arr[i][1]);
    }
    cout << "Compact matrix has been transposed." << endl;
}


int getMatrix(int **&mat, int rows, int cols)
{
    int z = 0;
    cout << "Enter matrix elements (" << rows << "x" << cols << "): " << endl;
    for (int i = 0; i < rows; i++)
    {
        mat[i] = new int[cols];
        for (int j = 0; j < cols; j++)
        {
            cin >> mat[i][j];
            if (mat[i][j] == 0)
                z++;
        }
    }
    return z;
}

void deleteMatrix(int**& mat, int rows) {
    if (mat != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete[] mat[i];
        }
        delete[] mat;
        mat = nullptr;
    }
}


int main()
{
    int rows, cols;
    cout << "Enter number of rows and columns: ";
    cin >> rows >> cols;

    int **matrix = new int *[rows];
    int **compactMatrix = nullptr;
    int zeroCount = 0, nonZeroCount = 0, choice = 0;

    zeroCount = getMatrix(matrix, rows, cols);

    while (choice != 5)
    {
        cout << "\n--- Sparse Matrix Menu ---" << endl;
        cout << "1. Display Original Matrix" << endl;
        cout << "2. Generate and Display Compact Representation" << endl;
        cout << "3. Transpose Compact Matrix" << endl;
        cout << "4. Re-enter matrix" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
            displayMatrix(matrix, rows, cols);
            break;
        case 2:
            deleteMatrix(compactMatrix, nonZeroCount);
            compactMatrix = convertToCompact(matrix, rows, cols, zeroCount, nonZeroCount);
            if (compactMatrix != nullptr) {
                 displayCompact(compactMatrix, nonZeroCount);
            }
            break;
        case 3:
            transposeCompact(compactMatrix, nonZeroCount);
            displayCompact(compactMatrix, nonZeroCount);
            break;
        case 4:
            deleteMatrix(matrix, rows);
            deleteMatrix(compactMatrix, nonZeroCount);

            cout << "Enter new number of rows and columns: ";
            cin >> rows >> cols;
            matrix = new int *[rows];
            zeroCount = getMatrix(matrix, rows, cols);
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    deleteMatrix(matrix, rows);
    deleteMatrix(compactMatrix, nonZeroCount);

    return 0;
}