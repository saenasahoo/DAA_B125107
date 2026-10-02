#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *a = malloc(n * sizeof(int));
    long long *dp = malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    long long best = 0;
    for (int i = 0; i < n; i++) {
        dp[i] = a[i];
        for (int j = 0; j < i; j++)
            if (a[j] < a[i] && dp[j] + a[i] > dp[i])
                dp[i] = dp[j] + a[i];
        if (dp[i] > best) best = dp[i];
    }
    printf("%lld\n", best);
    free(a); free(dp);
    return 0;
}
/* Time: O(n^2), Space: O(n) */