#include <iostream>
#include <iomanip> // For std::setw

using namespace std;

int** createMatrix(int n) {
    int** mat = new int*[n];
    for (int i = 0; i < n; ++i) {
        mat[i] = new int[n](); 
    }
    return mat;
}


void deleteMatrix(int** mat, int n) {
    if (mat) {
        for (int i = 0; i < n; ++i) {
            delete[] mat[i];
        }
        delete[] mat;
    }
}

void printMatrix(int** mat, int n) {
    int width = to_string(n * n).length() + 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(width) << mat[i][j];
        }
        cout << endl;
    }
}

int** constructOddMagicSquare(int n) {
    int** mat = createMatrix(n);

    int i = 0;
    int j = n / 2;

    for (int k = 1; k <= n * n; ++k) {
        mat[i][j] = k;
        int next_i = (i - 1 + n) % n; 
        int next_j = (j + 1) % n;    

        if (mat[next_i][next_j] != 0) {
            i = (i + 1) % n;
        } else {
            i = next_i;
            j = next_j;
        }
    }
    return mat;
}

int** constructDoublyEvenMagicSquare(int n) {
    int** mat = createMatrix(n);
    int k = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mat[i][j] = k++;
        }
    }
    int complement = n * n + 1;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int k_block = n / 4;
            bool in_swap_region = (i < k_block || i >= n - k_block) && (j < k_block || j >= n - k_block);
            bool in_center_region = i >= k_block && i < n - k_block && j >= k_block && j < n - k_block;
            if (in_swap_region || in_center_region) {
                mat[i][j] = complement - mat[i][j];
            }
        }
    }
    return mat;
}

bool verifyMagicSquare(int** mat, int n) {
    if (!mat || n <= 0) return false;

    int expected_sum = n * (n * n + 1) / 2;
    cout << "Expected Magic Constant (M): " << expected_sum << endl;

    for (int i = 0; i < n; ++i) {
        long long row_sum = 0; 
        long long col_sum = 0;
        for (int j = 0; j < n; ++j) {
            row_sum += mat[i][j];
            col_sum += mat[j][i];
        }
        if (row_sum != expected_sum) {
            cout << "Verification failed: Row " << i << " sum (" << row_sum << ") failed." << endl;
            return false;
        }
        if (col_sum != expected_sum) {
            cout << "Verification failed: Column " << i << " sum (" << col_sum << ") failed." << endl;
            return false;
        }
    }
    long long diag1_sum = 0;
    for (int i = 0; i < n; ++i) {
        diag1_sum += mat[i][i];
    }
    if (diag1_sum != expected_sum) {
        cout << "Verification failed: Main Diagonal sum (" << diag1_sum << ") failed." << endl;
        return false;
    }
    long long diag2_sum = 0;
    for (int i = 0; i < n; ++i) {
        diag2_sum += mat[i][n - 1 - i];
    }
    if (diag2_sum != expected_sum) {
        cout << "Verification failed: Anti-Diagonal sum (" << diag2_sum << ") failed." << endl;
        return false;
    }
    return true;
}

int main() {
    int n;
    cout << "Enter the order (n) of the magic square (n >= 3): ";
    cin >> n;

    if (n < 3) {
        cout << "Magic square order must be 3 or greater." << endl;
        return 1;
    }
    if (n % 2 == 0 && n % 4 != 0) {
        cout << "\nSingly-Even order (" << n << ") is a complex case." << endl;
        cout << "The program is designed for Odd (3, 5, 7, ...) and Doubly-Even (4, 8, 12, ...) orders." << endl;
        return 1;
    }
    if (n == 2) {
        cout << "\nA magic square of order 2 is impossible." << endl;
        return 1;
    }
    int** magic_square = nullptr;
    if (n % 2 != 0) {
        cout << "\n--- Constructing Odd-Order Magic Square (Siamese Method) ---" << endl;
        magic_square = constructOddMagicSquare(n);
    } else if (n % 4 == 0) {
        cout << "\n--- Constructing Doubly-Even Magic Square (Continuous Method) ---" << endl;
        magic_square = constructDoublyEvenMagicSquare(n);
    } 
    if (magic_square) {
        cout << "\nConstructed Magic Square of Order " << n << ":" << endl;
        printMatrix(magic_square, n);

        cout << "\n--- Verification ---" << endl;
        if (verifyMagicSquare(magic_square, n)) {
            int magic_constant = n * (n * n + 1) / 2;
            cout << "Verification Succeeded! The Magic Constant (M) is: " << magic_constant << endl;
        } else {
            cout << "Verification Failed." << endl;
        }
        deleteMatrix(magic_square, n);
    }

    return 0;
}