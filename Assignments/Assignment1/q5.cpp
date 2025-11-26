// Develop a program to compute the fast transpose of a sparse matrix
// using its compact (triplet) representation efficiently.

#include <iostream>
#include <iomanip>
using namespace std;

#define MAX_TERMS 100
#define MAX_COLS  50

// Forward declarations
struct Term;
void fastTranspose(const Term A[], Term B[]);
void printSparseMatrix(const Term mat[], const char* name);
void printFullMatrix(const Term mat[], const char* name);
void inputSparseMatrix(Term mat[]);
void simpleTranspose(const Term A[], Term B[]);
void demonstrateExample();

struct Term {
    int row;
    int col;
    int value;
};

// Fast Transpose Algorithm - O(n + m) where n = non-zeros, m = columns
void fastTranspose(const Term A[], Term B[]) {
    int rows = A[0].row;
    int cols = A[0].col;
    int num_non_zeros = A[0].value;

    if (num_non_zeros <= 0 || cols > MAX_COLS) {
        if (cols > MAX_COLS) {
            cerr << "Error: Number of columns (" << cols 
                 << ") exceeds MAX_COLS (" << MAX_COLS << ")." << endl;
        }
        B[0].row = cols;
        B[0].col = rows;
        B[0].value = 0;
        return;
    }

    // Set header of transpose matrix
    B[0].row = cols;       
    B[0].col = rows;       
    B[0].value = num_non_zeros; 

    int row_terms[MAX_COLS + 1] = {0};
    int starting_pos[MAX_COLS + 1] = {0};

    // Count number of elements in each column of A
    for (int i = 1; i <= num_non_zeros; ++i) {
        int col_index_A = A[i].col;
        row_terms[col_index_A]++;
    }

    // Calculate starting positions for each row in B
    starting_pos[0] = 1; 
    for (int i = 1; i < cols; ++i) {
        starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
    }

    // Place elements in B
    for (int i = 1; i <= num_non_zeros; ++i) {
        int val = A[i].value;
        int row_A = A[i].row;
        int col_A = A[i].col;

        int j = starting_pos[col_A];

        B[j].row = col_A;   
        B[j].col = row_A;   
        B[j].value = val;   

        starting_pos[col_A]++;
    }
}

// Simple Transpose Algorithm - O(cols * n) for comparison
void simpleTranspose(const Term A[], Term B[]) {
    int rows = A[0].row;
    int cols = A[0].col;
    int num_non_zeros = A[0].value;

    B[0].row = cols;
    B[0].col = rows;
    B[0].value = num_non_zeros;

    if (num_non_zeros <= 0) {
        return;
    }

    int currentB = 1;
    
    // For each column in A (becomes row in B)
    for (int col = 0; col < cols; col++) {
        for (int i = 1; i <= num_non_zeros; i++) {
            if (A[i].col == col) {
                B[currentB].row = A[i].col;
                B[currentB].col = A[i].row;
                B[currentB].value = A[i].value;
                currentB++;
            }
        }
    }
}

// Print sparse matrix in triplet form
void printSparseMatrix(const Term mat[], const char* name) {
    int rows = mat[0].row;
    int cols = mat[0].col;
    int num_non_zeros = mat[0].value;

    cout << "\n" << name << " (" << rows << "x" << cols 
         << ", " << num_non_zeros << " non-zeros):\n";
    cout << "Triplet Representation:\n";
    cout << setw(5) << "Row" << " |" << setw(5) << "Col" 
         << " |" << setw(7) << "Value" << "\n";
    cout << "------------------------\n";

    for (int i = 1; i <= num_non_zeros; ++i) {
        cout << setw(5) << mat[i].row << " |" << setw(5) 
             << mat[i].col << " |" << setw(7) << mat[i].value << "\n";
    }
    cout << "\n";
}

// Print sparse matrix in full 2D form
void printFullMatrix(const Term mat[], const char* name) {
    int rows = mat[0].row;
    int cols = mat[0].col;
    int num_non_zeros = mat[0].value;

    cout << "\n" << name << " (Full Matrix Form):\n";
    
    // Create 2D array initialized with zeros
    int** fullMatrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        fullMatrix[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            fullMatrix[i][j] = 0;
        }
    }

    // Fill non-zero values
    for (int i = 1; i <= num_non_zeros; i++) {
        fullMatrix[mat[i].row][mat[i].col] = mat[i].value;
    }

    // Print matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(5) << fullMatrix[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    // Free memory
    for (int i = 0; i < rows; i++) {
        delete[] fullMatrix[i];
    }
    delete[] fullMatrix;
}

