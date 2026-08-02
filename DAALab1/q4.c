
#include <stdio.h>

long move_count = 0;


void hanoi(int n, char from, char to, char via, int print_moves) {
    if (n == 0) return;
    hanoi(n - 1, from, via, to, print_moves);
    move_count++;
    if (print_moves)
        printf("Move disc %d from %c to %c\n", n, from, to);
    hanoi(n - 1, via, to, from, print_moves);
}

int main(void) {
    int MAX_DISCS = 20;

    
    printf("Solution trace for n = 3 discs:\n");
    move_count = 0;
    hanoi(3, 'A', 'C', 'B', 1);
    printf("Total moves for n=3: %ld\n\n", move_count);

    
    printf("n,moves,formula_2^n_minus_1\n");
    for (int n = 1; n <= MAX_DISCS; n++) {
        move_count = 0;
        hanoi(n, 'A', 'C', 'B', 0);
        long formula = (1L << n) - 1; 
        printf("%d,%ld,%ld\n", n, move_count, formula);
    }

    fprintf(stderr,
        "\nConclusion: the number of moves is always exactly 2^n - 1, which\n"
        "matches the recurrence T(n) = 2*T(n-1) + 1, T(0) = 0. This grows\n"
        "EXPONENTIALLY with n, so the algorithm has time complexity Theta(2^n)\n"
        "-- it becomes impractical very quickly as n increases (e.g. n=64\n"
        "would require over 1.8*10^19 moves).\n");

    return 0;
}