
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Version (i): terminates early if array becomes sorted */
long bubble_sort_early_exit(int arr[], int n) {
    long comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
                swapped = 1;
            }
        }
        if (!swapped) break; 
    }
    return comparisons;
}


long bubble_sort_full(int arr[], int n) {
    long comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
        }
    }
    return comparisons;
}

void fill_random(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % (n * 10);
}

int main(void) {
    srand((unsigned) time(NULL));

    int sizes[] = {100, 200, 400, 800, 1600, 3200, 6400};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("n,comparisons_early_exit,comparisons_full\n");
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int *a1 = malloc(n * sizeof(int));
        int *a2 = malloc(n * sizeof(int));
        fill_random(a1, n);
        for (int i = 0; i < n; i++) a2[i] = a1[i]; 

        long c1 = bubble_sort_early_exit(a1, n);
        long c2 = bubble_sort_full(a2, n);

        printf("%d,%ld,%ld\n", n, c1, c2);

        free(a1);
        free(a2);
    }

    fprintf(stderr,
        "\nObservation: version (ii) always does exactly n(n-1)/2 comparisons\n"
        "(worst-case Theta(n^2)), regardless of input order. Version (i) does\n"
        "the same in the worst case (reverse-sorted input) but can finish much\n"
        "earlier -- best case Theta(n) -- if the array happens to be sorted or\n"
        "nearly sorted early on. Copy the CSV output above into a spreadsheet\n"
        "or plotting tool (n on x-axis, comparisons on y-axis) to visualise\n"
        "this difference.\n");

    return 0;
}