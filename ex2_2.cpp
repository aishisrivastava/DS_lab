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

// Function 2: Fast Transpose of a Compact Matrix
CompactMatrix fastTranspose(CompactMatrix compact) {
    CompactMatrix trans;
    trans.rows = compact.cols;
    trans.cols = compact.rows;
    trans.nonZeroCount = compact.nonZeroCount;

    if (compact.nonZeroCount > 0) {
        // Arrays to hold the count of elements per column and their starting positions
        int rowTerms[COLS] = {0}; 
        int startingPos[COLS] = {0}; 

        // Step 1: Count the number of non-zero elements in each column of the original matrix
        for (int i = 0; i < compact.nonZeroCount; i++) {
            rowTerms[compact.data[i].col]++;
        }

        // Step 2: Calculate the starting position for each row in the transposed matrix
        startingPos[0] = 0;
        for (int i = 1; i < compact.cols; i++) {
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        }

        // Step 3: Place elements directly into their correct transposed positions
        for (int i = 0; i < compact.nonZeroCount; i++) {
            // Find where this element belongs
            int j = startingPos[compact.data[i].col]++;
            
            // Insert and swap row and col
            trans.data[j].row = compact.data[i].col;
            trans.data[j].col = compact.data[i].row;
            trans.data[j].value = compact.data[i].value;
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

    // 3. Perform Fast Transpose
    CompactMatrix transposed = fastTranspose(compact);
    printCompact(transposed, "Fast Transposed Compact Matrix");

    return 0;
}