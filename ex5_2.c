#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node {
    int coeff;
    int exp;
    struct Node* next;
};

// Function to insert a term into the polynomial in descending order of exponents
void insertTerm(struct Node** head, int coeff, int exp) {
    if (coeff == 0) return;
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;

    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
        return;
    }

    struct Node* curr = *head;
    struct Node* prev = NULL;

    if (exp > (*head)->exp) {
        struct Node* last = *head;
        while (last->next != *head) {
            last = last->next;
        }
        newNode->next = *head;
        *head = newNode;
        last->next = *head;
        return;
    } else if (exp == (*head)->exp) {
        (*head)->coeff += coeff;
        free(newNode);
        return;
    }

    curr = *head;
    do {
        prev = curr;
        curr = curr->next;
        if (curr == *head) break;

        if (exp > curr->exp) {
            prev->next = newNode;
            newNode->next = curr;
            return;
        } else if (exp == curr->exp) {
            curr->coeff += coeff;
            free(newNode);
            return;
        }
    } while (curr != *head);

    struct Node* last = *head;
    while (last->next != *head) {
        last = last->next;
    }
    last->next = newNode;
    newNode->next = *head;
}

// Function to display the polynomial
void displayPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    struct Node* curr = head;
    int first = 1;
    do {
        if (!first) {
            if (curr->coeff > 0) printf(" + ");
            else printf(" - ");
        } else {
            if (curr->coeff < 0) printf("-");
        }
        int c = curr->coeff < 0 ? -curr->coeff : curr->coeff;
        if (curr->exp == 0) {
            printf("%d", c);
        } else if (curr->exp == 1) {
            if (c == 1) printf("x");
            else printf("%dx", c);
        } else {
            if (c == 1) printf("x^%d", curr->exp);
            else printf("%dx^%d", c, curr->exp);
        }
        first = 0;
        curr = curr->next;
    } while (curr != head);
    printf("\n");
}

// Function to evaluate the polynomial for a given value of x[cite: 5]
double evaluatePolynomial(struct Node* head, double x) {
    if (head == NULL) return 0;
    double result = 0;
    struct Node* curr = head;
    do {
        result += curr->coeff * pow(x, curr->exp);
        curr = curr->next;
    } while (curr != head);
    return result;
}

int main() {
    struct Node* poly = NULL;

    // Creating polynomial: 3x^2 + 2x + 5[cite: 5]
    insertTerm(&poly, 3, 2);
    insertTerm(&poly, 2, 1);
    insertTerm(&poly, 5, 0);

    printf("Polynomial: ");
    displayPolynomial(poly);[cite: 5]

    double x;
    printf("Enter the value of x for evaluation: ");
    scanf("%lf", &x);[cite: 5]

    double value = evaluatePolynomial(poly, x);[cite: 5]
    printf("Evaluated value at x = %.2lf is: %.2lf\n", x, value);

    return 0;
}