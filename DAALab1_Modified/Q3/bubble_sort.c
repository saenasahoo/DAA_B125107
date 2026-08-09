/* ============================================================
   Design and Analysis of Algorithms - Lab 01, Question 3
   "Performance analysis of bubble sort"

   Two versions on randomised data of size n:
     (i)  Bubble sort that STOPS EARLY if the array becomes
          sorted before the (n-1)th pass (uses a 'swapped' flag).
     (ii) Bubble sort that ALWAYS completes all (n-1) passes,
          regardless of whether the array is already sorted.

   Both versions count the number of comparisons performed.
   The program sweeps n over a range, averages comparison
   counts over several random trials per n, and writes a CSV
   for plotting.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRIALS_PER_N 10   /* average over this many random arrays per n */

/* Fill arr[0..n-1] with a random permutation-like sequence */
void fill_random(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % (n * 10);
}

/* (i) Early-terminating bubble sort. Returns comparison count. */
long bubble_sort_early(int *arr, int n) {
    long comparisons = 0;
    int swapped;
    for (int pass = 0; pass < n - 1; pass++) {
        swapped = 0;
        for (int j = 0; j < n - 1 - pass; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;   /* array is already sorted, stop early */
    }
    return comparisons;
}

/* (ii) Always-complete bubble sort: ignores whether the array is
   already sorted and always runs all (n-1) passes. Returns
   comparison count. */
long bubble_sort_full(int *arr, int n) {
    long comparisons = 0;
    for (int pass = 0; pass < n - 1; pass++) {
        for (int j = 0; j < n - 1 - pass; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp;
            }
        }
        /* no early exit, even if already sorted */
    }
    return comparisons;
}

int main(void) {
    srand((unsigned) time(NULL));

    int n_values[] = {50, 100, 200, 400, 600, 800, 1000, 1500, 2000, 3000};
    int num_n = sizeof(n_values) / sizeof(n_values[0]);

    FILE *csv = fopen("bubble_sort.csv", "w");
    if (!csv) { perror("fopen"); return 1; }
    fprintf(csv, "n,avg_comparisons_early,avg_comparisons_full\n");

    printf("%-8s %-22s %-22s\n", "n", "Avg Comparisons (early)", "Avg Comparisons (full)");

    for (int i = 0; i < num_n; i++) {
        int n = n_values[i];
        long total_early = 0, total_full = 0;

        for (int t = 0; t < TRIALS_PER_N; t++) {
            int *arr1 = malloc(n * sizeof(int));
            int *arr2 = malloc(n * sizeof(int));
            fill_random(arr1, n);
            for (int k = 0; k < n; k++) arr2[k] = arr1[k]; /* same data, both sorts */

            total_early += bubble_sort_early(arr1, n);
            total_full  += bubble_sort_full(arr2, n);

            free(arr1);
            free(arr2);
        }

        double avg_early = (double) total_early / TRIALS_PER_N;
        double avg_full  = (double) total_full  / TRIALS_PER_N;

        printf("%-8d %-22.1f %-22.1f\n", n, avg_early, avg_full);
        fprintf(csv, "%d,%.2f,%.2f\n", n, avg_early, avg_full);
    }

    fclose(csv);
    printf("\nCSV written to bubble_sort.csv (use it to plot comparisons vs n).\n");
    return 0;
}
