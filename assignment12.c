#include <stdio.h>

int main() {
    int a, b, i, min, gcd, smallestCD = -1;

    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    // a) Find Smallest Common Divisor (other than 1)
    min = (a < b) ? a : b; 
    for (i = 2; i <= min; i++) {
        if (a % i == 0 && b % i == 0) {
            smallestCD = i;
            break; // Stop at the first common divisor found
        }
    }

    if (smallestCD != -1)
        printf("Smallest Common Divisor (other than 1): %d\n", smallestCD);
    else
        printf("No common divisor found other than 1.\n");

    // b) Find GCD using Euclidean Algorithm
    int tempA = a, tempB = b;
    while (tempB != 0) {
        int temp = tempB;
        tempB = tempA % tempB;
        tempA = temp;
    }
    gcd = tempA;

    printf("Greatest Common Divisor (GCD): %d\n", gcd);

    return 0;
}