/*
 * DAA Lab-6, Q1
 * Nth Fibonacci number using Dynamic Programming (Bottom-Up Tabulation)
 */

#include <stdio.h>
#include <stdlib.h>

long long fibonacci(int n) {
    if (n <= 1)
        return n;

    long long *dp = (long long *)malloc((n + 1) * sizeof(long long));

    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    long long result = dp[n];
    free(dp);
    return result;
}

int main() {
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Fibonacci is not defined for negative numbers.\n");
        return 1;
    }

    printf("Fibonacci(%d) = %lld\n", n, fibonacci(n));

    return 0;
}
