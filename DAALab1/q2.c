#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double simulate_coin(int tosses, double p) {
    int heads = 0;
    for (int i = 0; i < tosses; i++) {
        double r = (double) rand() / ((double) RAND_MAX + 1.0);
        if (r < p) heads++;
    }
    return (double) heads / tosses;
}

int main(void) {
    srand((unsigned) time(NULL));

    int trial_sizes[] = {100, 1000, 10000, 100000, 1000000};
    int num_trials = sizeof(trial_sizes) / sizeof(trial_sizes[0]);

    printf("=== Fair coin (p = 0.5) ===\n");
    printf("%-12s %-15s\n", "Tosses", "P(HEAD) estimate");
    for (int i = 0; i < num_trials; i++) {
        double phat = simulate_coin(trial_sizes[i], 0.5);
        printf("%-12d %-15.5f\n", trial_sizes[i], phat);
    }
    printf("As the number of tosses grows, P(HEAD) converges to 0.5,\n"
           "illustrating the Law of Large Numbers.\n\n");

    printf("=== Fair vs Biased coin comparison (1,000,000 tosses each) ===\n");
    double biased_ps[] = {0.5, 0.3, 0.7, 0.9};
    int num_p = sizeof(biased_ps) / sizeof(biased_ps[0]);
    printf("%-15s %-15s %-15s\n", "True p", "Estimated P(HEAD)", "Type");
    for (int i = 0; i < num_p; i++) {
        double phat = simulate_coin(1000000, biased_ps[i]);
        const char *type = (biased_ps[i] == 0.5) ? "Fair" : "Biased";
        printf("%-15.2f %-15.5f %-15s\n", biased_ps[i], phat, type);
    }

    return 0;
}