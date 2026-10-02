#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main() {
    int n;
    scanf("%d", &n);
    double *p = calloc(n + 2, sizeof(double));   /* p[1..n] */
    double *q = calloc(n + 1, sizeof(double));   /* q[0..n] */
    for (int i = 1; i <= n; i++) scanf("%lf", &p[i]);
    for (int i = 0; i <= n; i++) scanf("%lf", &q[i]);

    double **e = malloc((n + 2) * sizeof(double *));
    double **w = malloc((n + 2) * sizeof(double *));
    int **root = malloc((n + 2) * sizeof(int *));
    for (int i = 0; i <= n + 1; i++) {
        e[i] = calloc(n + 1, sizeof(double));
        w[i] = calloc(n + 1, sizeof(double));
        root[i] = calloc(n + 1, sizeof(int));
    }

    for (int i = 1; i <= n + 1; i++) { e[i][i - 1] = q[i - 1]; w[i][i - 1] = q[i - 1]; }

    for (int l = 1; l <= n; l++)
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = DBL_MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; r++) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) { e[i][j] = t; root[i][j] = r; }
            }
        }

    printf("Minimum expected search cost: %.4f\n", e[1][n]);
    printf("Root table:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            printf("%3d ", j >= i ? root[i][j] : 0);
        printf("\n");
    }
    return 0;
}
/* Time: O(n^3), Space: O(n^2) */