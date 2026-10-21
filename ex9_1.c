#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 5  // Maximum capacity of the printer queue

typedef struct {
    int jobId;
    char docName[50];
} PrintJob;

typedef struct {
    PrintJob items[MAX];
    int front, rear;
} CircularQueue;

// Initialize the circular queue
void initQueue(CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is full
bool isFull(CircularQueue *q) {
    return (q->rear + 1) % MAX == q->front;
}

// Check if the queue is empty
bool isEmpty(CircularQueue *q) {
    return q->front == -1;
}

// a) Add a Print Job (Enqueue)
void enqueue(CircularQueue *q, int id, char *name) {
    if (isFull(q)) {
        printf("Printer Queue Overflow! Queue is full. Cannot add '%s'.\n", name);
        return;
    }
    
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    
    q->items[q->rear].jobId = id;
    strcpy(q->items[q->rear].docName, name);
    printf("Successfully added: [%d] %s\n", id, name);
}

// b) Process a Print Job (Dequeue)
void dequeue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Printer Queue Underflow! No pending print jobs.\n");
        return;
    }
    
    printf("Printing Job... Done: [%d] %s\n", q->items[q->front].jobId, q->items[q->front].docName);
    
    // If there was only one element, reset the queue
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
}

// c) Display All Pending Print Jobs
void display(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("\nPrinter queue is currently empty.\n");
        return;
    }
    
    printf("\n--- Current Pending Print Jobs (Circular Queue) ---\n");
    int i = q->front;
    while (true) {
        printf("Job ID: %d | Document: %s\n", q->items[i].jobId, q->items[i].docName);
        if (i == q->rear) {
            break;
        }
        i = (i + 1) % MAX;
    }
    printf("---------------------------------------------------\n");
}

int main() {
    CircularQueue q;
    initQueue(&q);

    // Test Enqueue
    enqueue(&q, 101, "Research_Paper.pdf");
    enqueue(&q, 102, "Resume.docx");
    enqueue(&q, 103, "Flight_Ticket.pdf");
    
    // Display Queue
    display(&q);

    // Test Dequeue (Process a job)
    printf("\nProcessing next print job:\n");
    dequeue(&q);
    
    // Display Queue after processing
    display(&q);

    // Add more jobs to demonstrate circular wraparound behavior
    printf("\nAdding more jobs:\n");
    enqueue(&q, 104, "Project_Report.pptx");
    enqueue(&q, 105, "Invoice.pdf");
    
    // Display final queue
    display(&q);

    return 0;
}