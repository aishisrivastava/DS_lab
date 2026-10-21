#include <stdio.h>
#include <string.h>

#define MAX 5

typedef struct {
    char customerName[50];
    int itemCount;
} Shopper;

typedef struct {
    Shopper items[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

void enqueue(Queue *q, char *name, int count) {
    if (q->rear == MAX - 1) {
        printf("Billing queue is full (Overflow)!\n");
        return;
    }
    q->rear++;
    strcpy(q->items[q->rear].customerName, name);
    q->items[q->rear].itemCount = count;
    printf("%s added to billing queue with %d items.\n", name, count);
}

void processQueue(Queue *q) {
    if (q->front > q->rear) {
        printf("Billing queue is empty (Underflow)!\n");
        return;
    }
    printf("\nBilling processed for: %s (%d items)\n", q->items[q->front].customerName, q->items[q->front].itemCount);
    q->front++;
}

void display(Queue *q) {
    if (q->front > q->rear) {
        printf("No customers waiting at the billing counter.\n");
        return;
    }
    printf("\n--- Supermarket Billing Queue ---\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d. %s (%d items)\n", i - q->front + 1, q->items[i].customerName, q->items[i].itemCount);
    }
    printf("---------------------------------\n");
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, "David", 4);
    enqueue(&q, "Eva", 12);
    enqueue(&q, "Frank", 2);
    
    display(&q);
    processQueue(&q);
    display(&q);

    return 0;
}