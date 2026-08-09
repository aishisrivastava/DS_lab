// Program 3: Arrange Students in Alphabetical Order (Selection Sort)

#include <stdio.h>
#include <string.h>

struct Student {
    int roll_no;
    char name[50];
    float marks;
};

void display(struct Student s[], int n) {
    printf("\nRoll No\tName\t\tMarks\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%-15s%.2f\n", s[i].roll_no, s[i].name, s[i].marks);
    }
}

void selectionSortByName(struct Student s[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            // Compare names alphabetically using strcmp
            if (strcmp(s[j].name, s[min_idx].name) < 0) {
                min_idx = j;
            }
        }
        // Swap structure elements
        if (min_idx != i) {
            struct Student temp = s[i];
            s[i] = s[min_idx];
            s[min_idx] = temp;
        }
    }
}

int main() {
    struct Student s[] = {
        {101, "David", 78.0},
        {102, "Alice", 85.5},
        {103, "Charlie", 75.5},
        {104, "Bob", 90.0}
    };
    int n = 4;

    printf("Original Student List:");
    display(s, n);

    selectionSortByName(s, n);

    printf("\nSorted Alphabetically (by Name):");
    display(s, n);

    return 0;
}