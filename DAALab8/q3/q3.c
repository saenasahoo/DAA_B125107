#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char X[1005], Y[1005];
    scanf("%s %s", X, Y);
    int m = strlen(X), n = strlen(Y);

    int **L = malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) L[i] = calloc(n + 1, sizeof(int));

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (X[i - 1] == Y[j - 1]) L[i][j] = L[i - 1][j - 1] + 1;
            else L[i][j] = L[i - 1][j] > L[i][j - 1] ? L[i - 1][j] : L[i][j - 1];

    int len = L[m][n];
    char *lcs = malloc(len + 1);
    lcs[len] = '\0';
    int i = m, j = n, k = len - 1;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) { lcs[k--] = X[i - 1]; i--; j--; }
        else if (L[i - 1][j] >= L[i][j - 1]) i--;
        else j--;
    }
    printf("Length: %d\nLCS: %s\n", len, lcs);

    for (int r = 0; r <= m; r++) free(L[r]);
    free(L); free(lcs);
    return 0;
}
/* Time: O(mn), Space: O(mn) */