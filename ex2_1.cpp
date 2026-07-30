#include <iostream>
using namespace std;

const int ROWS = 4;
const int COLS = 5;
const int MAX_TERMS = 100;

// Structure for a single non-zero element
struct SparseElement {
    int row;
    int col;
    int value;
};

// Structure for the compact matrix
struct CompactMatrix {
    int rows;
    int cols;
    int nonZeroCount;
    SparseElement data[MAX_TERMS];
};

// Function 1: Convert a 2D sparse matrix to Compact form
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

// Function 2: Simple Transpose of a Compact Matrix
CompactMatrix simpleTranspose(CompactMatrix compact) {
    CompactMatrix trans;
    // The dimensions flip: rows become cols, cols become rows
    trans.rows = compact.cols;
    trans.cols = compact.rows;
    trans.nonZeroCount = compact.nonZeroCount;

    int k = 0; // Tracks the current index in the transposed matrix

    // Iterate through all possible columns of the original matrix
    // This ensures the transposed matrix remains sorted by its new rows
    for (int c = 0; c < compact.cols; c++) {
        for (int i = 0; i < compact.nonZeroCount; i++) {
            // If the original element's column matches 'c'
            if (compact.data[i].col == c) {
                trans.data[k].row = compact.data[i].col;   // Swap row and col
                trans.data[k].col = compact.data[i].row;
                trans.data[k].value = compact.data[i].value;
                k++;
            }
        }
    }
    
    return trans;
}

// Function 3: Print a compact matrix
void printCompact(CompactMatrix M, string name) {
    cout << name << " (Dimensions: " << M.rows << "x" << M.cols << ")" << endl;
    cout << "Row\tCol\tValue" << endl;
    cout << "----------------------" << endl;
    for (int i = 0; i < M.nonZeroCount; i++) {
        cout << M.data[i].row << "\t" << M.data[i].col << "\t" << M.data[i].value << endl;
    }
    cout << endl;
}

int main() {
    // 1. Define a 4x5 sparse matrix
    int sparseMatrix[ROWS][COLS] = {
        {0, 0, 3, 0, 4},
        {0, 0, 5, 7, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 6, 0, 0}
    };

    // 2. Convert to compact matrix
    CompactMatrix compact = convertToCompact(sparseMatrix);
    printCompact(compact, "Original Compact Matrix");

    // 3. Perform Simple Transpose
    CompactMatrix transposed = simpleTranspose(compact);
    printCompact(transposed, "Transposed Compact Matrix");

    return 0;
}