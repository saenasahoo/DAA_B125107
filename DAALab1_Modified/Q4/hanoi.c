/* ============================================================
   Design and Analysis of Algorithms - Lab 01, Question 4
   "Towers of Hanoi (ToH)"

   Simulates the recursive solution to Towers of Hanoi for
   n = 1..N_MAX discs, counting the total number of moves used.
   Writes a CSV (n, moves, log2(moves+1)) for plotting.

   Known closed form: moves(n) = 2^n - 1, so growth is
   exponential in n. Plotting log2(moves+1) vs n should give a
   straight line with slope 1, confirming this.
   ============================================================ */

#include <stdio.h>
#include <math.h>

#define N_MAX 20   /* 2^20 - 1 ~ a million moves; keeps runtime reasonable */

long move_count;   /* global counter, reset before each simulation */

/* Recursively solve ToH for n discs, moving from rod `from` to
   rod `to`, using rod `aux` as auxiliary. Each disc move
   increments move_count. (Moves aren't printed here to avoid
   flooding output for large n -- uncomment the printf to see
   the actual move sequence for small n.) */
void hanoi(int n, char from, char to, char aux) {
    if (n == 0) return;
    hanoi(n - 1, from, aux, to);
    move_count++;
    /* printf("Move disc %d from %c to %c\n", n, from, to); */
    hanoi(n - 1, aux, to, from);
}

int main(void) {
    FILE *csv = fopen("hanoi.csv", "w");
    if (!csv) { perror("fopen"); return 1; }
    fprintf(csv, "n,moves,log2_moves_plus1\n");

    printf("%-6s %-14s %-10s\n", "n", "Moves", "2^n - 1");

    for (int n = 1; n <= N_MAX; n++) {
        move_count = 0;
        hanoi(n, 'A', 'C', 'B');

        long expected = 1;
        for (int i = 0; i < n; i++) expected *= 2;
        expected -= 1;

        double log2_moves_plus1 = log2((double) move_count + 1.0);

        printf("%-6d %-14ld %-10ld\n", n, move_count, expected);
        fprintf(csv, "%d,%ld,%.6f\n", n, move_count, log2_moves_plus1);
    }

    fclose(csv);
    printf("\nCSV written to hanoi.csv (columns: n, moves, log2(moves+1)).\n");
    printf("Conclusion: moves(n) = 2^n - 1, i.e. EXPONENTIAL growth in n.\n");
    return 0;
}
