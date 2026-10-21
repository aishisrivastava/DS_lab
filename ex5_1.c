#include <stdio.h>
#include <stdlib.h>

// Structure representing a term in the polynomial
struct Node {
    int coeff;
    int exp;
    struct Node* next;
};

// Function to create a new polynomial term node
struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = newNode; // Points to itself initially for circular linkage
    return newNode;
}

// 1. Create a polynomial by inserting terms in descending order of exponents
void insertTerm(struct Node** head, int coeff, int exp) {
    if (coeff == 0) return; // Do not insert zero-coefficient terms

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

    // Check if new term has a higher exponent than the head
    if (exp > (*head)->exp) {
        struct Node* last = *head;
        while (last->next != *head) {
            last = last->next;
        }
        newNode->next = *head;
        *head = newNode;
        last->next = *head;
        return;
    } 
    else if (exp == (*head)->exp) {
        (*head)->coeff += coeff;
        free(newNode);
        return;
    }

    // Traverse to find the correct position
    curr = *head;
    do {
        prev = curr;
        curr = curr->next;
        if (curr == *head) break;

        if (exp > curr->exp) {
            prev->next = newNode;
            newNode->next = curr;
            return;
        } 
        else if (exp == curr->exp) {
            curr->coeff += coeff;
            free(newNode);
            return;
        }
    } while (curr != *head);

    // If it belongs at the very end
    struct Node* last = *head;
    while (last->next != *head) {
        last = last->next;
    }
    last->next = newNode;
    newNode->next = *head;
}

// 2. Display the polynomial in a readable mathematical form
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

// 3. Add two polynomials and return the resultant polynomial
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    if (poly1 != NULL) {
        struct Node* p1 = poly1;
        do {
            insertTerm(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        } while (p1 != poly1);
    }

    if (poly2 != NULL) {
        struct Node* p2 = poly2;
        do {
            insertTerm(&result, p2->coeff, p2->exp);
            p2 = p2->next;
        } while (p2 != poly2);
    }

    return result;
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* sum = NULL;

    // Creating Polynomial 1: 3x^3 + 5x^2 + 2
    printf("Creating Polynomial 1 (3x^3 + 5x^2 + 2):\n");
    insertTerm(&poly1, 3, 3);
    insertTerm(&poly1, 5, 2);
    insertTerm(&poly1, 2, 0);
    printf("Polynomial 1: ");
    displayPolynomial(poly1);[cite: 4]

    // Creating Polynomial 2: 4x^2 + 2x + 1
    printf("\nCreating Polynomial 2 (4x^2 + 2x + 1):\n");
    insertTerm(&poly2, 4, 2);
    insertTerm(&poly2, 2, 1);
    insertTerm(&poly2, 1, 0);
    printf("Polynomial 2: ");
    displayPolynomial(poly2);[cite: 4]

    // Adding Polynomials
    sum = addPolynomials(poly1, poly2);[cite: 4]
    printf("\nResultant Polynomial (Poly1 + Poly2): ");
    displayPolynomial(sum);[cite: 4]

    return 0;
}