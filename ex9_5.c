#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 4

typedef struct {
    int callId;
    char callerName[50];
} Call;

typedef struct {
    Call items[MAX];
    int front, rear;
} CallQueue;

void initQueue(CallQueue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isFull(CallQueue *q) {
    return (q->rear + 1) % MAX == q->front;
}

bool isEmpty(CallQueue *q) {
    return q->front == -1;
}

void insertCall(CallQueue *q, int id, char *name) {
    if (isFull(q)) {
        printf("\nQueue Overflow! Call center lines are busy.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->items[q->rear].callId = id;
    strcpy(q->items[q->rear].callerName, name);
    printf("\nCall [%d] from %s added to queue.\n", id, name);
}

void deleteCall(CallQueue *q) {
    if (isEmpty(q)) {
        printf("\nQueue Underflow! No pending calls.\n");
        return;
    }
    printf("\nConnecting agent to Call [%d]: %s\n", q->items[q->front].callId, q->items[q->front].callerName);
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
}

void display(CallQueue *q) {
    if (isEmpty(q)) {
        printf("\nCall queue is currently empty.\n");
        return;
    }
    printf("\n--- Active Call Queue ---\n");
    int i = q->front;
    while (true) {
        printf("Call ID: %d | Caller: %s\n", q->items[i].callId, q->items[i].callerName);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("-------------------------\n");
}

int main() {
    CallQueue q;
    initQueue(&q);
    int choice, id;
    char name[50];

    // Demonstrating pre-loaded operations for automated execution or interactive testing
    insertCall(&q, 501, "George");
    insertCall(&q, 502, "Hannah");
    display(&q);

    deleteCall(&q);
    display(&q);

    insertCall(&q, 503, "Ian");
    insertCall(&q, 504, "Julia");
    display(&q);

    return 0;
}