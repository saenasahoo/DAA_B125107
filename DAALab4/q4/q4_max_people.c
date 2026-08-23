/*
 * Application of sorting - IV
 * -----------------------------------------------------------------
 * Input : n persons, person i has entry time a_i and exit time b_i
 *         (b_i > a_i), all 2n times are distinct.
 * Output: the time at which the maximum number of people were
 *         simultaneously present, and that maximum count.
 *
 * Algorithm (O(n log n)) -- classic sweep line:
 *   1. Build 2n events: (a_i, +1)  "someone enters"
 *                        (b_i, -1) "someone leaves"
 *   2. Sort all 2n events by time.                    O(n log n)
 *   3. Sweep left to right, keeping a running count;
 *      an ENTRY increases the count *before* we record it,
 *      an EXIT decreases the count. Track the time at which
 *      the running count is maximal.                   O(n)
 *   Total: O(n log n)
 * -----------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;
    int delta; /* +1 for entry, -1 for exit */
} Event;

int cmpEvent(const void *a, const void *b) {
    return ((Event *)a)->time - ((Event *)b)->time;
}

/* returns the maximum simultaneous count and sets *bestTime */
int maxSimultaneous(int a[], int b[], int n, int *bestTime) {
    Event *events = (Event *)malloc(2 * n * sizeof(Event));
    for (int i = 0; i < n; i++) {
        events[2 * i]     = (Event){a[i], +1};
        events[2 * i + 1] = (Event){b[i], -1};
    }

    qsort(events, 2 * n, sizeof(Event), cmpEvent);   /* O(n log n) */

    int count = 0, best = 0;
    *bestTime = events[0].time;
    for (int i = 0; i < 2 * n; i++) {                /* O(n) */
        count += events[i].delta;
        if (count > best) {
            best = count;
            *bestTime = events[i].time;
        }
    }

    free(events);
    return best;
}

int main(void) {
    /* person i: entry a[i], exit b[i] */
    int a[] = {1, 2, 10, 4, 15};
    int b[] = {8, 6, 20, 12, 18};
    int n = sizeof(a) / sizeof(a[0]);

    int bestTime;
    int best = maxSimultaneous(a, b, n, &bestTime);

    printf("Maximum number of people present simultaneously: %d\n", best);
    printf("This maximum first occurs at time: %d\n", bestTime);

    return 0;
}
