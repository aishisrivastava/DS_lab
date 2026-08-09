// Program 1: Insert a New Record into Existing Records

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
        {104, "David", 78.0}
    };
    int n = 3; // Initial count
    int pos;

    printf("Initial Student List:");
    display(s, n);

    printf("\nEnter position to insert (1 to %d): ", n + 1);
    scanf("%d", &pos);

    // Shift elements to the right to make space
    for (int i = n; i >= pos; i--) {
        s[i] = s[i - 1];
    }

    // Insert new student details at (pos - 1)
    printf("Enter Roll No: ");
    scanf("%d", &s[pos - 1].roll_no);
    printf("Enter Name: ");
    scanf(" %[^\n]", s[pos - 1].name);
    printf("Enter Marks: ");
    scanf("%f", &s[pos - 1].marks);

    n++; // Increment total record count

    printf("\nUpdated Student List:");
    display(s, n);

    return 0;
}