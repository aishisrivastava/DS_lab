#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int regNo;
    char name[50];
    struct Student* next;
};

void insertEnd(struct Student** head, int regNo, char* name) {
    struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
    newNode->regNo = regNo;
    strcpy(newNode->name, name);
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Student* temp = *head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }
}

struct Student* mergeLists(struct Student* head1, struct Student* head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    struct Student* temp = head1;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = head2;
    return head1;
}

void display(struct Student* head) {
    struct Student* temp = head;
    while (temp != NULL) {
        printf("[%d: %s] -> ", temp->regNo, temp->name);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Student* workshop1 = NULL;
    struct Student* workshop2 = NULL;

    insertEnd(&workshop1, 101, "Alice");
    insertEnd(&workshop1, 102, "Bob");

    insertEnd(&workshop2, 103, "Charlie");
    insertEnd(&workshop2, 104, "Diana");

    printf("Workshop 1: "); display(workshop1);
    printf("Workshop 2: "); display(workshop2);

    workshop1 = mergeLists(workshop1, workshop2);[cite: 3]

    printf("Merged Workshop List[cite: 3]: "); display(workshop1);
    return 0;
}