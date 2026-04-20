#include <stdio.h>

struct Student {
    int roll;
    char name[50];
    int m1, m2, m3;
    int total;
    float percent;
};

int main() {
    int n, i;
    printf("Enter number of students: ");
    scanf("%d", &n);

    struct Student s[n];

    for (i = 0; i < n; i++) {
        printf("\nRoll Number: ");
        scanf("%d", &s[i].roll);
        printf("Name: ");
        scanf("%s", s[i].name);
        printf("Marks in 3 subjects: ");
        scanf("%d %d %d", &s[i].m1, &s[i].m2, &s[i].m3);

        // Calculations
        s[i].total = s[i].m1 + s[i].m2 + s[i].m3;
        s[i].percent = s[i].total / 3.0;
    }

    printf("\nStudent Result:\n");
    for (i = 0; i < n; i++) {
        printf("Roll No: %d\n", s[i].roll);
        printf("Name: %s\n", s[i].name);
        printf("Total Marks: %d\n", s[i].total);
        printf("Percentage: %.2f%%\n", s[i].percent);
    }
    return 0;
}