// Input sparse matrix from user
void inputSparseMatrix(Term mat[]) {
    int rows, cols, numNonZeros;
    
    cout << "\nEnter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;
    cout << "Enter number of non-zero elements: ";
    cin >> numNonZeros;

    if (cols > MAX_COLS) {
        cout << "Error: Number of columns exceeds MAX_COLS (" << MAX_COLS << ")\n";
        mat[0].row = 0;
        mat[0].col = 0;
        mat[0].value = 0;
        return;
    }

    if (numNonZeros > MAX_TERMS - 1) {
        cout << "Error: Too many non-zero elements. Max: " << (MAX_TERMS - 1) << "\n";
        mat[0].row = 0;
        mat[0].col = 0;
        mat[0].value = 0;
        return;
    }

    mat[0].row = rows;
    mat[0].col = cols;
    mat[0].value = numNonZeros;

    cout << "\nEnter non-zero elements (row col value):\n";
    cout << "(Rows: 0 to " << (rows - 1) << ", Cols: 0 to " << (cols - 1) << ")\n";
    
    for (int i = 1; i <= numNonZeros; i++) {
        cout << "Element " << i << ": ";
        cin >> mat[i].row >> mat[i].col >> mat[i].value;

        if (mat[i].row < 0 || mat[i].row >= rows || 
            mat[i].col < 0 || mat[i].col >= cols) {
            cout << "Invalid row or column! Try again.\n";
            i--;
            continue;
        }

        if (mat[i].value == 0) {
            cout << "Warning: Zero value entered for non-zero element!\n";
        }
    }
}

// Demonstrate with example matrix
void demonstrateExample() {
    cout << "\n========== Example Demonstration ==========\n";
    cout << "Using a 4x6 sparse matrix with 5 non-zero elements\n";
    
    Term A[MAX_TERMS] = {
        {4, 6, 5},      // Header: 4 rows, 6 cols, 5 non-zeros
        {0, 3, 10},     // Element at (0,3) = 10
        {1, 1, 20},     // Element at (1,1) = 20
        {1, 5, 12},     // Element at (1,5) = 12
        {2, 2, 30},     // Element at (2,2) = 30
        {3, 4, 40}      // Element at (3,4) = 40
    };

    Term B[MAX_TERMS];

    cout << "\n--- Original Matrix ---";
    printFullMatrix(A, "Matrix A");
    printSparseMatrix(A, "Matrix A");

    cout << "--- Performing Fast Transpose ---\n";
    fastTranspose(A, B);

    cout << "--- Transposed Matrix ---";
    printFullMatrix(B, "Matrix B (Transposed)");
    printSparseMatrix(B, "Matrix B (Transposed)");
}

int main() {
    Term userMatrix[MAX_TERMS];
    Term transposed[MAX_TERMS];
    int choice;
    bool matrixEntered = false;

    cout << "================================================\n";
    cout << "  Fast Transpose of Sparse Matrix\n";
    cout << "  (Compact Triplet Representation)\n";
    cout << "================================================\n";

    do {
        cout << "\n========== Menu ==========\n";
        cout << "1. Input Sparse Matrix\n";
        cout << "2. Display Current Matrix\n";
        cout << "3. Perform Fast Transpose\n";
        cout << "4. Compare Fast vs Simple Transpose\n";
        cout << "5. Run Example Demonstration\n";
        cout << "6. Exit\n";
        cout << "==========================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                inputSparseMatrix(userMatrix);
                if (userMatrix[0].value > 0) {
                    matrixEntered = true;
                    cout << "\nMatrix entered successfully!\n";
                }
                break;

            case 2:
                if (!matrixEntered) {
                    cout << "\nNo matrix entered yet! Please input a matrix first.\n";
                } else {
                    printFullMatrix(userMatrix, "Current Matrix");
                    printSparseMatrix(userMatrix, "Current Matrix");
                }
                break;

            case 3:
                if (!matrixEntered) {
                    cout << "\nNo matrix entered yet! Please input a matrix first.\n";
                } else {
                    cout << "\n--- Performing Fast Transpose ---\n";
                    fastTranspose(userMatrix, transposed);
                    cout << "Transpose completed!\n";
                    
                    printFullMatrix(transposed, "Transposed Matrix");
                    printSparseMatrix(transposed, "Transposed Matrix");
                }
                break;

            case 4:
                if (!matrixEntered) {
                    cout << "\nNo matrix entered yet! Please input a matrix first.\n";
                } else {
                    Term fastResult[MAX_TERMS];
                    Term simpleResult[MAX_TERMS];
                    
                    cout << "\n========== Comparison ==========\n";
                    cout << "Fast Transpose: O(n + m) where n=non-zeros, m=columns\n";
                    cout << "Simple Transpose: O(cols * n)\n\n";
                    
                    fastTranspose(userMatrix, fastResult);
                    simpleTranspose(userMatrix, simpleResult);
                    
                    cout << "--- Fast Transpose Result ---";
                    printSparseMatrix(fastResult, "Fast Transpose");
                    
                    cout << "--- Simple Transpose Result ---";
                    printSparseMatrix(simpleResult, "Simple Transpose");
                    
                    cout << "Both methods produce the same result!\n";
                    cout << "Fast Transpose is more efficient for large matrices.\n";
                }
                break;

            case 5:
                demonstrateExample();
                break;

            case 6:
                cout << "\nExiting program...\n";
                cout << "Thank you!\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}