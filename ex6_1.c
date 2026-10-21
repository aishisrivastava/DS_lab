#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

// Stack structure for characters
typedef struct {
    char data[MAX];
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

void push(Stack *s, char c) {
    if (!isFull(s)) {
        s->data[++(s->top)] = c;
    }
}

char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return '\0';
}

// Function to check palindrome
bool isPalindrome(char *str) {
    Stack s;
    initStack(&s);
    int len = strlen(str);

    // Push all characters onto the stack
    for (int i = 0; i < len; i++) {
        push(&s, str[i]);
    }

    // Pop and compare with original string characters
    for (int i = 0; i < len; i++) {
        if (str[i] != pop(&s)) {
            return false;
        }
    }
    return true;
}

int main() {
    char str[MAX];
    printf("Enter a string: ");
    scanf("%s", str);

    if (isPalindrome(str)) {
        printf("\"%s\" is a palindrome.\n", str);
    } else {
        printf("\"%s\" is not a palindrome.\n", str);
    }

    return 0;
}