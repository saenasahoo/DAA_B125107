/* ============================================================
   Design and Analysis of Algorithms - Lab 02, Q2
   Merge Sort (standard, 2-way) vs Modified Merge Sort (3-way,
   divide into thirds) - empirical validation of running time.

   Theory:
     Standard merge sort:  T(n) = 2T(n/2) + O(n) = Theta(n log n)
     Modified merge sort:  T(n) = 3T(n/3) + O(n) = Theta(n log n)
   Both are Theta(n log n); only the constant factor differs.

   Output: merge_results.csv (algorithm,n,time_us,comparisons)
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(_WIN32)
    #include <windows.h>
    static double now_us(void) {
        static LARGE_INTEGER freq; static int init = 0;
        LARGE_INTEGER counter;
        if (!init) { QueryPerformanceFrequency(&freq); init = 1; }
        QueryPerformanceCounter(&counter);
        return (double)counter.QuadPart * 1e6 / (double)freq.QuadPart;
    }
#else
    static double now_us(void) {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return ts.tv_sec * 1e6 + ts.tv_nsec / 1e3;
    }
#endif

static long comparisons; /* global counter, reset before each sort */

/* ============================================================
   STANDARD MERGE SORT (2-way, divide into halves)
   ============================================================ */
static void merge2(int *a, int lo, int mid, int hi, int *tmp) {
    int i = lo, j = mid, k = lo;
    while (i < mid && j < hi) {
        comparisons++;
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else tmp[k++] = a[j++];
    }
    while (i < mid) tmp[k++] = a[i++];
    while (j < hi)  tmp[k++] = a[j++];
    for (int t = lo; t < hi; t++) a[t] = tmp[t];
}

static void mergeSort2(int *a, int lo, int hi, int *tmp) {
    if (hi - lo <= 1) return;
    int mid = lo + (hi - lo) / 2;
    mergeSort2(a, lo, mid, tmp);
    mergeSort2(a, mid, hi, tmp);
    merge2(a, lo, mid, hi, tmp);
}

/* ============================================================
   MODIFIED MERGE SORT (3-way, divide into thirds)
   ============================================================ */
static void merge3(int *a, int lo, int m1, int m2, int hi, int *tmp) {
    int i = lo, j = m1, k = m2, t = lo;
    while (i < m1 && j < m2 && k < hi) {
        comparisons += 2; /* two comparisons to find min of three */
        if (a[i] <= a[j] && a[i] <= a[k])       tmp[t++] = a[i++];
        else if (a[j] <= a[i] && a[j] <= a[k])  tmp[t++] = a[j++];
        else                                    tmp[t++] = a[k++];
    }
    /* at most one sub-range remains active; finish with 2-way merges */
    while (i < m1 && j < m2) { comparisons++; if (a[i] <= a[j]) tmp[t++] = a[i++]; else tmp[t++] = a[j++]; }
    while (j < m2 && k < hi) { comparisons++; if (a[j] <= a[k]) tmp[t++] = a[j++]; else tmp[t++] = a[k++]; }
    while (i < m1 && k < hi) { comparisons++; if (a[i] <= a[k]) tmp[t++] = a[i++]; else tmp[t++] = a[k++]; }
    while (i < m1) tmp[t++] = a[i++];
    while (j < m2) tmp[t++] = a[j++];
    while (k < hi) tmp[t++] = a[k++];
    for (int x = lo; x < hi; x++) a[x] = tmp[x];
}

static void mergeSort3(int *a, int lo, int hi, int *tmp) {
    int len = hi - lo;
    if (len <= 1) return;
    if (len == 2) { /* fall back to a simple 2-way split for tiny ranges */
        int mid = lo + 1;
        mergeSort3(a, lo, mid, tmp);
        mergeSort3(a, mid, hi, tmp);
        merge2(a, lo, mid, hi, tmp);
        return;
    }
    int third = len / 3;
    int m1 = lo + third;
    int m2 = lo + 2 * third;
    mergeSort3(a, lo, m1, tmp);
    mergeSort3(a, m1, m2, tmp);
    mergeSort3(a, m2, hi, tmp);
    merge3(a, lo, m1, m2, hi, tmp);
}

/* ============================================================
   Helpers
   ============================================================ */
static int* random_array(int n, unsigned seed) {
    int *a = malloc(sizeof(int) * n);
    srand(seed);
    for (int i = 0; i < n; i++) a[i] = rand();
    return a;
}

static int is_sorted(int *a, int n) {
    for (int i = 1; i < n; i++) if (a[i - 1] > a[i]) return 0;
    return 1;
}

int main(void) {
    FILE *out = fopen("merge_results.csv", "w");
    fprintf(out, "algorithm,n,time_us,comparisons\n");

    int sizes[] = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000};
    int ns = sizeof(sizes) / sizeof(sizes[0]);
    int trials = 5;

    for (int s = 0; s < ns; s++) {
        int n = sizes[s];

        /* ---- standard merge sort ---- */
        double total_time = 0; long total_cmp = 0;
        for (int t = 0; t < trials; t++) {
            int *a = random_array(n, 1000 + t);
            int *tmp = malloc(sizeof(int) * n);
            comparisons = 0;
            double t0 = now_us();
            mergeSort2(a, 0, n, tmp);
            double t1 = now_us();
            if (!is_sorted(a, n)) fprintf(stderr, "ERROR: mergeSort2 failed to sort n=%d\n", n);
            total_time += (t1 - t0);
            total_cmp += comparisons;
            free(a); free(tmp);
        }
        fprintf(out, "MergeSort2way,%d,%.4f,%ld\n", n, total_time / trials, total_cmp / trials);

        /* ---- modified merge sort (3-way) ---- */
        total_time = 0; total_cmp = 0;
        for (int t = 0; t < trials; t++) {
            int *a = random_array(n, 2000 + t);
            int *tmp = malloc(sizeof(int) * n);
            comparisons = 0;
            double t0 = now_us();
            mergeSort3(a, 0, n, tmp);
            double t1 = now_us();
            if (!is_sorted(a, n)) fprintf(stderr, "ERROR: mergeSort3 failed to sort n=%d\n", n);
            total_time += (t1 - t0);
            total_cmp += comparisons;
            free(a); free(tmp);
        }
        fprintf(out, "MergeSort3way,%d,%.4f,%ld\n", n, total_time / trials, total_cmp / trials);

        fprintf(stderr, "done n=%d\n", n);
    }

    fclose(out);
    printf("Wrote merge_results.csv\n");
    return 0;
}
