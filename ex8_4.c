#include <stdio.h>
#include <string.h>

#define MAX 5

typedef struct {
    int docId;
    char docName[50];
} Document;

typedef struct {
    Document items[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

void addDocument(Queue *q, int id, char *name) {
    if (q->rear == MAX - 1) {
        printf("Queue Overflow! Scanner memory is full.\n");
        return;
    }
    q->rear++;
    q->items[q->rear].docId = id;
    strcpy(q->items[q->rear].docName, name);
    printf("Document added: [%d] %s\n", id, name);
}

void processDocument(Queue *q) {
    if (q->front > q->rear) {
        printf("Queue Underflow! No pending documents to scan.\n");
        return;
    }
    printf("Scanning Document: [%d] %s\n", q->items[q->front].docId, q->items[q->front].docName);
    q->front++;
}

void displayPending(Queue *q) {
    if (q->front > q->rear) {
        printf("No pending documents.\n");
        return;
    }
    printf("\n--- Pending Scanning Queue ---\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("ID: %d, Name: %s\n", q->items[i].docId, q->items[i].docName);
    }
    printf("-----------------------------\n");
}

int main() {
    Queue q;
    initQueue(&q);

    addDocument(&q, 1, "Resume.pdf");
    addDocument(&q, 2, "Invoice.pdf");

    displayPending(&q);
    processDocument(&q);
    displayPending(&q);

    return 0;
}