#include <stdio.h>
#include <stdlib.h>

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

// Function to display the polynomial[cite: 5]
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

// Function to multiply two polynomials term-by-term and combine like terms[cite: 5]
struct Node* multiplyPolynomials(struct Node* poly1, struct Node* poly2) {
    if (poly1 == NULL || poly2 == NULL) return NULL;
    struct Node* result = NULL;
    struct Node* p1 = poly1;

    do {
        struct Node* p2 = poly2;
        do {
            int newCoeff = p1->coeff * p2->coeff;
            int newExp = p1->exp + p2->exp;
            insertTerm(&result, newCoeff, newExp);
            p2 = p2->next;
        } while (p2 != poly2);
        p1 = p1->next;
    } while (p1 != poly1);

    return result;
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* product = NULL;

    // Creating Polynomial 1: 3x + 2[cite: 5]
    insertTerm(&poly1, 3, 1);
    insertTerm(&poly1, 2, 0);

    // Creating Polynomial 2: 2x^2 + 4x + 1[cite: 5]
    insertTerm(&poly2, 2, 2);
    insertTerm(&poly2, 4, 1);
    insertTerm(&poly2, 1, 0);

    printf("Polynomial 1: ");
    displayPolynomial(poly1);[cite: 5]

    printf("Polynomial 2: ");
    displayPolynomial(poly2);[cite: 5]

    // Multiply polynomials[cite: 5]
    product = multiplyPolynomials(poly1, poly2);

    printf("Resultant Product Polynomial: ");
    displayPolynomial(product);[cite: 5]

    return 0;
}