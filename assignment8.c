#include <stdio.h>

int main() {
    int i;
    float marks[5], total = 0, percentage;

    printf("Enter marks of 5 subjects:\n");

    for(i = 0; i < 5; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%f", &marks[i]);
        total += marks[i];
    }

    for(i = 0; i < 5; i++) {
        if(marks[i] < 40) {
            printf("\nResult: FAIL\n");
            return 0;
        }
    }

    percentage = (total / 500) * 100;

    printf("\nTotal = %.2f", total);
    printf("\nPercentage = %.2f%%", percentage);

    if(percentage >= 75)
        printf("\nGrade: A");
    else if(percentage >= 60)
        printf("\nGrade: B");
    else if(percentage >= 50)
        printf("\nGrade: C");
    else if(percentage >= 40)
        printf("\nGrade: D");

    return 0;
}