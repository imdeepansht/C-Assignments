#include <stdio.h>

int main() {
    float base, hra, ta, gross, tax, net;

    printf("Enter basic salary: ");
    scanf("%f", &base);

    hra = 0.10 * base;
    ta = 0.05 * base;
    gross = base + hra + ta;
    tax = 0.02 * gross;
    net = gross - tax;

    printf("\nBase Salary: %.2f", base);
    printf("\nHRA: %.2f", hra);
    printf("\nTA: %.2f", ta);
    printf("\nGross Salary: %.2f", gross);
    printf("\nTax: %.2f", tax);
    printf("\nNet Salary: %.2f", net);

    return 0;
}
