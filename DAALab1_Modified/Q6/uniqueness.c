/* ============================================================
   Design and Analysis of Algorithms - Lab 01, Question 6
   "Element uniqueness"

   Given n random numbers, check whether any duplicates exist.
   Two methods implemented and compared:

     (i)  Naive pairwise check - O(n^2)
          Compare every pair (i, j), i < j.

     (ii) Sort-then-scan - O(n log n)
          Sort the array (qsort), then a single linear scan
          checking adjacent elements for equality.

   Both report whether duplicates were found, and the number of
   comparisons used, so the growth rates can be compared.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long qsort_comparisons;   /* global counter, incremented inside comparator */

int cmp_int(const void *a, const void *b) {
    qsort_comparisons++;
    return (*(int *)a - *(int *)b);
}

/* (i) Naive O(n^2) pairwise duplicate check */
int has_duplicates_naive(int *A, int n, long *comparisons) {
    long c = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            c++;
            if (A[i] == A[j]) { *comparisons = c; return 1; }
        }
    }
    *comparisons = c;
    return 0;
}

/* (ii) Sort-then-scan O(n log n) duplicate check.
   Works on a COPY of the array so the original ordering (and
   the naive method's result) is unaffected. */
int has_duplicates_sorted(int *A, int n, long *comparisons) {
    int *B = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) B[i] = A[i];

    qsort_comparisons = 0;
    qsort(B, n, sizeof(int), cmp_int);

    long scan_c = 0;
    int found = 0;
    for (int i = 0; i + 1 < n; i++) {
        scan_c++;
        if (B[i] == B[i + 1]) { found = 1; break; }
    }

    *comparisons = qsort_comparisons + scan_c;
    free(B);
    return found;
}

/* Fisher-Yates shuffle -> produces a permutation with NO
   duplicates. Used for the worst-case benchmark: both methods
   must examine (essentially) everything, since no early exit
   on a match is possible. This gives a clean, monotonic
   comparison-count curve for plotting. */
void fill_unique_shuffled(int *A, int n) {
    for (int i = 0; i < n; i++) A[i] = i;
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = A[i]; A[i] = A[j]; A[j] = tmp;
    }
}

int main(void) {
    srand((unsigned) time(NULL));

    /* ---- Correctness check with a forced duplicate ---- */
    int sample[] = {5, 3, 8, 1, 9, 3, 7};
    int n_sample = sizeof(sample) / sizeof(sample[0]);
    long c1, c2;
    int d1s = has_duplicates_naive(sample, n_sample, &c1);
    int d2s = has_duplicates_sorted(sample, n_sample, &c2);
    printf("Sample array duplicates? naive=%s sorted=%s\n\n",
           d1s ? "yes" : "no", d2s ? "yes" : "no");

    /* ---- Worst-case benchmark (no duplicates, forces full scan) ---- */
    int n_values[] = {10, 50, 100, 500, 1000, 5000, 10000, 50000};
    int num_n = sizeof(n_values) / sizeof(n_values[0]);

    FILE *csv = fopen("uniqueness.csv", "w");
    if (!csv) { perror("fopen"); return 1; }
    fprintf(csv, "n,naive_comparisons,sorted_comparisons,duplicates_found\n");

    printf("%-8s %-20s %-20s %-10s\n", "n", "Naive comparisons", "Sorted comparisons", "Dup?");

    for (int i = 0; i < num_n; i++) {
        int n = n_values[i];
        int *A = malloc(n * sizeof(int));
        fill_unique_shuffled(A, n);   /* worst case: no duplicates exist */

        long naive_c, sorted_c;
        int d1 = has_duplicates_naive(A, n, &naive_c);
        int d2 = has_duplicates_sorted(A, n, &sorted_c);

        if (d1 != d2) printf("MISMATCH at n=%d!\n", n);

        printf("%-8d %-20ld %-20ld %-10s\n", n, naive_c, sorted_c, d1 ? "yes" : "no");
        fprintf(csv, "%d,%ld,%ld,%d\n", n, naive_c, sorted_c, d1);

        free(A);
    }

    fclose(csv);
    printf("\nCSV written to uniqueness.csv (use it to plot comparisons vs n).\n");
    printf("Conclusion: naive check is O(n^2); sort-then-scan is O(n log n).\n");
    printf("For sufficiently large n, sort-then-scan is dramatically faster.\n");
    return 0;
}
