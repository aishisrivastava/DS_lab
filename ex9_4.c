#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 4

typedef struct {
    int tokenNo;
    char patientName[50];
    char department[30];
} Patient;

typedef struct {
    Patient items[MAX];
    int front, rear;
} HospitalQueue;

void initQueue(HospitalQueue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isFull(HospitalQueue *q) {
    return (q->rear + 1) % MAX == q->front;
}

bool isEmpty(HospitalQueue *q) {
    return q->front == -1;
}

void generateToken(HospitalQueue *q, int token, char *name, char *dept) {
    if (isFull(q)) {
        printf("Queue Overflow! Waiting list is full.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->items[q->rear].tokenNo = token;
    strcpy(q->items[q->rear].patientName, name);
    strcpy(q->items[q->rear].department, dept);
    printf("Generated Token #%d for %s (%s)\n", token, name, dept);
}

void attendPatient(HospitalQueue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! No patients in the waiting list.\n");
        return;
    }
    printf("Attending Patient: Token #%d (%s - %s)\n", 
           q->items[q->front].tokenNo, 
           q->items[q->front].patientName, 
           q->items[q->front].department);
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
}

void display(HospitalQueue *q) {
    if (isEmpty(q)) {
        printf("Waiting list is empty.\n");
        return;
    }
    printf("\n--- Hospital Waiting List ---\n");
    int i = q->front;
    while (true) {
        printf("Token #%d | Patient: %s | Dept: %s\n", 
               q->items[i].tokenNo, q->items[i].patientName, q->items[i].department);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("-----------------------------\n");
}

int main() {
    HospitalQueue q;
    initQueue(&q);

    generateToken(&q, 1, "Alice", "Cardiology");
    generateToken(&q, 2, "Bob", "Orthopedics");
    generateToken(&q, 3, "Charlie", "Pediatrics");
    display(&q);

    attendPatient(&q);
    display(&q);

    generateToken(&q, 4, "David", "Neurology");
    display(&q);

    return 0;
}