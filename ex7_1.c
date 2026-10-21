#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX 100

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

bool isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int val) {
    if (isFull(s)) {
        printf("Stack overflow error!\n");
        exit(1);
    }
    s->data[++(s->top)] = val;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow error! Invalid expression.\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

// Function to evaluate a postfix expression
int evaluatePostfix(char *exp) {
    Stack s;
    initStack(&s);

    for (int i = 0; exp[i] != '\0'; i++) {
        // Skip whitespace if any
        if (exp[i] == ' ' || exp[i] == '\t') {
            continue;
        }

        // If the character is an operand (digit), push it to the stack
        if (isdigit(exp[i])) {
            push(&s, exp[i] - '0'); // Convert char digit to int value
        } 
        // If the character is an operator, pop two operands and apply the operator
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
            int val2 = pop(&s); // Second operand comes off first
            int val1 = pop(&s); // First operand comes off second

            switch (exp[i]) {
                case '+': push(&s, val1 + val2); break;
                case '-': push(&s, val1 - val2); break;
                case '*': push(&s, val1 * val2); break;
                case '/': 
                    if (val2 == 0) {
                        printf("Error: Division by zero!\n");
                        exit(1);
                    }
                    push(&s, val1 / val2); 
                    break;
            }
        } else {
            printf("Error: Invalid character '%c' in expression.\n", exp[i]);
            exit(1);
        }
    }

    // The final result is the only element left in the stack
    return pop(&s);
}

int main() {
    char exp[MAX];

    printf("Enter a postfix expression (e.g., 23*5+): ");
    scanf("%s", exp);

    int result = evaluatePostfix(exp);
    printf("Evaluated Result: %d\n", result);

    return 0;
}