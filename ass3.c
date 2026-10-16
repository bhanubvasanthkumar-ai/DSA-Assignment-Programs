#include <stdio.h>
#define MAX 101

typedef struct {
    int degree;
    float coef[MAX];
} polynomial;

/* Function to add two polynomials */
polynomial polynomial_add(polynomial a, polynomial b) {
    polynomial result;
    int i;

    result.degree = (a.degree > b.degree) ? a.degree : b.degree;

    for (i = 0; i <= result.degree; i++) {
        float x = (i <= a.degree) ? a.coef[i] : 0;
        float y = (i <= b.degree) ? b.coef[i] : 0;

        result.coef[i] = x + y;
    }

    /* Remove leading zero coefficients */
    while (result.degree > 0 &&
           result.coef[0] == 0) {
        for (i = 0; i < result.degree; i++) {
            result.coef[i] = result.coef[i + 1];
        }
        result.degree--;
    }

    return result;
}

/* Function to display a polynomial */
void display(polynomial p) {
    int i, first = 1;
    float c;

    for (i = 0; i <= p.degree; i++) {
        c = p.coef[i];

        if (c == 0)
            continue;

        if (!first) {
            if (c > 0)
                printf(" + ");
            else
                printf(" - ");
        } else if (c < 0) {
            printf("-");
        }

        if (c < 0)
            c = -c;

        /* Print coefficient */
        if (i == 0 || c != 1)
            printf("%g", c);

        /* Print variable and exponent */
        if (i < p.degree) {
            printf("x");
            if (p.degree - i > 1)
                printf("^%d", p.degree - i);
        }

        first = 0;
    }

    if (first)
        printf("0");

    printf("\n");
}

/* Function to read a polynomial */
void read_polynomial(polynomial *p) {
    int i;

    printf("Enter the degree of the polynomial: ");
    scanf("%d", &p->degree);

    if (p->degree < 0 || p->degree >= MAX) {
        printf("Invalid degree! Enter a degree from 0 to 100.\n");
        p->degree = -1;
        return;
    }

    printf("Enter coefficients from highest degree to constant term:\n");

    for (i = 0; i <= p->degree; i++) {
        printf("Coefficient of x^%d: ",
               p->degree - i);
        scanf("%f", &p->coef[i]);
    }
}

int main() {
    polynomial a, b, sum;

    printf("Enter the first polynomial:\n");
    read_polynomial(&a);

    if (a.degree < 0)
        return 1;

    printf("\nEnter the second polynomial:\n");
    read_polynomial(&b);

    if (b.degree < 0)
        return 1;

    printf("\nFirst polynomial: ");
    display(a);

    printf("Second polynomial: ");
    display(b);

    sum = polynomial_add(a, b);

    printf("Sum of the polynomials: ");
    display(sum);

    return 0;
}
