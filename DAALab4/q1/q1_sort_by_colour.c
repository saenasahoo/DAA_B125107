/*
 * Application of sorting - I
 * -----------------------------------------------------------------
 * Input : n pairs (number, colour) already sorted by "number".
 *         colour in {RED, BLUE, YELLOW}
 * Output: the pairs re-ordered so that all REDs come before all
 *         BLUEs before all YELLOWs, and within a colour the numbers
 *         stay in the same (sorted) relative order.
 *
 * Idea (O(n)):
 *   Since the input is already sorted by number, we only need a
 *   STABLE bucket separation by colour.  We make one pass over the
 *   array and copy each item into one of 3 buckets (RED / BLUE /
 *   YELLOW) in the order we meet them.  Because we scan left to
 *   right and only append, every bucket individually stays sorted
 *   by number.  Finally we concatenate RED + BLUE + YELLOW.
 *   This is exactly a 3-colour counting/bucket sort -> O(n) time,
 *   O(n) extra space.
 * -----------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>

typedef enum { RED = 0, BLUE = 1, YELLOW = 2 } Colour;

typedef struct {
    int number;
    Colour colour;
} Item;

const char *colourName(Colour c) {
    switch (c) {
        case RED: return "RED";
        case BLUE: return "BLUE";
        case YELLOW: return "YELLOW";
    }
    return "?";
}

/* O(n) stable colour sort, using the fact the input is number-sorted */
void sortByColour(Item arr[], int n, Item out[]) {
    Item *bucket[3];
    int count[3] = {0, 0, 0};

    for (int i = 0; i < 3; i++) bucket[i] = (Item *)malloc(n * sizeof(Item));

    /* single pass: O(n) */
    for (int i = 0; i < n; i++) {
        Colour c = arr[i].colour;
        bucket[c][count[c]++] = arr[i];
    }

    /* concatenate RED, BLUE, YELLOW: O(n) */
    int idx = 0;
    for (int c = 0; c < 3; c++)
        for (int j = 0; j < count[c]; j++)
            out[idx++] = bucket[c][j];

    for (int i = 0; i < 3; i++) free(bucket[i]);
}

void printItems(const char *label, Item arr[], int n) {
    printf("%s:\n", label);
    for (int i = 0; i < n; i++)
        printf("  (%d, %s)\n", arr[i].number, colourName(arr[i].colour));
}

int main(void) {
    /* Example input, already sorted by number */
    Item arr[] = {
        {1, BLUE}, {2, RED}, {3, YELLOW}, {5, RED},
        {7, BLUE}, {9, YELLOW}, {10, BLUE}, {12, RED}
    };
    int n = sizeof(arr) / sizeof(arr[0]);

    Item *out = (Item *)malloc(n * sizeof(Item));

    printItems("Input (sorted by number)", arr, n);
    sortByColour(arr, n, out);
    printItems("Output (grouped by colour, numbers stay sorted within colour)", out, n);

    free(out);
    return 0;
}
