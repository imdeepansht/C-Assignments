#include <stdio.h>

int main() {
    int choice;
    int x, y, i;
    int result = 1;

    printf("Simple Calculator\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Power (x^y)\n");
    printf("6. Factorial (x!)\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    if(choice >= 1 && choice <= 5) {
        printf("Enter x and y: ");
        scanf("%d %d", &x, &y);
    }

    if(choice == 1)
        printf("Result = %d", x + y);

    else if(choice == 2)
        printf("Result = %d", x - y);

    else if(choice == 3)
        printf("Result = %d", x * y);

    else if(choice == 4) {
        if(y == 0)
            printf("Cannot divide by zero");
        else
            printf("Result = %d", x / y);
    }

    else if(choice == 5) {
        for(i = 1; i <= y; i++)
            result *= x;
        printf("Result = %d", result);
    }

    else if(choice == 6) {
        int fact = 1;
        printf("Enter x: ");
        scanf("%d", &x);

        for(i = 1; i <= x; i++)
            fact *= i;

        printf("Result = %d", fact);
    }

    else
        printf("Invalid choice");

    return 0;
}