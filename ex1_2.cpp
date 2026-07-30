#include <iostream>
using namespace std;

const int ROWS = 4;
const int COLS = 4;
const int MAX_TERMS = 100; 

// Structure to hold a single non-zero element
struct SparseElement {
    int row;
    int col;
    int value;
};

// Structure to hold the entire compact matrix
struct CompactMatrix {
    int rows;
    int cols;
    int nonZeroCount;
    SparseElement data[MAX_TERMS];
};

// Function 1: Convert a 2D sparse matrix to a Compact Matrix
CompactMatrix convertToCompact(int sparse[ROWS][COLS]) {
    CompactMatrix compact;
    compact.rows = ROWS;
    compact.cols = COLS;
    compact.nonZeroCount = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (sparse[i][j] != 0) {
                compact.data[compact.nonZeroCount].row = i;
                compact.data[compact.nonZeroCount].col = j;
                compact.data[compact.nonZeroCount].value = sparse[i][j];
                compact.nonZeroCount++;
            }
        }
    }
    return compact;
}

// Function 2: Add two compact matrices
CompactMatrix addCompactMatrices(CompactMatrix A, CompactMatrix B) {
    CompactMatrix result;
    result.rows = A.rows;
    result.cols = A.cols;
    result.nonZeroCount = 0;

    int i = 0, j = 0, k = 0;

    // Traverse both compact matrices
    while (i < A.nonZeroCount && j < B.nonZeroCount) {
        
        // If element in A comes before element in B
        if (A.data[i].row < B.data[j].row || 
           (A.data[i].row == B.data[j].row && A.data[i].col < B.data[j].col)) {
            result.data[k++] = A.data[i++];
        } 
        // If element in B comes before element in A
        else if (A.data[i].row > B.data[j].row || 
                (A.data[i].row == B.data[j].row && A.data[i].col > B.data[j].col)) {
            result.data[k++] = B.data[j++];
        } 
        // If row and col are the exact same, add their values
        else {
            int sum = A.data[i].value + B.data[j].value;
            // Only store if the sum is not zero
            if (sum != 0) {
                result.data[k].row = A.data[i].row;
                result.data[k].col = A.data[i].col;
                result.data[k].value = sum;
                k++;
            }
            i++;
            j++;
        }
    }

    // Insert any remaining elements from Matrix A
    while (i < A.nonZeroCount) {
        result.data[k++] = A.data[i++];
    }

    // Insert any remaining elements from Matrix B
    while (j < B.nonZeroCount) {
        result.data[k++] = B.data[j++];
    }

    result.nonZeroCount = k;
    return result;
}

// Function 3: Print a compact matrix
void printCompact(CompactMatrix M, string name) {
    cout << name << " (Row, Col, Value):" << endl;
    cout << "Row\tCol\tValue" << endl;
    cout << "----------------------" << endl;
    for (int i = 0; i < M.nonZeroCount; i++) {
        cout << M.data[i].row << "\t" << M.data[i].col << "\t" << M.data[i].value << endl;
    }
    cout << endl;
}

int main() {
    // 1. Define two 4x4 sparse matrices
    int sparse1[ROWS][COLS] = {
        {0, 5, 0, 0},
        {0, 0, 3, 0},
        {4, 0, 0, 0},
        {0, 0, 0, 8}
    };

    int sparse2[ROWS][COLS] = {
        {0, 2, 0, 0},
        {0, 0, 0, 7},
        {1, 0, 0, 0},
        {0, 0, 0, -8} // Note: This will cancel out the 8 in sparse1
    };

    // 2. Convert to compact form
    CompactMatrix compact1 = convertToCompact(sparse1);
    CompactMatrix compact2 = convertToCompact(sparse2);

    // 3. Print the input compact matrices
    printCompact(compact1, "Compact Matrix 1");
    printCompact(compact2, "Compact Matrix 2");

    // 4. Add the matrices
    CompactMatrix sumMatrix = addCompactMatrices(compact1, compact2);

    // 5. Print the result
    printCompact(sumMatrix, "Resulting Sum Matrix");

    return 0;
}