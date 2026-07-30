#include <iostream>
using namespace std;

const int MAX = 10; // Maximum matrix size

// Function to take matrix input
void inputMatrix(int mat[MAX][MAX], int rows, int cols, string name) {
    cout << "Enter elements for Matrix " << name << " (" << rows << "x" << cols << "):" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> mat[i][j];
        }
    }
}

// Function to print a matrix
void printMatrix(int mat[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}

// Function for Matrix Addition
void addMatrices(int A[MAX][MAX], int B[MAX][MAX], int rows, int cols) {
    int C[MAX][MAX];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    cout << "\nResult of Addition (A + B):" << endl;
    printMatrix(C, rows, cols);
}

// Function for Matrix Subtraction
void subtractMatrices(int A[MAX][MAX], int B[MAX][MAX], int rows, int cols) {
    int C[MAX][MAX];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    cout << "\nResult of Subtraction (A - B):" << endl;
    printMatrix(C, rows, cols);
}

// Function for Matrix Multiplication
void multiplyMatrices(int A[MAX][MAX], int B[MAX][MAX], int r1, int c1, int c2) {
    int C[MAX][MAX] = {0}; // Initialize result matrix with zeros
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    cout << "\nResult of Multiplication (A * B):" << endl;
    printMatrix(C, r1, c2);
}

int main() {
    int A[MAX][MAX], B[MAX][MAX];
    int r1, c1, r2, c2;
    int choice;

    do {
        cout << "\nMATRIX OPERATIONS MENU" << endl;
        cout << "1. Matrix Addition" << endl;
        cout << "2. Matrix Subtraction" << endl;
        cout << "3. Matrix Multiplication" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        if (choice >= 1 && choice <= 3) {
            cout << "\nEnter rows and columns for Matrix A: ";
            cin >> r1 >> c1;
            cout << "Enter rows and columns for Matrix B: ";
            cin >> r2 >> c2;
        }

        switch (choice) {
            case 1:
                if (r1 == r2 && c1 == c2) {
                    inputMatrix(A, r1, c1, "A");
                    inputMatrix(B, r2, c2, "B");
                    addMatrices(A, B, r1, c1);
                } else {
                    cout << "Error: Addition requires matrices of the same dimensions." << endl;
                }
                break;

            case 2:
                if (r1 == r2 && c1 == c2) {
                    inputMatrix(A, r1, c1, "A");
                    inputMatrix(B, r2, c2, "B");
                    subtractMatrices(A, B, r1, c1);
                } else {
                    cout << "Error: Subtraction requires matrices of the same dimensions." << endl;
                }
                break;

            case 3:
                if (c1 == r2) {
                    inputMatrix(A, r1, c1, "A");
                    inputMatrix(B, r2, c2, "B");
                    multiplyMatrices(A, B, r1, c1, c2);
                } else {
                    cout << "Error: Multiplication requires columns of A to match rows of B." << endl;
                }
                break;

            case 4:
                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid choice! Please select an option from 1 to 4." << endl;
        }
    } while (choice != 4);

    return 0;
}