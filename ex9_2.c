#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 4

typedef struct {
    int studentId;
    char name[50];
    char course[50];
} Student;

typedef struct {
    Student items[MAX];
    int front, rear;
} CircularQueue;

void initQueue(CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isFull(CircularQueue *q) {
    return (q->rear + 1) % MAX == q->front;
}

bool isEmpty(CircularQueue *q) {
    return q->front == -1;
}

void enqueue(CircularQueue *q, int id, char *name, char *course) {
    if (isFull(q)) {
        printf("Queue Overflow! Registration slots are full.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->items[q->rear].studentId = id;
    strcpy(q->items[q->rear].name, name);
    strcpy(q->items[q->rear].course, course);
    printf("Registered: [%d] %s for %s\n", id, name, course);
}

void dequeue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! No registrations to process.\n");
        return;
    }
    printf("Processed registration for: [%d] %s\n", q->items[q->front].studentId, q->items[q->front].name);
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
}

void display(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Registration queue is empty.\n");
        return;
    }
    printf("\n--- Student Registration Queue ---\n");
    int i = q->front;
    while (true) {
        printf("ID: %d | Name: %s | Course: %s\n", q->items[i].studentId, q->items[i].name, q->items[i].course);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("----------------------------------\n");
}

int main() {
    CircularQueue q;
    initQueue(&q);

    enqueue(&q, 101, "Alice", "Data Structures");
    enqueue(&q, 102, "Bob", "Algorithms");
    enqueue(&q, 103, "Charlie", "Operating Systems");
    display(&q);

    dequeue(&q);
    display(&q);

    // Demonstrating circular reuse
    enqueue(&q, 104, "Diana", "Database Systems");
    display(&q);

    return 0;
}