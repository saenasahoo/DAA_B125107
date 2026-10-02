#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, V;
    scanf("%d", &n);
    int *c = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);
    scanf("%d", &V);

    unsigned long long *dp = calloc(V + 1, sizeof(unsigned long long));
    dp[0] = 1;
    for (int i = 0; i < n; i++)          /* coin outer loop => combinations */
        for (int v = c[i]; v <= V; v++)
            dp[v] += dp[v - c[i]];

    printf("%llu\n", dp[V]);
    free(c); free(dp);
    return 0;
}
/* Time: O(nV), Space: O(V) */