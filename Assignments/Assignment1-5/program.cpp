#include <iostream>
#include <iomanip> 


#define MAX_TERMS 100
#define MAX_COLS  50


struct Term{
    int row;
    int col;
    int value;
};



void fastTranspose(const Term A[], Term B[]) {
    // A[0] contains the metadata
    int rows = A[0].row;
    int cols = A[0].col;
    int num_non_zeros = A[0].value;

    if (num_non_zeros <= 0 || cols > MAX_COLS) {
        if (cols > MAX_COLS) {
            std::cerr << "Error: Number of columns (" << cols 
                      << ") exceeds MAX_COLS (" << MAX_COLS << ")." << std::endl;
        }
        B[0].row = cols;
        B[0].col = rows;
        B[0].value = 0;
        return;
    }

    // Set the metadata for the transposed matrix B
    B[0].row = cols;       // Original columns become new rows
    B[0].col = rows;       // Original rows become new columns
    B[0].value = num_non_zeros; // Non-zero count remains the same

    // Auxiliary arrays: using fixed-size arrays as requested
    // row_terms[i]: count of non-zero elements in column 'i' of A (which is new row 'i' of B)
    int row_terms[MAX_COLS + 1] = {0};
    // starting_pos[i]: starting index in B for the elements of new row 'i'
    int starting_pos[MAX_COLS + 1] = {0};

    // --- First Pass: Count the number of terms in each column of A ---
    for (int i = 1; i <= num_non_zeros; ++i) {
        int col_index_A = A[i].col;
        row_terms[col_index_A]++;
    }

    // --- Second Pass: Determine the starting position for each new row in B ---
    starting_pos[0] = 1; // The first non-zero element is always at index 1 in the triplet array
    for (int i = 1; i < cols; ++i) {
        // The start position of new row i is the start of new row i-1 
        // plus the count of elements in new row i-1
        starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
    }

    // --- Third Pass: Place the transposed elements into B ---
    for (int i = 1; i <= num_non_zeros; ++i) {
        int val = A[i].value;
        int row_A = A[i].row;
        int col_A = A[i].col;

        // The column of A (col_A) becomes the row of B (row_B).
        int row_B = col_A;

        // Use the starting position array to find the current placement index (j) for this row_B
        int j = starting_pos[row_B];

        // Fill the transposed triplet (col_A, row_A, val) into B[j]
        B[j].row = col_A;   // New Row
        B[j].col = row_A;   // New Column
        B[j].value = val;   // Value

        // Increment the starting position for the next element belonging to this row_B
        starting_pos[row_B]++;
    }
}




void printSparseMatrix(const Term mat[], const char* name) {
    int rows = mat[0].row;
    int cols = mat[0].col;
    int num_non_zeros = mat[0].value;

    std::cout << name << " (" << rows << "x" << cols 
              << ", " << num_non_zeros << " non-zeros):\n";
    std::cout << std::setw(3) << "Row" << " |" << std::setw(3) << "Col" 
              << " |" << std::setw(5) << "Value" << "\n";
    std::cout << "-----------------\n";

    for (int i = 1; i <= num_non_zeros; ++i) {
        std::cout << std::setw(3) << mat[i].row << " |" << std::setw(3) 
                  << mat[i].col << " |" << std::setw(5) << mat[i].value << "\n";
    }
    std::cout << "\n";
}



// --- Main Example ---
int main() {
    Term A[MAX_TERMS] = {
        {4, 6, 5},
        {0, 3, 10}, // A[0][3] = 10
        {1, 1, 20}, // A[1][1] = 20
        {1, 5, 12}, // A[1][5] = 12
        {2, 2, 30}, // A[2][2] = 30
        {3, 4, 40}  // A[3][4] = 40
    };

    // The result array B must also be a fixed-size array
    Term B[MAX_TERMS];

    printSparseMatrix(A, "Original Matrix A");

    // Perform the Fast Transpose
    fastTranspose(A, B);

    std::cout << "============================================\n";

    // Print the Transposed Matrix B (should be 6x4)
    printSparseMatrix(B, "Transposed Matrix B (Fast Transpose)");

    return 0;
}