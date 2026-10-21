#include <stdio.h>
#include <string.h>

#define MAX 5

typedef struct {
    int tokenNumber;
    char name[50];
} Customer;

typedef struct {
    Customer items[MAX];
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

void enqueue(Queue *q, int token, char *name) {
    if (isFull(q)) {
        printf("Queue Overflow! Bank counter queue is full.\n");
        return;
    }
    q->rear++;
    q->items[q->rear].tokenNumber = token;
    strcpy(q->items[q->rear].name, name);
    printf("Customer %s (Token #%d) added to the queue.\n", name, token);
}

void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! No customers waiting at the bank counter.\n");
        return;
    }
    printf("Serving Customer: %s (Token #%d)\n", q->items[q->front].name, q->items[q->front].tokenNumber);
    q->front++;
}

void display(Queue *q) {
    if (isEmpty(q)) {
        printf("The bank queue is currently empty.\n");
        return;
    }
    printf("\n--- Current Bank Queue ---\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("Token #%d: %s\n", q->items[i].tokenNumber, q->items[i].name);
    }
    printf("--------------------------\n");
}

int main() {
    Queue q;
    initQueue(&q);
    
    enqueue(&q, 101, "Alice");
    enqueue(&q, 102, "Bob");
    enqueue(&q, 103, "Charlie");
    display(&q);

    dequeue(&q);
    display(&q);

    return 0;
}