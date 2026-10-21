#include <stdio.h>
#include <stdbool.h>

#define MAX 32

// Stack structure for integers
typedef struct {
    int data[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

bool isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int val) {
    if (s->top < MAX - 1) {
        s->data[++(s->top)] = val;
    }
}

int pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return -1;
}

// Function to convert decimal to binary
void decimalToBinary(int n) {
    Stack s;
    initStack(&s);

    if (n == 0) {
        printf("Binary: 0\n");
        return;
    }

    // Push remainders onto the stack
    while (n > 0) {
        push(&s, n % 2);
        n = n / 2;
    }

    // Pop from stack to display binary digits
    printf("Binary: ");
    while (!isEmpty(&s)) {
        printf("%d", pop(&s));
    }
    printf("\n");
}

int main() {
    int decimal;
    printf("Enter a decimal number: ");
    scanf("%d", &decimal);

    if (decimal < 0) {
        printf("Please enter a non-negative decimal number.\n");
    } else {
        decimalToBinary(decimal);
    }

    return 0;
}