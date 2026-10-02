#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int min3(int a, int b, int c) {
    int m = a < b ? a : b;
    return m < c ? m : c;
}

int main() {
    char A[1005], B[1005];
    scanf("%s %s", A, B);
    int m = strlen(A), n = strlen(B);

    int **D = malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) D[i] = malloc((n + 1) * sizeof(int));

    for (int i = 0; i <= m; i++) D[i][0] = i;
    for (int j = 0; j <= n; j++) D[0][j] = j;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            D[i][j] = min3(D[i - 1][j] + 1, D[i][j - 1] + 1,
                           D[i - 1][j - 1] + (A[i - 1] != B[j - 1]));

    printf("Edit distance: %d\nOperations (reverse order):\n", D[m][n]);
    int i = m, j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1] && D[i][j] == D[i - 1][j - 1]) {
            printf("Match %c\n", A[i - 1]); i--; j--;
        } else if (i > 0 && j > 0 && D[i][j] == D[i - 1][j - 1] + 1) {
            printf("Substitute %c -> %c\n", A[i - 1], B[j - 1]); i--; j--;
        } else if (i > 0 && D[i][j] == D[i - 1][j] + 1) {
            printf("Delete %c\n", A[i - 1]); i--;
        } else {
            printf("Insert %c\n", B[j - 1]); j--;
        }
    }
    for (int r = 0; r <= m; r++) free(D[r]);
    free(D);
    return 0;
}
/* Time: O(mn), Space: O(mn) */