/*
 * Application of sorting - VI
 * -----------------------------------------------------------------
 * Input : set S of n intervals [l_i, r_i] on a line (endpoints are
 *         INCLUDED in the interval).
 * Output: a point p that lies in the largest number of intervals,
 *         and that count.
 *
 * Algorithm (O(n log n)) -- sweep line:
 *   1. Build 2n events: (l_i, START) and (r_i, END).
 *   2. Sort events by coordinate; if two events share the same
 *      coordinate, process all STARTs before ENDs. This is what
 *      makes shared endpoints count as "inside" both intervals
 *      (since endpoints are inclusive).                 O(n log n)
 *   3. Sweep: a START increases the running count, an END
 *      decreases it. After applying a START, check if the running
 *      count is a new maximum; if so remember this coordinate as
 *      the candidate point p.                            O(n)
 *   Total: O(n log n)
 *
 * Example from the handout:
 *   S = {(10,40),(20,60),(50,90),(15,70)}
 *   No point lies in all four, but p = 50 lies in three intervals
 *   ((20,60), (50,90), (15,70)).
 * -----------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>

typedef enum { START = 0, END = 1 } EventType; /* START must sort before END on ties */

typedef struct {
    int coord;
    EventType type;
} Event;

int cmpEvent(const void *a, const void *b) {
    Event *e1 = (Event *)a, *e2 = (Event *)b;
    if (e1->coord != e2->coord) return e1->coord - e2->coord;
    return e1->type - e2->type; /* START(0) before END(1) at same coordinate */
}

/* returns the max coverage count, sets *bestPoint to a point achieving it */
int maxPointCoverage(int l[], int r[], int n, int *bestPoint) {
    Event *events = (Event *)malloc(2 * n * sizeof(Event));
    for (int i = 0; i < n; i++) {
        events[2 * i]     = (Event){l[i], START};
        events[2 * i + 1] = (Event){r[i], END};
    }

    qsort(events, 2 * n, sizeof(Event), cmpEvent);  /* O(n log n) */

    int count = 0, best = 0;
    *bestPoint = events[0].coord;
    for (int i = 0; i < 2 * n; i++) {                /* O(n) */
        if (events[i].type == START) {
            count++;
            if (count > best) {
                best = count;
                *bestPoint = events[i].coord;
            }
        } else {
            count--;
        }
    }

    free(events);
    return best;
}

int main(void) {
    int l[] = {10, 20, 50, 15};
    int r[] = {40, 60, 90, 70};
    int n = sizeof(l) / sizeof(l[0]);

    int bestPoint;
    int best = maxPointCoverage(l, r, n, &bestPoint);

    printf("Maximum number of intervals covering a single point: %d\n", best);
    printf("An example such point: p = %d\n", bestPoint);

    return 0;
}
