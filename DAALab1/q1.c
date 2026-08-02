#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    char name[32];
    double log_value;
} Func;

int cmp(const void *a, const void *b) {
    double d = ((Func *)a)->log_value - ((Func *)b)->log_value;
    return (d > 0) - (d < 0);
}

int main(void) {
    double n = 1e6;
    double ln_n = log(n);
    double ln2  = log(2.0);
    double log2_n = ln_n / ln2;

    Func f[12];
    int r = 0;

    strcpy(f[r].name, "1/n");                 f[r++].log_value = -ln_n;
    strcpy(f[r].name, "log2(n)");              f[r++].log_value = log(log2_n);
    strcpy(f[r].name, "12*sqrt(n)");           f[r++].log_value = log(12.0) + 0.5 * ln_n;
    strcpy(f[r].name, "50*n^0.5");             f[r++].log_value = log(50.0) + 0.5 * ln_n;
    strcpy(f[r].name, "n^0.51");               f[r++].log_value = 0.51 * ln_n;
    strcpy(f[r].name, "2^32 * n");             f[r++].log_value = 32 * ln2 + ln_n;
    strcpy(f[r].name, "n*log2(n)");            f[r++].log_value = ln_n + log(log2_n);
    strcpy(f[r].name, "n^2 - 324");            f[r++].log_value = 2 * ln_n;
    strcpy(f[r].name, "100n^2 + 6n");          f[r++].log_value = log(100.0) + 2 * ln_n;
    strcpy(f[r].name, "2n^3");                 f[r++].log_value = log(2.0) + 3 * ln_n;
    strcpy(f[r].name, "n^log2(n)");            f[r++].log_value = log2_n * ln_n;
    strcpy(f[r].name, "3^n");                  f[r++].log_value = n * log(3.0);

    qsort(f, r, sizeof(Func), cmp);

    printf("Increasing order of growth (evaluated near n = %.0f):\n", n);
    for (int i = 0; i < r; i++)
        printf("%2d. %s\n", i + 1, f[i].name);

    printf("\nNote: n^0.51 and n^0.5-type terms (12*sqrt(n), 50*n^0.5) belong to\n"
           "different growth classes (n^0.5 vs n^0.51). n^0.51 eventually overtakes\n"
           "them, but because the exponents are so close, the crossover point is an\n"
           "astronomically large n, so for any n a computer can actually evaluate,\n"
           "the sqrt(n) terms still appear larger numerically.\n");

    return 0;
}