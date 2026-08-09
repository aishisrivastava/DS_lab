#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

// Define Student structure
struct Student {
    int roll_no;
    char name[50];
    float marks;
};


void displayStudents(struct Student s[], int n);
int linearSearch(struct Student s[], int n, int target);
int binarySearch(struct Student s[], int n, int target);
void insertionSort(struct Student s[], int n);
void selectionSort(struct Student s[], int n);
void shellSort(struct Student s[], int n);

int main() {
    struct Student s[MAX_STUDENTS];
    int n = 0, choice, roll, index, isSorted = 0;

    while (1) {
        
        printf("\nSTUDENT DATABASE MENU");
        printf("\n1. Add Student Records");
        printf("\n2. Display Student Records");
        printf("\n3. Linear Search (by Roll No)");
        printf("\n4. Binary Search (by Roll No)");
        printf("\n5. Insertion Sort (by Roll No)");
        printf("\n6. Selection Sort (by Roll No)");
        printf("\n7. Shell Sort (by Roll No)");
        printf("\n8. Exit");
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                printf("Enter number of students to add: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("\n--- Student %d ---\n", i + 1);
                    printf("Enter Roll Number: ");
                    scanf("%d", &s[i].roll_no);
                    printf("Enter Name: ");
                    scanf(" %[^\n]", s[i].name); // Reads full line including spaces
                    printf("Enter Marks: ");
                    scanf("%f", &s[i].marks);
                }
                isSorted = 0; // Reset sorted state when new items are added
                break;

            case 2:
                displayStudents(s, n);
                break;

            case 3:
                if (n == 0) {
                    printf("Database is empty!\n");
                    break;
                }
                printf("Enter Roll Number to search: ");
                scanf("%d", &roll);
                index = linearSearch(s, n, roll);
                if (index != -1) {
                    printf("\n[Linear Search] Student Found at Index %d:\n", index);
                    printf("Roll No: %d | Name: %s | Marks: %.2f\n", s[index].roll_no, s[index].name, s[index].marks);
                } else {
                    printf("\nStudent with Roll No %d not found.\n", roll);
                }
                break;

            case 4:
                if (n == 0) {
                    printf("Database is empty!\n");
                    break;
                }
                if (!isSorted) {
                    printf("\n[Warning] Database must be sorted by Roll No before applying Binary Search.");
                    printf("\nSorting automatically using Shell Sort...\n");
                    shellSort(s, n);
                    isSorted = 1;
                }
                printf("Enter Roll Number to search: ");
                scanf("%d", &roll);
                index = binarySearch(s, n, roll);
                if (index != -1) {
                    printf("\n[Binary Search] Student Found at Index %d:\n", index);
                    printf("Roll No: %d | Name: %s | Marks: %.2f\n", s[index].roll_no, s[index].name, s[index].marks);
                } else {
                    printf("\nStudent with Roll No %d not found.\n", roll);
                }
                break;

            case 5:
                if (n == 0) {
                    printf("Database is empty!\n");
                    break;
                }
                insertionSort(s, n);
                isSorted = 1;
                printf("\nDatabase sorted successfully using Insertion Sort.\n");
                displayStudents(s, n);
                break;

            case 6:
                if (n == 0) {
                    printf("Database is empty!\n");
                    break;
                }
                selectionSort(s, n);
                isSorted = 1;
                printf("\nDatabase sorted successfully using Selection Sort.\n");
                displayStudents(s, n);
                break;

            case 7:
                if (n == 0) {
                    printf("Database is empty!\n");
                    break;
                }
                shellSort(s, n);
                isSorted = 1;
                printf("\nDatabase sorted successfully using Shell Sort.\n");
                displayStudents(s, n);
                break;

            case 8:
                printf("\nExiting program...\n");
                return 0;

            default:
                printf("\nInvalid choice! Please enter a number between 1 and 8.\n");
        }
    }
    return 0;
}

// Display all student records
void displayStudents(struct Student s[], int n) {
    if (n == 0) {
        printf("\nDatabase is empty!\n");
        return;
    }
    printf("Roll No", "Name", "Marks");
    
    for (int i = 0; i < n; i++) {
        printf(s[i].roll_no, s[i].name, s[i].marks);
    }
}

// Linear Search: Time Complexity O(N)
int linearSearch(struct Student s[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (s[i].roll_no == target) {
            return i;
        }
    }
    return -1;
}

// Binary Search: Time Complexity O(log N) - Requires array to be sorted
int binarySearch(struct Student s[], int n, int target) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (s[mid].roll_no == target)
            return mid;
        else if (s[mid].roll_no < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// Insertion Sort: Time Complexity O(N^2)
void insertionSort(struct Student s[], int n) {
    for (int i = 1; i < n; i++) {
        struct Student key = s[i];
        int j = i - 1;

        while (j >= 0 && s[j].roll_no > key.roll_no) {
            s[j + 1] = s[j];
            j = j - 1;
        }
        s[j + 1] = key;
    }
}

// Selection Sort: Time Complexity O(N^2)
void selectionSort(struct Student s[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (s[j].roll_no < s[min_idx].roll_no) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            struct Student temp = s[i];
            s[i] = s[min_idx];
            s[min_idx] = temp;
        }
    }
}

// Shell Sort: Time Complexity O(N^1.25) to O(N^1.5) on average
void shellSort(struct Student s[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            struct Student temp = s[i];
            int j;
            for (j = i; j >= gap && s[j - gap].roll_no > temp.roll_no; j -= gap) {
                s[j] = s[j - gap];
            }
            s[j] = temp;
        }
    }
}