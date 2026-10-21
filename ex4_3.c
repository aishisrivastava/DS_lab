#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int regNo;
    char name[50];
    char department[30];
    int year;
    char email[50];
    char mobile[15];
    struct Student* next;
};

void insertEnd(struct Student** head, int regNo, char* name, char* dept, int year, char* email, char* mobile) {
    struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
    newNode->regNo = regNo;
    strcpy(newNode->name, name);
    strcpy(newNode->department, dept);
    newNode->year = year;
    strcpy(newNode->email, email);
    strcpy(newNode->mobile, mobile);
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Student* temp = *head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }
}

void searchStudent(struct Student* head, int regNo) {
    struct Student* temp = head;
    while (temp != NULL) {
        if (temp->regNo == regNo) {
            printf("\n--- Student Found ---\n");
            printf("RegNo     : %d\n", temp->regNo);
            printf("Name      : %s\n", temp->name);
            printf("Department: %s\n", temp->department);
            printf("Year      : %d\n", temp->year);
            printf("Email     : %s\n", temp->email);
            printf("Mobile    : %s\n", temp->mobile);
            return;
        }
        temp = temp->next;
    }
    printf("Student with Registration Number %d not found[cite: 3].\n", regNo);
}

int main() {
    struct Student* head = NULL;
    insertEnd(&head, 101, "Alice Smith", "CSE", 3, "alice@mail.com", "9876543210");
    insertEnd(&head, 102, "Bob Jones", "IT", 2, "bob@mail.com", "9988776655");

    searchStudent(head, 102);[cite: 3]
    searchStudent(head, 999);[cite: 3]
    return 0;
}