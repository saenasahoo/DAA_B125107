/*
 * Application of sorting - II
 * -----------------------------------------------------------------
 * Input : S1, S2 (each size n), and integer x
 * Output: whether there exist a in S1, b in S2 with a + b == x
 *
 * Algorithm (O(n log n)):
 *   1. Sort S2. (O(n log n))
 *   2. For every element a in S1, binary search for (x - a) in the
 *      sorted S2. (n searches * O(log n) = O(n log n))
 *   Total: O(n log n).
 * -----------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

/* returns 1 if 'target' is found in sorted array a[0..n-1] */
int binarySearch(int a[], int n, int target) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) return 1;
        else if (a[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return 0;
}

/* returns 1 and sets *outA,*outB if a pair is found */
int findPairSum(int S1[], int n1, int S2[], int n2, int x, int *outA, int *outB) {
    int *sorted2 = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n2; i++) sorted2[i] = S2[i];
    qsort(sorted2, n2, sizeof(int), cmp);           /* O(n log n) */

    for (int i = 0; i < n1; i++) {                  /* O(n) */
        int need = x - S1[i];
        if (binarySearch(sorted2, n2, need)) {       /* O(log n) */
            *outA = S1[i];
            *outB = need;
            free(sorted2);
            return 1;
        }
    }
    free(sorted2);
    return 0;
}

int main(void) {
    int S1[] = {8, 3, 15, 6, 20};
    int S2[] = {2, 11, 5, 30, 9};
    int n1 = sizeof(S1) / sizeof(S1[0]);
    int n2 = sizeof(S2) / sizeof(S2[0]);

    int x = 17; /* 8 + 9 = 17 exists */
    int a, b;

    if (findPairSum(S1, n1, S2, n2, x, &a, &b))
        printf("Found pair summing to %d: %d (from S1) + %d (from S2)\n", x, a, b);
    else
        printf("No pair sums to %d\n", x);

    x = 100; /* should not exist */
    if (findPairSum(S1, n1, S2, n2, x, &a, &b))
        printf("Found pair summing to %d: %d (from S1) + %d (from S2)\n", x, a, b);
    else
        printf("No pair sums to %d\n", x);

    return 0;
}
