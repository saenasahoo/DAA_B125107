/* ============================================================
   Design and Analysis of Algorithms - Lab 01, Question 1
   "Put them in Order": Empirically verify the increasing
   order of growth of the given 12 functions of n.

   Functions:
     f1  = n * log2(n)
     f2  = 12 * sqrt(n)
     f3  = 1 / n
     f4  = n ^ (log2 n)
     f5  = 100*n^2 + 6*n
     f6  = n ^ 0.51
     f7  = n^2 - 324
     f8  = 50 * n^0.5
     f9  = 2 * n^3
     f10 = 3^n
     f11 = 2^32 * n
     f12 = log2(n)

   Approach:
     For each n in a chosen range we compute every function's
     value, then sort the (name,value) pairs to see the
     empirical ranking. Because several functions blow up
     extremely fast (3^n, n^log2n, 2n^3), values are computed
     and compared using natural log (to avoid overflow) rather
     than the raw numbers themselves. The program prints both
     the raw value (where it still fits in a double) and the
     log-value used for ranking, and writes a CSV so results
     can be plotted (e.g. in Excel or Python/matplotlib).
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NUM_FUNCS 12

typedef struct {
    char name[32];
    double log_value;   /* natural log of the function's value, used for ranking   */
    double raw_value;   /* actual value (may be inf for huge n, that's fine)       */
} FuncVal;

/* log(3^n) = n*ln(3), log(n^log2n) = log2(n)*ln(n), etc.
   Using logs keeps everything numerically stable even for
   n in the thousands or more. */
void compute_log_values(double n, FuncVal vals[NUM_FUNCS]) {
    double ln_n = log(n);
    double log2_n = ln_n / log(2.0);

    strcpy(vals[0].name, "n*log2(n)");
    vals[0].raw_value = n * log2_n;
    vals[0].log_value = log(n) + log(log2_n);

    strcpy(vals[1].name, "12*sqrt(n)");
    vals[1].raw_value = 12.0 * sqrt(n);
    vals[1].log_value = log(12.0) + 0.5 * ln_n;

    strcpy(vals[2].name, "1/n");
    vals[2].raw_value = 1.0 / n;
    vals[2].log_value = -ln_n;

    strcpy(vals[3].name, "n^log2(n)");
    vals[3].raw_value = pow(n, log2_n);   /* will overflow to inf for larger n */
    vals[3].log_value = log2_n * ln_n;

    strcpy(vals[4].name, "100n^2+6n");
    vals[4].raw_value = 100.0 * n * n + 6.0 * n;
    vals[4].log_value = log(vals[4].raw_value);

    strcpy(vals[5].name, "n^0.51");
    vals[5].raw_value = pow(n, 0.51);
    vals[5].log_value = 0.51 * ln_n;

    strcpy(vals[6].name, "n^2-324");
    vals[6].raw_value = n * n - 324.0;
    vals[6].log_value = log(fabs(vals[6].raw_value) < 1e-9 ? 1e-9 : vals[6].raw_value);

    strcpy(vals[7].name, "50*n^0.5");
    vals[7].raw_value = 50.0 * sqrt(n);
    vals[7].log_value = log(50.0) + 0.5 * ln_n;

    strcpy(vals[8].name, "2n^3");
    vals[8].raw_value = 2.0 * n * n * n;
    vals[8].log_value = log(2.0) + 3.0 * ln_n;

    strcpy(vals[9].name, "3^n");
    vals[9].raw_value = pow(3.0, n);      /* overflows fast, that's expected */
    vals[9].log_value = n * log(3.0);

    strcpy(vals[10].name, "2^32*n");
    vals[10].raw_value = pow(2.0, 32) * n;
    vals[10].log_value = 32.0 * log(2.0) + ln_n;

    strcpy(vals[11].name, "log2(n)");
    vals[11].raw_value = log2_n;
    vals[11].log_value = log(log2_n);
}

int cmp_by_log(const void *a, const void *b) {
    double diff = ((FuncVal *)a)->log_value - ((FuncVal *)b)->log_value;
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}

int main(void) {
    /* n values chosen to show both small-n behaviour and the
       large-n asymptotic behaviour the question asks about */
    double n_values[] = {5, 10, 20, 50, 100, 500, 1000, 5000, 10000, 50000};
    int num_n = sizeof(n_values) / sizeof(n_values[0]);

    FILE *csv = fopen("growth_functions.csv", "w");
    if (!csv) { perror("fopen"); return 1; }
    fprintf(csv, "n,rank,function,log_value,raw_value\n");

    for (int i = 0; i < num_n; i++) {
        double n = n_values[i];
        FuncVal vals[NUM_FUNCS];
        compute_log_values(n, vals);
        qsort(vals, NUM_FUNCS, sizeof(FuncVal), cmp_by_log);

        printf("\n================ n = %.0f ================\n", n);
        printf("%-4s %-14s %-14s %-16s\n", "Rank", "Function", "ln(value)", "value");
        for (int r = 0; r < NUM_FUNCS; r++) {
            printf("%-4d %-14s %-14.4f %-16.6g\n",
                   r + 1, vals[r].name, vals[r].log_value, vals[r].raw_value);
            fprintf(csv, "%.0f,%d,%s,%.6f,%.6g\n",
                    n, r + 1, vals[r].name, vals[r].log_value, vals[r].raw_value);
        }
    }

    fclose(csv);
    printf("\nCSV written to growth_functions.csv (use it to plot growth curves).\n");
    return 0;
}
