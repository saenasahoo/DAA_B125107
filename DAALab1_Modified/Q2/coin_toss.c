/* ============================================================
   Design and Analysis of Algorithms - Lab 01, Question 2
   "Fair vs Biased Coin"

   Simulates tossing a coin N times and estimates P(HEAD).
   - A FAIR coin (p = 0.5) should converge to ~0.5 as N grows.
   - A BIASED coin (p != 0.5, set below) should converge to its
     true bias instead.

   The program sweeps N over several magnitudes to show
   convergence, printing a table and writing a CSV for plotting.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FAIR_P    0.5   /* true probability of HEAD for the fair coin   */
#define BIASED_P  0.7   /* true probability of HEAD for the biased coin */

/* Simulate n tosses of a coin with true head-probability p.
   Returns the number of heads observed. */
long simulate_tosses(long n, double p) {
    long heads = 0;
    for (long i = 0; i < n; i++) {
        double r = rand() / (RAND_MAX + 1.0);   /* uniform in [0,1) */
        if (r < p) heads++;
    }
    return heads;
}

int main(void) {
    srand((unsigned) time(NULL));

    long n_values[] = {10, 100, 1000, 10000, 100000, 1000000};
    int num_n = sizeof(n_values) / sizeof(n_values[0]);

    FILE *csv = fopen("coin_toss.csv", "w");
    if (!csv) { perror("fopen"); return 1; }
    fprintf(csv, "n,fair_heads,fair_prob,biased_heads,biased_prob\n");

    printf("%-10s %-14s %-14s %-14s %-14s\n",
           "N", "Fair Heads", "Fair P(H)", "Biased Heads", "Biased P(H)");

    for (int i = 0; i < num_n; i++) {
        long n = n_values[i];

        long fair_heads = simulate_tosses(n, FAIR_P);
        double fair_prob = (double) fair_heads / n;

        long biased_heads = simulate_tosses(n, BIASED_P);
        double biased_prob = (double) biased_heads / n;

        printf("%-10ld %-14ld %-14.4f %-14ld %-14.4f\n",
               n, fair_heads, fair_prob, biased_heads, biased_prob);

        fprintf(csv, "%ld,%ld,%.6f,%ld,%.6f\n",
                n, fair_heads, fair_prob, biased_heads, biased_prob);
    }

    fclose(csv);
    printf("\nTrue fair probability   = %.2f\n", FAIR_P);
    printf("True biased probability = %.2f\n", BIASED_P);
    printf("CSV written to coin_toss.csv (use it to plot convergence).\n");

    return 0;
}
