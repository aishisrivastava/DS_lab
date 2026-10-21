#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a student node
struct Node {
    int regNo;
    char name[50];
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int regNo, char* name) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->regNo = regNo;
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

// a) Add a Student (at the end of the list)
void addStudent(struct Node** head, int regNo, char* name) {
    struct Node* newNode = createNode(regNo, name);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Student %s (RegNo: %d) added successfully.\n", name, regNo);
}

// b) Remove a Student by Registration Number
void removeStudent(struct Node** head, int regNo) {
    if (*head == NULL) {
        printf("The registration list is empty.\n");
        return;
    }

    struct Node* temp = *head;
    struct Node* prev = NULL;

    // If the node to be deleted is the head node
    if (temp != NULL && temp->regNo == regNo) {
        *head = temp->next;
        printf("Student with RegNo %d removed successfully.\n", regNo);
        free(temp);
        return;
    }

    // Search for the node to be deleted
    while (temp != NULL && temp->regNo != regNo) {
        prev = temp;
        temp = temp->next;
    }

    // If the student was not found
    if (temp == NULL) {
        printf("Student with RegNo %d not found in the list.\n", regNo);
        return;
    }

    // Unlink the node from the linked list
    prev->next = temp->next;
    printf("Student with RegNo %d removed successfully.\n", regNo);
    free(temp);
}

// c) Display the List
void displayList(struct Node* head) {
    if (head == NULL) {
        printf("The workshop registration list is empty.\n");
        return;
    }

    printf("\n--- Workshop Registration List ---\n");
    printf("%-15s | %-20s\n", "Registration No", "Student Name");
    printf("----------------------------------\n");
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%-15d | %-20s\n", temp->regNo, temp->name);
        temp = temp->next;
    }
    printf("----------------------------------\n");
}

// d) Count Total Participants
int countParticipants(struct Node* head) {
    int count = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// e) Sort List by Registration Number (using data swapping)
void sortList(struct Node* head) {
    if (head == NULL || head->next == NULL) {
        printf("List has 0 or 1 element, already sorted.\n");
        return;
    }

    int swapped;
    struct Node* ptr1;
    struct Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->regNo > ptr1->next->regNo) {
                // Swap registration numbers
                int tempReg = ptr1->regNo;
                ptr1->regNo = ptr1->next->regNo;
                ptr1->next->regNo = tempReg;

                // Swap names
                char tempName[50];
                strcpy(tempName, ptr1->name);
                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->next->name, tempName);

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    printf("Registration list sorted successfully by Registration Number!\n");
}

// f) Reverse the List
void reverseList(struct Node** head) {
    struct Node* prev = NULL;
    struct Node* current = *head;
    struct Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
    printf("Registration list reversed successfully!\n");
}

int main() {
    struct Node* head = NULL;
    int choice, regNo;
    char name[50];

    do {
        printf("\n=== Workshop Enrollment System Menu ===\n");
        printf("1. Add a Student\n");
        printf("2. Remove a Student\n");
        printf("3. Display the List\n");
        printf("4. Count Total Participants\n");
        printf("5. Sort List by RegNo\n");
        printf("6. Reverse the List\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Registration Number: ");
                scanf("%d", &regNo);
                printf("Enter Student Name: ");
                scanf("%s", name);
                addStudent(&head, regNo, name);
                break;
            case 2:
                printf("Enter Registration Number to remove: ");
                scanf("%d", &regNo);
                removeStudent(&head, regNo);
                break;
            case 3:
                displayList(head);
                break;
            case 4:
                printf("Total Participants registered: %d\n", countParticipants(head));
                break;
            case 5:
                sortList(head);
                displayList(head);
                break;
            case 6:
                reverseList(&head);
                displayList(head);
                break;
            case 7:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}