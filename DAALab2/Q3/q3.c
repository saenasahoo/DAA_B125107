/* ============================================================
   Design and Analysis of Algorithms - Lab 02, Q3
   Merging k sorted arrays, each of size n.

   Method 1: merge sequentially - merge arr[0],arr[1] -> R,
             then merge R with arr[2], then with arr[3], ...
             Worst-case time: O(k^2 * n)

   Method 2: pairwise ("tournament") merge - merge k arrays into
             k/2 arrays of size 2n, then k/4 arrays of size 4n,
             etc., until one array of size k*n remains.
             Worst-case time: O(k*n*log k)

   Output: kmerge_results.csv (method,n,k,time_us)
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

/* merge two sorted arrays a[0..na) and b[0..nb) into freshly malloc'd result */
static int* merge2(int *a, int na, int *b, int nb) {
    int *r = malloc(sizeof(int) * (na + nb));
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) r[k++] = (a[i] <= b[j]) ? a[i++] : b[j++];
    while (i < na) r[k++] = a[i++];
    while (j < nb) r[k++] = b[j++];
    return r;
}

static int cmp_int(const void *x, const void *y) { return (*(int*)x - *(int*)y); }

/* build k sorted arrays, each of length n */
static int** build_arrays(int k, int n, unsigned seed) {
    int **arrs = malloc(sizeof(int*) * k);
    srand(seed);
    for (int i = 0; i < k; i++) {
        arrs[i] = malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) arrs[i][j] = rand();
        qsort(arrs[i], n, sizeof(int), cmp_int);
    }
    return arrs;
}

static void free_arrays(int **arrs, int k) {
    for (int i = 0; i < k; i++) free(arrs[i]);
    free(arrs);
}

static int is_sorted(int *a, int n) {
    for (int i = 1; i < n; i++) if (a[i-1] > a[i]) return 0;
    return 1;
}

/* ---------------- Method 1: sequential merge ---------------- */
static double method1(int **arrs, int k, int n, int total_expected) {
    double t0 = now_us();
    int *result = malloc(sizeof(int) * n);
    memcpy(result, arrs[0], sizeof(int) * n);
    int cur_len = n;
    for (int i = 1; i < k; i++) {
        int *merged = merge2(result, cur_len, arrs[i], n);
        free(result);
        result = merged;
        cur_len += n;
    }
    double t1 = now_us();
    if (cur_len != total_expected || !is_sorted(result, cur_len))
        fprintf(stderr, "ERROR method1: bad result k=%d n=%d\n", k, n);
    free(result);
    return t1 - t0;
}

/* ---------------- Method 2: pairwise tournament merge ---------------- */
static double method2(int **arrs, int k, int n, int total_expected) {
    double t0 = now_us();

    int cur_count = k;
    int *cur_lens = malloc(sizeof(int) * k);
    int **cur = malloc(sizeof(int*) * k);
    for (int i = 0; i < k; i++) { cur[i] = malloc(sizeof(int) * n); memcpy(cur[i], arrs[i], sizeof(int) * n); cur_lens[i] = n; }

    while (cur_count > 1) {
        int next_count = (cur_count + 1) / 2;
        int **next = malloc(sizeof(int*) * next_count);
        int *next_lens = malloc(sizeof(int) * next_count);
        int idx = 0;
        for (int i = 0; i + 1 < cur_count; i += 2) {
            next[idx] = merge2(cur[i], cur_lens[i], cur[i+1], cur_lens[i+1]);
            next_lens[idx] = cur_lens[i] + cur_lens[i+1];
            free(cur[i]); free(cur[i+1]);
            idx++;
        }
        if (cur_count % 2 == 1) { /* odd one out carries forward untouched */
            next[idx] = cur[cur_count - 1];
            next_lens[idx] = cur_lens[cur_count - 1];
            idx++;
        }
        free(cur); free(cur_lens);
        cur = next; cur_lens = next_lens; cur_count = next_count;
    }

    double t1 = now_us();
    if (cur_lens[0] != total_expected || !is_sorted(cur[0], cur_lens[0]))
        fprintf(stderr, "ERROR method2: bad result k=%d n=%d\n", k, n);
    free(cur[0]); free(cur); free(cur_lens);
    return t1 - t0;
}

int main(void) {
    FILE *out = fopen("kmerge_results.csv", "w");
    fprintf(out, "method,n,k,time_us\n");
    int trials = 5;

    /* Experiment A: fix n, vary k -> shows k^2*n vs k*n*log(k) */
    int n_fixed = 2000;
    int k_values[] = {2, 4, 8, 16, 32, 64, 128, 256};
    int nk = sizeof(k_values) / sizeof(k_values[0]);
    for (int idx = 0; idx < nk; idx++) {
        int k = k_values[idx];
        double t1_total = 0, t2_total = 0;
        for (int t = 0; t < trials; t++) {
            int **arrs = build_arrays(k, n_fixed, 1000 + t);
            t1_total += method1(arrs, k, n_fixed, k * n_fixed);
            t2_total += method2(arrs, k, n_fixed, k * n_fixed);
            free_arrays(arrs, k);
        }
        fprintf(out, "Method1_Sequential,%d,%d,%.4f\n", n_fixed, k, t1_total / trials);
        fprintf(out, "Method2_Pairwise,%d,%d,%.4f\n", n_fixed, k, t2_total / trials);
        fprintf(stderr, "varyK done k=%d\n", k);
    }

    /* Experiment B: fix k, vary n -> shows linear-in-n scaling for both */
    int k_fixed = 32;
    int n_values[] = {500, 1000, 2000, 4000, 8000, 16000, 32000, 64000};
    int nn = sizeof(n_values) / sizeof(n_values[0]);
    for (int idx = 0; idx < nn; idx++) {
        int n = n_values[idx];
        double t1_total = 0, t2_total = 0;
        for (int t = 0; t < trials; t++) {
            int **arrs = build_arrays(k_fixed, n, 2000 + t);
            t1_total += method1(arrs, k_fixed, n, k_fixed * n);
            t2_total += method2(arrs, k_fixed, n, k_fixed * n);
            free_arrays(arrs, k_fixed);
        }
        fprintf(out, "Method1_Sequential,%d,%d,%.4f\n", n, k_fixed, t1_total / trials);
        fprintf(out, "Method2_Pairwise,%d,%d,%.4f\n", n, k_fixed, t2_total / trials);
        fprintf(stderr, "varyN done n=%d\n", n);
    }

    fclose(out);
    printf("Wrote kmerge_results.csv\n");
    return 0;
}
