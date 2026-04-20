#include <stdio.h>

int main() {
    int choice;
    float a, b;

    printf("Enter two numbers: ");
    scanf("%f %f", &a, &b);

    printf("\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: 
            printf("Result = %.2f", a + b); 
            break;
        case 2: 
            printf("Result = %.2f", a - b); 
            break;
        case 3: 
            printf("Result = %.2f", a * b); 
            break;
        case 4: 
            printf("Result = %.2f", a / b); 
        break;
        default: 
            printf("Invalid choice");
    }

    return 0;
}
