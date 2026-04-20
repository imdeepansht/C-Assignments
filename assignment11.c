#include <stdio.h>
#include <math.h>

int main() {
    int n, i;
    int fact = 1;
    int isPrime = 1;

    printf("Enter a number: ");
    scanf("%d", &n);

    
    printf("\nSquare root = %.2f", sqrt(n));


    printf("\nSquare = %d", n * n);

    printf("\nCube = %d", n * n * n);

    if(n <= 1)
        isPrime = 0;

    for(i = 2; i <= n/2; i++) {
        if(n % i == 0) {
            isPrime = 0;
            break;
        }
    }

    if(isPrime)
        printf("\nPrime number");
    else
        printf("\nNot a prime number");

    /* Factorial */
    for(i = 1; i <= n; i++)
        fact = fact * i;

    printf("\nFactorial = %d", fact);

    /* Prime factors */
    printf("\nPrime factors: ");

    for(i = 2; i <= n; i++) {
        while(n % i == 0) {
            printf("%d ", i);
            n = n / i;
        }
    }

    return 0;
}