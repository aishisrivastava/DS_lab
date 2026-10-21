#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 4

typedef struct {
    int orderId;
    char customerName[50];
} FoodOrder;

typedef struct {
    FoodOrder items[MAX];
    int front, rear;
} OrderQueue;

void initQueue(OrderQueue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isFull(OrderQueue *q) {
    return (q->rear + 1) % MAX == q->front;
}

bool isEmpty(OrderQueue *q) {
    return q->front == -1;
}

void placeOrder(OrderQueue *q, int id, char *name) {
    if (isFull(q)) {
        printf("Queue Overflow! Kitchen capacity reached. Cannot accept order #%d.\n", id);
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->items[q->rear].orderId = id;
    strcpy(q->items[q->rear].customerName, name);
    printf("Order Placed: [#%d] for %s\n", id, name);
}

void processOrder(OrderQueue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! No pending food orders.\n");
        return;
    }
    printf("Order Ready & Served: [#%d] %s\n", q->items[q->front].orderId, q->items[q->front].customerName);
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
}

void displayPending(OrderQueue *q) {
    if (isEmpty(q)) {
        printf("No pending orders in the kitchen queue.\n");
        return;
    }
    printf("\n--- Pending Food Orders ---\n");
    int i = q->front;
    while (true) {
        printf("Order ID: #%d | Customer: %s\n", q->items[i].orderId, q->items[i].customerName);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("---------------------------\n");
}

int main() {
    OrderQueue q;
    initQueue(&q);

    placeOrder(&q, 101, "Liam");
    placeOrder(&q, 102, "Olivia");
    placeOrder(&q, 103, "Noah");
    displayPending(&q);

    processOrder(&q);
    displayPending(&q);

    // Reuse space for new incoming orders
    placeOrder(&q, 104, "Emma");
    displayPending(&q);

    return 0;
}