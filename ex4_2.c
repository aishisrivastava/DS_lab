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

struct Student* createStudent(int regNo, char* name, char* dept, int year, char* email, char* mobile) {
    struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
    newNode->regNo = regNo;
    strcpy(newNode->name, name);
    strcpy(newNode->department, dept);
    newNode->year = year;
    strcpy(newNode->email, email);
    strcpy(newNode->mobile, mobile);
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(struct Student** head, int regNo, char* name, char* dept, int year, char* email, char* mobile) {
    struct Student* newNode = createStudent(regNo, name, dept, year, email, mobile);
    newNode->next = *head;
    *head = newNode;
}

void insertAtEnd(struct Student** head, int regNo, char* name, char* dept, int year, char* email, char* mobile) {
    struct Student* newNode = createStudent(regNo, name, dept, year, email, mobile);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Student* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertAtMiddle(struct Student** head, int position, int regNo, char* name, char* dept, int year, char* email, char* mobile) {
    if (position <= 1) {
        insertAtBeginning(head, regNo, name, dept, year, email, mobile);
        return;
    }
    struct Student* newNode = createStudent(regNo, name, dept, year, email, mobile);
    struct Student* temp = *head;
    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        insertAtEnd(head, regNo, name, dept, year, email, mobile);
        free(newNode);
    } else {
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void displayList(struct Student* head) {
    struct Student* temp = head;
    printf("\n--- Workshop Enrollment List ---\n");
    while (temp != NULL) {
        printf("RegNo: %d | Name: %s | Dept: %s | Year: %d | Email: %s | Mobile: %s\n", 
               temp->regNo, temp->name, temp->department, temp->year, temp->email, temp->mobile);
        temp = temp->next;
    }
    printf("-------------------------------------------\n");
}

int main() {
    struct Student* head = NULL;
    
    insertAtEnd(&head, 101, "Alice", "CSE", 3, "alice@mail.com", "9876543210");[cite: 3]
    insertAtEnd(&head, 103, "Charlie", "IT", 2, "charlie@mail.com", "9123456789");[cite: 3]
    insertAtMiddle(&head, 2, 102, "Bob", "ECE", 3, "bob@mail.com", "9988776655");[cite: 3]
    insertAtBeginning(&head, 100, "Zack", "Mech", 1, "zack@mail.com", "9000011111");[cite: 3]
    
    displayList(head);[cite: 3]
    return 0;
}