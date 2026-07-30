#include <stdio.h>

int main() {
   
    int sparseMatrix[4][5] = {
        {0, 0, 3, 0, 4},
        {0, 0, 5, 7, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 6, 0, 0}
    };

    int rows = 4;
    int cols = 5;
    int nonZeroCount = 0;

   
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (sparseMatrix[i][j] != 0) {
                nonZeroCount++;
            }
        }
    }

    
    int compactMatrix[nonZeroCount][3];
    int k = 0; 

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (sparseMatrix[i][j] != 0) {
                compactMatrix[k][0] = i;                 
                compactMatrix[k][1] = j;                  
                compactMatrix[k][2] = sparseMatrix[i][j];
                k++;
            }
        }
    }

   
    printf("Original Sparse Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", sparseMatrix[i][j]);
        }
        printf("\n");
    }

    
    printf("\nCompact Matrix (Row, Column, Value):\n");
    printf("Row\tCol\tValue\n");
   
    for (int i = 0; i < nonZeroCount; i++) {
        printf("%d\t%d\t%d\n", compactMatrix[i][0], compactMatrix[i][1], compactMatrix[i][2]);
    }

    return 0;
}