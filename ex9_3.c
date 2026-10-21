#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 3

typedef struct {
    char vehicleNo[20];
    char owner[50];
} Vehicle;

typedef struct {
    Vehicle items[MAX];
    int front, rear;
} ParkingQueue;

void initQueue(ParkingQueue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isFull(ParkingQueue *q) {
    return (q->rear + 1) % MAX == q->front;
}

bool isEmpty(ParkingQueue *q) {
    return q->front == -1;
}

void parkVehicle(ParkingQueue *q, char *vNo, char *owner) {
    if (isFull(q)) {
        printf("Parking Full! Cannot park vehicle %s.\n", vNo);
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    strcpy(q->items[q->rear].vehicleNo, vNo);
    strcpy(q->items[q->rear].owner, owner);
    printf("Vehicle Parked: %s (%s)\n", vNo, owner);
}

void removeVehicle(ParkingQueue *q) {
    if (isEmpty(q)) {
        printf("Parking Lot is empty!\n");
        return;
    }
    printf("Vehicle Exited: %s (%s)\n", q->items[q->front].vehicleNo, q->items[q->front].owner);
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
}

void display(ParkingQueue *q) {
    if (isEmpty(q)) {
        printf("Parking area is currently empty.\n");
        return;
    }
    printf("\n--- Current Parked Vehicles ---\n");
    int i = q->front;
    while (true) {
        printf("Vehicle: %s | Owner: %s\n", q->items[i].vehicleNo, q->items[i].owner);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("-------------------------------\n");
}

int main() {
    ParkingQueue q;
    initQueue(&q);

    parkVehicle(&q, "MH-12-AB-1234", "John");
    parkVehicle(&q, "MH-14-XY-5678", "Sarah");
    parkVehicle(&q, "MH-02-CD-9999", "Mike");
    display(&q);

    // Vehicle leaves, freeing up space at the front
    removeVehicle(&q);
    display(&q);

    // New vehicle parks using the freed circular slot
    printf("Parking new vehicle using circular memory reuse:\n");
    parkVehicle(&q, "MH-01-EF-1111", "Emma");
    display(&q);

    return 0;
}