// Program 2: Delete a Record from Existing Records

#include <stdio.h>

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

int main() {
    struct Student s[100] = {
        {101, "Alice", 85.5},
        {102, "Bob", 90.0},
        {103, "Charlie", 75.5},
        {104, "David", 78.0}
    };
    int n = 4;
    int roll, found = -1;

    printf("Initial Student List:");
    display(s, n);

    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &roll);

    // Find the index of the student record
    for (int i = 0; i < n; i++) {
        if (s[i].roll_no == roll) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nRecord with Roll No %d not found.\n", roll);
    } else {
        // Shift elements left to overwrite the deleted record
        for (int i = found; i < n - 1; i++) {
            s[i] = s[i + 1];
        }
        n--; // Decrement total record count
        printf("\nRecord deleted successfully!\n");
        printf("Updated Student List:");
        display(s, n);
    }

    return 0;
}