/*
 * Application of sorting - V
 * -----------------------------------------------------------------
 * Input : list I of n intervals (x_i, y_i)
 * Output: the merged, non-overlapping list of intervals covering
 *         the same union of points.
 *
 * Algorithm (worst-case O(n log n)):
 *   1. Sort intervals by their left endpoint x_i.        O(n log n)
 *   2. Sweep once, keeping a "current" merged interval.
 *      If the next interval's start <= current end, extend
 *      current's end to max(current end, next end).
 *      Otherwise close current and start a new one.       O(n)
 *   Total: O(n log n)
 *
 * Example from the handout:
 *   I = {(1,3),(2,6),(8,10),(7,18)}  ->  {(1,6),(7,18)}
 * -----------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct { int x, y; } Interval;

int cmpInterval(const void *a, const void *b) {
    return ((Interval *)a)->x - ((Interval *)b)->x;
}

/* merges intervals in-place-ish: writes result into out[], returns count */
int mergeIntervals(Interval I[], int n, Interval out[]) {
    if (n == 0) return 0;

    Interval *arr = (Interval *)malloc(n * sizeof(Interval));
    for (int i = 0; i < n; i++) arr[i] = I[i];
    qsort(arr, n, sizeof(Interval), cmpInterval);   /* O(n log n) */

    int m = 0;
    Interval cur = arr[0];
    for (int i = 1; i < n; i++) {                   /* O(n) */
        if (arr[i].x <= cur.y) {
            if (arr[i].y > cur.y) cur.y = arr[i].y;
        } else {
            out[m++] = cur;
            cur = arr[i];
        }
    }
    out[m++] = cur;

    free(arr);
    return m;
}

int main(void) {
    Interval I[] = {{1, 3}, {2, 6}, {8, 10}, {7, 18}};
    int n = sizeof(I) / sizeof(I[0]);
    Interval out[10];

    int m = mergeIntervals(I, n, out);

    printf("Input intervals: ");
    for (int i = 0; i < n; i++) printf("(%d,%d) ", I[i].x, I[i].y);
    printf("\n");

    printf("Merged intervals: ");
    for (int i = 0; i < m; i++) printf("(%d,%d) ", out[i].x, out[i].y);
    printf("\n");

    return 0;
}
