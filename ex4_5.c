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

void removeDuplicates(struct Student* head) {
    struct Student *current = head, *ptr2, *dup;
    while (current != NULL && current->next != NULL) {
        ptr2 = current;
        while (ptr2->next != NULL) {
            if (ptr2->next->regNo == current->regNo) {
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                free(dup);
            } else {
                ptr2 = ptr2->next;
            }
        }
        current = current->next;
    }
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
    struct Student* head = NULL;
    insertEnd(&head, 101, "Alice");
    insertEnd(&head, 102, "Bob");
    insertEnd(&head, 101, "Alice (Duplicate)");
    insertEnd(&head, 103, "Charlie");

    printf("Before removing duplicates: "); display(head);
    removeDuplicates(head);[cite: 3]
    printf("After removing duplicates[cite: 3]: "); display(head);
    return 0;
}