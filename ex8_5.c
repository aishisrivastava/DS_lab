#include <stdio.h>
#include <string.h>

#define MAX 5

typedef struct {
    int studentId;
    char courseName[50];
} Registration;

typedef struct {
    Registration items[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

int isFull(Queue *q) {
    return q->rear == MAX - 1;
}

int isEmpty(Queue *q) {
    return q->front > q->rear;
}

void enqueue(Queue *q, int id, char *course) {
    if (isFull(q)) {
        printf("Queue Overflow! Registration server limit reached.\n");
        return;
    }
    q->rear++;
    q->items[q->rear].studentId = id;
    strcpy(q->items[q->rear].courseName, course);
    printf("Student ID %d registered for %s.\n", id, course);
}

void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! No registrations to process.\n");
        return;
    }
    printf("Processed registration for Student ID %d (Course: %s)\n", q->items[q->front].studentId, q->items[q->front].courseName);
    q->front++;
}

void display(Queue *q) {
    if (isEmpty(q)) {
        printf("Registration queue is empty.\n");
        return;
    }
    printf("\n--- Course Registration Queue ---\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("Student ID: %d -> Course: %s\n", q->items[i].studentId, q->items[i].courseName);
    }
    printf("---------------------------------\n");
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 1001, "Data Structures");
    enqueue(&q, 1002, "Operating Systems");
    enqueue(&q, 1003, "Database Systems");

    display(&q);
    dequeue(&q);
    display(&q);

    return 0;
}