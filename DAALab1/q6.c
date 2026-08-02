
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp_int(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

/* Returns 1 if a duplicate exists, 0 otherwise. Sorts a COPY of the array. */
int has_duplicates(int arr[], int n) {
    int *copy = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) copy[i] = arr[i];

    qsort(copy, n, sizeof(int), cmp_int);

    int found = 0;
    for (int i = 0; i < n - 1; i++) {
        if (copy[i] == copy[i + 1]) { found = 1; break; }
    }
    free(copy);
    return found;
}

void fill_random(int arr[], int n, int range) {
    for (int i = 0; i < n; i++) arr[i] = rand() % range;
}

int main(void) {
    srand((unsigned) time(NULL));

    /* Small manual test */
    int test1[] = {5, 3, 8, 1, 9, 2};
    int test2[] = {5, 3, 8, 1, 3, 2}; /* has duplicate 3 */
    printf("test1 (no duplicates expected): %s\n",
           has_duplicates(test1, 6) ? "DUPLICATES FOUND" : "all unique");
    printf("test2 (duplicate expected):     %s\n\n",
           has_duplicates(test2, 6) ? "DUPLICATES FOUND" : "all unique");

    /* Large-n experiment: numbers drawn from a range MUCH bigger than n,
     * so duplicates become increasingly rare as n grows (birthday-paradox
     * effect still applies, but with a wide enough range, most large draws
     * will show as unique unless n approaches sqrt(range)). */
    int sizes[] = {100, 1000, 10000, 100000, 1000000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int range = 100000000; /* 10^8 possible values */

    printf("Large-n experiment (values drawn from range 0..%d):\n", range - 1);
    printf("%-10s %-15s\n", "n", "Duplicates?");
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int *arr = malloc(n * sizeof(int));
        fill_random(arr, n, range);
        int dup = has_duplicates(arr, n);
        printf("%-10d %-15s\n", n, dup ? "yes" : "no");
        free(arr);
    }

    fprintf(stderr,
        "\nConclusion: sorting first makes uniqueness checking O(n log n),\n"
        "far better than the naive O(n^2) all-pairs comparison. For\n"
        "sufficiently large n relative to the value range, the probability\n"
        "of a collision rises quickly (birthday paradox: ~50%% chance of a\n"
        "duplicate once n is roughly sqrt(range)).\n");

    return 0;
}