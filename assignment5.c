#include <stdio.h>

int main() {
    int a[10][10], b[10][10], sum[10][10], r, c, i, j;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &r, &c);

    // Input Matrix A
    printf("Enter elements of Matrix A:\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // 1. Matrix Addition
    printf("Enter elements of Matrix B for Addition:\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &b[i][j]);
            sum[i][j] = a[i][j] + b[i][j];
        }
    }

    printf("\nResult of Addition:\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            printf("%d ", sum[i][j]);
        }
        printf("\n");
    }

    // 2. Finding Saddle Point in Matrix A
    // Logic: Smallest in its row AND Largest in its column
    int found = 0;
    for (i = 0; i < r; i++) {
        int min_row = a[i][0], col_index = 0;
        
        // Find smallest in current row
        for (j = 1; j < c; j++) {
            if (a[i][j] < min_row) {
                min_row = a[i][j];
                col_index = j;
            }
        }

        // Check if this min_row is the largest in its column
        int k;
        for (k = 0; k < r; k++) {
            if (a[k][col_index] > min_row) {
                break; // Not the largest in column
            }
        }

        if (k == r) {
            printf("\nSaddle Point found: %d at row %d, col %d\n", min_row, i, col_index);
            found = 1;
        }
    }

    if (!found) printf("\nNo Saddle Point found in Matrix A.\n");

    return 0;
}