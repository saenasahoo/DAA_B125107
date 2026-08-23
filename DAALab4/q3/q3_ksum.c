/*
 * Application of sorting - III
 * -----------------------------------------------------------------
 * Input : set S of n integers, integer T, integer k (k >= 2)
 * Output: whether some k of the integers in S add up to T
 *
 * Algorithm (O(n^(k-1) * log n)):
 *   1. Sort S.                                            O(n log n)
 *   2. Fix the first (k-2) elements using (k-2) nested
 *      loops over strictly increasing indices.             O(n^(k-2))
 *   3. For the remaining 2 elements, instead of a further
 *      nested loop, use BINARY SEARCH: for each candidate
 *      element scan the rest and binary-search for the
 *      complement that makes the running sum equal T.       O(n log n)
 *
 *   Combining steps 2 and 3:
 *      O(n^(k-2)) * O(n log n)  =  O(n^(k-1) log n)
 *
 * We implement this with a recursion that peels off one element
 * per level; the base case (k == 2) is solved with binary search
 * instead of a two-pointer scan, which is what gives the extra
 * log n factor demanded by the problem.
 * -----------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

/* binary search for 'target' in arr[lo..hi] (inclusive), returns index or -1 */
int binarySearch(int arr[], int lo, int hi, int target) {
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

/* base case: does any pair in arr[start..n-1] sum to 'target'? uses binary search */
int pairSumBinarySearch(int arr[], int n, int start, int target, int chosen[], int chosenCount) {
    for (int i = start; i < n; i++) {
        int need = target - arr[i];
        int pos = binarySearch(arr, i + 1, n - 1, need);
        if (pos != -1) {
            chosen[chosenCount] = arr[i];
            chosen[chosenCount + 1] = arr[pos];
            return 1;
        }
    }
    return 0;
}

/* recursively fix elements; remaining == 2 triggers the binary-search base case */
int kSumRec(int arr[], int n, int start, int remaining, int target,
            int chosen[], int chosenCount) {
    if (remaining == 2)
        return pairSumBinarySearch(arr, n, start, target, chosen, chosenCount);

    for (int i = start; i <= n - remaining; i++) {
        chosen[chosenCount] = arr[i];
        if (kSumRec(arr, n, i + 1, remaining - 1, target - arr[i], chosen, chosenCount + 1))
            return 1;
    }
    return 0;
}

/* returns 1 if some k elements of S sum to T, fills chosen[0..k-1] */
int kSum(int S[], int n, int k, int T, int chosen[]) {
    if (k < 2 || n < k) return 0;
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = S[i];
    qsort(arr, n, sizeof(int), cmp);                 /* O(n log n) */

    int result = kSumRec(arr, n, 0, k, T, chosen, 0);
    free(arr);
    return result;
}

int main(void) {
    int S[] = {2, 7, 4, 11, 15, 1, 9, 6};
    int n = sizeof(S) / sizeof(S[0]);
    int chosen[10];

    int T1 = 20, k1 = 3; /* e.g. 4 + 7 + 9 = 20 */
    if (kSum(S, n, k1, T1, chosen)) {
        printf("Found %d numbers summing to %d: ", k1, T1);
        for (int i = 0; i < k1; i++) printf("%d ", chosen[i]);
        printf("\n");
    } else {
        printf("No %d numbers sum to %d\n", k1, T1);
    }

    int T2 = 4, k2 = 4;
    if (kSum(S, n, k2, T2, chosen)) {
        printf("Found %d numbers summing to %d: ", k2, T2);
        for (int i = 0; i < k2; i++) printf("%d ", chosen[i]);
        printf("\n");
    } else {
        printf("No %d numbers sum to %d\n", k2, T2);
    }

    int T3 = 100, k3 = 3;
    if (kSum(S, n, k3, T3, chosen)) {
        printf("Found %d numbers summing to %d\n", k3, T3);
    } else {
        printf("No %d numbers sum to %d\n", k3, T3);
    }

    return 0;
}
