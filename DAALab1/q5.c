
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int find_partition_point(int A[], int n) {
    int lo = 0, hi = n; /* hi = n represents "no 1 found yet" sentinel */
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (A[mid] == 1)
            hi = mid;       /* first 1 is at mid or earlier */
        else
            lo = mid + 1;   /* first 1 is after mid */
    }
    return lo; /* index of first 1, or n if none exists */
}

void generate_test_array(int A[], int n, int transition) {
    for (int i = 0; i < n; i++)
        A[i] = (i < transition) ? 0 : 1;
}

int main(void) {
    srand((unsigned) time(NULL));

    int test_cases[][2] = {
        {10, 0},   /* all 1's */
        {10, 10},  /* all 0's */
        {10, 4},   /* transition at index 4 */
        {15, 7},
        {1000000, 456789} /* large array to show efficiency */
    };
    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int c = 0; c < num_cases; c++) {
        int n = test_cases[c][0];
        int transition = test_cases[c][1];
        int *A = malloc(n * sizeof(int));
        generate_test_array(A, n, transition);

        int found = find_partition_point(A, n);

        if (n <= 20) {
            printf("Array: ");
            for (int i = 0; i < n; i++) printf("%d ", A[i]);
            printf("\n");
        }
        printf("n = %d, expected transition = %d, found = %d -> %s\n\n",
               n, transition, found, (found == transition) ? "PASS" : "FAIL");

        free(A);
    }

    printf("Binary search finds the partition point in O(log n) comparisons,\n"
           "much faster than an O(n) linear scan for large arrays.\n");

    return 0;
}