/* ============================================================
   Design and Analysis of Algorithms - Lab 01, Question 5
   "Find the partition point"

   Array A has n elements: a run of 0's followed by a run of
   1's (e.g. 0 0 0 0 1 1 1 1 1). Find the exact index of the
   first 1 (the transition point). If there is no 1, return n
   (meaning "all zeros"); if the array is all 1's, return 0.

   Two methods implemented and compared:
     (i)  Linear scan   - O(n)
     (ii) Binary search  - O(log n)   <-- the efficient method,
          since the array is sorted-like (0's then 1's), we can
          binary search on the predicate "is A[mid] == 1?"

   The program verifies both methods agree, then benchmarks
   comparison counts across growing n and writes a CSV.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* (i) Linear scan: first index where A[i] == 1 */
int find_partition_linear(int *A, int n, long *comparisons) {
    long c = 0;
    for (int i = 0; i < n; i++) {
        c++;
        if (A[i] == 1) { *comparisons = c; return i; }
    }
    *comparisons = c;
    return n;   /* no 1 found -> all zeros */
}

/* (ii) Binary search: find first index where A[i] == 1.
   Invariant: A[lo-1] == 0 (or lo == 0), A[hi] == 1 (or hi == n) */
int find_partition_binary(int *A, int n, long *comparisons) {
    int lo = 0, hi = n;   /* search space [lo, hi) */
    long c = 0;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        c++;
        if (A[mid] == 1) {
            hi = mid;       /* first 1 is at mid or earlier */
        } else {
            lo = mid + 1;   /* first 1 is after mid */
        }
    }
    *comparisons = c;
    return lo;   /* index of first 1, or n if all zeros */
}

/* Build an array of n elements: k zeros followed by (n-k) ones */
void build_array(int *A, int n, int k) {
    for (int i = 0; i < n; i++) A[i] = (i < k) ? 0 : 1;
}

int main(void) {
    srand((unsigned) time(NULL));

    /* ---- Correctness check on a small example ---- */
    int sample[] = {0, 0, 0, 0, 1, 1, 1, 1, 1};
    int n_sample = sizeof(sample) / sizeof(sample[0]);
    long c1, c2;
    int p1 = find_partition_linear(sample, n_sample, &c1);
    int p2 = find_partition_binary(sample, n_sample, &c2);
    printf("Sample array partition point (linear) = %d (comparisons=%ld)\n", p1, c1);
    printf("Sample array partition point (binary) = %d (comparisons=%ld)\n\n", p2, c2);

    /* ---- Benchmark across growing n ---- */
    int n_values[] = {100, 1000, 10000, 100000, 1000000, 10000000};
    int num_n = sizeof(n_values) / sizeof(n_values[0]);

    FILE *csv = fopen("partition_point.csv", "w");
    if (!csv) { perror("fopen"); return 1; }
    fprintf(csv, "n,linear_comparisons,binary_comparisons\n");

    printf("%-10s %-20s %-20s\n", "n", "Linear comparisons", "Binary comparisons");

    for (int i = 0; i < num_n; i++) {
        int n = n_values[i];
        int k = n / 2 + (rand() % (n / 4 + 1)) - (n / 8); /* random-ish split point */
        if (k < 0) k = 0;
        if (k > n) k = n;

        int *A = malloc(n * sizeof(int));
        build_array(A, n, k);

        long lin_c, bin_c;
        int p_lin = find_partition_linear(A, n, &lin_c);
        int p_bin = find_partition_binary(A, n, &bin_c);

        if (p_lin != p_bin) {
            printf("MISMATCH at n=%d! linear=%d binary=%d\n", n, p_lin, p_bin);
        }

        printf("%-10d %-20ld %-20ld\n", n, lin_c, bin_c);
        fprintf(csv, "%d,%ld,%ld\n", n, lin_c, bin_c);

        free(A);
    }

    fclose(csv);
    printf("\nCSV written to partition_point.csv (use it to plot comparisons vs n).\n");
    printf("Conclusion: linear scan is O(n); binary search is O(log n).\n");
    return 0;
}
