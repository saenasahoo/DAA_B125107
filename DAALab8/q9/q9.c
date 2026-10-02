#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned long long ull;

/* Returns 0 on success, -1 on overflow. Fills steps and peak. */
int collatz(ull n, ull *steps, ull *peak) {
    *steps = 0;
    *peak = n;
    while (n != 1) {
        if (n % 2 == 0) n /= 2;
        else {
            if (n > (ULLONG_MAX - 1) / 3) return -1;   /* overflow guard */
            n = 3 * n + 1;
        }
        if (n > *peak) *peak = n;
        (*steps)++;
    }
    return 0;
}

void printTrajectory(ull n) {
    printf("%llu", n);
    while (n != 1) {
        if (n % 2 == 0) n /= 2;
        else {
            if (n > (ULLONG_MAX - 1) / 3) { printf(" -> OVERFLOW"); break; }
            n = 3 * n + 1;
        }
        printf(" -> %llu", n);
    }
    printf("\n");
}

void analyseInterval(ull a, ull b) {
    ull bestN = a, bestSteps = 0, bestPeak = 0, total = 0, count = 0;
    for (ull n = a; n <= b; n++) {
        ull s, pk;
        if (collatz(n, &s, &pk) != 0) { printf("Overflow at n = %llu\n", n); continue; }
        total += s; count++;
        if (s > bestSteps) { bestSteps = s; bestN = n; }
        if (pk > bestPeak) bestPeak = pk;
    }
    printf("Interval [%llu, %llu]\n", a, b);
    printf("Longest trajectory: n = %llu with %llu steps\n", bestN, bestSteps);
    printf("Highest peak reached: %llu\n", bestPeak);
    if (count) printf("Average steps: %.2f\n", (double)total / count);
}

int main() {
    ull n, a, b, steps, peak;

    printf("Enter starting value n (>= 1): ");
    scanf("%llu", &n);
    if (n < 1) { printf("Invalid input\n"); return 1; }

    printTrajectory(n);
    if (collatz(n, &steps, &peak) == 0)
        printf("Steps: %llu, Peak: %llu\n", steps, peak);
    else
        printf("Overflow detected\n");

    printf("Enter interval [a b]: ");
    scanf("%llu %llu", &a, &b);
    if (a < 1 || a > b) { printf("Invalid interval\n"); return 1; }
    analyseInterval(a, b);
    return 0;
}
/* Time per n: O(steps(n)); interval: O(sum of steps). Space: O(1). */