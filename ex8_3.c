#include <stdio.h>
#include <string.h>

#define MAX 5

typedef struct {
    char passengerName[50];
    char flightNo[10];
} Passenger;

typedef struct {
    Passenger items[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

void enqueue(Queue *q, char *name, char *flight) {
    if (q->rear == MAX - 1) {
        printf("Check-in queue overflow!\n");
        return;
    }
    q->rear++;
    strcpy(q->items[q->rear].passengerName, name);
    strcpy(q->items[q->rear].flightNo, flight);
    printf("Passenger %s checked in for flight %s.\n", name, flight);
}

void processPassenger(Queue *q) {
    if (q->front > q->rear) {
        printf("Check-in queue underflow! No passengers waiting.\n");
        return;
    }
    printf("Processing Check-in for: %s (Flight: %s)\n", q->items[q->front].passengerName, q->items[q->front].flightNo);
    q->front++;
}

void display(Queue *q) {
    if (q->front > q->rear) {
        printf("Current Check-in Queue is empty.\n");
        return;
    }
    printf("\n--- Airport Check-in Queue ---\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("Passenger: %s | Flight: %s\n", q->items[i].passengerName, q->items[i].flightNo);
    }
    printf("------------------------------\n");
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, "Grace", "AA-123");
    enqueue(&q, "Hank", "BA-456");

    display(&q);
    processPassenger(&q);
    display(&q);

    return 0;
}