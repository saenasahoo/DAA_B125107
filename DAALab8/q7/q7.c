#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *p = malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) scanf("%d", &p[i]);

    int *r = calloc(n + 1, sizeof(int));
    int *cut = calloc(n + 1, sizeof(int));
    for (int j = 1; j <= n; j++) {
        r[j] = -1;
        for (int i = 1; i <= j; i++)
            if (p[i] + r[j - i] > r[j]) {
                r[j] = p[i] + r[j - i];
                cut[j] = i;
            }
    }
    printf("Max revenue: %d\nPieces:", r[n]);
    for (int len = n; len > 0; len -= cut[len]) printf(" %d", cut[len]);
    printf("\n");
    free(p); free(r); free(cut);
    return 0;
}
/* Time: O(n^2), Space: O(n) */