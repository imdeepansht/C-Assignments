#include <stdio.h>

int main() {
    int n, i;
    long long fact = 1; 

    printf("Enter a number: ");
    scanf("%d", &n);

    // 1. Validation Check
    if (n < 0) {
        printf("Invalid Input\n");
    } 
    else {
        // 2. The Loop (Algorithm logic)
        for (i = 1; i <= n; i++) {
            fact = fact * i;
        }

        // 3. Output
        printf("Factorial of %d is %lld\n", n, fact);
    }

    return 0;
}
